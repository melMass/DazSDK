/**********************************************************************
	Copyright (c) 2002-2020 Daz 3D, Inc. All Rights Reserved.

	This file is part of the Daz Studio SDK.

	This file may be used only in accordance with the Daz Studio SDK
	license provided with the Daz Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of Daz 3D, Inc, except as explicitly
	allowed in the Daz Studio SDK license.

	See http://www.daz3d.com to contact Daz 3D, Inc or for more
	information about the Daz Studio SDK.
**********************************************************************/
/*****************************
	Include files
*****************************/
#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <QtGui/QToolTip>

#include "dzactionmgr.h"
#include "dzapp.h"
#include "dzstyle.h"

#include "afirstplugindlg.h"

/*****************************
   Local definitions
*****************************/
#define A_FIRST_PLUGIN_NAME		"AFirstPlugin"

///////////////////////////////////////////////////////////////////////
// DzAFirstPluginDlg
///////////////////////////////////////////////////////////////////////

/**
**/
DzAFirstPluginDlg::DzAFirstPluginDlg( QWidget* parent ) :
	DzBasicDialog( parent, A_FIRST_PLUGIN_NAME )
{
	// Declarations
	const int wgtHeight = style()->pixelMetric( DZ_PM_ButtonHeight );
	const int btnMinWidth = style()->pixelMetric( DZ_PM_ButtonMinWidth );

	// Set the dialog title
	setWindowTitle( tr( "A First Plugin : Dialog" ) );

	//... more widgets/layouts here
	QLabel* lbl = new QLabel( tr( "Hello, World!" ), this );
	lbl->setObjectName( QString( "%1DlgHelloWorldLbl" ).arg( A_FIRST_PLUGIN_NAME ) );
	lbl->setFixedHeight( wgtHeight );
	lbl->setMinimumWidth( btnMinWidth );

	// Add the widget to the basic dialog
	DzBasicDialog::addWidget( lbl );

	// Make the dialog fit its contents, with a minimum width, and lock it down
	resize( QSize( 300, 0 ).expandedTo( QDialog::minimumSizeHint() ) );
	setFixedWidth( width() );
	setFixedHeight( height() );
}

#include "moc_afirstplugindlg.cpp"
