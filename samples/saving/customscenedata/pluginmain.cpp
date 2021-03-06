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
#include "myscenemodel.h"
#include "mysceneview.h"

/*****************************
   Plugin Definition
*****************************/

/**
	This macro creates the plugin definition, and the functions that are needed
	for Daz Studio to load our plugin.
**/
DZ_PLUGIN_DEFINITION( "Custom Scene Data Loading Saving (SDK Example)" );

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
	"This plugin is a simple example provided with the %1 SDK. It provides "
	"developers an example of the basics with regard to loading and saving "
	"custom data with a DSF scene " ).arg( dzApp->getAppName() )
);

/**
	This macro adds our classes to the objects exported by the plugin, and specifies the
	GUID (Globally Unique Identifier) that makes this class unique from any other class
	that is available from Daz Studio or one of it's plug-ins. DO NOT USE THE GUIDS BELOW
	IN YOUR PLUG-IN. Make sure that you generate a new GUID for every class that you export
	from your plug-in. See the 'ClassIDs' page in the Daz Studio SDK documentation for more
	information.
**/
DZ_PLUGIN_CLASS_GUID( MyScenePane,			0164811A-FC78-4721-9955-C068675C3DF1 );
DZ_PLUGIN_CLASS_GUID( MyScenePaneAction,	0164811A-FC78-4721-9955-C068675C3DF2 );
DZ_PLUGIN_CLASS_GUID( MySceneModel,			F820DACE-1D55-44a5-89C4-69492E2D2F69 );
DZ_PLUGIN_CLASS_GUID( MySceneModelIO,		562B5DF6-0F2A-432f-A78F-53263F53538B );
DZ_PLUGIN_REGISTER_SCENEDATA_EXTRA_OBJECT_IO( "my_scene_data", MySceneModelIO,  MySceneModel );
