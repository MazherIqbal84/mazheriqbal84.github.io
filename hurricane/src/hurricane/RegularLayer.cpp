// -*- C++ -*-
//
// Copyright (c) BULL S.A. 2000-2018, All Rights Reserved
//
// This file is part of Hurricane.
//
// Hurricane is free software: you can redistribute it  and/or  modify
// it under the terms of the GNU  Lesser  General  Public  License  as
// published by the Free Software Foundation, either version 3 of  the
// License, or (at your option) any later version.
//
// Hurricane is distributed in the hope that it will  be  useful,  but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHAN-
// TABILITY or FITNESS FOR A PARTICULAR PURPOSE. See  the  Lesser  GNU
// General Public License for more details.
//
// You should have received a copy of the Lesser  GNU  General  Public
// License along with Hurricane. If not, see
//                                     <http://www.gnu.org/licenses/>.
//
// +-----------------------------------------------------------------+
// |                  H U R R I C A N E                              |
// |     V L S I   B a c k e n d   D a t a - B a s e                 |
// |                                                                 |
// |  Author      :                    Jean-Paul Chaput              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Module  :  "./RegularLayer.cpp"                            |
// +-----------------------------------------------------------------+


#include "hurricane/DataBase.h"
#include "hurricane/BasicLayer.h"
#include "hurricane/RegularLayer.h"
#include "hurricane/Technology.h"
#include "hurricane/Error.h"


namespace {

  const char* nullLayer =
    "RegularLayer::setBasicLayer() [%s]\n"
    "  basicLayer argument mustn't be NULL.";

  const char* resetLayer =
    "RegularLayer::setBasicLayer() [%s]\n"
    "  Reseting the basic layer is forbidden.";

}


namespace Hurricane {

// -------------------------------------------------------------------
// Class :  "Hurricane::RegularLayer_RegularLayers".


  class RegularLayer_RegularLayers : public Collection<BasicLayer*> {

    public:
    // Subclass: Locator.
      class Locator : public Hurricane::Locator<BasicLayer*> {
        public:
        // Constructors.
                                                   Locator    ( const BasicLayer* basicLayer = NULL );
                                                   Locator    ( const Locator& locator );
        // Methods.
                  Locator&                         operator=  ( const Locator& locator );
          virtual BasicLayer*                      getElement () const;
          virtual Hurricane::Locator<BasicLayer*>* getClone   () const;
          virtual bool                             isValid    () const;
          virtual void                             progress   ();
          virtual string                           _getString () const;

        private:
        // Internal: Attributes.
                  const BasicLayer*                _basicLayer;
    };

    public:
    // Constructors.
                                               RegularLayer_RegularLayers ( const RegularLayer* regularLayer = NULL );
                                               RegularLayer_RegularLayers ( const RegularLayer_RegularLayers& );
    // Methods.
              RegularLayer_RegularLayers&      operator=              ( const RegularLayer_RegularLayers& );
      virtual Collection<BasicLayer*>*         getClone               () const;
      virtual Hurricane::Locator<BasicLayer*>* getLocator             () const;
      virtual string                           _getString             () const;

    private:
    // Internal: Attributes.
              const RegularLayer*              _regularLayer;
  };


  RegularLayer_RegularLayers::RegularLayer_RegularLayers ( const RegularLayer* regularLayer )
    : Collection<BasicLayer*>()
    , _regularLayer(regularLayer)
  { }


  RegularLayer_RegularLayers::RegularLayer_RegularLayers ( const RegularLayer_RegularLayers& regularLayers )
    : Collection<BasicLayer*>()
    , _regularLayer(regularLayers._regularLayer)
  { }


  RegularLayer_RegularLayers& RegularLayer_RegularLayers::operator= ( const RegularLayer_RegularLayers& regularLayers )
  {
    _regularLayer = regularLayers._regularLayer;
    return *this;
  }


  Collection<BasicLayer*>* RegularLayer_RegularLayers::getClone () const
  { return new RegularLayer_RegularLayers(*this); }


  Locator<BasicLayer*>* RegularLayer_RegularLayers::getLocator () const
  { return new Locator(_regularLayer->getBasicLayer()); }


  void  RegularLayer::_onDbuChange ( float scale )
  {
    Layer::_onDbuChange ( scale );

    _enclosure      = (DbU::Unit)( (float)_enclosure      * scale );
    _extentionCap   = (DbU::Unit)( (float)_extentionCap   * scale );
    _extentionWidth = (DbU::Unit)( (float)_extentionWidth * scale );
  }


  string RegularLayer_RegularLayers::_getString () const
  {
    string s = "<" + _TName("RegularLayer::RegularLayers");
    if (_regularLayer) s += " " + getString(_regularLayer);
    s += ">";
    return s;
  }


  RegularLayer_RegularLayers::Locator::Locator ( const BasicLayer* basicLayer )
    : Hurricane::Locator<BasicLayer*>()
    , _basicLayer(basicLayer)
  { }


