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
	Defines the DzContentMgr class.
**/

#ifndef DAZ_CONTENT_MGR_H
#define DAZ_CONTENT_MGR_H

/****************************
	Include files
****************************/

#include <QtCore/QVariantList>

#include "dzbase.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzContentDropOptions;
class DzContentFolder;
class DzContentReplaceMgr;
class DzFileLoadFilter;
class DzNode;
class QDir;
class DzSettings;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzContentMgr : public DzBase {
	Q_OBJECT
	Q_FLAGS( DirectoryTypes )
#ifndef DSON_IO
	Q_PROPERTY( QString startupScene READ getStartupScene WRITE setStartupScene )
	Q_PROPERTY( bool autoRefresh READ isAutoRefreshOn WRITE setAutoRefreshOn )
	Q_PROPERTY( bool showBuiltInContent READ isBuiltInContentShowing WRITE setBuiltInContentShowing )

	friend class DzApp;
	friend class DzContentUpdateThread;
#else
	friend class DzDSONIO;
#endif
private:
	//
	// CREATORS
	//

	DzContentMgr();
	~DzContentMgr();

public:
	enum DirectoryType
	{
		NativeDirs = 0x01,
		PoserDirs = 0x02,
		ImportDirs = 0x04,
		BuiltInDirs = 0x08,
		NativeAndBuiltInDirs = NativeDirs | BuiltInDirs,
		AllDirs = NativeDirs | PoserDirs | ImportDirs | BuiltInDirs
	};
	Q_DECLARE_FLAGS( DirectoryTypes, DirectoryType )

	//
	// REIMPLEMENTATIONS
	//
#ifndef DSON_IO
	virtual bool	event( QEvent *e );
	//
	// MANIPULATORS
	//
	bool	startup();
	void	shutdown();

	void	setStartupScene( const QString &filepath );
	void	setOnNewScene( const QString &filepath );
	QString	getStartupScene() const;
	QString	getOnNewScene() const;
	void	setAutoRefreshOn( bool onOff );
	bool	isAutoRefreshOn() const;

	void	setBuiltInContentShowing( bool onOff );
	bool	isBuiltInContentShowing() const;

	void	setContentDropOptions( DzContentDropOptions *options );
	void	importPreviouslyMappedDirectories();
	bool	userFindFile( const QString &filename, QString &foundPath, const QString& emptyName ) const;
#endif

public slots:

#ifndef DSON_IO
	void	setUseDatabaseSearch( bool useDatabase );
	void	setCheckCompatibilityOn( bool useCheckCompatibility );
	bool	usingDatabaseSearch();
	bool	usingCheckCompatibility();
	bool	doContentSearch();
#endif

	void	addContentDirectory( const QString &directory, bool saveSetting = true );
	void	addImportDirectory( const QString &directory, bool saveSetting = true );
	void	addPoserDirectory( const QString &directory, bool saveSetting = true );
#ifdef DSON_IO
	void	replaceContentAndPoserDirectories( const QStringList &dirs );
#endif
#ifndef DSON_IO
	bool	removeContentDirectory( const QString &directory );
	void	removeAllContentDirectories();
	bool	removeImportDirectory( const QString &directory );
	void	removeAllImportDirectories();
	bool	removePoserDirectory( const QString &directory );
	void	removeAllPoserDirectories();
	void	refresh( bool reloadIcons = false );
	bool	openFile( const QString &filename, bool merge = true );
	bool	mergeFiles( const QStringList &filenames );
	bool	openNativeFile( const QString &filename, bool isMerge=true );
	bool	importFile( const QString &path );
	void	fileCreated( const QString &filename );
	bool	poserDirectoryIsMapped( const QString &dirPath );
#endif
	
	
#ifndef DSON_IO
#ifndef Q_MOC_RUN
	static
#endif
	QString	getContentPath( const DzNode *node );
#endif	
	//
	// ACCESSORS
	//

	QString				getRelativePath( const QString &absolutePath, bool useImportFolders ) const;
	QStringList			getRelativePaths( const QString &absolutePath, bool useImportFolders ) const;
	QString				getMappedPath( const QString &path, bool useImportFolders, bool isRelative ) const;
	QString				getAbsolutePath( const QString &relativePath, bool useImportFolders, const QString& perferredPath = QString::null ) const;
	QStringList			getAbsolutePaths( const QString &relativePath, bool useImportFolders ) const;
	
