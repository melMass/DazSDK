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
	Defines the DzNodeSelectionInterface class.
**/

#ifndef DAZ_NODE_SELECTION_INTERFACE_H
#define DAZ_NODE_SELECTION_INTERFACE_H

/*****************************
	Include files
*****************************/

#include "dztypes.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNodeSelectionInterface {
public:
	//
	// CREATORS
	//

	DzNodeSelectionInterface();
	virtual ~DzNodeSelectionInterface();

public slots:

	virtual void	clear() = 0;
	virtual void	setIndeterminate() = 0;
	virtual void	selectNode( DzNode *obj ) = 0;
	void			setNodeList( const DzNodeList &nodes );
	void			setNodeList( DzNodeListIterator &nodes );
	void			setNodeList( const DzBoneList &nodes );
	void			setNodeList( DzBoneListIterator &nodes );
	void			setNodeList( const DzCameraList &nodes );
	void			setNodeList( DzCameraListIterator &nodes );
	void			setNodeList( const DzLightList &nodes );
	void			setNodeList( DzLightListIterator &nodes );
	void			setNodeList( const DzSkeletonList &nodes );
	void			setNodeList( DzSkeletonListIterator &nodes );
	virtual DzNode*	getCurrent() const = 0;

protected:

	virtual void	setNodes( const DzNodeList &nodes ) = 0;
};

#endif // DAZ_NODE_SELECTION_INTERFACE_H