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
	Defines the DzJsonWriter class for writing JSON to an I/O device.
**/

#ifndef DAZ_JSON_WRITER_H
#define DAZ_JSON_WRITER_H

/****************************
	Include files
****************************/

#include "idzjsonio.h"

/****************************
	Forward declarations
****************************/

class QIODevice;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzJsonWriter : public IDzJsonIO {
public:

	DzJsonWriter( QIODevice *device );
	virtual ~DzJsonWriter();

	virtual bool	startObject( bool multiLine = true );
	virtual bool	startArray( bool multiLine = true );

	virtual bool	startMemberObject( const QString &name, bool multiLine = true );
	virtual bool	startMemberArray( const QString &name, bool multiLine = true );

	virtual bool	finishObject();
	virtual bool	finishArray();

	virtual bool	skipObject();
	virtual bool	skipArray();

	virtual bool	addMember( const QString &name, const QString &val );
	virtual bool	addMember( const QString &name, int val );
	virtual bool	addMember( const QString &name, float val );
	virtual bool	addMember( const QString &name, double val );
	virtual bool	addMember( const QString &name, bool val );
	virtual bool	addMemberNull( const QString &name );

	virtual bool	addItem( const QString &val );
	virtual bool	addItem( int val );
	virtual bool	addItem( float val );
	virtual bool	addItem( double val );
	virtual bool	addItem( bool val );
	virtual bool	addItemNull();

	virtual QString	getLastError();

	void			setNumericPrecision(int floatPrecision,int doublePercision);
	void			getNumericPrecision(int &floatPrecision,int &doublePercision)const;

private:

	void	writeSpace();
	void	writeSeparator();
	QString	escapeString( const QString &str );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_JSON_WRITER_H
