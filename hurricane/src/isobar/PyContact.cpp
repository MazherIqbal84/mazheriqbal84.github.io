// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC 2008-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |    I s o b a r  -  Hurricane / Python Interface                 |
// |                                                                 |
// |  Author      :                   Jean-Paul Chaput               |
// |  E-mail      :      Jean-Paul.Chaput@asim.lip6.fr               |
// | =============================================================== |
// |  C++ Module  :       "./PyContact.cpp"                          |
// +-----------------------------------------------------------------+


#include "hurricane/isobar/PyNet.h"
#include "hurricane/isobar/PyLayer.h"
#include "hurricane/isobar/PyHook.h"
#include "hurricane/isobar/PyContact.h"
#include "hurricane/isobar/PyHorizontal.h"
#include "hurricane/isobar/PyVertical.h"


namespace  Isobar {

using namespace Hurricane;


extern "C" {


#undef  ACCESS_OBJECT
#undef  ACCESS_CLASS
#define ACCESS_OBJECT           _baseObject._baseObject._object
#define ACCESS_CLASS(_pyObject) &(_pyObject->_baseObject._baseObject)
#define METHOD_HEAD(function)   GENERIC_METHOD_HEAD(Contact,contact,function)


#if defined(__PYTHON_MODULE__)

// +=================================================================+
// |              "PyContact" Python Module Code Part                |
// +=================================================================+

  // Standart Accessors (Attributes).
  DirectGetLongAttribute(PyContact_getWidth     , getWidth     , PyContact,Contact)
  DirectGetLongAttribute(PyContact_getHalfWidth , getHalfWidth , PyContact,Contact)
  DirectGetLongAttribute(PyContact_getHeight    , getHeight    , PyContact,Contact)
  DirectGetLongAttribute(PyContact_getHalfHeight, getHalfHeight, PyContact,Contact)

  DirectGetLongAttribute(PyContact_getDx, getDx, PyContact,Contact)
  DirectGetLongAttribute(PyContact_getDy, getDy, PyContact,Contact)

  DirectSetLongAttribute(PyContact_setX     ,setX     ,PyContact,Contact)
  DirectSetLongAttribute(PyContact_setY     ,setY     ,PyContact,Contact)
  DirectSetLongAttribute(PyContact_setDx    ,setDx    ,PyContact,Contact)
  DirectSetLongAttribute(PyContact_setDy    ,setDy    ,PyContact,Contact)
  DirectSetLongAttribute(PyContact_setWidth ,setWidth ,PyContact,Contact)
  DirectSetLongAttribute(PyContact_setHeight,setHeight,PyContact,Contact)
  accessorHook(getAnchorHook,PyContact,Contact)

  
  // Standart destroy (Attribute).
  DBoDestroyAttribute(PyContact_destroy, PyContact)
  

  static PyObject* PyContact_create ( PyObject*, PyObject *args ) {
    cdebug_log(20,0) << "PyContact_create()" << endl;

    Contact* contact = NULL;

    HTRY
    PyNet* pyNet = NULL;
    PyLayer* pyLayer = NULL;
    PyComponent* pyComponent = NULL;
    DbU::Unit x=0, y=0, width=0, height=0;
   if (PyArg_ParseTuple(args, "O!O!ll|ll:Contact.create",
                &PyTypeNet, &pyNet, &PyTypeLayer, &pyLayer,
                &x, &y, &width, &height)) {
        contact = Contact::create(PYNET_O(pyNet), PYLAYER_O(pyLayer), x, y, width, height);
    } else {
      PyErr_Clear ();
      if (PyArg_ParseTuple(args, "O!O!ll|ll:Contact.create",
                &PyTypeComponent, &pyComponent, &PyTypeLayer, &pyLayer,
                &x, &y, &width, &height)) {
        contact = Contact::create(PYCOMPONENT_O(pyComponent), PYLAYER_O(pyLayer), x, y, width, height);
      } else {
        PyErr_SetString ( ConstructorError, "invalid number of parameters for Contact constructor." );
        return NULL;
      }
    }


    HCATCH

    return PyContact_Link(contact);
  }
 

  static PyObject* PyContact_getAnchor ( PyContact *self )
  {
    cdebug_log(20,0) << "PyContact_getAnchor ()" << endl;
    METHOD_HEAD ( "Contact.getAnchor()" )
    Component* anchor   = NULL;
    PyObject*  pyAnchor = NULL;
    HTRY
      anchor = contact->getAnchor();
      if (anchor) pyAnchor = PyEntity_NEW( anchor );
      else
        Py_RETURN_NONE;
    HCATCH
    return pyAnchor;
  }


  static PyObject* PyContact_translate ( PyContact *self, PyObject* args ) {
    cdebug_log(20,0) << "PyContact_translate ()" << endl;
    
    HTRY
    METHOD_HEAD ( "Contact.translate()" )
    PyObject* arg0 = NULL;
    PyObject* arg1 = NULL;
    __cs.init ("Contact.translate");
    if (PyArg_ParseTuple(args,"O&O&:Contact.translate", Converter, &arg0, Converter, &arg1)) {
      if (__cs.getObjectIds() == INTS2_ARG) contact->translate( PyAny_AsLong(arg0), PyAny_AsLong(arg1) );
      else {
        PyErr_SetString ( ConstructorError, "Contact.translate(): Invalid type for parameter(s)." );
        return NULL;
      }
    } else {
      PyErr_SetString ( ConstructorError, "Contact.translate(): Invalid number of parameters." );
      return NULL;
    }
    HCATCH

    Py_RETURN_NONE;
  }


  static PyObject* PyContact_setLayer ( PyContact* self, PyObject* args )
  {
    cdebug_log(30,0) << "PyContact_setLayer()" << endl;
    HTRY
      METHOD_HEAD("Contact.setLayer()")
      PyObject* pyLayer = NULL;
      if (PyArg_ParseTuple( args, "O:Contact.setLayer", &pyLayer)) {
        if (IsPyDerivedLayer(pyLayer)) {
          contact->setLayer( PYDERIVEDLAYER_O( pyLayer ));
        } else {
          PyErr_SetString ( ConstructorError, "invalid parameter type for Contact.setLayer()." );
          return NULL;
        }
      } else {
        PyErr_SetString ( ConstructorError, "Invalid number of parameters passed to Contact.setLayer()." );
        return NULL;
      }
    HCATCH
    Py_RETURN_NONE;
  }


  PyMethodDef PyContact_Methods[] =
    { { "create"          , (PyCFunction)PyContact_create         , METH_VARARGS|METH_STATIC
                          , "Create a new Contact." }
    , { "destroy"         , (PyCFunction)PyContact_destroy        , METH_NOARGS
                          , "Destroy associated hurricane object, the python object remains." }
    , { "getAnchorHook"   , (PyCFunction)PyContact_getAnchorHook  , METH_NOARGS , "Return the contact anchor hook." }
    , { "getAnchor"       , (PyCFunction)PyContact_getAnchor      , METH_NOARGS , "Return the contact anchor (component)." }
    , { "getWidth"        , (PyCFunction)PyContact_getWidth       , METH_NOARGS , "Return the contact width." }
    , { "getHalfWidth"    , (PyCFunction)PyContact_getHalfWidth   , METH_NOARGS , "Return the contact half width." }
    , { "getHeight"       , (PyCFunction)PyContact_getHeight      , METH_NOARGS , "Return the contact height." }
    , { "getHalfHeight"   , (PyCFunction)PyContact_getHalfHeight  , METH_NOARGS , "Return the contact half height." }
    , { "getDx"           , (PyCFunction)PyContact_getDx          , METH_NOARGS , "Return the contact dx value." }
    , { "getDy"           , (PyCFunction)PyContact_getDy          , METH_NOARGS , "Return the contact dy value." }
    , { "translate"       , (PyCFunction)PyContact_translate      , METH_VARARGS, "Translates the Contact of dx and dy." }
    , { "setX"            , (PyCFunction)PyContact_setX           , METH_VARARGS, "Sets the contact X value." }
    , { "setY"            , (PyCFunction)PyContact_setY           , METH_VARARGS, "Sets the contact Y value." }
    , { "setDx"           , (PyCFunction)PyContact_setDx          , METH_VARARGS, "Sets the contact dx value." }
    , { "setDy"           , (PyCFunction)PyContact_setDy          , METH_VARARGS, "Sets the contact dy value." }
    , { "setWidth"        , (PyCFunction)PyContact_setWidth       , METH_VARARGS, "Sets the contact width." }
    , { "setHeight"       , (PyCFunction)PyContact_setHeight      , METH_VARARGS, "Sets the contact height." }
    , { "setLayer"        , (PyCFunction)PyContact_setLayer       , METH_VARARGS, "Sets the contact layer." }
    , {NULL, NULL, 0, NULL} /* sentinel */
    };


  DBoDeleteMethod(Contact)
  PyTypeObjectLinkPyType(Contact)


#else  // End of Python Module Code Part.


// +=================================================================+
// |             "PyContact" Shared Library Code Part                |
// +=================================================================+


  // Link/Creation Method.
  DBoLinkCreateMethod(Contact)

  PyTypeInheritedObjectDefinitions(Contact, Component)

#endif  // End of Shared Library Code Part.


}  // extern "C".

}  // Isobar namespace.
