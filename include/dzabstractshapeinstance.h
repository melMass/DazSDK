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
	Defines the DzAbstractShapeInstance class.
**/

#ifndef DZ_ABSTRACT_SHAPE_INSTANCE_GROUP_H
#define DZ_ABSTRACT_SHAPE_INSTANCE_GROUP_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"
#include "dzmatrix3.h"

/*****************************
	Forward declarations
*****************************/
class DzNode;
class DzShape;
class DzRenderSettings;
class DzDrawStyle;

/****************************
	Type definitions
****************************/

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzAbstractShapeInstance : public QObject {
	Q_OBJECT
public:
	DzAbstractShapeInstance();
	virtual ~DzAbstractShapeInstance();

	virtual void	addedToShape(DzShape* shape)=0;

public slots:
	virtual DzNode* getPickNode()const=0;
	virtual DzMatrix3 getWSTransform() const=0;
	virtual DzMatrix3 getWSTransform(DzTime tm) const=0;
	virtual bool	shouldRender( const DzRenderSettings &settings )const=0;
	virtual bool	shouldDraw( const DzDrawStyle &style )const=0;
};

#endif //DZ_ABSTRACT_SHAPE_INSTANCE_GROUP_H