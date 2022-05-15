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
	Defines the DzImporter class.
**/

#ifndef DAZ_IMPORTER_H
#define DAZ_IMPORTER_H

/****************************
	Include files
****************************/

#include "dzfileio.h"

/***************************
	Forward Declarations
****************************/

class DzNode;
class DzFileLoadFilter;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzImporter : public DzFileIO {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzImporter();
	virtual ~DzImporter();

public slots:

	//
	// MANIPULATORS
	//

	DzError				readFile( const QString &filename );
	DzError				readFile( const QString &filename, const DzFileIOSettings *options );

	void				setLoadFilter( DzFileLoadFilter *filter );
	DzFileLoadFilter*	getFileLoadFilter() const;
	void				addNodetoFilter( DzNode *node );
	void				finishFilter();
	
	//
	// ACCESSORS
	//

	virtual bool	recognize( const QString &filename ) const = 0;
	virtual int		getNumExtensions() const = 0;
	virtual QString	getExtension( int i ) const = 0;
	virtual QString	getDescription() const = 0;

protected:

	//
	// MANIPULATORS
	//

	virtual DzError	read( const QString &filename, const DzFileIOSettings *options ) = 0;

private:

	struct Data; 
	Data	*m_data;
};

#endif // DAZ_IMPORTER_H