  RegularLayer_RegularLayers::Locator::Locator ( const Locator& locator )
    : Hurricane::Locator<BasicLayer*>()
    , _basicLayer(locator._basicLayer)
  { }


  RegularLayer_RegularLayers::Locator& RegularLayer_RegularLayers::Locator::operator= ( const Locator& locator )
  {
    _basicLayer = locator._basicLayer;
    return *this;
  }


  BasicLayer* RegularLayer_RegularLayers::Locator::getElement () const
  { return (BasicLayer*)_basicLayer; }


  Locator<BasicLayer*>* RegularLayer_RegularLayers::Locator::getClone () const
  { return new Locator(*this); }


  bool RegularLayer_RegularLayers::Locator::isValid () const
  { return (_basicLayer != NULL); }


  void RegularLayer_RegularLayers::Locator::progress ()
  { _basicLayer = NULL; }


  string RegularLayer_RegularLayers::Locator::_getString () const
  {
    string s = "<" + _TName("RegularLayer::RegularLayers::Locator");
    if (_basicLayer) s += " " + getString(_basicLayer);
    s += ">";
    return s;
  }


// -------------------------------------------------------------------
// Class :  "Hurricane::RegularLayer".


  RegularLayer::RegularLayer ( Technology*     technology
                             , const Name&     name
                             ) : Layer(technology
                                      ,name
                                      ,0  // minimalSize.
                                      ,0) // minmalSpacing.
                               ,_basicLayer(NULL)
                               ,_enclosure(0)
                               ,_extentionCap(0)
                               ,_extentionWidth(0)
  {
  }


  RegularLayer* RegularLayer::create ( Technology* technology
                                     , const Name& name
                                     , BasicLayer* layer
                                     )
  {
    RegularLayer* regularLayer = new RegularLayer( technology, name );

    regularLayer->_postCreate();
    regularLayer->setBasicLayer( layer );

    return regularLayer;
  }


  const Layer* RegularLayer::getBlockageLayer () const
  { return _basicLayer->getBlockageLayer(); }
 

  BasicLayers  RegularLayer::getBasicLayers () const
  { return RegularLayer_RegularLayers(this); }


  const Layer* RegularLayer::getTop () const
  { return getTechnology()->getLayer(_basicLayer->getMask()); } 


  const Layer* RegularLayer::getBottom () const
  { return getTechnology()->getLayer(_basicLayer->getMask()); } 


  const Layer* RegularLayer::getOpposite ( const Layer* ) const
  { return getTechnology()->getLayer(_basicLayer->getMask()); } 


  DbU::Unit  RegularLayer::getEnclosure ( uint32_t ) const
  { return _enclosure; }


  DbU::Unit  RegularLayer::getExtentionCap () const
  { return _extentionCap; }


  DbU::Unit  RegularLayer::getExtentionWidth () const
  { return _extentionWidth; }


  DbU::Unit  RegularLayer::getEnclosure ( const BasicLayer* layer, uint32_t ) const
  {
    return (layer == _basicLayer) ? _enclosure : 0;
  }


  DbU::Unit  RegularLayer::getExtentionCap ( const BasicLayer* layer ) const
  {
    return (layer == _basicLayer) ? _extentionCap : 0;
  }


  DbU::Unit  RegularLayer::getExtentionWidth ( const BasicLayer* layer ) const
  {
    return (layer == _basicLayer) ? _extentionWidth : 0;
  }


  void  RegularLayer::setBasicLayer ( BasicLayer* basicLayer )
  {
    if ( !basicLayer )
      throw Error ( nullLayer, getString(getName()).c_str() );

    if ( _basicLayer )
      throw Error ( resetLayer, getString(getName()).c_str() );

    getTechnology()->_removeFromLayerMaskMap ( this );

    _basicLayer = basicLayer;

    _setMask        ( _basicLayer->getMask()        );
    _setExtractMask ( _basicLayer->getExtractMask() );

    getTechnology()->_insertInLayerMaskMap ( this );
  }


  void  RegularLayer::setEnclosure ( const BasicLayer* layer, DbU::Unit enclosure, uint32_t )
  {
    if ( _basicLayer == layer ) _enclosure = enclosure;
  }


  void  RegularLayer::setExtentionCap ( const BasicLayer* layer, DbU::Unit cap )
  {
    if ( _basicLayer == layer ) _extentionCap = cap;
  }


  void  RegularLayer::setExtentionWidth ( const BasicLayer* layer, DbU::Unit width )
  {
    if ( _basicLayer == layer ) _extentionWidth = width;
  }


  string  RegularLayer::_getTypeName () const
  { return _TName("RegularLayer"); }


  string RegularLayer::_getString () const
  {
    string s = Layer::_getString();
  // s.insert(s.length() - 1, " " + getString(_type));
    return s;
  }


