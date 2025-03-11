// -*- C++ -*-
//
// This file is part of the Coriolis Software.
// Copyright (c) UPMC/LIP6 2008-2018, All Rights Reserved
//
// +-----------------------------------------------------------------+ 
// |                   C O R I O L I S                               |
// |          Alliance / Hurricane  Interface                        |
// |                                                                 |
// |  Author      :                Christophe Alexandre              |
// |  E-mail      :   Christophe.Alexandre@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Header  :       "./ApDriver.h"                             |
// +-----------------------------------------------------------------+


#include <time.h>
#include "hurricane/Pin.h"
#include "hurricane/Instance.h"
#include "hurricane/Net.h"
#include "hurricane/NetExternalComponents.h"
#include "hurricane/Reference.h"
#include "hurricane/Horizontal.h"
#include "hurricane/Vertical.h"
#include "hurricane/RoutingPad.h"
#include "hurricane/Cell.h"
#include "hurricane/Layer.h"
#include "hurricane/RegularLayer.h"
#include "hurricane/Warning.h"
#include "Ap.h"
#include "crlcore/Catalog.h"

using namespace std;


namespace {

using namespace Hurricane;
    
struct PinSort
{
    bool operator()(const Pin* pin1, const Pin* pin2) const {
        if (pin1->getY() > pin2->getY())
            return true;
        else if (pin2->getY() > pin1->getY())
            return false;
        else if (pin1->getX() > pin2->getX())
            return true;
        else
            return false;
    }
};

