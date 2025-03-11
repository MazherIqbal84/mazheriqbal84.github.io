// ****************************************************************************************************
// File: ./HyperNet.cpp
// Authors: R. Escassut
// Copyright (c) BULL S.A. 2000-2018, All Rights Reserved
//
// This file is part of Hurricane.
//
// Hurricane is free software: you can redistribute it  and/or  modify it under the  terms  of the  GNU
// Lesser General Public License as published by the Free Software Foundation, either version 3 of  the
// License, or (at your option) any later version.
//
// Hurricane is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without  even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A  PARTICULAR  PURPOSE. See  the  Lesser  GNU
// General Public License for more details.
//
// You should have received a copy of the Lesser GNU General Public License along  with  Hurricane.  If
// not, see <http://www.gnu.org/licenses/>.
// ****************************************************************************************************

#include "hurricane/HyperNet.h"
#include "hurricane/Cell.h"
#include "hurricane/Net.h"
#include "hurricane/Instance.h"
#include "hurricane/Rubber.h"
#include "hurricane/Plug.h"
#include "hurricane/BasicLayer.h"
#include "hurricane/Error.h"

namespace Hurricane {



// ****************************************************************************************************
// HyperNet_NetOccurrences definition
// ****************************************************************************************************

class HyperNet_NetOccurrences : public Collection<Occurrence> {
// ********************************************************

// Types
// *****

    public: typedef Collection<Occurrence> Inherit;

    public: class Locator : public Hurricane::Locator<Occurrence> {
    // *********************************************************

        public: typedef Hurricane::Locator<Occurrence> Inherit;

        private: const HyperNet* _hyperNet;
        private: bool _doExtraction;
        private: bool _allowInterruption;
        private: set<Occurrence> _netOccurrenceSet;
        private: stack<Occurrence> _netOccurrenceStack;

        public: Locator();
        public: Locator(const HyperNet* hyperNet, bool doExtraction = false, bool allowInterruption = false);
        public: Locator(const Locator& locator);

        public: Locator& operator=(const Locator& locator);

        public: virtual Occurrence getElement() const;
        public: virtual Hurricane::Locator<Occurrence>* getClone() const;

        public: virtual bool isValid() const;

        public: virtual void progress();

        public: virtual string _getString() const;

    };

// Attributes
// **********

    private: const HyperNet* _hyperNet;
    private: bool _doExtraction;
    private: bool _allowInterruption;

// Constructors
// ************

    public: HyperNet_NetOccurrences();
    public: HyperNet_NetOccurrences(const HyperNet* hyperNet, bool doExtraction = false, bool allowInterruption = false);
    public: HyperNet_NetOccurrences(const HyperNet_NetOccurrences& netOccurrences);

// Operators
// *********

    public: HyperNet_NetOccurrences& operator=(const HyperNet_NetOccurrences& netOccurrences);

// Accessors
// *********

    public: virtual Collection<Occurrence>* getClone() const;
    public: virtual Hurricane::Locator<Occurrence>* getLocator() const;

// Others
// ******

    public: virtual string _getString() const;

};

// ****************************************************************************************************
// HyperNet_NetOccurrencesUnder definition
// ****************************************************************************************************

class HyperNet_NetOccurrencesUnder : public Collection<Occurrence> {
// ***************************************************************

// Types
// *****

    public: typedef Collection<Occurrence> Inherit;

    public: class Locator : public Hurricane::Locator<Occurrence> {
    // *********************************************************

        public: typedef Hurricane::Locator<Occurrence> Inherit;

        private: const HyperNet* _hyperNet;
        private: Box  _area;
        private: bool _doExtraction;
        private: bool _allowInterruption;
        private: set<Occurrence> _netOccurrenceSet;
        private: stack<Occurrence> _netOccurrenceStack;

        public: Locator();
        public: Locator(const HyperNet* hyperNet
                       , Box area
                       , bool doExtraction = false
                       , bool allowInterruption = false);
        public: Locator(const Locator& locator);

        public: Locator& operator=(const Locator& locator);

        public: virtual Occurrence getElement() const;
        public: virtual Hurricane::Locator<Occurrence>* getClone() const;

        public: virtual bool isValid() const;

        public: virtual void progress();

        public: virtual string _getString() const;

    };

// Attributes
// **********

    private: const HyperNet* _hyperNet;
    private: Box  _area;
    private: bool _doExtraction;
    private: bool _allowInterruption;

// Constructors
// ************

    public: HyperNet_NetOccurrencesUnder();
    public: HyperNet_NetOccurrencesUnder(const HyperNet* hyperNet,
                                                    Box area,
                                                    bool doExtraction = false,
                                                    bool allowInterruption = false);
    public: HyperNet_NetOccurrencesUnder(const HyperNet_NetOccurrencesUnder& netOccurrences);

// Operators
// *********

    public: HyperNet_NetOccurrencesUnder& operator=(const HyperNet_NetOccurrencesUnder& netOccurrences);

// Accessors
// *********

    public: virtual Collection<Occurrence>* getClone() const;
    public: virtual Hurricane::Locator<Occurrence>* getLocator() const;

// Others
// ******

