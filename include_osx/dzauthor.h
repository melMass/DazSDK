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
	Defines the DzAuthor class.
**/

#ifndef DAZ_AUTHOR_H
#define DAZ_AUTHOR_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAuthor {
public:
	//
	// CREATORS
	//

	DzAuthor();
	DzAuthor( const QString &name, const QString &email, const QString &url = QString::null );
	DzAuthor( const DzAuthor &author );
	~DzAuthor();

	//
	// ACCESSORS
	//

	bool	isValid() const;
	QString	getName() const;
	QString	getEmail() const;
	QString	getUrl() const;

	//
	// OPERATORS
	//

	DzAuthor&	operator=( const DzAuthor &author );
	bool		operator==( const DzAuthor &author ) const;
	bool		operator!=( const DzAuthor &author ) const;

private:
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

Q_DECLARE_METATYPE( DzAuthor );

#endif // DAZ_AUTHOR_H