  int toMBKlambda ( DbU::Unit u )
  {
    return (int)( DbU::getLambda(u)*100.0 );
  }

bool  toMBKLayer ( const char*& mbkLayer
                 , const Name&  layerName
                 , bool         isContact =false
                 , bool         isExternal=false
                 )
{
  static bool  firstCall = true;
  static map<const Name,const char*> tableLayer;
  static map<const Name,const char*> tableContact;
  static map<const Name,const char*> tableConnector;

  if ( firstCall ) {
    firstCall = false;

    tableLayer [ "NWELL"  ] = "NWELL";
    tableLayer [ "PWELL"  ] = "PWELL";
    tableLayer [ "NTIE"   ] = "NTIE";
    tableLayer [ "PTIE"   ] = "PTIE";
    tableLayer [ "NDIF"   ] = "NDIF";
    tableLayer [ "PDIF"   ] = "PDIF";
    tableLayer [ "NTRANS" ] = "NTRANS";
    tableLayer [ "PTRANS" ] = "PTRANS";
    tableLayer [ "POLY"   ] = "POLY";
    tableLayer [ "POLY2"  ] = "POLY2";
  
    tableLayer [ "METAL1" ] = "ALU1";
    tableLayer [ "METAL2" ] = "ALU2";
    tableLayer [ "METAL3" ] = "ALU3";
    tableLayer [ "METAL4" ] = "ALU4";
    tableLayer [ "METAL5" ] = "ALU5";
    tableLayer [ "METAL6" ] = "ALU6";
    tableLayer [ "METAL7" ] = "ALU7";
    tableLayer [ "METAL8" ] = "ALU8";

    tableLayer [ "BLOCKAGE1" ] = "TALU1";
    tableLayer [ "BLOCKAGE2" ] = "TALU2";
    tableLayer [ "BLOCKAGE3" ] = "TALU3";
    tableLayer [ "BLOCKAGE4" ] = "TALU4";
    tableLayer [ "BLOCKAGE5" ] = "TALU5";
    tableLayer [ "BLOCKAGE6" ] = "TALU6";
    tableLayer [ "BLOCKAGE7" ] = "TALU7";
    tableLayer [ "BLOCKAGE8" ] = "TALU8";

    tableLayer [ "blockage1" ] = "TALU1";
    tableLayer [ "blockage2" ] = "TALU2";
    tableLayer [ "blockage3" ] = "TALU3";
    tableLayer [ "blockage4" ] = "TALU4";
    tableLayer [ "blockage5" ] = "TALU5";
    tableLayer [ "blockage6" ] = "TALU6";
    tableLayer [ "blockage7" ] = "TALU7";
    tableLayer [ "blockage8" ] = "TALU8";

    tableConnector [ "METAL1" ] = "CALU1";
    tableConnector [ "METAL2" ] = "CALU2";
    tableConnector [ "METAL3" ] = "CALU3";
    tableConnector [ "METAL4" ] = "CALU4";
    tableConnector [ "METAL5" ] = "CALU5";
    tableConnector [ "METAL6" ] = "CALU6";
    tableConnector [ "METAL7" ] = "CALU7";
    tableConnector [ "METAL8" ] = "CALU8";

    tableContact [ "CONT_BODY_N" ] = "CONT_BODY_N";
    tableContact [ "CONT_BODY_P" ] = "CONT_BODY_P";
    tableContact [ "CONT_DIF_N"  ] = "CONT_DIF_N";
    tableContact [ "CONT_DIF_P"  ] = "CONT_DIF_P";
    tableContact [ "CONT_POLY"   ] = "CONT_POLY";
    tableContact [ "CONT_POLY2"  ] = "CONT_POLY2";
    tableContact [ "VIA12"       ] = "CONT_VIA";
    tableContact [ "VIA23"       ] = "CONT_VIA2";
    tableContact [ "VIA34"       ] = "CONT_VIA3";
    tableContact [ "VIA45"       ] = "CONT_VIA4";
    tableContact [ "VIA56"       ] = "CONT_VIA5";
    tableContact [ "VIA67"       ] = "CONT_VIA6";
    tableContact [ "VIA78"       ] = "CONT_VIA7";
    tableContact [ "METAL1"      ] = "CONT_TURN1";
    tableContact [ "METAL2"      ] = "CONT_TURN2";
    tableContact [ "METAL3"      ] = "CONT_TURN3";
    tableContact [ "METAL4"      ] = "CONT_TURN4";
    tableContact [ "METAL5"      ] = "CONT_TURN5";
    tableContact [ "METAL6"      ] = "CONT_TURN6";
    tableContact [ "METAL7"      ] = "CONT_TURN7";
    tableContact [ "METAL8"      ] = "CONT_TURN8";
  }

  map<const Name,const char*>::iterator  it;
  if ( isContact ) {
    it = tableContact.find ( layerName );
    if ( it != tableContact.end() ) {
      mbkLayer = it->second;
      return true;
    }
  }
  if ( isExternal ) {
    it = tableConnector.find ( layerName );
    if ( it != tableConnector.end() ) {
      mbkLayer = it->second;
      return true;
    }
  }
  it = tableLayer.find ( layerName );
  if ( it != tableLayer.end() ) {
    mbkLayer = it->second;
    return true;
  }

  mbkLayer = "UNTRANSLATED";
  return false;
}


string  toMBKName ( const Name& name )
{
  string mbkName = getString(name);

  if ( mbkName.size() && (mbkName[mbkName.size()-1] == ')') ) {
    size_t i = mbkName.find_last_of ( '(' );
    if ( i != string::npos ) {
      mbkName[i] = ' ';
      mbkName.erase ( mbkName.size()-1 );
    }
  }

  return mbkName;
}


void DumpReference(ofstream& ccell, Cell *cell)
{
  for_each_reference(reference, cell->getReferences()) {
    ccell << "R "
          << toMBKlambda(reference->getPoint().getX()) << ","
          << toMBKlambda(reference->getPoint().getY()) << ","
          << "ref_ref,"
          << toMBKName(reference->getName())
          << endl;
    end_for;
  }
}


void DumpContacts(ofstream& ccell, Cell *cell)
{
  const char* mbkLayer;

  for ( Net* net : cell->getNets() ) {
    string netName = toMBKName( net->getName() );
    if (net->isFused()) netName = "*";
    
    for ( Component* component : net->getComponents()) {
      if (Contact* contact = dynamic_cast<Contact*>(component)) {
        if (dynamic_cast<Pin*>(contact))
          continue;
        else {
          if (  (contact->getWidth () <= contact->getLayer()->getMinimalSize())
             or (contact->getHeight() <= contact->getLayer()->getMinimalSize())) {
            if (toMBKLayer(mbkLayer,contact->getLayer()->getName(),true))
              ccell << "V "
                    << toMBKlambda(contact->getX()) << ","
                    << toMBKlambda(contact->getY()) << ","
                    << mbkLayer << ","
                    << netName
                    << endl;
          } else {
            DbU::Unit expand = 0;
            if ( not dynamic_cast<const RegularLayer*>(contact->getLayer()) )
              expand = DbU::lambda(1.0);

            if (toMBKLayer(mbkLayer,contact->getLayer()->getName(),true))
              ccell << "B "
                    << toMBKlambda(contact->getX()) << ","
                    << toMBKlambda(contact->getY()) << ","
                    << toMBKlambda(contact->getWidth () + expand) << ","
                    << toMBKlambda(contact->getHeight() + expand) << ","
                    << mbkLayer << ","
                    << netName
                    << endl;
          }
        }
      }
    } // for(Component*)
  } // for(Net*)
}


