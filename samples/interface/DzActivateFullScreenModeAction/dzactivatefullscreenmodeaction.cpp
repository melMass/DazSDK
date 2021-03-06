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
#include "dzactivatefullscreenmodeaction.h"

#include <QtGui/QMessageBox>

#include "dzapp.h"
#include "dzmainwindow.h"

///////////////////////////////////////////////////////////////////////
// DzActivateFullScreenModeAction
///////////////////////////////////////////////////////////////////////

/**
	Creates a new action with the menu text "Activate Full Screen Mode"
**/
DzActivateFullScreenModeAction::DzActivateFullScreenModeAction() : DzAction( tr( "&Activate Full Screen Mode" ),
	tr( "Cause the active viewport to enter full screen mode. Use the ESC key to exit full screen mode." ) )
{
	// Set the object name for the action to register it with the help and
	// interactive lesson systems

	setObjectName( DzActivateFullScreenModeAction::metaObject()->className() );
}

/**
	This gets called when the user clicks on our action item.
**/
void DzActivateFullScreenModeAction::executeAction()
{
	// Check if the main window has been created yet.
	// If it hasn't, alert the user and exit early.

	DzMainWindow* mw = dzApp->getInterface();
	if ( !mw )
	{
		QMessageBox::warning( 0, tr( "Error" ),
			tr( "The main window has not been created yet." ), QMessageBox::Ok );

		return;
	}

	// Make the call that causes the main window to enter full-screen mode.

	mw->goFullScreen();
}
