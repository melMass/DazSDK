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
	Defines the DzGzIO class.
**/

#ifndef DAZ_GZ_IO_H
#define DAZ_GZ_IO_H

/*****************************
	Include files
*****************************/

#include <QtCore/QIODevice>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzGzIO : public QIODevice {
	Q_OBJECT
public:
	DzGzIO( QIODevice *device, int compressionLevel = 6, int bufferSize = 65536 );
	~DzGzIO();

	virtual bool	isSequential() const;
	virtual bool	open( OpenMode mode );
	virtual void	close();
	virtual void	flush();
	virtual qint64	bytesAvailable() const;

protected:

	virtual qint64	readData( char *data, qint64 maxSize );
	virtual qint64	writeData( const char *data, qint64 maxSize );

private:

	void	flushZlib( int flushMode );
	bool	writeBytes( char *buffer, int outputSize );
	void	setZlibError( const QString &errorMsg, int zlibErrorCode );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_GZ_IO_H