  void DumpSegments ( ofstream& ccell, Cell* cell )
  {
    const char* mbkLayer     = NULL;
    DbU::Unit   x1, x2, y1, y2, width;
    Segment*    segment      = NULL;
    RoutingPad* rp           = NULL;
    bool        external     = false;
    const char* direction    = NULL;

    for ( Net* net : cell->getNets() ) {
      string netName = toMBKName( net->getName() );
      if (net->isFused()) netName = "*";
    
      for ( Component* component : net->getComponents() ) {
        direction = NULL;

        if ( (rp = dynamic_cast<RoutingPad*>(component)) ) {
          if (not net->isExternal()) continue;
          if (not cell->isRouted())  continue;

          external = true;
          segment  = dynamic_cast<Segment*>( rp->getOccurrence().getEntity() );
          if (segment) {
            x1           = rp->getSourceX();
            x2           = rp->getTargetX();
            y1           = rp->getSourceY();
            y2           = rp->getTargetY();
            width        = segment->getWidth();
          } else {
            Pin* pin = dynamic_cast<Pin*>( rp->getOccurrence().getEntity() );
            if (pin and (rp->getOccurrence().getPath().getHeadInstance() != NULL)) {
              Box bb ( pin->getBoundingBox() );
              rp->getOccurrence().getPath().getTransformation().applyOn( bb );
            //if (bb.getWidth() > bb.getHeight()) {
              if (  (pin->getAccessDirection() == Pin::AccessDirection::NORTH)
                 or (pin->getAccessDirection() == Pin::AccessDirection::SOUTH)) {
                x1        = bb.getCenter().getX();
                x2        = x1;
                y1        = bb.getCenter().getY();
                y2        = y1;
                width     = bb.getWidth();
                direction = "UP";
              } else {
                x1        = bb.getCenter().getX();
                x2        = x1;
                y1        = bb.getCenter().getY();
                y2        = y1;
                width     = bb.getHeight();
                direction = "RIGHT";
              }
            } else
              continue;
          }
        } else if ( (segment = dynamic_cast<Segment*>(component)) ) {
          external = NetExternalComponents::isExternal( component );
          x1       = segment->getSourceX();
          x2       = segment->getTargetX();
          y1       = segment->getSourceY();
          y2       = segment->getTargetY();
          width    = segment->getWidth();
        } else
          continue;

        if (not direction) {
          direction = "RIGHT";
          if ( (x1 == x2) and (y1 != y2) ) direction = "UP";
        }

        if (x1 > x2) std::swap( x1, x2 );
        if (y1 > y2) std::swap( y1, y2 );

        if (toMBKLayer(mbkLayer,component->getLayer()->getName(),false,external))
          ccell << "S "
                << toMBKlambda(x1) << ","
                << toMBKlambda(y1) << ","
                << toMBKlambda(x2) << ","
                << toMBKlambda(y2) << ","
                << toMBKlambda(width) << ","
                << netName << ","
                << direction << "," 
                << mbkLayer
                << endl;
      }
    }
  }

    
unsigned getPinIndex(Name& pinname)
{
    string pinNameString = getString(pinname);
    string::size_type pointString = pinNameString.find('.');
    if (pointString == string::npos)
        return 0;
    else
    {
        string indexString(pinNameString, pointString + 1, pinNameString.size() - 1);
        pinNameString = string(pinNameString, 0, pointString);
        pinname = Name(pinNameString);
        return atoi(indexString.c_str());
    }
}


void DumpPins(ofstream &ccell, Cell* cell)
{
  const char* mbkLayer = NULL;

  for ( Net* net : cell->getExternalNets() ) {
    vector<Pin*> pins;
    for ( Pin* pin : net->getPins() ) {
      pins.push_back(pin);
    }

    sort( pins.begin(), pins.end(), PinSort() ); 
    set<unsigned> indexesSet;
    for ( Pin* pin : pins  ) {
      if (not toMBKLayer(mbkLayer,pin->getLayer()->getName(),false)) continue;

      Name     pinName (pin->getName());
      unsigned index = getPinIndex(pinName);
      if (pinName != net->getName()) {
        throw Error( "CRL::ApDriver(): Pin \"%s\" and Net \"%s[.index]\" must have the same name to driven in AP format."
                   , getString(pinName).c_str()
                   , getString(net->getName()).c_str() );
      }

      if (indexesSet.find(index) != indexesSet.end()) 
        throw Error( "CRL::ApDriver(): Net \"%s\" has more than one Pin indexed %u."
                   , getString(net->getName()).c_str(), index );

      indexesSet.insert(index);

      DbU::Unit width = 0;
      switch ( pin->getAccessDirection() ) {
        case Pin::AccessDirection::NORTH:
        case Pin::AccessDirection::SOUTH: width = pin->getWidth(); break;
        case Pin::AccessDirection::EAST:
        case Pin::AccessDirection::WEST: width = pin->getHeight(); break;
        default:
          break;
      }

      ccell << "C " << toMBKlambda(pin->getX())
            << ","  << toMBKlambda(pin->getY())
            << ","  << toMBKlambda(width)
            << ","  << toMBKName(pinName)
            << ","  << index
            << ",";
      switch ( pin->getAccessDirection() ) {
        case Pin::AccessDirection::NORTH: ccell << "NORTH"; break;
        case Pin::AccessDirection::SOUTH: ccell << "SOUTH"; break;
        case Pin::AccessDirection::EAST:  ccell << "EAST" ; break;
        case Pin::AccessDirection::WEST:  ccell << "WEST" ; break;
        case Pin::AccessDirection::UNDEFINED:
        default:
          throw Error( "CRL::ApDriver(): Pin \" has undefined access direction."
                     , getString(pin->getName()).c_str() );
      }
      ccell << "," << mbkLayer << endl;
    }
  }
}


void DumpDate(ofstream &ccell)
{
    time_t tim;
    time(&tim);
    struct tm* rest = localtime(&tim);
    ccell << rest->tm_mday
        << "/" << rest->tm_mon+1
        << "/" << rest->tm_year+1900;
}


