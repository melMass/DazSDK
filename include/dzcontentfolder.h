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
	Defines the DzContentFolder class.
**/

#ifndef DAZ_CONTENT_FOLDER_H
#define DAZ_CONTENT_FOLDER_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"
#ifndef DSON_IO
#include "dzcontentfile.h"
#endif


class DzContentFolder;

/*****************************
	Definitions
*****************************/

typedef DzTSharedPointer<DzContentFolder>		DzContentFolderPtr;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzContentFolder : public DzBase, public DzRefCountedItem {
	Q_OBJECT
	Q_ENUMS( FolderType )
	Q_PROPERTY( QString fullPath READ getFullPath )
	Q_PROPERTY( QString folderName READ getFolderName )
	
#ifndef DSON_IO
	Q_PROPERTY( QString label READ getLabel )
	Q_PROPERTY( QPixmap icon READ getIcon )
	Q_PROPERTY( bool foldersAreLoaded READ foldersAreLoaded )
	Q_PROPERTY( bool filesAreLoaded READ filesAreLoaded )
	Q_PROPERTY( bool canAddSubFolder READ canAddSubFolder )
	Q_PROPERTY( int folderType READ getFolderTypeAsInt )
	Q_PROPERTY( bool canDelete READ canDelete )
	Q_PROPERTY( bool canRename READ canRename )
	Q_PROPERTY( bool isBuiltInContentFolder READ isBuiltInContentFolder )
#endif
	

public:
	enum FolderType { NATIVE_TYPE, POSER_TYPE, IMPORT_TYPE };

	//
	// CREATORS
	//

	DzContentFolder( const QString &name = "Blank", FolderType tp = NATIVE_TYPE,
		DzContentFolder *parent = NULL );
	~DzContentFolder();

	//
	// MANIPULATORS
	//
#ifndef DSON_IO
	void		loadFolders();
	void		unloadFolders();
	void		loadFiles();
	void		unloadFiles();
	void		addAlias( DzContentFolder *folder, const QString &name );
	void		removeAlias( DzContentFolder *folder );


	bool		filesNeedUpdate( QStringList *names = NULL );
	bool		foldersNeedUpdate( QStringList *names = NULL );
#endif

	QString		getFullPath() const;
	QString		getFolderName() const;
	FolderType	getFolderType() const;

#ifndef DSON_IO
	QString		getLabel() const;
	QPixmap		getIcon() const;
	int			getFolderTypeAsInt() const { return (int) getFolderType(); } // for DAZ Script
	bool		foldersAreLoaded() const;
	bool		filesAreLoaded() const;
	bool		canAddSubFolder() const;
	bool		canDelete() const;
	bool		canRename() const;
	bool		isBuiltInContentFolder() const;
	bool		containsFile( QString &fileName );
#endif

public slots:
	DzContentFolder*		getParent() const;

#ifndef DSON_IO
	bool					refresh( bool reloadIcons = false );
	DzContentFolder*		getFirstFolder() const;
	DzContentFolder*		getFirstHiddenFolder() const;
	DzContentFolder*		getNext() const;

	DzContentFile*			getFirstFile() const;
	DzContentFile*			getFirstHiddenFile() const;
	bool					canMoveFile( DzContentFilePtr file ) const;
	bool					canMoveFiles( const QList<DzContentFilePtr> &files ) const;
	bool					moveFile( DzContentFilePtr file ) const;
	bool					moveFiles( const QList<DzContentFilePtr> &files ) const;
	bool					copyFile( DzContentFilePtr file ) const;
	bool					copyFiles( const QList<DzContentFilePtr> &files ) const;

	bool					hasSubFolders() const;
	bool					addSubFolder( const QString &folderName ) const;
	bool					deleteFolder() const;
	bool					rename( const QString &newName );

#endif
	bool					isModifiable() const;

#ifndef DSON_IO
signals:

	void				addedFolder( DzContentFolder *newFolder );
	void				removedFolder( DzContentFolder *folder );
	void				folderListChanged();
	void				fileListChanged();

#endif

private:

	struct	Data;
	Data	*m_data;

#ifndef DSON_IO
	void				getFolderList( QStringList &folderList ) const;
	void				getFileList( QStringList &fileList );
	void				loadFiles( QStringList &files );
	void				loadFolders( QStringList &folders );
	bool				copyFile( const QString &srcFilename, const QString &tgtFilename ) const;
	bool				deleteFolderRecurse( const QString &folderPath ) const;
#endif
	void				setIsModifiable();

};

#endif // DAZ_CONTENT_FOLDER_H