    public: virtual string _getString() const;

};


// ****************************************************************************************************
// HyperNet_TerminalNetlistPlugOccurrences definition
// ****************************************************************************************************

class HyperNet_TerminalNetlistPlugOccurrences : public Collection<Occurrence> {
// *****************************************************************

// Types
// *****

    public: typedef Collection<Occurrence> Inherit;

    public: class Locator : public Hurricane::Locator<Occurrence> {
    // *********************************************************

        public: typedef Hurricane::Locator<Occurrence> Inherit;

        private: OccurrenceLocator _netOccurrenceLocator;
        private: Occurrence _plugOccurrence;

        public: Locator();
        public: Locator(const HyperNet* hyperNet, bool doExtraction = false, bool allowInterruption = false);
        public: Locator(const Locator& locator);

        public: Locator& operator=(const Locator& locator);

        public: virtual Occurrence getElement() const;
        public: virtual Hurricane::Locator<Occurrence>* getClone() const;

        public: virtual bool isValid() const;

        public: virtual void progress();

        public: virtual string _getString() const;

    };

// Attributes
// **********

    private: const HyperNet* _hyperNet;
    private: bool _doExtraction;
    private: bool _allowInterruption;

// Constructors
// ************

    public: HyperNet_TerminalNetlistPlugOccurrences();
    public: HyperNet_TerminalNetlistPlugOccurrences(const HyperNet* hyperNet, bool doExtraction = false, bool allowInterruption = false);
    public: HyperNet_TerminalNetlistPlugOccurrences(const HyperNet_TerminalNetlistPlugOccurrences& netOccurrences);

// Operators
// *********

    public: HyperNet_TerminalNetlistPlugOccurrences& operator=(const HyperNet_TerminalNetlistPlugOccurrences& netOccurrences);

// Accessors
// *********

    public: virtual Collection<Occurrence>* getClone() const;
    public: virtual Hurricane::Locator<Occurrence>* getLocator() const;

// Others
// ******

    public: virtual string _getString() const;

};


// ****************************************************************************************************
// HyperNet_ComponentOccurrences definition
// ****************************************************************************************************

class HyperNet_ComponentOccurrences : public Collection<Occurrence> {
// *****************************************************************

// Types
// *****

    public: typedef Collection<Occurrence> Inherit;

    public: class Locator : public Hurricane::Locator<Occurrence> {
    // *********************************************************

        public: typedef Hurricane::Locator<Occurrence> Inherit;

        private: bool _withTerminalNetlistCells;
        private: OccurrenceLocator _netOccurrenceLocator;
        private: ComponentLocator _componentLocator;
        private: Occurrence _componentOccurrence;

        public: Locator();
        public: Locator(const HyperNet* hyperNet, bool withTerminalNetlistCells = false, bool doExtraction = false, bool allowInterruption = false);
        public: Locator(const Locator& locator);

        public: Locator& operator=(const Locator& locator);

        public: virtual Occurrence getElement() const;
        public: virtual Hurricane::Locator<Occurrence>* getClone() const;

        public: virtual bool isValid() const;

        public: virtual void progress();

        public: virtual string _getString() const;

    };

// Attributes
// **********

    private: const HyperNet* _hyperNet;
    private: bool _withTerminalNetlistCells;
    private: bool _doExtraction;
    private: bool _allowInterruption;

// Constructors
// ************

    public: HyperNet_ComponentOccurrences();
    public: HyperNet_ComponentOccurrences(const HyperNet* hyperNet, bool withTerminalNetlistCells = false, bool doExtraction = false, bool allowInterruption = false);
    public: HyperNet_ComponentOccurrences(const HyperNet_ComponentOccurrences& componentOccurrences);

// Operators
// *********

    public: HyperNet_ComponentOccurrences& operator=(const HyperNet_ComponentOccurrences& componentOccurrences);

// Accessors
// *********

    public: virtual Collection<Occurrence>* getClone() const;
    public: virtual Hurricane::Locator<Occurrence>* getLocator() const;

// Others
// ******

