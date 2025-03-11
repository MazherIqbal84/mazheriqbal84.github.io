
// -*- C++ -*-
//
// This file is part of the Coriolis Project.
// Copyright (C) Laboratoire LIP6 - Departement ASIM
// Universite Pierre et Marie Curie
//
// Main contributors :
//        Christophe Alexandre   <Christophe.Alexandre@lip6.fr>
//        Sophie Belloeil             <Sophie.Belloeil@lip6.fr>
//        Hugo Cl�ment                   <Hugo.Clement@lip6.fr>
//        Jean-Paul Chaput           <Jean-Paul.Chaput@lip6.fr>
//        Damien Dupuis                 <Damien.Dupuis@lip6.fr>
//        Christian Masson           <Christian.Masson@lip6.fr>
//        Marek Sroka                     <Marek.Sroka@lip6.fr>
// 
// The  Coriolis Project  is  free software;  you  can redistribute it
// and/or modify it under the  terms of the GNU General Public License
// as published by  the Free Software Foundation; either  version 2 of
// the License, or (at your option) any later version.
// 
// The  Coriolis Project is  distributed in  the hope that it  will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY  or FITNESS FOR  A PARTICULAR PURPOSE.   See the
// GNU General Public License for more details.
// 
// You should have  received a copy of the  GNU General Public License
// along with the Coriolis Project; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
//
// License-Tag
// Authors-Tag
// ===================================================================
//
// $Id$
//
// x-----------------------------------------------------------------x 
// |                                                                 |
// |                   C O R I O L I S                               |
// |      C y c l o p  -  S i m p l e   V i e w e r                  |
// |                                                                 |
// |  Author      :                    Jean-Paul CHAPUT              |
// |  E-mail      :       Jean-Paul.Chaput@asim.lip6.fr              |
// | =============================================================== |
// |  C++ Module  :       "./OpenCellDialog.cpp"                     |
// | *************************************************************** |
// |  U p d a t e s                                                  |
// |                                                                 |
// x-----------------------------------------------------------------x


#include  <iostream>
using namespace std;

#include  <QLabel>
#include  <QLineEdit>
#include  <QPushButton>
#include  <QRadioButton>
#include  <QButtonGroup>
#include  <QCheckBox>
#include  <QHBoxLayout>
#include  <QVBoxLayout>

#include  "hurricane/Warning.h"
#include  "hurricane/viewer/Graphics.h"

#include  "crlcore/Environment.h"
#include  "crlcore/AllianceFramework.h"
#include  "OpenCellDialog.h"


namespace CRL {


  using Hurricane::Warning;
  using Hurricane::Graphics;


// -------------------------------------------------------------------
// Class  :  "OpenCellDialog".


  OpenCellDialog::OpenCellDialog ( QWidget* parent )
    : QDialog        (parent)
    , _lineEdit      (NULL)
    , _viewerCheckBox(NULL)
  {
    setWindowTitle ( tr("Open Cell") );

    QLabel* label = new QLabel ();
    label->setText ( tr("Enter Cell name (without extention)") );
    label->setFont ( Graphics::getNormalFont(true) );

    _lineEdit = new QLineEdit ();
    _lineEdit->setMinimumWidth ( 400 );

    _viewerCheckBox = new QCheckBox ();
    _viewerCheckBox->setText ( tr("Open in new Viewer") );

    QPushButton* okButton = new QPushButton ();
    okButton->setText    ( "OK" );
    okButton->setDefault ( true );

    QPushButton* cancelButton = new QPushButton ();
    cancelButton->setText ( "Cancel" );

    QHBoxLayout* hLayout1 = new QHBoxLayout ();
    hLayout1->addStretch ();
    hLayout1->addWidget ( okButton );
    hLayout1->addStretch ();
    hLayout1->addWidget ( cancelButton );
    hLayout1->addStretch ();

    QFrame* separator = new QFrame ();
    separator->setFrameShape  ( QFrame::HLine );
    separator->setFrameShadow ( QFrame::Sunken );

    QHBoxLayout*  hLayout2     = new QHBoxLayout ();
    QButtonGroup* formatGroup  = new QButtonGroup ();

    QRadioButton* formatButton = new QRadioButton ();
    formatButton->setText ( tr("vst/ap") );
    formatButton->setChecked ( true );
    formatGroup->setId     ( formatButton, 0 );
    formatGroup->addButton ( formatButton );
    hLayout2->addWidget    ( formatButton  );

    formatButton = new QRadioButton ();
    formatButton->setText ( tr("DEF") );
    formatButton->setChecked ( false );
    formatGroup->setId     ( formatButton, 1 );
    formatGroup->addButton ( formatButton );
    hLayout2->addWidget    ( formatButton  );

    QVBoxLayout* vLayout = new QVBoxLayout ();
    vLayout->setSizeConstraint  ( QLayout::SetFixedSize );
    vLayout->addWidget ( label );
    vLayout->addWidget ( _lineEdit );
    vLayout->addWidget ( _viewerCheckBox );
    vLayout->addLayout ( hLayout1 );
    vLayout->addWidget ( separator );
    vLayout->addLayout ( hLayout2 );

    setLayout ( vLayout );
  //setModal  ( true );

    connect (     okButton, SIGNAL(clicked())         , this, SLOT(accept()) );
    connect ( cancelButton, SIGNAL(clicked())         , this, SLOT(reject()) );
    connect ( formatGroup , SIGNAL(buttonClicked(int)), this, SLOT(formatChanged(int)) );
  }


  const QString  OpenCellDialog::getCellName () const
  {
    return _lineEdit->text();
  }


  bool  OpenCellDialog::newViewerRequest () const
  {
    return _viewerCheckBox->isChecked();
  }


  bool  OpenCellDialog::runDialog ( QWidget* parent, QString& name, bool& newViewerRequest )
  {
    OpenCellDialog* dialog = new OpenCellDialog ( parent );
    bool dialogResult = (dialog->exec() == Accepted);

    name             = dialog->getCellName ();
    newViewerRequest = dialog->newViewerRequest ();

    delete dialog;

    return dialogResult;
  }


  void  OpenCellDialog::formatChanged ( int index )
  {
    Environment* environment = AllianceFramework::get()->getEnvironment();
    switch ( index ) {
      case 0:
        environment->setIN_LO ( "vst" );
        environment->setIN_PH ( "ap"  );
        break;
      case 1:
        environment->setIN_LO ( "def" );
        environment->setIN_PH ( "def" );
        break;
      default:
        cerr << Warning("Unknown input format: %d.",index) << endl;
    }
  }


} // End of CRL namespace.
