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
	Defines the DzInFile class.
**/

#ifndef DAZ_IN_FILE_H
#define DAZ_IN_FILE_H

/****************************
	Include files
****************************/

#include "dzversion.h"
#include "dzerrorcodes.h"
#include "dzauthor.h"

/****************************
	Forward declarations
****************************/

class DzBase;
class DzGuid;
class DzMatrix3;
class DzMatrix4;
class DzQuat;
class DzStorable;
class DzTimeRange;
class DzVec3;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzInFile : public QObject {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzInFile( const QString &filename );
	~DzInFile();

public slots:

	DzError	open();
	void	close();

public:

	//
	// MANIPULATORS
	//

	DzError	read( DzBase *ptr, bool isMerge = false );
	DzError	readChar( char &val );
	DzError	readChars( char *buf, int count );
	DzError	readUChar( unsigned char &val );
	DzError	readUChars( unsigned char *buf, int count );
	DzError	readInt( int &val );
	DzError	readInts( int *buf, int count );
	DzError	readUInt( unsigned int &val );
	DzError	readUInts( unsigned int *buf, int count );
	DzError	readInt64( qint64 &val );
	DzError	readInt64s( qint64 *buf, int count );
	DzError	readUInt64( quint64 &val );
	DzError	readUInt64s( quint64 *buf, int count );
	DzError	readShort( short &val );
	DzError	readShorts( short *buf, int count );
	DzError	readUShort( unsigned short &val );
	DzError	readUShorts( unsigned short *buf, int count );
	DzError	readFloat( float &val );
	DzError	readFloats( float *buf, int count );
	DzError	readDouble( double &val );
	DzError	readDoubles( double *buf, int count );
	DzError	readBool( bool &val );
	DzError	readString( QString &val );
	DzError	readCompressedString( QString &val );
	DzError	readTimeRange( DzTimeRange &val );
	DzError	readVec( DzVec3 &vec );
	DzError readShortVec( DzVec3 &vec, float scale );
	DzError	readRot( DzQuat &rot );
	DzError	readMatrix3( DzMatrix3 &mtx );
	DzError	readMatrix4( DzMatrix4 &mtx );
	DzError	readByteArray( QByteArray &bytes );
	DzError	readPointer();
	DzError	readGUID( DzGuid &guid );

public slots:

	//
	// ACCESSORS
	//

	bool		exists() const;
	QString		getFilename() const;
	QString		getFiletype() const;
	DzVersion	getFileVersion() const;
	DzAuthor	getAuthor() const;
	QString		getAuthorComment() const;
	bool		isMerge() const;

signals:

	void	unableToFindFile( const QString &file );
	void	readFinished();
	void	postReadFinished();

private:

	DzError	readFileInformation();
	void	loadSection( short sectionID );
	QString	getAbsolutePath( const QString &filename ) const;
	int		readBlock( char *data, int maxlen );
	DzError	readPointerInternal( int sectionLength );
	DzError	readUIntInternal( unsigned int &val );
	DzError	readUInt64Internal( quint64 &val );
	DzError	readUShortInternal( unsigned short &val );
	DzError	readStringInternal( QString &val );
	DzError	readGUIDInternal( DzGuid &guid );
	DzError	getStorable( const DzGuid &classID, const QString &filename, DzStorable **storable );
	bool	isCancelled();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_IN_FILE_H
