// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2008-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                  H U R R I C A N E                              |
// |     V L S I   B a c k e n d   D a t a - B a s e                 |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Module  :       "./AreaCommand.cpp"                        |
// +-----------------------------------------------------------------+


#include <QMouseEvent>
#include <QKeyEvent>

#include <hurricane/viewer/Graphics.h>
#include <hurricane/viewer/CellWidget.h>
#include <hurricane/viewer/AreaCommand.h>


namespace Hurricane {


// -------------------------------------------------------------------
// Class  :  "AreaCommand".


  AreaCommand::AreaCommand ()
    : Command          ()
    , _startPoint      ()
    , _stopPoint       ()
    , _drawingThreshold(10)
    , _drawingEnabled  (false)
  { }


  AreaCommand::~AreaCommand ()
  { }



  void  AreaCommand::mouseMoveEvent ( QMouseEvent* event )
  {
    if (not _drawingEnabled) return;

    setStopPoint( event->pos() );
    _cellWidget->update();
  }


  void  AreaCommand::draw ()
  {
    if (not _drawingEnabled) return;

    if (   (abs(_stopPoint.x()-_startPoint.x()) > _drawingThreshold)
       and (abs(_stopPoint.y()-_startPoint.y()) > _drawingThreshold) ) {
      _cellWidget->setPen        ( Graphics::getPen("grid"), CellWidget::PlaneId::Widget );
      _cellWidget->drawScreenRect( _startPoint, _stopPoint,  CellWidget::PlaneId::Widget );
      drawCorner( true  );
      drawCorner( false );
    }
  }


  void  AreaCommand::drawCorner ( bool bottomLeft )
  {
    QRect  zoomRect = QRect(_startPoint,_stopPoint).normalized();
    QPoint base     = (bottomLeft) ? zoomRect.bottomLeft() : zoomRect.topRight();

    if (bottomLeft) base.rx() += 2;
    else            base.ry() += 2;

    _cornerPoints[0] = base;
    _cornerPoints[1] = base;
    _cornerPoints[2] = base;

    _cornerPoints[0].ry() += (bottomLeft) ? -10 :  10;
    _cornerPoints[2].rx() += (bottomLeft) ?  10 : -10;

    _cellWidget->drawScreenPolyline( _cornerPoints, 3, 4, CellWidget::PlaneId::Widget );
  }


} // Hurricane namespace.
