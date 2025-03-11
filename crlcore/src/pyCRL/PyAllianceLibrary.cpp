// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2016-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |          Alliance / Hurricane  Interface                        |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@lip6.fr                   |
// | =============================================================== |
// |  C++ Module  :  "./PyAllianceLibrary.cpp"                       |
// +-----------------------------------------------------------------+


#include "hurricane/isobar/PyLibrary.h"
#include "crlcore/PyAllianceLibrary.h"
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
  using Hurricane::Library;
  using Isobar::ProxyProperty;
  using Isobar::ProxyError;
  using Isobar::ConstructorError;
  using Isobar::HurricaneError;
  using Isobar::HurricaneWarning;
  using Isobar::getPyHash;
  using Isobar::ParseOneArg;
  using Isobar::ParseTwoArg;
  using Isobar::__cs;
  using Isobar::PyLibrary_Link;


extern "C" {


#define METHOD_HEAD(function) GENERIC_METHOD_HEAD(AllianceLibrary,alib,function)


#if defined(__PYTHON_MODULE__)

// +=================================================================+
// |          "PyAllianceLibrary" Python Module Code Part            |
// +=================================================================+


  static PyObject* PyAllianceLibrary_getLibrary ( PyAllianceLibrary* self, PyObject* )
  {
    cdebug_log(30,0) << "PyAllianceLibrary_getLibrary()" << endl;

    Library* lib = NULL;
    HTRY
      METHOD_HEAD("AllianceLibrary.getLibrary()")
      lib = alib->getLibrary();
    HCATCH
    return PyLibrary_Link(lib);
  }


  static PyObject* PyAllianceLibrary_getPath ( PyAllianceLibrary* self, PyObject* )
  {
    cdebug_log(30,0) << "PyAllianceLibrary_getPath()" << endl;
    HTRY
      METHOD_HEAD("AllianceLibrary.getPath()")
      return PyString_FromString( getString(alib->getPath()).c_str() );
    HCATCH
    return NULL;
  }


  static PyObject* PyAllianceLibrary_saveCells ( PyAllianceLibrary* self, PyObject* )
  {
    cdebug_log(30,0) << "PyAllianceLibrary_saveCells()" << endl;
    HTRY
      METHOD_HEAD("AllianceLibrary.saveCells()")
      alib->saveCells();
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyAllianceLibrary_saveCATAL ( PyAllianceLibrary* self, PyObject* )
  {
    cdebug_log(30,0) << "PyAllianceLibrary_saveCATAL()" << endl;
    HTRY
      METHOD_HEAD("AllianceLibrary.saveCATAL()")
      alib->saveCATAL();
    HCATCH
    Py_RETURN_NONE;
  }


  static PyObject* PyAllianceLibrary_Repr ( PyAllianceLibrary* self )
  {
    if ( self->ACCESS_OBJECT == NULL )
      return PyString_FromString("<PyObject unbound>");

    string s = getString( self->ACCESS_OBJECT );
    return PyString_FromString( s.c_str() );
  }


  // Standart Destroy (Attribute).
  // DBoDestroyAttribute(PyAllianceLibrary_destroy,PyAllianceLibrary)


  PyMethodDef PyAllianceLibrary_Methods[] =
    { { "getPath"         , (PyCFunction)PyAllianceLibrary_getPath       , METH_NOARGS
                          , "Return the complete path of the library." }
    , { "getLibrary"      , (PyCFunction)PyAllianceLibrary_getLibrary    , METH_NOARGS
                          , "Returns the associated Hurricane library." }
    , { "saveCells"       , (PyCFunction)PyAllianceLibrary_saveCells     , METH_NOARGS
                          , "Save all the library cells." }
    , { "saveCATAL"       , (PyCFunction)PyAllianceLibrary_saveCATAL     , METH_NOARGS
                          , "Rewrite the library CATAL file." }
  //, { "destroy"         , (PyCFunction)PyAllianceLibrary_destroy       , METH_VARARGS
  //                      , "Destroy the associated hurricane object. The python object remains." }
    , {NULL, NULL, 0, NULL}   /* sentinel */
    };


  PythonOnlyDeleteMethod(AllianceLibrary)
  DirectHashMethod(PyAllianceLibrary_Hash, AllianceLibrary)

  extern void  PyAllianceLibrary_LinkPyType() {
    cdebug_log(30,0) << "PyAllianceLibrary_LinkType()" << endl;

    PyTypeAllianceLibrary.tp_dealloc = (destructor) PyAllianceLibrary_DeAlloc;
    PyTypeAllianceLibrary.tp_repr    = (reprfunc)   PyAllianceLibrary_Repr;
    PyTypeAllianceLibrary.tp_str     = (reprfunc)   PyAllianceLibrary_Repr;
    PyTypeAllianceLibrary.tp_hash    = (hashfunc)   PyAllianceLibrary_Hash;
    PyTypeAllianceLibrary.tp_methods = PyAllianceLibrary_Methods;
  }


#else  // End of Python Module Code Part.

// +=================================================================+
// |           "PyAllianceLibrary" Shared Library Code Part          |
// +=================================================================+

  // Type Definition.
  PyTypeObjectDefinitionsOfModule(CRL,AllianceLibrary)

  // Link/Creation Method.
  LinkCreateMethod(AllianceLibrary)


#endif  // End of Shared Library Code Part.


}  // extern "C".

}  // CRL namespace.
