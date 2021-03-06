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
#pragma once

/*****************************
	Include files
*****************************/

#include <QtGui/QKeySequence>

#include "dzaction.h"

/*****************************
	Class definitions
*****************************/
/**
	Our plugin adds a new action class to Daz Studio. Actions are menu and tool bar
	entries that the user can click on. Creating a new action is the easiest way to
	extend the Daz Studio interface from a plugin.
**/
class DzActivateFullScreenModeAction : public DzAction {
	Q_OBJECT
public:

	// Constructor
	DzActivateFullScreenModeAction();

	/**
		We need to re-implement these virtual functions to provide defaults for our
		'action'. These get called by DzActionMgr during initialization. The user's
		settings file is then processed for customization.
	**/
	virtual QString			getActionGroup() const { return tr( "SDK Examples" ); }
	virtual QKeySequence	getDefaultAccel() const { return Qt::SHIFT + Qt::Key_Escape; }
	virtual QString			getDefaultMenuPath() const { return tr( "&SDK Examples" ); }

protected:

	/**
		We need to re-implement this virtual function to perform our 'action'.
		This gets called whenever the user clicks on our action item.
	**/
	virtual void			executeAction();
};