    public: virtual string _getString() const;

};


// ****************************************************************************************************
// HyperNet implementation
// ****************************************************************************************************

HyperNet::HyperNet(const Occurrence& occurrence)
// *********************************************
  : _netOccurrence(occurrence.getNetOccurrence())
{
  if (not occurrence.isValid()) 
    throw Error("Can't create " + _TName("HyperNet") + " : bad occurrence entity type");
}


HyperNet::HyperNet(const HyperNet& other)
// *********************************************
  : _netOccurrence(other._netOccurrence)
{
}


Occurrences HyperNet::getNetOccurrences(bool doExtraction, bool allowInterruption) const
// ***********************************************************************************
{
    return HyperNet_NetOccurrences(this, doExtraction, allowInterruption);
}

Occurrences HyperNet::getNetOccurrencesUnder(Box area, bool doExtraction, bool allowInterruption) const
// **************************************************************************************************
{
    return HyperNet_NetOccurrencesUnder(this, area, doExtraction, allowInterruption);
}

Occurrences HyperNet::getTerminalNetlistPlugOccurrences(bool doExtraction, bool allowInterruption) const
// ********************************************************************************************
{
    return HyperNet_TerminalNetlistPlugOccurrences(this, doExtraction, allowInterruption);
}

Occurrences HyperNet::getComponentOccurrences(bool doExtraction, bool allowInterruption) const
// *******************************************************************************************
{
  return HyperNet_ComponentOccurrences(this, false, doExtraction, allowInterruption);
}

string HyperNet::_getString() const
// ********************************
{
    string s = "<" + _TName("HyperNet");
    if (isValid()) s += " " + getString(_netOccurrence);
    s += ">";
    return s;
}

Record* HyperNet::_getRecord() const
// ***************************
{
     Record* record = new Record(getString(this));
    if (record) {
        record->add(getSlot("NetOccurrence", &_netOccurrence));
    }
    return record;
}

Occurrence getHyperNetRootNetOccurrence(const Occurrence& netoccurrence)
// *********************************************************************
{
    if (!netoccurrence.isValid())
        throw Error("getHyperNetRootNetOccurrence : invalid occurrence");
    
    Net* net = dynamic_cast<Net*>(netoccurrence.getEntity());
    if (!net)
        throw Error("getHyperNetRootNetOccurrence : not a net occurrence");
    
    if (!net->isExternal())
        return netoccurrence;

    Path path = netoccurrence.getPath();
    
    if (path.isEmpty())
        return netoccurrence;
    
    Instance* instance = path.getTailInstance();

    Plug* plug = instance->getPlug(net);
    if (!plug)
        throw Error("getHyperNetRootNetOccurrence : no plug for external net !");
    
    if(!plug->isConnected())
        return netoccurrence;
    
    return getHyperNetRootNetOccurrence(Occurrence(plug->getNet(), path.getHeadPath()));
}


bool isHyperNetRootNetOccurrence(Occurrence netoccurrence)
// *******************************************************
{
    Net* net=dynamic_cast<Net*>(netoccurrence.getEntity());
    if (!net) return false;
    if (net->isAutomatic() )               return false;
    if (!net->isExternal())                return true;
    if (netoccurrence.getPath().isEmpty()) return true;
    if (net->isGlobal())                   return false;
    if (!netoccurrence.getPath().getTailInstance()->getPlug(net)->isConnected())
                                           return true;
    return false;
}



// ****************************************************************************************************
// HyperNet_NetOccurrences implementation
// ****************************************************************************************************

HyperNet_NetOccurrences::HyperNet_NetOccurrences()
// *********************************************
:     Inherit(),
    _hyperNet(NULL),
    _doExtraction(false),
    _allowInterruption(false)
{
}

HyperNet_NetOccurrences::HyperNet_NetOccurrences(const HyperNet* hyperNet, bool doExtraction, bool allowInterruption)
// ****************************************************************************************************
:     Inherit(),
    _hyperNet(hyperNet),
    _doExtraction(doExtraction),
    _allowInterruption(allowInterruption)
{
}

HyperNet_NetOccurrences::HyperNet_NetOccurrences(const HyperNet_NetOccurrences& netOccurrences)
// ****************************************************************************************
:     Inherit(),
    _hyperNet(netOccurrences._hyperNet),
    _doExtraction(netOccurrences._doExtraction),
    _allowInterruption(netOccurrences._allowInterruption)
{
}

HyperNet_NetOccurrences& HyperNet_NetOccurrences::operator=(const HyperNet_NetOccurrences& netOccurrences)
// ***************************************************************************************************
{
    _hyperNet = netOccurrences._hyperNet;
    _doExtraction = netOccurrences._doExtraction;
    _allowInterruption = netOccurrences._allowInterruption;
    return *this;
}

Collection<Occurrence>* HyperNet_NetOccurrences::getClone() const
// ************************************************************
{
    return new HyperNet_NetOccurrences(*this);
}

Locator<Occurrence>* HyperNet_NetOccurrences::getLocator() const
// ***********************************************************
{
    return new Locator(_hyperNet, _doExtraction, _allowInterruption);
}

string HyperNet_NetOccurrences::_getString() const
// **********************************************
{
    string s = "<" + _TName("HyperNet::NetOccurrences");
    if (_hyperNet) {
        s += " " + getString(_hyperNet);
        if (_doExtraction) {
            s += " DO_EXTRACTION";
            if (_allowInterruption) s += " ALLOW_INTERRUPTION";
        }
    }
    s += ">";
    return s;
}



// ****************************************************************************************************
// HyperNet_NetOccurrences::Locator implementation
// ****************************************************************************************************

HyperNet_NetOccurrences::Locator::Locator()
// ***************************************
:    Inherit(),
    _hyperNet(NULL),
    _doExtraction(false),
    _allowInterruption(false),
    _netOccurrenceSet(),
    _netOccurrenceStack()
{
}

HyperNet_NetOccurrences::Locator::Locator(const HyperNet* hyperNet, bool doExtraction, bool allowInterruption)
// ****************************************************************************************************
:    Inherit(),
    _hyperNet(hyperNet),
    _doExtraction(doExtraction),
    _allowInterruption(allowInterruption),
    _netOccurrenceSet(),
    _netOccurrenceStack()
{
    if (_hyperNet) {
        Occurrence netOccurrence = _hyperNet->getNetOccurrence();
        if (netOccurrence.isValid()) {
            _netOccurrenceSet.insert(netOccurrence);
            _netOccurrenceStack.push(netOccurrence);
        }
    }
}

HyperNet_NetOccurrences::Locator::Locator(const Locator& locator)
// *************************************************************
:    Inherit(),
    _hyperNet(locator._hyperNet),
    _doExtraction(locator._doExtraction),
    _allowInterruption(locator._allowInterruption),
    _netOccurrenceSet(locator._netOccurrenceSet),
    _netOccurrenceStack(locator._netOccurrenceStack)
{
}

HyperNet_NetOccurrences::Locator& HyperNet_NetOccurrences::Locator::operator=(const Locator& locator)
// ************************************************************************************************
{
    _hyperNet = locator._hyperNet;
    _doExtraction = locator._doExtraction;
    _allowInterruption = locator._allowInterruption;
    _netOccurrenceSet = locator._netOccurrenceSet;
    _netOccurrenceStack = locator._netOccurrenceStack;
    return *this;
}

Occurrence HyperNet_NetOccurrences::Locator::getElement() const
// **********************************************************
{
    return (!_netOccurrenceStack.empty()) ? _netOccurrenceStack.top() : Occurrence();
}

Locator<Occurrence>* HyperNet_NetOccurrences::Locator::getClone() const
// ******************************************************************
{
    return new Locator(*this);
}

bool HyperNet_NetOccurrences::Locator::isValid() const
// **************************************************
{
    return !_netOccurrenceStack.empty();
}

static bool IsConnex(const Occurrence& componentOccurrence1, const Occurrence& componentOccurrence2)
// *********************************************************************************************
{
    Component* component1 = (Component*)componentOccurrence1.getEntity();
    Component* component2 = (Component*)componentOccurrence2.getEntity();
    const Layer* layer1 = component1->getLayer();
    const Layer* layer2 = component2->getLayer();
    if (layer1->getExtractMask() & layer2->getExtractMask()) {
        Transformation transformation1 = componentOccurrence1.getPath().getTransformation();
        Transformation transformation2 = componentOccurrence2.getPath().getTransformation();
        for_each_basic_layer(basicLayer1, layer1->getBasicLayers()) {
            Box box1 = transformation1.getBox(component1->getBoundingBox(basicLayer1));
            for_each_basic_layer(basicLayer2, layer2->getBasicLayers()) {
                if (basicLayer1->getExtractMask() & basicLayer2->getExtractMask()) {
                    Box box2 = transformation2.getBox(component2->getBoundingBox(basicLayer2));
                    if (box1.intersect(box2)) return true;
                }
                end_for;
            }
            end_for;
        }
    }
    return false;
}

void HyperNet_NetOccurrences::Locator::progress()
// **********************************************
{
    if (not _netOccurrenceStack.empty()) {
      Occurrence netOccurrence = _netOccurrenceStack.top();
      _netOccurrenceStack.pop();
      Net* net = (Net*)netOccurrence.getEntity();
      Path path = netOccurrence.getPath();

      if (_doExtraction) {
        Cell* cell = netOccurrence.getOwnerCell();
        for ( Component* component : net->getComponents()) {
          if (not dynamic_cast<Plug*>(component)) {
          //if (_allowInterruption && !((i++) % 200)) gtk_check_for_interruption();
            Occurrence occurrence = Occurrence( component, path );
            Box        area       = occurrence.getBoundingBox();

            for ( Occurrence occurrence2 : cell->getOccurrencesUnder(area)) {
              if (dynamic_cast<Component*>(occurrence2.getEntity())) {
                Component* component2 = static_cast<Component*>( occurrence2.getEntity() );

                if (IsConnex(occurrence,occurrence2)) {
                  Occurrence net2Occurrence =
                    Occurrence( component2->getNet(), occurrence2.getPath() );
                  
                  if (_netOccurrenceSet.find(net2Occurrence) == _netOccurrenceSet.end()) {
                    _netOccurrenceSet.insert(net2Occurrence);
                    _netOccurrenceStack.push(net2Occurrence);
                  }
                }
              }
            }  // for occurence2.
          }
        } // for component*.
      }

      if (not net->getCell()->isTerminalNetlist()) {
        for ( Plug* plug : net->getPlugs() ) {
          Occurrence occurrence = Occurrence( plug->getMasterNet(), Path(path, plug->getInstance()) );

          if (_netOccurrenceSet.find(occurrence) == _netOccurrenceSet.end()) {
            _netOccurrenceSet.insert(occurrence);
            _netOccurrenceStack.push(occurrence);
          }
        }
      }

      if (net->isExternal()) {
        Instance* instance = path.getTailInstance();
        if (instance) {
          Plug* plug = instance->getPlug(net);
          if (plug) {
            Net* net = plug->getNet();
            if (net) {
              Occurrence occurrence = Occurrence(net, path.getHeadPath());
              if (_netOccurrenceSet.find(occurrence) == _netOccurrenceSet.end()) {
                _netOccurrenceSet.insert(occurrence);
                _netOccurrenceStack.push(occurrence);
              }
            }
          }
        }
      } // if net->isExternal().
    }
}

string HyperNet_NetOccurrences::Locator::_getString() const
// *******************************************************
{
    string s = "<" + _TName("HyperNet::NetOccurrences::Locator");
    if (_hyperNet) {
        s += " " + getString(_hyperNet);
        if (_doExtraction) {
            s += " DO_EXTRACTION";
            if (_allowInterruption) s += " ALLOW_INTERRUPTION";
        }
    }
    s += ">";
    return s;
}

// ****************************************************************************************************
// HyperNet_NetOccurrencesUnder implementation
// ****************************************************************************************************

HyperNet_NetOccurrencesUnder::HyperNet_NetOccurrencesUnder()
// *******************************************************
:     Inherit(),
        _hyperNet(NULL),
        _area(),
        _doExtraction(false),
        _allowInterruption(false)
{
}

HyperNet_NetOccurrencesUnder::HyperNet_NetOccurrencesUnder(const HyperNet* hyperNet,
                                                                             Box area,  bool doExtraction,
                                                                             bool allowInterruption)
// ***********************************************************************************
:     Inherit(),
        _hyperNet(hyperNet),
        _area(area),
        _doExtraction(doExtraction),
        _allowInterruption(allowInterruption)
{
}

HyperNet_NetOccurrencesUnder::HyperNet_NetOccurrencesUnder(const HyperNet_NetOccurrencesUnder& netOccurrences)
// *******************************************************************************************************
:     Inherit(),
        _hyperNet(netOccurrences._hyperNet),
        _area(netOccurrences._area),
        _doExtraction(netOccurrences._doExtraction),
        _allowInterruption(netOccurrences._allowInterruption)
{
}

HyperNet_NetOccurrencesUnder& HyperNet_NetOccurrencesUnder::operator=(const HyperNet_NetOccurrencesUnder& netOccurrences)
// ******************************************************************************************************************
{
    _hyperNet = netOccurrences._hyperNet;
    _area = netOccurrences._area;
    _doExtraction = netOccurrences._doExtraction;
    _allowInterruption = netOccurrences._allowInterruption;
    return *this;
}

Collection<Occurrence>* HyperNet_NetOccurrencesUnder::getClone() const
// *****************************************************************
{
    return new HyperNet_NetOccurrencesUnder(*this);
}

Locator<Occurrence>* HyperNet_NetOccurrencesUnder::getLocator() const
// ****************************************************************
{
    return new Locator(_hyperNet, _area, _doExtraction, _allowInterruption);
}

string HyperNet_NetOccurrencesUnder::_getString() const
// ***************************************************
{
    string s = "<" + _TName("HyperNet::NetOccurrences");
    if (_hyperNet) {
        s += " " + getString(_hyperNet);
        if (_doExtraction) {
            s += " DO_EXTRACTION";
            if (_allowInterruption) s += " ALLOW_INTERRUPTION";
        }
    }
    s += ">";
    return s;
}



// ****************************************************************************************************
// HyperNet_NetOccurrencesUnder::Locator implementation
// ****************************************************************************************************

HyperNet_NetOccurrencesUnder::Locator::Locator()
// ********************************************
:    Inherit(),
    _hyperNet(NULL),
    _area(),
    _doExtraction(false),
    _allowInterruption(false),
    _netOccurrenceSet(),
    _netOccurrenceStack()
{
}

HyperNet_NetOccurrencesUnder::Locator::Locator(const HyperNet* hyperNet, Box area,
                                                                bool doExtraction, bool allowInterruption)
// *************************************************************************************
:    Inherit(),
    _hyperNet(hyperNet),
    _area(area),
    _doExtraction(doExtraction),
    _allowInterruption(allowInterruption),
    _netOccurrenceSet(),
    _netOccurrenceStack()
{
    if (_hyperNet) {
        Occurrence netOccurrence = _hyperNet->getNetOccurrence();
        if (netOccurrence.isValid()) {
            _netOccurrenceSet.insert(netOccurrence);
            _netOccurrenceStack.push(netOccurrence);
        }
    }
}

HyperNet_NetOccurrencesUnder::Locator::Locator(const Locator& locator)
// ******************************************************************
:    Inherit(),
    _hyperNet(locator._hyperNet),
    _area(locator._area),
    _doExtraction(locator._doExtraction),
    _allowInterruption(locator._allowInterruption),
    _netOccurrenceSet(locator._netOccurrenceSet),
    _netOccurrenceStack(locator._netOccurrenceStack)
{
}

HyperNet_NetOccurrencesUnder::Locator& HyperNet_NetOccurrencesUnder::Locator::operator=(const Locator& locator)
// **********************************************************************************************************
{
    _hyperNet = locator._hyperNet;
    _area = locator._area;
    _doExtraction = locator._doExtraction;
    _allowInterruption = locator._allowInterruption;
    _netOccurrenceSet = locator._netOccurrenceSet;
    _netOccurrenceStack = locator._netOccurrenceStack;
    return *this;
}

Occurrence HyperNet_NetOccurrencesUnder::Locator::getElement() const
// ***************************************************************
{
    return (!_netOccurrenceStack.empty()) ? _netOccurrenceStack.top() : Occurrence();
}

Locator<Occurrence>* HyperNet_NetOccurrencesUnder::Locator::getClone() const
// ***********************************************************************
{
    return new Locator(*this);
}

bool HyperNet_NetOccurrencesUnder::Locator::isValid() const
// *******************************************************
{
    return !_netOccurrenceStack.empty();
}

void HyperNet_NetOccurrencesUnder::Locator::progress()
// **************************************************
{
    if (!_netOccurrenceStack.empty()) {
        Occurrence netOccurrence = _netOccurrenceStack.top();
        _netOccurrenceStack.pop();
        Net* net = (Net*)netOccurrence.getEntity();
        Path path = netOccurrence.getPath();

        if (_doExtraction) {
            Cell* cell = netOccurrence.getOwnerCell();
            for_each_component(component, net->getComponents()) {
                Occurrence occurrence = Occurrence(component, path);
                Box area = occurrence.getBoundingBox();
                if (! area.intersect (_area)) {
                    // Outside useful area
                } else if (dynamic_cast<Plug*>(component)) {
                    // Will be  processed below
                } else if (dynamic_cast<Rubber*>(component)) {
                    // Don't go through the Rubbers (go only trough connecting layers)
                } else {
                    //if (_allowInterruption && !((i++) % 200)) gtk_check_for_interruption();
                    Box under = area.getIntersection (_area);
                    for_each_occurrence(occurrence2, cell->getOccurrencesUnder(under)) {
                        if (dynamic_cast<Component*>(occurrence2.getEntity())) {
                            Component* component2 = (Component*)occurrence2.getEntity();
                            if (IsConnex(occurrence, occurrence2)) {
                                Occurrence net2Occurrence =
                                    Occurrence(component2->getNet(), occurrence2.getPath());
                                if (_netOccurrenceSet.find(net2Occurrence) == _netOccurrenceSet.end()) {
                                    _netOccurrenceSet.insert(net2Occurrence);
                                    _netOccurrenceStack.push(net2Occurrence);
                                }
                            }
                        }
                        end_for;
                    }
                }
                end_for;
            }
        }

        for_each_plug(plug, net->getPlugs()) {
            Occurrence occurrence = Occurrence(plug->getMasterNet(), Path(path, plug->getInstance()));
            if (_netOccurrenceSet.find(occurrence) == _netOccurrenceSet.end()) {
                _netOccurrenceSet.insert(occurrence);
                _netOccurrenceStack.push(occurrence);
            }
            end_for;
        }

        if (net->isExternal()) {
            Instance* instance = path.getTailInstance();
            if (instance) {
                Plug* plug = instance->getPlug(net);
                if (plug) {
                    Net* net = plug->getNet();
                    if (net) {
                        Occurrence occurrence = Occurrence(net, path.getHeadPath());
                        if (_netOccurrenceSet.find(occurrence) == _netOccurrenceSet.end()) {
                            _netOccurrenceSet.insert(occurrence);
                            _netOccurrenceStack.push(occurrence);
                        }
                    }
                }
            }
        }
    }
}

string HyperNet_NetOccurrencesUnder::Locator::_getString() const
// ***********************************************************
{
    string s = "<" + _TName("HyperNet::NetOccurrences::Locator");
    if (_hyperNet) {
        s += " " + getString(_hyperNet);
        if (_doExtraction) {
            s += " DO_EXTRACTION";
            if (_allowInterruption) s += " ALLOW_INTERRUPTION";
        }
    }
    s += ">";
    return s;
}

// ****************************************************************************************************
// HyperNet_TerminalNetlistPlugOccurrences implementation
// ****************************************************************************************************

HyperNet_TerminalNetlistPlugOccurrences::HyperNet_TerminalNetlistPlugOccurrences()
// *********************************************
:     Inherit(),
    _hyperNet(NULL),
    _doExtraction(false),
    _allowInterruption(false)
{
}

HyperNet_TerminalNetlistPlugOccurrences::HyperNet_TerminalNetlistPlugOccurrences(const HyperNet* hyperNet, bool doExtraction, bool allowInterruption)
// ****************************************************************************************************
:     Inherit(),
    _hyperNet(hyperNet),
    _doExtraction(doExtraction),
    _allowInterruption(allowInterruption)
{
}

HyperNet_TerminalNetlistPlugOccurrences::HyperNet_TerminalNetlistPlugOccurrences(const HyperNet_TerminalNetlistPlugOccurrences& netOccurrences)
// ****************************************************************************************
:     Inherit(),
    _hyperNet(netOccurrences._hyperNet),
    _doExtraction(netOccurrences._doExtraction),
    _allowInterruption(netOccurrences._allowInterruption)
{
}

HyperNet_TerminalNetlistPlugOccurrences& HyperNet_TerminalNetlistPlugOccurrences::operator=(const HyperNet_TerminalNetlistPlugOccurrences& netOccurrences)
// ***************************************************************************************************
{
    _hyperNet = netOccurrences._hyperNet;
    _doExtraction = netOccurrences._doExtraction;
    _allowInterruption = netOccurrences._allowInterruption;
    return *this;
}

Collection<Occurrence>* HyperNet_TerminalNetlistPlugOccurrences::getClone() const
// ************************************************************
{
    return new HyperNet_TerminalNetlistPlugOccurrences(*this);
}

Locator<Occurrence>* HyperNet_TerminalNetlistPlugOccurrences::getLocator() const
// ***********************************************************
{
    return new Locator(_hyperNet, _doExtraction, _allowInterruption);
}

string HyperNet_TerminalNetlistPlugOccurrences::_getString() const
// **********************************************
{
    string s = "<" + _TName("HyperNet::TerminalNetlistPlugOccurrences");
    if (_hyperNet) {
        s += " " + getString(_hyperNet);
        if (_doExtraction) {
            s += " DO_EXTRACTION";
            if (_allowInterruption) s += " ALLOW_INTERRUPTION";
        }
    }
    s += ">";
    return s;
}



// ****************************************************************************************************
// HyperNet_TerminalNetlistPlugOccurrences::Locator implementation
// ****************************************************************************************************

HyperNet_TerminalNetlistPlugOccurrences::Locator::Locator ()
  : Inherit()
  , _netOccurrenceLocator()
  , _plugOccurrence()
{ }


HyperNet_TerminalNetlistPlugOccurrences::Locator::Locator ( const HyperNet* hyperNet
                                                          ,       bool      doExtraction
                                                          ,       bool      allowInterruption )
  : Inherit()
  , _netOccurrenceLocator()
  , _plugOccurrence()
{
  if (hyperNet) {
    _netOccurrenceLocator = hyperNet->getNetOccurrences( doExtraction
                                                       , allowInterruption ).getLocator();
    progress();
  }
}


HyperNet_TerminalNetlistPlugOccurrences::Locator::Locator ( const Locator& locator )
  : Inherit()
  , _netOccurrenceLocator()
  , _plugOccurrence()
{ }


HyperNet_TerminalNetlistPlugOccurrences::Locator& HyperNet_TerminalNetlistPlugOccurrences::Locator::operator= ( const Locator& locator )
{
  _netOccurrenceLocator = locator._netOccurrenceLocator;
  _plugOccurrence       = locator._plugOccurrence;
  return *this;
}


Occurrence  HyperNet_TerminalNetlistPlugOccurrences::Locator::getElement () const
{ return _plugOccurrence; }


Locator<Occurrence>* HyperNet_TerminalNetlistPlugOccurrences::Locator::getClone () const
{ return new Locator( *this ); }


bool  HyperNet_TerminalNetlistPlugOccurrences::Locator::isValid () const
{ return _plugOccurrence.isValid(); }


void HyperNet_TerminalNetlistPlugOccurrences::Locator::progress ()
{
  _plugOccurrence = Occurrence();
  while(_netOccurrenceLocator.isValid() and not _plugOccurrence.isValid()) {
    Occurrence netOccurrence = _netOccurrenceLocator.getElement();

    _netOccurrenceLocator.progress();
    Net* net  = static_cast<Net*>( netOccurrence.getEntity() );
    Path path = netOccurrence.getPath();

    if (not path.isEmpty() and net->getCell()->isTerminalNetlist()) {
      Instance* instance = path.getTailInstance();
      Plug*     plug     = instance->getPlug(net);
      if (plug)
        _plugOccurrence = Occurrence( plug,path.getHeadPath() );
    }
  }
}


string  HyperNet_TerminalNetlistPlugOccurrences::Locator::_getString () const
{
  string s = "<" + _TName("HyperNet::TerminalNetlistPlugOccurrences::Locator");
  s += " " + getString(_netOccurrenceLocator);
  s += ">";
  return s;
}


// ****************************************************************************************************
// HyperNet_ComponentOccurrences implementation
// ****************************************************************************************************

HyperNet_ComponentOccurrences::HyperNet_ComponentOccurrences()
// ***********************************************************
:     Inherit(),
    _hyperNet(NULL),
    _withTerminalNetlistCells(false),
    _doExtraction(false),
    _allowInterruption(false)
{
}

