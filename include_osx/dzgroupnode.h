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
	Defines the DzGroupNode class.
**/



#ifndef DZ_GROUPNODE_H
#define DZ_GROUPNODE_H

/*****************************
	Include files
*****************************/
#include "dznode.h"

/****************************
	Forward declarations
****************************/


class DZ_EXPORT DzGroupNode : public DzNode
{
	Q_OBJECT
public:
	DzGroupNode();
	~DzGroupNode();
public slots:
	virtual void			invalidateBoundingBoxes( bool checkSkeleton = true );

	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;

protected :
	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;

private slots:
	void					connectChildNode( DzNode *child );
	void					disconnectChildNode( DzNode *child );
	void					setChildrenVisible();
	void					setChildrenSelectable();

	virtual bool			shouldSortOnLoad() const;
private:

	void					setVisibleOnChildren( bool isVis, DzNode *parent );
	void					setSelectableOnChildren( bool isSel, DzNode *parent );

	struct Data;
	Data	*m_data;
};

#endif
