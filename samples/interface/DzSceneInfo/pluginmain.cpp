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
#include "dzplugin.h"
#include "dzapp.h"

#include "version.h"
#include "dzinfopane.h"

/*****************************
   Plugin Definition
*****************************/

/**
	This macro creates the plugin definition, and the functions that are needed
	for Daz Studio to load our plugin.
**/
DZ_PLUGIN_DEFINITION( "Scene Info Pane (SDK Example)" );

/**
	This macro sets the author string for the plugin
**/
DZ_PLUGIN_AUTHOR( "Daz 3D, Inc" );

/**
	This macro sets the version number for the plugin
**/
DZ_PLUGIN_VERSION( PLUGIN_MAJOR, PLUGIN_MINOR, PLUGIN_REV, PLUGIN_BUILD );

/**
	This macro sets the description string for the plugin. This is a good place
	to provide specific information about the plugin, including an HTML link to
	any external documentation. Links are shown in the system default browser.
**/
DZ_PLUGIN_DESCRIPTION( QString(
	"This plugin is a very simple example of extending the %1 interface by inheriting from the "
	"DzPane class. Plugins that need a persistent interface where the user is still able to interact "
	"with the rest of the %1 interface should implement their interface as a DzPane subclass."
	"<br><br>"
	"In this example, we provide a simple HTML-based display of general information about the scene "
	"contents and the current selection. This pane also updates itself whenever the scene or primary "
	"selection is changed so that the display reflects the contents of the scene in \'real time\'." )
	.arg( dzApp->getAppName() )
);

/**
	This macro adds our classes to the objects exported by the plugin, and specifies the
	GUID (Globally Unique Identifier) that makes this class unique from any other class
	that is available from Daz Studio or one of it's plug-ins. DO NOT USE THE GUIDS BELOW
	IN YOUR PLUG-IN. Make sure that you generate a new GUID for every class that you export
	from your plug-in. See the 'ClassIDs' page in the Daz Studio SDK documentation for more
	information.
**/
DZ_PLUGIN_CLASS_GUID( DzSceneInfoPane,			B833CC13-F88D-4fd2-8C95-F82D0BF3A5D0 );
DZ_PLUGIN_CLASS_GUID( DzSceneInfoPaneAction,	295A67A3-0442-42d0-9F03-F675799D7573 );