	QString				getPoserAbsolutePath( const QString &relativePath ) const;
	QString				getNativeAbsolutePath( const QString &relativePath ) const;
	QString				getImportAbsolutePath( const QString &relativePath ) const;

#ifndef DSON_IO
	DzContentFolder*	getBuiltInContentDirectory() const;
	QString				getBuiltInContentDirectoryPath() const;
#endif

	int					getNumContentDirectories() const;
	DzContentFolder*	getContentDirectory( int which ) const;
	QString				getContentDirectoryPath( int which ) const;
	int					getNumImportDirectories() const;
	DzContentFolder*	getImportDirectory( int which ) const;
	QString				getImportDirectoryPath( int which ) const;
	int					getNumPoserDirectories() const;
	DzContentFolder*	getPoserDirectory( int which ) const;
	QString				getPoserDirectoryPath( int which ) const;
	QString				findFile( const QString &partialPath, DirectoryTypes dirTypes = NativeAndBuiltInDirs ) const;
	DzContentFolder*	findBaseDirectory( const QString &path, bool useImportFolders ) const;

#ifndef DSON_IO
	void				doDirNumCheck() const;

	DzContentReplaceMgr*	getContentReplaceMgr();
	
	QString				getDefaultContentDir() const;
	void				saveAllMappedDirectories() const;

	
	bool				isDirectoryMapped( const QString &directory )const;
	
	
	bool				reloadSceneAssetsFromSource( const DzSettings* settings);
	DzError				reloadAssetsFromSource( DzNode* sceneNode, const DzSettings* settings, const QString& srcFilePath=QString::null);
	DzError				reloadAssetsFromSource( const DzNodeList& sceneNodes, const DzSettings* settings, const QString& absolutePath );

	QString				findSourcePathForNode( DzNode* sceneNode );


public:

	bool		findPoserPaths( QStringList &list ) const;


	DzContentDropOptions*	getContentDropOptions() const;

signals:

	void	contentDirectoryListChanged();
	void	importDirectoryListChanged();
	void	poserDirectoryListChanged();
	void	folderTreeChanged();
	void	autoRefreshChanged( bool onOff );
	void	startupSceneChanged( const QString &filename );
	void	onNewSceneChanged( const QString &filename );
	void	newFileCreated( const QString &filename );

protected:


	//////////////////////
	// from QObject
	virtual void	timerEvent( QTimerEvent *e );

	bool			needUpdate();
#endif

private:

#ifndef DSON_IO
	bool				loadScript( const QString &path, const QVariantList &args );
	bool				updateBaseItemForLoad( const QString &fileName );
	void				contentReplaceInit( const QString &filename );
	void				doContentReplace();
	void				setDefaultContentDir();
#endif
	QString				getRelativePath( const QString &folderPath, const QString &absolutePath ) const;
	QString				getMappedPath( const QString &folderPath, const QString &path, bool isRelative ) const;
	QString				getAbsolutePath( const QString &folderPath, const QString &relativePath ) const;
#ifndef DSON_IO
	DzContentFolder*	findFolderRecurse( const QString &path, const DzContentFolder *folder ) const;
	bool				refreshRecurse( DzContentFolder *folder, bool reloadIcons );
	bool				needUpdateRecurse( DzContentFolder *folder );
	void				findPoserPathsRecurse( QDir &dir, QStringList &list ) const;
	void				savePoserDirectories() const;
	void				saveImportDirectories() const;
	void				saveContentDirectories() const;
	void				saveLegacyContentDirectories() const;
	void				saveStartupScene() const;
	void				saveOnNewScene() const;
	DzFileLoadFilter*	getFilterForFile( const QString &filename );
	QString				getProgramDataContentDir() const;
	void				cleanUpDBPathReferences( const QString& dir );
#endif

	struct	Data;
	Data	*m_data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( DzContentMgr::DirectoryTypes )

#endif // DAZ_CONTENT_MGR_H
