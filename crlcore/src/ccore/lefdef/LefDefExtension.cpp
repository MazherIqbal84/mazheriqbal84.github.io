// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2008-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+
// |                   C O R I O L I S                               |
// |          Alliance / Hurricane  Interface                        |
// |                                                                 |
// |  Author      :                    Jean-Paul Chaput              |
// |  E-mail      :            Jean-Paul.Chaput@lip6.fr              |
// | =============================================================== |
// |  C++ Module  :       "./LefDefExtension.cpp"                    |
// +-----------------------------------------------------------------+


#include "hurricane/Error.h"
#include "hurricane/Cell.h"
#include "crlcore/LefDefExtension.h"


template<>
Hurricane::Name  CRL::LefDefExtension::Extension::_name = "CRL::LefDefExtension";


namespace CRL {


  using Hurricane::Error;


  const char* MissingLefDefExtension = "LefDefExtension::%s(): %s missing the LEF/DEF extension.";

  
// -------------------------------------------------------------------
// Class  :  "CRL::LefDefExtensionDatas".


  LefDefExtensionDatas::LefDefExtensionDatas ()
    : _lefDbuPerMicron(1)
    , _defDbuPerMicron(1)
    , _rowsBox()
    , _northOrder()
    , _southOrder()
    , _eastOrder()
    , _westOrder()
    , _undefined()
  { }

  
// -------------------------------------------------------------------
// Class  :  "CRL::LefDefExtension".


  Box  LefDefExtension::getRowsBox ( const Cell* cell )
  {
    Extension* extension = Extension::get ( cell );
    if ( !extension )
      return Box ();

    return extension->getValue()._rowsBox;
  }


  const Box& LefDefExtension::addRowsBox ( Cell* cell, Box rowBox )
  {
    Extension* extension = Extension::get ( cell, true );

    return extension->getValue()._rowsBox.merge(rowBox);
  }


  unsigned int  LefDefExtension::getLefDbuPerMicron ( const Cell* cell )
  {
    Extension* extension = Extension::get ( cell );
    if ( !extension )
      return 1;

    return extension->getValue()._lefDbuPerMicron;
  }


  void  LefDefExtension::setLefDbuPerMicron ( Cell* cell, unsigned int dbuPerMicron )
  {
    Extension* extension = Extension::get ( cell, true );

    extension->getValue()._lefDbuPerMicron = dbuPerMicron;
  }


  unsigned int  LefDefExtension::getDefDbuPerMicron ( const Cell* cell )
  {
    Extension* extension = Extension::get ( cell );
    if ( !extension )
      return 1;

    return extension->getValue()._defDbuPerMicron;
  }


  void  LefDefExtension::setDefDbuPerMicron ( Cell* cell, unsigned int dbuPerMicron )
  {
    Extension* extension = Extension::get ( cell, true );

    extension->getValue()._defDbuPerMicron = dbuPerMicron;
  }


  PinIocOrder& LefDefExtension::getNorthPinIocOrder ( Cell* cell, bool create )
  {
    Extension* extension = Extension::get ( cell, create );
    if ( !extension )
      throw Error ( MissingLefDefExtension, "getNorthPinOrder", getString(cell).c_str() );

    return extension->getValue()._northOrder;
  }


  PinIocOrder& LefDefExtension::getSouthPinIocOrder ( Cell* cell, bool create )
  {
    Extension* extension = Extension::get ( cell, create );
    if ( !extension )
      throw Error ( MissingLefDefExtension, "getSouthPinOrder", getString(cell).c_str() );

    return extension->getValue()._southOrder;
  }


  PinIocOrder& LefDefExtension::getEastPinIocOrder ( Cell* cell, bool create )
  {
    Extension* extension = Extension::get ( cell, create );
    if ( !extension )
      throw Error ( MissingLefDefExtension, "getEastPinOrder", getString(cell).c_str() );

    return extension->getValue()._eastOrder;
  }


  PinIocOrder& LefDefExtension::getWestPinIocOrder ( Cell* cell, bool create )
  {
    Extension* extension = Extension::get ( cell, create );
    if ( !extension )
      throw Error ( MissingLefDefExtension, "getWestPinOrder", getString(cell).c_str() );

    return extension->getValue()._westOrder;
  }


  PinIocOrder& LefDefExtension::getUndefinedPinIoc ( Cell* cell, bool create )
  {
    Extension* extension = Extension::get ( cell, create );
    if ( !extension )
      throw Error ( MissingLefDefExtension, "getUndefinedPin", getString(cell).c_str() );

    return extension->getValue()._undefined;
  }


} // End of CRL namespace.
