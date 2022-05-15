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
	Defines the DzContentFile class.
**/

#ifndef DAZ_CONTENT_FILE_H
#define DAZ_CONTENT_FILE_H

/*****************************
	Include files
*****************************/

#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class DzContentFile;
class DzContentFolder;
class QPixmap;

/*****************************
	Definitions
*****************************/

typedef DzTSharedPointer<DzContentFile>	DzContentFilePtr;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzContentFile : public QObject, public DzRefCountedItem {
	Q_OBJECT
	Q_PROPERTY( QString name READ getName )
	Q_PROPERTY( QString label READ getLabel )
	Q_PROPERTY( QString fullPath READ getFullPath )
	Q_PROPERTY( QString companionPath READ getCompanionPath )
	Q_PROPERTY( QPixmap icon READ getIcon )
	Q_PROPERTY( QPixmap smallIcon READ getSmallIcon )
	Q_PROPERTY( bool isNative READ isNative )
	Q_PROPERTY( bool isScript READ isScript )
	Q_PROPERTY( bool hasCompanion READ hasCompanion )
	Q_PROPERTY( bool companionIsScript READ companionIsScript )
	Q_PROPERTY( bool hasCompanionScript READ hasCompanionScript )
	Q_PROPERTY( bool canDelete READ canDelete )
	Q_PROPERTY( bool canRename READ canRename )
public:
	//
	// CREATORS
	//

	DzContentFile( const QString &name, DzContentFolder *parent, DzContentFile *prevSibling = NULL );
	DzContentFile( const int contentIndex, const QString &path, DzContentFile *prevSibling = NULL );
	DzContentFile( const int contentIndex, bool isNew, const QString &path, DzContentFile *prevSibling = NULL );
	~DzContentFile();

	int		getContentIndex() const;
	QString	getName() const;
	QString	getLabel() const;
	QString	getFullPath() const;
	QString	getCompanionPath() const;
	QPixmap	getIcon() const;
	QPixmap	getSmallIcon() const;
	bool	isNative() const;
	bool	isScript() const;
	bool	hasCompanion() const;
	bool	companionIsScript() const;
	bool	hasCompanionScript() const; // keep for compatibility
	bool	canDelete() const;
	bool	canRename() const;
	bool	isNew() const;

	void	setNew( bool isNew );

public slots:
	//
	// MANIPULATORS
	//

	bool	deleteFile();
	bool	rename( const QString &newName );
	void	reloadIcon();

	//
	// ACCESSORS
	//

	DzContentFolder*	getFolder() const;
	DzContentFile*		getNext() const;

private slots:

	void				folderRemoved();

private:
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;

	//
	// MANIPULATORS
	//

	bool	loadPngIcon( const QString &path );
	bool	loadRsrIcon( const QString &path );
};

#endif // DAZ_CONTENT_FILE_H
