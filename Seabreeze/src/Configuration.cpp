// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) SU 2022-2022, All Rights Reserved
//
// +-----------------------------------------------------------------+
// |                   C O R I O L I S                               |
// |        S e a b r e e z e  -  Timing Analysis                    |
// |                                                                 |
// |  Author      :                   Vu Hoang Anh PHAM              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Module  :  "./Configuration.cpp"                           |
// +-----------------------------------------------------------------+


#include <iostream>
#include <sstream>
#include <iomanip>
#include "hurricane/configuration/Configuration.h"
#include "hurricane/Warning.h"
#include "hurricane/Error.h"
#include "hurricane/Technology.h"
#include "hurricane/DataBase.h"
#include "hurricane/RoutingPad.h"
#include "hurricane/Contact.h"
#include "hurricane/Net.h"
#include "hurricane/Segment.h"
#include "hurricane/Cell.h"
#include "crlcore/Utilities.h"
#include "seabreeze/Configuration.h"


namespace Seabreeze {

  using std::string;
  using std::ostringstream;
  using Hurricane::Warning;
  using Hurricane::Error;
  using Hurricane::Technology;
  using Hurricane::RoutingPad;
  using Hurricane::Contact;
  using Hurricane::Segment;
  using Hurricane::Cell;
  using Hurricane::Net;
  using Hurricane::DataBase;
  using Hurricane::Record;
  using Hurricane::Name;
  using Hurricane::Layer;
  using Hurricane::DbU;


//------------------------------------------------------------------------
// Class : "Seabreeze::Configuration"

  Configuration::Configuration () 
    : _Rct (1)
    , _Rsm (1)
    , _Csm (1)
  {}


  Configuration::~Configuration () 
  {}


  Configuration::Configuration ( const Configuration& other )
    : _Rct (other._Rct)
    , _Rsm (other._Rsm)
    , _Csm (other._Csm)
  {}


  Configuration* Configuration::clone () const
  { return new Configuration( *this ); }

  
  string Configuration::_getTypeName () const
  { return "Seabreeze::Configuration"; }


  string Configuration::_getString () const
  {
    ostringstream os;
    os << "<" << _getTypeName() << ">";
    return os.str();
  }

  
  Record* Configuration::_getRecord () const 
  {
    Record* record = new Record ( _getString() );
    if (record != nullptr) {
      record->add( getSlot("_Rct", _Rct) );
      record->add( getSlot("_Rsm", _Rsm) );
      record->add( getSlot("_Csm", _Csm) );
    }
    return record;
  }

  
} // Seabreeze namespace.