  Record* RegularLayer::_getRecord () const
  {
    Record* record = Layer::_getRecord();
    if (record) {
      record->add(getSlot("_basicLayer"    ,  _basicLayer    ));
      record->add(getSlot("_enclosure"     , &_enclosure     ));
      record->add(DbU::getValueSlot("_extentionCap"  , &_extentionCap  ));
      record->add(DbU::getValueSlot("_extentionWidth", &_extentionWidth));
    }
    return record;
  }


  void  RegularLayer::_toJson ( JsonWriter* writer ) const
  {
    Super::_toJson( writer );

    jsonWrite( writer, "_basicLayer"     , _basicLayer->getName() );
    jsonWrite( writer, "_enclosure"      , _enclosure             );
    jsonWrite( writer, "_extentionCap"   , _extentionCap          );
    jsonWrite( writer, "_extentionWidth" , _extentionWidth        );
  }


// -------------------------------------------------------------------
// Class :  "Hurricane::JsonRegularLayer".

  Initializer<JsonRegularLayer>  jsonRegularLayerInit ( 0 );


  void  JsonRegularLayer::initialize ()
  { JsonTypes::registerType( new JsonRegularLayer (JsonWriter::RegisterMode) ); }


  JsonRegularLayer::JsonRegularLayer ( unsigned long flags )
    : JsonLayer(flags)
  {
    if (flags & JsonWriter::RegisterMode) return;

    cdebug_log(19,0) << "JsonRegularLayer::JsonRegularLayer()" << endl;

    add( "_basicLayer"    , typeid(string)  );
    add( "_enclosure"     , typeid(int64_t) );
    add( "_extentionCap"  , typeid(int64_t) );
    add( "_extentionWidth", typeid(int64_t) );
  }


  JsonRegularLayer::~JsonRegularLayer ()
  { }


  string  JsonRegularLayer::getTypeName () const
  { return "RegularLayer"; }


  JsonRegularLayer* JsonRegularLayer::clone ( unsigned long flags ) const
  { return new JsonRegularLayer ( flags ); }


  void JsonRegularLayer::toData( JsonStack& stack )
  {
    cdebug_tabw(19,1);

    check( stack, "JsonRegularLayer::toData" );

    Technology*   techno = lookupTechnology( stack, "JsonRegularLayer::toData" );
    RegularLayer* layer  = NULL;

    if (techno) {
      string       name           = get<string> ( stack, "_name"           );
      string       smask          = get<string> ( stack, "_mask"           );
      DbU::Unit    minimalSize    = get<int64_t>( stack, "_minimalSize"    );
      DbU::Unit    minimalSpacing = get<int64_t>( stack, "_minimalSpacing" );
      bool         isSymbolic     = get<bool>   ( stack, "_symbolic"       );

      BasicLayer*  basicLayer     = techno->getBasicLayer( get<string>(stack,"_basicLayer" ) );
      DbU::Unit    enclosure      = get<int64_t>( stack, "_enclosure"      );
      DbU::Unit    extensionCap   = get<int64_t>( stack, "_extentionCap"   );
      DbU::Unit    extensionWidth = get<int64_t>( stack, "_extentionWidth" );

      Layer::Mask mask = Layer::Mask::fromString( smask );

      if (stack.issetFlags(JsonWriter::TechnoMode)) {
      // Actual creation.
        layer = RegularLayer::create( techno, name, basicLayer );
        layer->setSymbolic      ( isSymbolic );
        layer->setMinimalSize   ( minimalSize );
        layer->setMinimalSpacing( minimalSpacing );
        layer->setEnclosure     ( basicLayer, enclosure      );
        layer->setExtentionCap  ( basicLayer, extensionCap   );
        layer->setExtentionWidth( basicLayer, extensionWidth );

        if (layer->getMask() != mask) {
          cerr << Error( "JsonRegularLayer::toData(): Layer mask re-creation discrepency on \"%s\":\n"
                         "        Blob:     %s\n"
                         "        DataBase: %s"
                       , name.c_str()
                       , getString(mask).c_str()
                       , getString(layer->getMask()).c_str()
                       ) << endl;
        }
      // Add here association with blockage layer...
      } else {
      // Check coherency with existing layer.
        layer = dynamic_cast<RegularLayer*>( techno->getLayer(name) );
        if (layer) {
          if (layer->getMask() != mask) {
            cerr << Error( "JsonRegularLayer::toData(): Layer mask discrepency on \"%s\":\n"
                           "        Blob:     %s\n"
                           "        DataBase: %s"
                         , name.c_str()
                         , getString(mask).c_str()
                         , getString(layer->getMask()).c_str()
                         ) << endl;
          }
        } else {
          cerr << Error( "JsonRegularLayer::toData(): No RegularLayer \"%s\" in the existing technology."
                       , name.c_str()
                       ) << endl;
        }
      }
    } else {
      cerr << Error( "JsonRegularLayer::toData(): Cannot find technology, aborting RegularLayer creation." ) << endl;
    }
    
    update( stack, layer );

    cdebug_tabw(19,-1);
  }

} // Hurricane namespace.