  HyperNet_ComponentOccurrences::HyperNet_ComponentOccurrences(const HyperNet* hyperNet, bool withTerminalNetlistCells, bool doExtraction, bool allowInterruption)
// ****************************************************************************************************************************************************
:     Inherit(),
    _hyperNet(hyperNet),
    _withTerminalNetlistCells(withTerminalNetlistCells),
    _doExtraction(doExtraction),
    _allowInterruption(allowInterruption)
{
}

HyperNet_ComponentOccurrences::HyperNet_ComponentOccurrences(const HyperNet_ComponentOccurrences& netOccurrences)
// **************************************************************************************************************
:     Inherit(),
    _hyperNet(netOccurrences._hyperNet),
    _withTerminalNetlistCells(netOccurrences._withTerminalNetlistCells),
    _doExtraction(netOccurrences._doExtraction),
    _allowInterruption(netOccurrences._allowInterruption)
{
}

HyperNet_ComponentOccurrences& HyperNet_ComponentOccurrences::operator=(const HyperNet_ComponentOccurrences& netOccurrences)
// *************************************************************************************************************************
{
    _hyperNet = netOccurrences._hyperNet;
    _withTerminalNetlistCells = netOccurrences._withTerminalNetlistCells;
    _doExtraction = netOccurrences._doExtraction;
    _allowInterruption = netOccurrences._allowInterruption;
    return *this;
}

Collection<Occurrence>* HyperNet_ComponentOccurrences::getClone() const
// ********************************************************************
{
    return new HyperNet_ComponentOccurrences(*this);
}

Locator<Occurrence>* HyperNet_ComponentOccurrences::getLocator() const
// *******************************************************************
{
  return new Locator(_hyperNet, _withTerminalNetlistCells, _doExtraction, _allowInterruption);
}

string HyperNet_ComponentOccurrences::_getString() const
// *****************************************************
{
    string s = "<" + _TName("HyperNet::ComponentOccurrences");
    if (_hyperNet) {
        s += " " + getString(_hyperNet);
        if (_withTerminalNetlistCells) {
          s += " LEAFS";
          if (_doExtraction) {
            s += " DO_EXTRACTION";
            if (_allowInterruption) s += " ALLOW_INTERRUPTION";
          }
        }
    }
    s += ">";
    return s;
}



// ****************************************************************************************************
// HyperNet_ComponentOccurrences::Locator implementation
// ****************************************************************************************************

HyperNet_ComponentOccurrences::Locator::Locator()
// **********************************************
:    Inherit(),
    _netOccurrenceLocator(),
    _componentLocator(),
    _componentOccurrence()
    
{
}

HyperNet_ComponentOccurrences::Locator::Locator(const HyperNet* hyperNet, bool withTerminalNetlistCells, bool doExtraction, bool allowInterruption)
// *************************************************************************************************************************************
:    Inherit(),
    _withTerminalNetlistCells(withTerminalNetlistCells),
    _netOccurrenceLocator(),
    _componentLocator(),
    _componentOccurrence()
{
    if (hyperNet) {
        _netOccurrenceLocator = hyperNet->getNetOccurrences(doExtraction,allowInterruption).getLocator();
        progress();
    }
}

HyperNet_ComponentOccurrences::Locator::Locator(const Locator& locator)
// ********************************************************************
:    Inherit(),
    _withTerminalNetlistCells(locator._withTerminalNetlistCells),
    _netOccurrenceLocator(locator._netOccurrenceLocator),
    _componentLocator(locator._componentLocator),
    _componentOccurrence(locator._componentOccurrence)
{
}

HyperNet_ComponentOccurrences::Locator& HyperNet_ComponentOccurrences::Locator::operator=(const Locator& locator)
// **************************************************************************************************************
{
    _withTerminalNetlistCells = locator._withTerminalNetlistCells;
    _netOccurrenceLocator = locator._netOccurrenceLocator;
    _componentLocator = locator._componentLocator;
    _componentOccurrence = locator._componentOccurrence;
    return *this;
}

Occurrence HyperNet_ComponentOccurrences::Locator::getElement() const
// ******************************************************************
{
    return _componentOccurrence;
}

Locator<Occurrence>* HyperNet_ComponentOccurrences::Locator::getClone() const
// **************************************************************************
{
    return new Locator(*this);
}

bool HyperNet_ComponentOccurrences::Locator::isValid() const
// *********************************************************
{
    return _componentOccurrence.isValid();
}


void HyperNet_ComponentOccurrences::Locator::progress()
// ****************************************************
{
  _componentOccurrence = Occurrence();
  while ( not _componentOccurrence.isValid() ) {
    if (_componentLocator.isValid()) {
      Path       path      = _netOccurrenceLocator.getElement().getPath();
      Component* component = _componentLocator.getElement();
      cdebug_log(18,0) << "| progress component: " << component << endl;
    //_componentOccurrence = Occurrence( component, path.getHeadPath() );
      _componentOccurrence = Occurrence( component, path );
      cdebug_log(18,0) << "| component occ OK" << endl;
      _componentLocator.progress();
      
    } else {
      _netOccurrenceLocator.progress();
      if (_netOccurrenceLocator.isValid()) {
        Occurrence netOccurrence = _netOccurrenceLocator.getElement();
        cdebug_log(18,0) << "| progress net occ: " << _netOccurrenceLocator.getElement() << endl;

        Net* net = static_cast<Net*>( netOccurrence.getEntity() );
      //if (_withTerminalNetlistCells or not net->getCell()->isTerminal()) {
        if (not net->getCell()->isTerminalNetlist()) {
          cdebug_log(18,0) << "| Non Terminal netlist: " << net->getCell() << endl;
          cdebug_log(18,0) << "| set component loc on: " << net << endl;
          _componentLocator = net->getComponents().getLocator();
        } else {
          cdebug_log(18,0) << "| Terminal netlist: " << net->getCell() << endl;
        }
      } else
        break;
    }
  }
  cdebug_log(18,0) << "| progress done: " << endl;
}

string HyperNet_ComponentOccurrences::Locator::_getString() const
// **************************************************************
{
    string s = "<" + _TName("HyperNet::ComponentOccurrences::Locator");
    s += " " + getString(_netOccurrenceLocator);
    s += "+" + getString(_componentLocator);
    s += ">";
    return s;
}

} // End of Hurricane namespace.


// ****************************************************************************************************
// Copyright (c) BULL S.A. 2000-2018, All Rights Reserved
// ****************************************************************************************************
