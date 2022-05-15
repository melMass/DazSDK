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

#ifndef DZ_CONTENT_DROP_OPTIONS
#define DZ_CONTENT_DROP_OPTIONS

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzVec3;
class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzContentDropOptions {
public:
	enum DropMode { DEFAULT_LOAD, FOLLOW, PARENT_TO, APPLY_TO, DROP_AT };

	DzContentDropOptions();
	~DzContentDropOptions();

	DropMode	getDropMode();
	void		setDropMode( DropMode mode );

	DzNode*	getDropTarget();
	void	setDropTarget( DzNode *dropTarget );

	DzVec3	getDropPoint();
	void	setDropPoint( DzVec3 dropPoint );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DZ_CONTENT_DROP_OPTIONS