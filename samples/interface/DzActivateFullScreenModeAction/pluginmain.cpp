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
#include "dzactivatefullscreenmodeaction.h"

/*****************************
   Plugin Definition
*****************************/

DZ_PLUGIN_DEFINITION( "Activate Full Screen Mode Action (SDK Example)" );
DZ_PLUGIN_AUTHOR( "Daz 3D, Inc" );
DZ_PLUGIN_VERSION( PLUGIN_MAJOR, PLUGIN_MINOR, PLUGIN_REV, PLUGIN_BUILD );

DZ_PLUGIN_DESCRIPTION( QString( "This plugin is a simple example provided with the %1 "
					   "SDK. It provides an action that will set the active viewport to "
					   "full-screen mode. By default the hotkey for this is Shift + Esc. "
					   "The Esc key will exit full-screen mode." ).arg( dzApp->getAppName() ) );

DZ_PLUGIN_CLASS_GUID( DzActivateFullScreenModeAction, F36BD363-913B-427a-B67D-8C7D600E0461 );
