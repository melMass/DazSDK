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
	Defines the IDzJsonIO interface for reading and writing JSON files.
**/

#ifndef I_DZ_JSON_H
#define I_DZ_JSON_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Class definitions
****************************/

class DZ_EXPORT IDzJsonIO {
public:
	virtual ~IDzJsonIO();

	virtual bool	startObject( bool multiLine = true ) = 0;
	virtual bool	startArray( bool multiLine = true ) = 0;

	virtual bool	startMemberObject( const QString &name, bool multiLine = true ) = 0;
	virtual bool	startMemberArray( const QString &name, bool multiLine = true ) = 0;

	virtual bool	finishObject() = 0;
	virtual bool	finishArray() = 0;

	virtual bool	skipObject() = 0;
	virtual bool	skipArray() = 0;

	virtual bool	addMember( const QString &name, const QString &val ) = 0;
	virtual bool	addMember( const QString &name, const char *val ) { return addMember( name, QString( val ) ); }
	virtual bool	addMember( const QString &name, int val ) = 0;
	virtual bool	addMember( const QString &name, float val ) = 0;
	virtual bool	addMember( const QString &name, double val ) = 0;
	virtual bool	addMember( const QString &name, bool val ) = 0;
	virtual bool	addMemberNull( const QString &name ) = 0;

	virtual bool	addItem( const QString &val ) = 0;
	virtual bool	addItem( const char *val ) { return addItem( QString( val ) ); }
	virtual bool	addItem( int val ) = 0;
	virtual bool	addItem( float val ) = 0;
	virtual bool	addItem( double val ) = 0;
	virtual bool	addItem( bool val ) = 0;
	virtual bool	addItemNull() = 0;

	virtual QString	getLastError() = 0;
};

#endif // I_DZ_JSON_H