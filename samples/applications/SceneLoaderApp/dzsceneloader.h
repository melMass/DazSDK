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

#include <QtCore/QObject>

/*****************************
	Forward declarations
*****************************/

class DzNode;

/*****************************
	Class definitions
*****************************/

class DzSceneLoader : public QObject {
	Q_OBJECT
public:

	// Constructor
	DzSceneLoader();

	bool	loadScene( const QString &filename );

private:

	void	printSceneStats();
	void	getGeometryStats( int &nVerts, int &nFacets );
	void	getGeometryStats( DzNode* node, int &nVerts, int &nFacets );
};
