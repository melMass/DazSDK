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
	Defines the DzModifier class.
**/

#ifndef DAZ_MODIFIER_H
#define DAZ_MODIFIER_H

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

class DZ_EXPORT DzModifier : public DzElement {
	Q_OBJECT
	friend class DzObject;
public:

	DzModifier();
	virtual ~DzModifier();
	
	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	save( DzOutFile *file ) const;
	
	virtual DzError	apply( DzVertexMesh &geom, DzNode &node ) = 0;
	virtual DzError	applyInverse( DzVertexMesh &geom, DzNode &node ) = 0;

	bool	isWeightMapModifier() const;
	void	setIsWeightMapModifier( bool onoff );

signals:

	void	currentValueChanged();
	void	aboutToBeRemoved();
	void	removed();
	void	added();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MODIFIER_H
