// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2015-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |          Alliance / Hurricane  Interface                        |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Module  :  "./PyBlif.cpp"                                  |
// +-----------------------------------------------------------------+


#include "crlcore/PyBlif.h"
#include "hurricane/isobar/PyCell.h"
#include "hurricane/isobar/PyLibrary.h"
#include <string>
#include <sstream>


namespace  CRL {

  using std::cerr;
  using std::endl;
  using std::hex;
  using std::string;
  using std::ostringstream;
  using Hurricane::tab;
  using Hurricane::Exception;
  using Hurricane::Bug;
  using Hurricane::Error;
  using Hurricane::Warning;
  using Isobar::ProxyProperty;
  using Isobar::ProxyError;
  using Isobar::ConstructorError;
  using Isobar::HurricaneError;
  using Isobar::HurricaneWarning;
  using Isobar::getPyHash;
  using Isobar::ParseOneArg;
  using Isobar::ParseTwoArg;
  using Isobar::__cs;
  using Isobar::PyCell;
  using Isobar::PyCell_Link;
  using Isobar::PyTypeCell;
  using Isobar::PyLibrary;
  using Isobar::PyLibrary_Link;
  using Isobar::PyTypeLibrary;


extern "C" {


#if defined(__PYTHON_MODULE__)

// +=================================================================+
// |               "PyBlif" Python Module Code Part                  |
// +=================================================================+


  static PyObject* PyBlif_add ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyBlif_add()" << endl;

    HTRY
      PyObject* pyLibrary = NULL;
      if (PyArg_ParseTuple( args, "O:Blif.add", &pyLibrary )) {
        if (not IsPyLibrary(pyLibrary)) {
          PyErr_SetString( ConstructorError, "Blif.add(): Argument is not of Library type." );
          return NULL;
        }
        Blif::add( PYLIBRARY_O(pyLibrary) );
      } else {
        PyErr_SetString( ConstructorError, "Blif.add(): bad number of parameters." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyBlif_load ( PyObject*, PyObject* args )
  {
    cdebug_log(30,0) << "PyBlif_load()" << endl;

    Cell* cell = NULL;
    
    HTRY
      char*     benchName     = NULL;
      PyObject* pyEnforceVhdl = NULL;
      
      if (PyArg_ParseTuple( args, "s|O:Blif.load", &benchName, &pyEnforceVhdl )) {
        bool enforceVhdl = true;
        if (pyEnforceVhdl and (PyObject_IsTrue(pyEnforceVhdl) == 0)) enforceVhdl = false;
        cell = Blif::load( benchName, enforceVhdl );
      } else {
        PyErr_SetString ( ConstructorError, "Blif.load(): Bad type or bad number of parameters." );
        return NULL;
      }
    HCATCH

    return (PyObject*)PyCell_Link(cell);
  }


  // Standart Destroy (Attribute).


  PyMethodDef PyBlif_Methods[] =
    { { "load"                , (PyCFunction)PyBlif_load     , METH_VARARGS|METH_STATIC
                              , "Load a complete Blif design." }
    , { "add"                 , (PyCFunction)PyBlif_add      , METH_VARARGS|METH_STATIC
                              , "Add a Library into which lookup master cells.." }
  //, { "destroy"             , (PyCFunction)PyBlif_destroy  , METH_VARARGS
  //                          , "Destroy the associated hurricane object. The python object remains." }
    , {NULL, NULL, 0, NULL}   /* sentinel */
    };


  NoObjectDeleteMethod(Blif)
  PyTypeObjectLinkPyTypeWithoutObject(Blif,Blif)


#else  // End of Python Module Code Part.


// +=================================================================+
// |                "PyBlif" Shared Library Code Part                |
// +=================================================================+

  // Type Definition.
  PyTypeObjectDefinitionsOfModule(CRL,Blif)


#endif  // End of Shared Library Code Part.

}  // extern "C".

}  // CRL namespace.
