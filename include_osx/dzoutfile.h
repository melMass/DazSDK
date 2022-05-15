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
	Defines the DzOutFile class.
**/

#ifndef DAZ_OUT_FILE_H
#define DAZ_OUT_FILE_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Definitions
****************************/

#define DZ_BINARY_FILE_IDENTIFIER	"DAZB"
#define DZ_ASCII_FILE_IDENTIFIER	"DAZA"
#define DZ_SCRIPT_FILE_IDENTIFIER	"DAZS"

// This flag will be set if the file has been encrypted.
#define DZ_FILE_IS_ENCRYPTED		0x00000001
#define DZ_FILE_HAS_PRODUCT_ID		0x00000002
#define DZ_FILE_IS_BETA_CONTENT		0x10000000

// These are reserved section ID's used to indicate the start of a pointer definition
#define DZ_FILE_POINTER_SECTION			0x00f0
#define DZ_FILE_STORABLE_SECTION		0x00f1
#define DZ_FILE_POINTER_REF_SECTION		0x00f2
#define DZ_FILE_STORABLE_REF_SECTION	0x00f3

/****************************
	Forward declarations
****************************/

class DzBase;
class DzGuid;
class DzMatrix3;
class DzMatrix4;
class DzQuat;
class DzTimeRange;
class DzVec3;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzOutFile : public QObject {
public:
	//
	// CREATORS/DESTRUCTORS
	//

	DzOutFile( const QString &filename, const QString &filetype, const QString &authorComment = QString::null );
	~DzOutFile();

	//
	// MANIPULATORS
	//

	DzError	open( bool allowPointerWrites );
	DzError	writePointerDefinitions();
	void	close();
	DzError	startSection( short sectionID );
	DzError	endSection();
	DzError	write( const DzBase *ptr );
	DzError	writeChar( char val );
	DzError	writeChars( const char *buf, int count );
	DzError	writeUChar( unsigned char val );
	DzError	writeUChars( const unsigned char *buf, int count );
	DzError	writeInt( int val );
	DzError	writeInts( const int *buf, int count );
	DzError	writeUInt( unsigned int val );
	DzError	writeUInts( const unsigned int *buf, int count );
	DzError	writeInt64( qint64 val );
	DzError	writeInt64s( qint64 *buf, int count );
	DzError	writeUInt64( quint64 val );
	DzError	writeUInt64s( quint64 *buf, int count );
	DzError	writeShort( short val );
	DzError	writeShorts( const short *buf, int count );
	DzError	writeUShort( unsigned short val );
	DzError	writeUShorts( const unsigned short *buf, int count );
	DzError	writeFloat( float val );
	DzError	writeFloats( const float *buf, int count );
	DzError	writeDouble( double val );
	DzError	writeDoubles( const double *buf, int count );
	DzError	writeBool( bool val );
	DzError	writeString( const QString &val );
	DzError	writeCompressedString( const QString &val );
	DzError	writeVec( const DzVec3 &vec );
	DzError	writeShortVec( const DzVec3 &vec, float scale );
	DzError	writeRot( const DzQuat &rot );
	DzError	writeMatrix3( const DzMatrix3 &mtx );
	DzError	writeMatrix4( const DzMatrix4 &mtx );
	DzError	writeByteArray( const QByteArray &bytes );
	DzError	writePointer( const DzBase *item, short pointerID );
	DzError	writeGUID( const DzGuid &guid );
	DzError	writeCharSection( short sectionID, char val );
	DzError	writeUCharSection( short sectionID, unsigned char val );
	DzError	writeIntSection( short sectionID, int val );
	DzError	writeUIntSection( short sectionID, unsigned int val );
	DzError	writeShortSection( short sectionID, short val );
	DzError	writeUShortSection( short sectionID, unsigned short val );
	DzError	writeFloatSection( short sectionID, float val );
	DzError	writeDoubleSection( short sectionID, double val );
	DzError	writeBoolSection( short sectionID, bool val );
	DzError	writeStringSection( short sectionID, const QString &val );
	DzError	writeCompressedStringSection( short sectionID, const QString &val );
	DzError	writeTimeRangeSection( short sectionID, const DzTimeRange &range );
	DzError	writeVecSection( short sectionID, const DzVec3 &vec );
	DzError	writeShortVecSection( short sectionID, const DzVec3 &vec, float scale );
	DzError	writeRotSection( short sectionID, const DzQuat &rot );
	DzError	writeMatrix3Section( short sectionID, const DzMatrix3 &mtx );
	DzError	writeMatrix4Section( short sectionID, const DzMatrix4 &mtx );
	DzError	writeByteArraySection( short sectionID, const QByteArray &bytes );
	DzError	writePointerSection( short sectionID, const DzBase *item, short pointerID );
	DzError	writeGuidSection( short sectionID, const DzGuid &guid );

	//
	// ACCESSORS
	//

	QString	getFullFilename() const;
	QString	getPath() const;
	QString	getFilename() const;
	bool	isOpen() const;

private:

	void			writeFileInformation();

	// Opens a section for writing. Returns DZ_ILLEGAL_OPERATION_ERROR if
	// a section is already open for writing.
	DzError			startSectionInternal( short sectionID );

	DzError			writeUIntInternal( unsigned int val );
	DzError			writeUInt64Internal( quint64 val );
	DzError			writeShortInternal( short val );
	DzError			writeUShortInternal( unsigned short val );
	DzError			writeStringInternal( const QString &val );
	DzError			writePointerInternal( const DzBase *item );
	DzError			writeGUIDInternal( const DzGuid &guid );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_OUT_FILE_H
