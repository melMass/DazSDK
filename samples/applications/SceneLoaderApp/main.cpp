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
#include <stdlib.h>

#include "dzapp.h"

#include "dzsceneloader.h"

namespace
{

/**
	Prints the usage message to the console.
**/
void printUsage()
{
	printf( "Usage:\n" );
	printf( "   SDK_SceneLoaderApp path/to/filename.duf\n" );
}

}//namespace

/**
	Program entry point. Creates and initializes DzApp with no interface and
	loads the scene file at a specified absolute path.

	@param argc		The number of command-line arguments provided.
	@param argv		A vector of command-line argument strings.

	@return An exit-code for the process; 0 for success, otherwise an error code.
**/
int main( int argc, char** argv )
{
	// Require exactly 2 arguments:
	//   0 - The program name (automatically populated)
	//   1 - The absolute path of a scene file
	
	if ( argc < 2 || argc > 2 )
	{
		printf( "No filename specified.\n" );
		printUsage();

		return 1; // Indicate that the application cannot be initialized
	}

	int myArgc = 1;
	DzApp app( myArgc, argv, false, true );
	DzSceneLoader loader;

	if ( !app.init( DzApp::NoInterface ) )
	{
		printf( "Initialization failed." );

		return 1; // Indicate that the application cannot be initialized
	}

	const QString filename( argv[1] );
	if ( !loader.loadScene( filename ) )
	{
		printf( "File could not be loaded." );

		return 2; // Indicate that the specified file cannot be loaded
	}

	return 0; // Indicate success
}
