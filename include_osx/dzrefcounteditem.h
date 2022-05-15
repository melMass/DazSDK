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
	Defines the DzRefCountedItem class.
**/

#ifndef DAZ_REF_COUNTED_ITEM
#define DAZ_REF_COUNTED_ITEM

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"
#include <QtCore/QAtomicInt>

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRefCountedItem {
public:
	DzRefCountedItem();
	DzRefCountedItem(const DzRefCountedItem&);
	virtual ~DzRefCountedItem();

	void	ref();
	void	unref();
	int		getRefCount() const;
	bool	isUnique() const;
	bool	isShared() const;

private:

	QAtomicInt	m_refCount;
};

#endif // DAZ_REF_COUNTED_ITEM