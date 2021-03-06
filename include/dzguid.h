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
	Defines the DzGuid class.
**/

#ifndef DAZ_GUID_H
#define DAZ_GUID_H

/*****************************
	Include files
*****************************/

#include <QtCore/QUuid>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

struct DZ_EXPORT DzGuidComponents
{
	unsigned int	m_data1;
	unsigned short	m_data2;
	unsigned short	m_data3;
	unsigned char	m_data4[8];
};

union DZ_EXPORT DzGuidData
{
	DzGuidComponents	m_components;
	quint64				m_values[2];
};

class DZ_EXPORT DzGuid {
public:
	DzGuid();
	DzGuid( unsigned int data1, unsigned short data2, unsigned short data3,
			unsigned char data4_0, unsigned char data4_1,
			unsigned char data4_2, unsigned char data4_3,
			unsigned char data4_4, unsigned char data4_5,
			unsigned char data4_6, unsigned char data4_7 );
	DzGuid( const DzGuid &guid );
	DzGuid( const QUuid &guid );

	bool	operator==( const DzGuid &guid ) const { return (m_data.m_values[0] == guid.m_data.m_values[0] && m_data.m_values[1] == guid.m_data.m_values[1]); }
	DzGuid&	operator=( const DzGuid &guid ) { m_data = guid.m_data; return *this; }
	DzGuid&	operator=( const QUuid &guid );

	void	setData( unsigned int data1, unsigned short data2, unsigned short data3,
				unsigned char data4_0, unsigned char data4_1,
				unsigned char data4_2, unsigned char data4_3,
				unsigned char data4_4, unsigned char data4_5,
				unsigned char data4_6, unsigned char data4_7 );

	unsigned int			data1() const { return m_data.m_components.m_data1; }
	unsigned short			data2() const { return m_data.m_components.m_data2; }
	unsigned short			data3() const { return m_data.m_components.m_data3; }
	const unsigned char*	data4() const { return m_data.m_components.m_data4; }

	bool	isValid() const;
	bool	isNil() const;
	QString	toString() const;
	QUuid	toQUuid() const;

	static QString	toString( const DzGuid &guid );
	static QUuid	toQUuid( const DzGuid &guid );
	static DzGuid	fromString( const QString &str );
	static DzGuid	fromCString( const char *str );
	static DzGuid	fromLegacyClassID( unsigned int classID );
	static DzGuid	createGuid();

	DzGuidData	m_data;
};

class DZ_EXPORT DzDigest {
public:
	DzDigest();
	~DzDigest();

	DzGuid	toGuid();

	void	append( char c );
	void	append( const char *data );
	void	append( const QString &data );
	void	append( const QByteArray &data );
	void	append( const void *data, int nBytes );

	DzDigest&	operator<<( char c );
	DzDigest&	operator<<( const char *data );
	DzDigest&	operator<<( const QString &data );
	DzDigest&	operator<<( const QByteArray &data );

private:
	void	close();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_GUID_H
