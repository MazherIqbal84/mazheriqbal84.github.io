// ****************************************************************************************************
// File: ./Rubber.cpp
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

#include "hurricane/Rubber.h"
#include "hurricane/Net.h"
#include "hurricane/Plug.h"
#include "hurricane/Instance.h"
#include "hurricane/Cell.h"
#include "hurricane/Hook.h"
#include "hurricane/Component.h"
#include "hurricane/Error.h"

namespace Hurricane {



// ****************************************************************************************************
// Rubber implementation
// ****************************************************************************************************

Rubber::Rubber(Net* net, Hook* hook)
// *********************************
:  Inherit(),
        _net(net),
        _hook(hook),
        _count(0),
        _boundingBox(),
        _nextOfNetRubberSet(NULL)
{
        if (!_net)
                throw Error("Can't create " + _TName("Rubber") + " : null net");

        if (!_hook)
                throw Error("Can't create " + _TName("Rubber") + " : null hook");

        if (_hook->getComponent()->getNet() != _net)
                throw Error("Can't create " + _TName("Rubber") + " : invalid hook");
}

void Rubber::destroy()
// ******************
{
        throw Error("Abnormal deletion of " + _TName("Rubber"));
}

Cell* Rubber::getCell() const
// **************************
{
        return _net->getCell();
}

Point Rubber::getCenter() const
// ****************************
{
        return getBoundingBox().getCenter();
}

Point Rubber::getBarycenter() const
// ********************************
{
        int n = getHooks().getSize();
        DbU::Unit x = 0;
        DbU::Unit y = 0;
        for_each_hook(hook, getHooks()) {
                Point position = hook->getComponent()->getBoundingBox().getCenter();
                x += position.getX() / n;
                y += position.getY() / n;
                end_for;
        }
        return Point(x,y);
}

Box Rubber::getBoundingBox() const
// *******************************
{
        if (_boundingBox.isEmpty())
        {
                Rubber* rubber = const_cast<Rubber*>(this);
                Box& boundingBox = rubber->_boundingBox;
                for_each_hook(hook, getHooks()) {
                        Point position = hook->getComponent()->getBoundingBox().getCenter();
                        boundingBox.merge(position);
                        end_for;
                }
        }
        return _boundingBox;
}

Hooks Rubber::getHooks() const
// ***************************
{
    return (_hook) ? _hook->getHooks().getSubSet(Hook::getIsMasterFilter()) : Hooks();
}

void Rubber::materialize()
// ***********************
{
    if (!isMaterialized()) {
        Cell* cell = getCell();
        QuadTree* quadTree = cell->_getQuadTree();
        quadTree->insert(this);
        cell->_fit(quadTree->getBoundingBox());
    }
}

void Rubber::unmaterialize()
// *************************
{
    if (isMaterialized()) {
        Cell* cell = getCell();
        cell->_unfit(getBoundingBox());
        cell->_getQuadTree()->remove(this);
    }
}

void Rubber::translate(const DbU::Unit& dx, const DbU::Unit& dy)
// ***************************************************
{
}

Rubber* Rubber::_create(Hook* hook)
// ********************************
{
        if (!hook)
                throw Error("Can't create " + _TName("Rubber") + " : null hook");

        if (!hook->isMaster())
                throw Error("Can't create " + _TName("Rubber") + " : not a master hook");

        Net* net = hook->getComponent()->getNet();

        if (!net)
                throw Error("Can't create " + _TName("Rubber") + " : unconnected component");

        Rubber* rubber = new Rubber(net, hook);

        rubber->_postCreate();

        return rubber;
}

void Rubber::_postCreate()
// ***********************
{
        _net->_getRubberSet()._insert(this);

        for_each_hook(hook, getHooks()) {
                hook->getComponent()->_setRubber(this);
                end_for;
        }

        Inherit::_postCreate();
}

void Rubber::_destroy()
// *******************
{
        _preDestroy();

        delete this;
}

void Rubber::_preDestroy()
// **********************
{
  cdebug_log(18,1) << "entering Rubber::_preDestroy: " << this << endl;

  Inherit::_preDestroy();

  _count = (unsigned)-1; // to avoid a new destruction

  for_each_hook(hook, getHooks()) {
    hook->getComponent()->_setRubber(NULL);
    end_for;
  }

  _net->_getRubberSet()._remove(this);

  cdebug_log(18,0) << "exiting Rubber::_preDestroy:" << endl;
  cdebug_tabw(18,-1);
}

string Rubber::_getString() const
// ******************************
{
        string s = Inherit::_getString();
        s.insert(s.length() - 1, " " + getString(_net->getName()));
        s.insert(s.length() - 1, " " + getString(_count));
        return s;
}

Record* Rubber::_getRecord() const
// *************************
{
        Record* record = Inherit::_getRecord();
        if (record) {
                record->add(getSlot("Net", _net));
                record->add(getSlot("Hook", _hook));
                record->add(getSlot("Count", _count));
                record->add(getSlot("BoundingBox", _boundingBox));
        }
        return record;
}

void Rubber::_setNet(Net* net)
// ***************************
{
        if (net != _net) {
                if (_net) _net->_getRubberSet()._remove(this);
                _net = net;
                if (_net) _net->_getRubberSet()._insert(this);
        }
}

void Rubber::_setHook(Hook* hook)
// ******************************
{
        assert(hook->isMaster());
        assert(hook->getComponent()->getNet() == getNet());
        _hook = hook;
}

void Rubber::_capture()
// ********************
{
        invalidate();
        _count++;
}

void Rubber::_release()
// ********************
{
        if (_count != ((unsigned)-1)) { // not in deletion
                invalidate();
                if ((--_count) == 1) _destroy();
        }
}

void Rubber::invalidate(bool propagateFlag)
// ****************************************
{
        Inherit::invalidate(false);
        _boundingBox.makeEmpty();
}

typedef struct pcmp_s {
    bool operator() (const Point& p1, const Point& p2) const {
        return (p1.getX() < p2.getX()) || ( (p1.getX() == p2.getX()) && (p1.getY() < p2.getY()) );
    }
} pcmp_t;

} // End of Hurricane namespace.


// ****************************************************************************************************
// Copyright (c) BULL S.A. 2000-2018, All Rights Reserved
// ****************************************************************************************************
