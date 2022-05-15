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
	Defines the DzFolderAssetContainer class.
**/

#ifndef DAZ_FOLDER_ASSET_CONTAINER_H
#define DAZ_FOLDER_ASSET_CONTAINER_H

/*****************************
	Include files
*****************************/

#include "dzabstractassetcontainer.h"

/*****************************
	Forward declare
*****************************/

class DzDBContentFoldersTable;

/*****************************
	Class definitions
*****************************/

class IDzDir;
typedef DzTSharedPointer<IDzDir> IDzDirPtr;

class DZ_EXPORT IDzDir : public DzRefCountedItem
{
public:
	virtual ~IDzDir(){}

	virtual QString		dirName() const = 0;
	virtual QString		absDirPath() const = 0;

	virtual QStringList	getChildDirectories() const = 0;
	virtual QStringList	getFiles( const QStringList &filters ) const = 0;
	virtual bool		createDir( const QString &dirName ) = 0;
	virtual bool		rename( const QString &oldName, const QString &newName ) = 0;
	virtual bool		remove( const QString &name ) = 0;
	virtual IDzDir*		newDir( const QString &dirName ) const = 0;
};

class DZ_EXPORT IDzSimpleFile
{
public:
	virtual ~IDzSimpleFile(){}

	virtual bool			copyFile( const QString &oldPath, const QString &newPath ) = 0;
	virtual bool			deleteFile( const QString &oldPath ) = 0;
	virtual bool			exists( const QString &path ) = 0;
	virtual IDzSimpleFile*	newSimpleFile() = 0;
};


class DZ_EXPORT DzFolderAssetContainer : public DzAbstractAssetContainer 
{
	Q_PROPERTY( QStringList excludeFolders READ getExludeFolders WRITE setExcludeFolders )
	Q_PROPERTY( QStringList onlyIncludeFolders READ getOnlyIncludeFolders WRITE setOnlyIncludeFolders )
	Q_PROPERTY( QStringList fileFilters READ getFileFilters WRITE setFileFilter )
	Q_OBJECT

public:
	DzFolderAssetContainer( QString dirPath, bool basePath, DzAbstractAssetContainer *owner = NULL );
	DzFolderAssetContainer( IDzDir *dir, IDzSimpleFile *fileWorker, DzAbstractAssetContainer *owner = NULL );
	DzFolderAssetContainer( IDzDir *dir, IDzSimpleFile *fileWorker, DzDBContentFoldersTable* folder, DzAbstractAssetContainer *owner);

	virtual ~DzFolderAssetContainer();

	virtual void	setExcludeFolders( const QStringList &excludeList );
	virtual void	setOnlyIncludeFolders( const QStringList &includeList );
	virtual void	setFileFilter( const QStringList &list );

	virtual QStringList	getExludeFolders() const;
	virtual QStringList	getOnlyIncludeFolders() const;
	virtual QStringList	getFileFilters() const;
	
	virtual bool	getCanCopyContainers() const;

	virtual void	loadMetadata( DzAsset *asset );
	virtual bool	updateMetadata( DzAsset *asset );
	virtual void	markAsTopLevelStudio();
	virtual bool	isTopLevelStudio() const;
	virtual void	markAsTopLevelPoser();
	virtual bool	isTopLevelPoser() const;
	virtual void	markAsTopLevelImport();
	virtual bool	isTopLevelImport() const;
	virtual void	makeNativeFolder();
	virtual bool	isNativeFolder() const;

	virtual bool	showAsNew();

	static int		getStandardFolderIconSize();

public slots:
	virtual QString	getFullPath() const;

	virtual bool	isFileSystemBased() const;

	virtual bool	renameChildContainer( DzAbstractAssetContainer *container, const QString &name );
	virtual bool	removeChildContainer( DzAbstractAssetContainer *container);
	virtual bool	createNewChildContainer( const QString &containerName );
	virtual bool	insertChildContainer( DzAbstractAssetContainer *container );
	virtual bool	moveFromParent( DzAbstractAssetContainer *child );

	virtual bool	hasAsset( const DzAsset *asset );
	virtual bool	removeAsset( DzAsset *asset );
	virtual bool	insertAsset( const DzAsset *asset );

	bool			fileMatchesFilter( const QString &shortFileName );
	virtual bool	renameAsset( DzAsset *asset, const QString &newAssetName );

	virtual int		getNumChildContainers() const;
	virtual DzAbstractAssetContainerPtr	getChildContainer( int index );

	virtual bool	getChildContainers( DzAbstractAssetContainerList &list );
	virtual bool	getAssets( DzAssetList &list );
	virtual int		getNumAssets();
	virtual DzAssetPtr	getAsset( int index );

	virtual bool	initChildren();
	virtual bool	update();
	virtual bool	updateAssets();
	virtual bool	clearRebuildableAssets();
	virtual bool	updateChildren();
	DzDBContentFoldersTable*	getContentFolder() const;

#ifndef Q_MOC_RUN
	static
#endif 
	DzPixmapPair	getIconForPoserTopChildren( DzFolderAssetContainer *folder );
#ifndef Q_MOC_RUN
	static
#endif 
	DzPixmapPair	getIconForStandardFolder( DzFolderAssetContainer *folder );


private:
	void	init( DzAbstractAssetContainer *owner );
	void	initIsModifiable();
	void	buildAssets();

	void buildAssetsDB( QStringList &files, DzAssetList &workList );
	void	buildChildContainers();
	void	buildChildContainersDB( QStringList &dirs, DzAbstractAssetContainerList &workList );
	DzFolderAssetContainer*	createChildContainer( const QString &childName );
	DzFolderAssetContainer*	createChildContainer( const QString &childName, DzDBContentFoldersTable* folderTab );
	void	handleFile( const QString& filename, DzAssetList &workList, DzDBContentInstanceTable* tbl=NULL );
	struct	Data;
	Data*	m_data;
};

typedef DzTSharedPointer<DzFolderAssetContainer> DzFolderAssetContainerPtr;
Q_DECLARE_METATYPE(DzFolderAssetContainerPtr);
#endif // DAZ_FOLDER_ASSET_CONTAINER_H
