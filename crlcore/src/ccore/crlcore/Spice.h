// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) SU/LIP6 2021-2021, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |         S P I C E  / Hurricane  Interface                       |
// |                                                                 |
// |  Author      :                  Jean-Paul CHAPUT                |
// |  E-mail      :          Jean-Paul.Chaput@lip6.fr                |
// | =============================================================== |
// |  C++ Header  :  "./crlcore/Spice.h"                             |
// +-----------------------------------------------------------------+


#pragma  once
#include <string>


namespace Hurricane {
  class Cell;
  class Library;
}


namespace CRL {

  using Hurricane::Cell;
  using Hurricane::Library;


  class Spice {
    public:
      static const uint64_t PIN_ORDERING = (1<<0);
    public:
      static bool  save ( Cell*, uint64_t flags );
      static bool  load ( Library*, std::string spicePath, uint64_t mode );
      static void  clearProperties ();
  };


} // CRL namespace.
