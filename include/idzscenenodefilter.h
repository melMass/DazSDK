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
	Defines the IDzSceneNodeFilter interface.
**/

#ifndef IDZ_SCENE_NODE_FILTER_H
#define IDZ_SCENE_NODE_FILTER_H

/*****************************
	Include files
*****************************/

#include "dzdrawstyle.h"

/*****************************
	Forward declarations
*****************************/

class DzNode;

/*****************************
	Class definitions
*****************************/

// Base class for scene node filters
class DZ_EXPORT IDzSceneNodeFilter : public QObject {
	Q_OBJECT
public:
	virtual ~IDzSceneNodeFilter();
	virtual bool isSelectable( const DzNode *node ) const = 0;
	virtual bool selectParent( const DzNode *node ) const = 0;
	virtual bool selectSkeleton( const DzNode *node ) const = 0;
	virtual DzDrawStyle::ShadeStyle getShadeStyle( DzNode *node ) = 0;
	virtual QList<DzDrawStyle::ShadeStyle> getFilterShadeStyles() = 0;
};

#endif // IDZ_SCENE_NODE_FILTER_H
