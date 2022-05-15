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
	Defines the DzIndexList class.
**/

#ifndef DAZ_INDEX_LIST_H
#define DAZ_INDEX_LIST_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzIndexList : public DzBase {
	Q_OBJECT
public:
	DzIndexList();
	DzIndexList( const QString &name );
	DzIndexList( const DzIndexList &list );
	virtual ~DzIndexList();

	DzIndexList		&operator=( const DzIndexList &list );

	int*	setCount( int count );
	void	preSizeArray( int count );

public slots:
	void	addIndex( int idx );
	int		findIndex( int idx ) const;
	bool	removeIndex( int idx );
	bool	removeComponent( int idx );
	void	clear();
	int		count() const;
	int		getIndex( int i ) const;

public:
	const int*	getIndicesPtr() const;

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_INDEX_LIST_H
