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
/**
	@sdk
	@file
	Defines the DzPolySorter class.
**/

#ifndef DAZ_POLY_SORTER_H
#define DAZ_POLY_SORTER_H

/*****************************
	Include files
*****************************/

#include "dztblockarray.h"

/****************************
	Forward declarations
****************************/

class DzVec3;
class DzMaterial;
class DzFacetMesh;
class DzFaceGroup;
class DzDrawStyle;
class DzBSPFace;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPolySorter {
public:

	DzPolySorter();
	~DzPolySorter();

	void	addPolygons( const DzFacetMesh *mesh, const DzFaceGroup *faces, const DzMaterial *mat );
	void	doSort( const DzVec3 &viewpoint );
	void	draw( const DzDrawStyle &style );

private:

	void	drawNTTV( const DzDrawStyle &style );
	void	drawNTV( const DzDrawStyle &style );
	void	drawNV( const DzDrawStyle &style );
	void	drawV( const DzDrawStyle &style );
	void	doSort( const DzBSPFace *node, const DzPnt3 viewpoint, DzTBlockArray<DzBSPFace*> &list );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_POLY_SORTER_H
