
# This file is part of the Coriolis Software.
# Copyright (c) Sorbonne Université 2019-2023, All Rights Reserved
#
# +-----------------------------------------------------------------+
# |                   C O R I O L I S                               |
# |      C u m u l u s  -  P y t h o n   T o o l s                  |
# |                                                                 |
# |  Author      :                    Jean-Paul CHAPUT              |
# |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
# | =============================================================== |
# |  Python      :       "./plugins/conductorplugin.py"             |
# +-----------------------------------------------------------------+


import sys
import traceback
import os.path
import math
try:
    from ..           import Cfg
    from ..Hurricane  import DbU, Breakpoint, UpdateSession
    from ..           import Viewer
    from ..CRL        import RoutingLayerGauge
    from ..helpers    import setTraceLevel, trace, l, u, n
    from ..helpers.io import ErrorMessage, catch
    from ..           import Anabatic, Etesian, Katana, Unicorn, plugins
except Exception as e:
    catch( e )
    sys.exit(2)


# --------------------------------------------------------------------
# Plugin hook functions, unicornHook:menus, ScritMain:call

def unicornHook ( **kw ):
    kw['beforeAction'] = 'placeAndRoute.conductor'

    plugins.kwAddMenu    ( 'placeAndRoute', 'P&&R', **kw )
    plugins.kwUnicornHook( 'misc.alpha.conductor'
                         , 'P&&R Conductor'
                         , 'Perform a placement driven by global routing, then detailed routing'
                         , sys.modules[__name__].__file__
                         , **kw
                         )
    return


def scriptMain ( **kw ):
    try:
       #setTraceLevel( 550 )
        errorCode = 0
      
        stopLevel = 1
        if Cfg.hasParameter('conductor.stopLevel'):
            stopLevel = Cfg.getParamInt('conductor.stopLevel').asInt()
        Breakpoint.setStopLevel( stopLevel )
      
        Cfg.Configuration.pushDefaultPriority( Cfg.Parameter.Priority.Interactive )
      
        grIterations = 10
        if Cfg.hasParameter('anabatic.globalIterations'):
            grIterations = Cfg.getParamInt('anabatic.globalIterations').asInt()
      
        grIterationsEstimate = 7
        if Cfg.hasParameter('anabatic.globalIterationsEstimate'):
            grIterationsEstimate = Cfg.getParamInt('anabatic.globalIterationsEstimate').asInt()
        Cfg.getParamInt('anabatic.globalIterations').setInt( grIterationsEstimate )
      
        maxPlaceIterations = 2
        if Cfg.hasParameter('conductor.maxPlaceIterations'):
            maxPlaceIterations = Cfg.getParamInt('conductor.maxPlaceIterations').asInt()
      
        useFixedAbHeight = False
        if Cfg.hasParameter('conductor.useFixedAbHeight'):
            useFixedAbHeight = Cfg.getParamBool('conductor.useFixedAbHeight').asBool()
      
        cell = None
        if ('cell' in kw) and kw['cell']:
            cell = kw['cell']
      
        editor = None
        if ('editor' in kw) and kw['editor']:
            editor = kw['editor']
            print( '  o  Editor found, running in graphic mode.' )
            editor.setLayerVisible( 'rubber', False )
            if cell == None: cell = editor.getCell()
      
        if cell == None:
            raise ErrorMessage( 3, 'Conductor: No cell loaded yet.' )
      
        success   = False
        etesian   = None
        katana    = None
        iteration = 0
      
        while iteration < maxPlaceIterations:
            print( '\n  o  P&R Conductor iteration: {} (max:{})'.format(iteration,maxPlaceIterations) )
            
            if not (katana is None):
                print( '  o  Global routing has failed, re-place design.' )
                katana.resetRouting()
                katana.destroy     ()
                katana = None
                if editor:
                    editor.setShowSelection( False )
        
            etesian = Etesian.EtesianEngine.create( cell )
            etesian.setPassNumber( iteration )
            if editor: etesian.setViewer( editor )
            if iteration:
                if useFixedAbHeight and iteration == 1:
                    etesian.setFixedAbHeight( cell.getAbutmentBox().getHeight() )
                    print( 'etesian.setFixedAbHeight(): {}'.format(
                        DbU.getValueString(cell.getAbutmentBox().getHeight())) )
                etesian.resetPlacement()
            etesian.place()
            etesian.destroy()
            etesian = None
            if editor:
                editor.refresh()
                editor.fit()
            
            if iteration+1 == maxPlaceIterations:
                Cfg.getParamInt('anabatic.globalIterations').setInt( grIterations )
            
            katana = Katana.KatanaEngine.create( cell )
            katana.setPassNumber( iteration )
            if editor: katana.setViewer( editor )
            katana.digitalInit    ()
            katana.runGlobalRouter( Katana.Flags.ShowBloatedInstances
                                  | Katana.Flags.ShowOverloadedEdges
                                  | Katana.Flags.ShowOverloadedGCells
                                  )
                                 #| Katana.Flags.ShowFailedNets 
            Breakpoint.stop( 1, 'After routing iteration %d' % iteration )
            if editor:
                editor.setShowSelection( False )
            
            if katana.isGlobalRoutingSuccess(): break
            iteration += 1
      
        if not (katana is None):
            katana.loadGlobalRouting( Anabatic.EngineLoadGrByNet )
            katana.layerAssign      ( Anabatic.EngineNoNetLayerAssign )
            katana.runNegociate     ( Katana.Flags.NoFlags )
            success = katana.isDetailedRoutingSuccess()
            
            Breakpoint.stop( 1, 'Before finalizing & destroying Katana.' )
            katana.finalizeLayout()
            katana.dumpMeasures()
            katana.destroy()
            katana = None
          
       #plugins.RSavePlugin.scriptMain( **kw )
      
        Cfg.Configuration.popDefaultPriority()
  
    except Exception as e:
        catch( e )
        
    return 0
