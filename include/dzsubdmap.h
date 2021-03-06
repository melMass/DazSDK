/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This file is part of the DAZ Studio SDK.

	This file may be used only in accordance with the DAZ Studio SDK 
	license provided with the DAZ Studio SDK.

	The contents of this file may not be disclosed to third parties, 
	copied or duplicated in any form, in whole or in part, without the 
	prior written permission of DAZ 3D, Inc, except as explicitly
	allowed in the DAZ Studio SDK license.

	See http://www.daz3d.com to contact DAZ 3D or for more 
	information about the DAZ Studio SDK.
**********************************************************************/

#ifndef DAZ_SUB_D_MAP_H
#define DAZ_SUB_D_MAP_H

/*****************************
	Include files
*****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzFacetMesh;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSubDMap {
	friend class DzCatmullClarkSubD;
	friend class DzSubDVertexSmoother;
public:

	DzSubDMap();
	~DzSubDMap();

public slots:

	DzError		initialize( DzFacetMesh *mesh );
	int*		getLeftPointIndices();
	int*		getRightPointIndices();

	int			getSubDLevel() const;
	int			getNumPoints() const;
	int			getLeftPoint( int which ) const;
	int			getRightPoint( int which ) const;
	const int*	getLeftPointIndices() const;
	const int*	getRightPointIndices() const;

private:

	DzError		startSubdivision( int nPoints );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SUB_D_MAP_H
