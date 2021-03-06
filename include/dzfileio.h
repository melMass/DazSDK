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
	Defines the DzFileIO class.
**/

#ifndef DAZ_FILE_IO_H
#define DAZ_FILE_IO_H

/****************************
	Include files
****************************/

#include "dzbase.h"

#ifndef DSON_IO
#include "dzoptionsframe.h"
#include "dzbasicdialog.h"
#endif

/****************************
	Forward declarations
****************************/

class DzFileIOSettings;

/****************************
	Class definitions
****************************/
#ifndef DSON_IO
class DZ_EXPORT DzFileIOFrame : public DzOptionsFrame {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzFileIOFrame( const QString &label, QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzFileIOFrame();

	virtual void	setOptions( const DzFileIOSettings *settings, const QString &filename ) = 0;
	virtual void	getOptions( DzFileIOSettings *settings ) const = 0;
};
#endif

class DZ_EXPORT DzFileIO : public DzBase {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzFileIO();
	virtual ~DzFileIO();

	//
	// ACCESSORS
	//
#ifndef DSON_IO 
	virtual DzFileIOFrame*	getOptionsFrame() const;
#endif

public slots:

	virtual void	getDefaultOptions( DzFileIOSettings *options ) const = 0;
	virtual bool	getOptions( DzFileIOSettings *options, bool useInterface, const QString &filename ) const;
	bool			showOptions() const;

public:

	//
	// STATIC
	//

	static bool			userFindFile( const QString &filename, QString &foundPath );
	static bool			pathExists( const QString &path, bool create = false );
	static void			resetUserFindFile();
	static QString		getFileExtension( const QString &filename );
	static QString		getFilePath( const QString &filename );
	static QString		getShortFileName( const QString &filename );
	static QString		getBaseFileName( const QString &filename );
	static QString		changeFileExtension( const QString &filename, const QString &newExtension );
	static QString		fixName( const QString &name );
	static bool			copyFile( const QString &srcFilename, const QString &tgtFilename, bool showProgress= false);
	static QStringList	getFilesFromDirectory( const QString &dirPath, const QStringList &extentions, bool recursive = true );

protected:

	//
	// MANIPULATORS
	//

	void			error( const QString &msg );
	void			info( const QString &msg );
	void			getSavedOptions( DzFileIOSettings *settings ) const;
	void			saveOptions( const DzFileIOSettings *settings ) const;
	virtual void	startIO();
	virtual void	finishIO();
	virtual QString	getPreIOErrorString();

private:

	//
	// DATA
	//

	struct	Data;
	Data	*m_data;
};

#ifndef DSON_IO
class DZ_EXPORT DzFileIODlg : public DzBasicDialog {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzFileIODlg( DzOptionsFrame *frame );

public:

	virtual void	apply();
protected:
	virtual void	accept();
private:

	DzOptionsFrame	*m_frame;
};
#endif

#endif // DAZ_FILE_IO_H