  void DumpInstances(ofstream &ccell, Cell* cell)
  {
    for ( Instance* instance : cell->getNotUnplacedInstances()) {
      ccell << "I " << toMBKlambda(instance->getAbutmentBox().getXMin())
            << ","  << toMBKlambda(instance->getAbutmentBox().getYMin())
            << ","  << instance->getMasterCell()->getName()
            << ","  << instance->getName()
            << ",";
  
      const Transformation& transformation = instance->getTransformation();
      switch (transformation.getOrientation()) {
        case Transformation::Orientation::ID:
          ccell << "NOSYM";
          break;
        case Transformation::Orientation::R1:
          ccell << "ROT_P";
          break;
        case Transformation::Orientation::R2:
          ccell << "SYMXY";
          break;
        case Transformation::Orientation::R3:
          ccell << "ROT_M";
          break;
        case Transformation::Orientation::MX:
          ccell << "SYM_X"; 
          break;
        case Transformation::Orientation::XR:
          ccell << "SY_RM";
          break;
        case Transformation::Orientation::MY:
          ccell << "SYM_Y"; 
          break;
        case Transformation::Orientation::YR:
          ccell << "SY_RP";
          break;
        default:
          throw Error("Unrecognized orientation in transformation");
      }
      ccell << endl;
    }
  }


}

namespace CRL {
    
void  apDriver( const string cellPath, Cell *cell, unsigned int &saveState) {
    ::std::ofstream ccell ( cellPath.c_str() );

    ccell << "V ALLIANCE : 6" << endl;
    unsigned scaleX = 100;
    ccell << "H " << cell->getName() << ",P,";
    DumpDate(ccell);
    ccell << "," << scaleX << endl;
    const Box& abutmentBox = cell->getAbutmentBox();
    ccell << "A " << toMBKlambda(abutmentBox.getXMin())
          << ","  << toMBKlambda(abutmentBox.getYMin())
          << ","  << toMBKlambda(abutmentBox.getXMax())
          << ","  << toMBKlambda(abutmentBox.getYMax())
          << endl;
    DumpPins(ccell, cell);
    DumpInstances(ccell, cell);
    DumpSegments(ccell, cell);
    DumpContacts(ccell, cell);
    DumpReference(ccell, cell);
    ccell << "EOF" << endl;
    ccell.close ();
    CRL::CatalogExtension::setPhysical(cell, true);
}

}
