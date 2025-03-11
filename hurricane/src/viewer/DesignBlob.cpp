// -*- mode: C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2016-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+
// |                   C O R I O L I S                               |
// |     V L S I   B a c k e n d   D a t a - B a s e                 |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Module  :  "./DesignBlob.cpp"                              |
// +-----------------------------------------------------------------+


#include <iostream>
#include "hurricane/JsonReader.h"
#include "hurricane/UpdateSession.h"
#include "hurricane/DataBase.h"
#include "hurricane/Cell.h"
#include "hurricane/viewer/Graphics.h"
#include "hurricane/viewer/DesignBlob.h"
#include "hurricane/viewer/JsonParameter.h"


namespace Hurricane {

  using std::cerr;
  using std::endl;


// -------------------------------------------------------------------
// Class  :  "DesignBlob".

  void DesignBlob::toJson( JsonWriter* w ) const
  {
    w->startObject();
    jsonWrite( w, "@typename"     , _getTypeName() );
    jsonWrite( w, "_topCell"      , getTopCell()->getHierarchicalName() );
    jsonWrite( w, "_database"     , DataBase::getDB()                   );
    jsonWrite( w, "_graphics"     , Graphics::getGraphics()             );
    jsonWrite( w, "_configuration", Cfg::Configuration::get()           );
    w->endObject();
  }


  DesignBlob* DesignBlob::fromJson ( const string& filename )
  {
    UpdateSession::open();

    JsonReader reader ( JsonWriter::DesignBlobMode );
    reader.parse( filename );

    UpdateSession::close();

    const JsonStack& stack = reader.getStack();
    if (stack.rhas(".DesignBlob")) return stack.as<DesignBlob*>(".DesignBlob");

    return NULL;
  }

// -------------------------------------------------------------------
// Class  :  "JsonDesignBlob".

  Initializer<JsonDesignBlob>  jsonDesignBlobInit ( 0 );


  void  JsonDesignBlob::initialize ()
  { JsonTypes::registerType( new JsonDesignBlob (JsonWriter::RegisterMode) ); }


  JsonDesignBlob::JsonDesignBlob ( unsigned long flags )
    : JsonObject(flags)
  {
    add( "_topCell"      , typeid(string)              );
    add( "_database"     , typeid(DataBase*)           );
    add( "_graphics"     , typeid(Graphics*)           );
    add( "_configuration", typeid(Cfg::Configuration*) );
  }


  string JsonDesignBlob::getTypeName () const
  { return "DesignBlob"; }


  JsonDesignBlob* JsonDesignBlob::clone ( unsigned long flags ) const
  { return new JsonDesignBlob ( flags ); }


  void JsonDesignBlob::toData ( JsonStack& stack )
  {
    check( stack, "JsonDesignBlob::toData" );

    DesignBlob* designBlob = new DesignBlob
      ( DataBase::getDB()->getCell( get<string>(stack,"_topCell"), DataBase::NoFlags ) );
    
    update( stack, designBlob );
  }


} // Hurricane namespace.
