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
#include "afirstpluginaction.h"

#include <QtGui/QMessageBox>

#include "dzapp.h"
#include "dzmainwindow.h"

#include "afirstplugindlg.h"

///////////////////////////////////////////////////////////////////////
// DzAFirstPluginAction
///////////////////////////////////////////////////////////////////////

/**
	Creates a new action with the menu text "Hello"
**/
DzAFirstPluginAction::DzAFirstPluginAction() : DzAction( tr( "Hello" ),
	tr( "Executes the Hello action." ) )
{
	// Set the object name for the action to register it with the help and
	// interactive lesson systems

	setObjectName( DzAFirstPluginAction::metaObject()->className() );
}

/**
	This gets called when the user clicks on our action item.
**/
void DzAFirstPluginAction::executeAction()
{
	/**
		When the action is activated, use the DzAFirstPluginDlg class to display a dialog
	**/

	// Check if the main window has been created yet.
	// If it hasn't, alert the user and exit early.

	DzMainWindow* mw = dzApp->getInterface();
	if ( !mw )
	{
		QMessageBox::warning( 0, tr( "Error" ),
			tr( "The main window has not been created yet." ), QMessageBox::Ok );

		return;
	}

	// Create and show the dialog. If the user cancels, exit early,
	// otherwise continue on and do the thing that required modal
	// input from the user.

	DzAFirstPluginDlg* dlg = new DzAFirstPluginDlg( mw );
	if ( dlg->exec() != QDialog::Accepted )
	{
		QMessageBox::information( dzApp->getDialogParent(), tr( "Information" ),
			tr( "The dialog was rejected." ), QMessageBox::Ok );

		return;
	}

	QMessageBox::information( dzApp->getDialogParent(), tr( "Information" ),
		tr( "The dialog was accepted." ), QMessageBox::Ok );
}

#include "moc_afirstpluginaction.cpp"
