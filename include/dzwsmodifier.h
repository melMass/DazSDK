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
	Defines the DzWSModifier class.
**/

#ifndef DAZ_WS_MODIFIER_H
#define DAZ_WS_MODIFIER_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"

/****************************
	Forward declarations
****************************/

class DzVertexMesh;
class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzWSModifier : public DzElement {
	Q_OBJECT
	friend class DzScene;
public:

	//
	// CREATORS
	//

	DzWSModifier();
	virtual ~DzWSModifier();

	//
	// MANIPULATORS
	//

	virtual DzError	apply( DzVertexMesh &geom, DzNode &node ) = 0;
	virtual DzError	applyInverse( DzVertexMesh &geom, DzNode &node ) = 0;

signals:

	void	currentValueChanged();
	void	aboutToBeRemoved();
	void	removed();
	void	added();
};

#endif // DAZ_WS_MODIFIER_H
