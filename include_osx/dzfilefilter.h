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
	Defines the DzFileFilter class.
**/

#ifndef DAZ_FILE_FILTER_H
#define DAZ_FILE_FILTER_H

/****************************
	Include files
****************************/

#include "dzgeneraldefs.h"

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzFileFilter : public QObject {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzFileFilter();
	DzFileFilter( const QString &description, const QString &extension );
	DzFileFilter( const QString &description, const QStringList &extensions );
	~DzFileFilter();

public slots:

	//
	// MANIPULATORS
	//

	void	newFilter( const QString &description );
	void	addExtension( const QString &extension );
	void	addExtensions( const QStringList &extensions );
	void	setDefaultFilter( int filterIdx );

	//
	// ACCESSORS
	//

	int		getNumFilters() const;
	QString	getFilterDescription( int filterIdx ) const;
	int		getNumExtensions( int filterIdx ) const;
	QString	getExtension( int filterIdx, int extensionIdx ) const;
	int		getDefaultFilter() const;

public:

	const QStringList&	getExtensions( int filterIdx ) const;

protected:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FILE_FILTER_H
