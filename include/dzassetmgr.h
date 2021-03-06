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
	Defines the DzAssetMgr class.
**/

#ifndef DAZ_ASSET_MGR_H
#define DAZ_ASSET_MGR_H

/****************************
	Include files
****************************/

#include <QtCore/QVariantList>

#include "dzbase.h"
#include "dztoplevelassetcontainer.h"
#include "dztsharedpointer.h"
#include "dzbasicdialog.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzCategoryAssetContainer;
class DzContentSearchOptions;
class DzDBCategoriesTable;
class DzDBCompatibilityBaseTable;
class DzDBContentTable;
class DzDBCriteria;
class DzDBSelect;
class DzFolderAssetContainer;
class DzGuid;
class DzNode;
class DzSearchDBThread;
class DzSearchFileThread;
class DzTopLevelAssetContainer;
class IDzDir;
class IDzObjectDatabase;
class IDzSimpleFile;
class QDomElement;
class QDomNode;
class QRadioButton;
class QImage;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzAbstractContentSupplier : public QObject
{
	Q_OBJECT
public:
	virtual void	setBuiltInContentShowing( bool onOff ) = 0;
	virtual bool	isBuiltInContentShowing() const = 0;
	virtual QString getBuiltInContentDirectoryPath() const = 0;

	virtual int		getNumContentDirectories() const = 0;
	virtual QString getContentDirectoryPath( int which ) const = 0;

	virtual int		getNumImportDirectories() const = 0;
	virtual QString	getImportDirectoryPath( int which ) const = 0;

	virtual int		getNumPoserDirectories() const = 0;
	virtual QString	getPoserDirectoryPath( int which ) const = 0;
		
	virtual QStringList	getRelativePaths( const QString &absolutePath, bool useImportFolders ) const = 0;

signals:
	void	contentDirectoryListChanged();
	void	importDirectoryListChanged();
	void	poserDirectoryListChanged();
	void	categoryListChanged();
	void	folderTreeChanged();
};

class DZ_EXPORT DzAssetMgr : public DzBase {
	Q_OBJECT
	Q_FLAGS( SearchOptions )
public:
	
	DzAssetMgr( IDzObjectDatabase *db = NULL, DzAbstractContentSupplier *supplier = NULL,
			IDzSimpleFile *simpleFile = NULL, IDzDir *dir = NULL );

	~DzAssetMgr();

	enum SearchOption
	{
		None = 0x0,
		WholeWord = 0x04,
		RegExp = 0x08,
		NativeScenes = 0x010,
		NativeScripts = 0x020,
		PoserFigures = 0x0100,
		PoserPoses = 0x0200,
		PoserProps = 0x0400,
		PoserHair = 0x0800,
		PoserFaces = 0x01000,
		PoserLights = 0x02000,
		PoserCameras = 0x04000,
		PoserHands = 0x08000,
		PoserMaterials = 0x010000,
		PoserScenes = 0x020000,
		ImportFiles = 0x0100000,
		AllNativeFiles = NativeScenes | NativeScripts,
		NoNativeFilesMask = ~AllNativeFiles,
		AllPoserFiles = PoserFigures | PoserPoses | PoserProps | PoserHair | PoserFaces |
			PoserLights | PoserCameras | PoserHands | PoserMaterials | PoserScenes,
		NoPoserFilesMask = ~AllPoserFiles,
		AllFiles = ImportFiles | AllPoserFiles | AllNativeFiles,
		DefaultOptions = AllFiles
	};
	Q_DECLARE_FLAGS( SearchOptions, SearchOption )

public:
	IDzObjectDatabase*	getObjectDatabase() const;

	static void			buildSearchCriteria( const QString &searchTerm, DzDBCriteria &crit, SearchOptions opts );
	static void			buildInternalSelect( const QString &searchTerm, DzDBSelect &select, const QStringList &cateogries, 
							const QStringList &compatibilityBases, const QStringList &contentTypes, bool includeKeywordsOnIns );
	static void			buildSearchCriteria( const QString &searchTerm, DzDBCriteria &crit, const QStringList &cateogries, 
							const QStringList &compatibilityBases, const QStringList &contentTypes );
	static void			breakSearchTermIntoList( const QString &searchTerm, QStringList &list );
	static DzDBCompatibilityBaseTablePtr findCompatibilityBase( const QString &uri );
	static QStringList	searchAutoComplete( const QStringList& previousTerms, const QString& curTerm, const QStringList &cateogries, 
											const QStringList &compatibilityBases, const QStringList &contentTypes, int limit );
	
	static bool	getTypeForContentFile( const QString fullPath, QString &type );
	static bool	typeIsClothing( const QString &type );
	static bool	typeIsFigure( const QString &type );
	static bool	typeIsHair( const QString &type );
	static bool	typeIsPreset( const QString &type );
	static bool	typeIsPresetForFigure( const QString &type );
	static bool	typeIsProp( const QString &type );
	static bool	typeIsFollower( const QString &type );
	static bool	typeIsReplaceable( const QString &type );
	static bool	typeNeedsBaseFigure( const QString &type );

	QStringList readMetaXml( const QByteArray &xml, bool runSilent = false, bool isVendor = false, bool markNew = true );
	void        shutdown();
	void        resetDatabase();
	void        showInStore(DzProductAssetContainerPtr pcontainer);

	QImage 	getPixmapForContentType( int typeId );
	

public slots:
	DzTopLevelAssetContainer*	getPoserDirs() const;
	DzTopLevelAssetContainer*	getContentDirs() const;
	DzTopLevelAssetContainer*	getImportDirs() const;
	DzTopLevelAssetContainer*	getProducts() const;
	DzCategoryAssetContainer*	getCategories() const;

#ifndef Q_MOC_RUN
	static
#endif
	DzError			saveUserDBData(const QString& directory, const QString& prefix);

#ifndef Q_MOC_RUN
	static
#endif
	QString		getMetaHost();

#ifndef Q_MOC_RUN
	static
#endif
	bool		setCompatibilityBase( const QString &uri, DzDBCompatibilityBaseTable *compatibility, bool isVendor );

#ifndef Q_MOC_RUN
	static
#endif
	QVariant	getStudioDirID();
#ifndef Q_MOC_RUN
	static
#endif
	QVariant	getImportDirID();
#ifndef Q_MOC_RUN
	static
#endif
	QVariant	getPoserDirID();

#ifndef Q_MOC_RUN
	static
#endif
	QVariant	getCategoriesID();

#ifndef Q_MOC_RUN
	static
#endif
	QVariant	getProductsID();

#ifndef Q_MOC_RUN
	static
#endif
	void	setTopLevelPoserNameOnContainer( const QString &name, DzFolderAssetContainer *cont );

#ifndef Q_MOC_RUN
	static
#endif
	QString	normalizePath( const QString &type, bool relative = true);

#ifndef Q_MOC_RUN
	static
#endif
	QString	escapeSearchTerm( const QString &searchTerm );

#ifndef Q_MOC_RUN
	static
#endif
	QString	getRealPathCasing( const QString &path, const QString &search );

#ifndef Q_MOC_RUN
	static
#endif
	QStringList	getStudioExcludes();

	void	updateUserMetadata();
	void	emitCategoryChanged( QVariantList idPath );

	void	markCategoriesChanged();
	void	markProductsChanged();

	bool	showLargeIcons() const;
	bool	showExtensions() const;
	bool	showAssetToolTip() const;
	int		getNumMaxItemsPerPage() const;
	int		getMaxChunkSize() const;
	bool	getMarkFoldersContainingNewContent() const;
	void	setMarkFoldersContainingNewContent( bool onOff );

	void	setShowLargeIcons( bool onOff );
	void	setShowExtensions( bool onOff );
	void	setShowAssetToolTip( bool onOff );
	void	setMaxItemsPerPage( int maxNum );
	void	setMaxChunkSize( int maxSize );

	void		refreshTypes();
	QStringList	getTypes();
	quint32		findTypeID( const QString &type, bool create = false, bool defaultLoad = false );
	quint32		createType( const QString &type, bool defaultLoad );
	QString		getType( quint32 id );
		
	QStringList	getAudiences();
	quint32		findAudienceID( const QString &audience );
	QString		getAudience( quint32 id );

	QStringList	getRootCategoryStrings();
	void		refreshCategoryRoots();

	DzDBCompatibilityBaseTable*	findCompatibilityBaseTable( const QString &plat, bool create = true );
	quint32		findCompatibilityBaseID( const QString &plat, bool create = true );
	quint32		createCompatibilityBase( const QString &plat );
	QString		getCompatibilityBase( quint32 id );

	void		refreshBasePaths();
	QStringList	getBasePaths();
	quint32		findBasePathID( const QString &basePath, bool create = true );
	quint32		createBasePath( const QString &basePath );
	QString		getBasePath( quint32 id );
	void		removeAndCleanBasePath( quint32 id );
	QStringList	getUnMappedBasePaths();


	void		refreshStores();
	QStringList	getStoresIDs() const;
	QString		getStoreUrl( const QString &storeID ) const;
	QString		getStoreToken( const QString &storeID ) const;
	bool		createStore( const QString &storeID, const QString &token, const QString &url );

	void	stopDBSearch();
	void	stopProductSyncThread();
	void	stopFileSearch();
	void	stopFileScan();
	void	stopSearchForFileAssociations();
	void	stopStoreSearch();
	void	stopSearchForProducts();
	void	stopAllSearches();
	
	bool	searchForFileAssociations( DzDBContentTable *tab, /*DzSearchContainerPtr requiresSearch, 
				DzSearchContainerPtr requiredBySearch,*/ DzSearchContainerPtr customizedBy,
				DzSearchContainerPtr customizes, QObject *finishObj = NULL, QObject *progress = NULL );

	void	scanFiles( SearchOptions opts, bool markFound, bool addToUnassigned, bool onlyNewToUnassigned, QObject *finishObj = NULL, QObject *progress = NULL );

	DzSearchContainerPtr	searchFiles( const QString &str, SearchOptions opts, QObject *finishObj = NULL, 
								QObject *progress = NULL);
	DzSearchContainerPtr	searchDB( const QString &str, SearchOptions opts, QObject *finishObj = NULL,
								QObject *progress = NULL);
	DzSearchContainerPtr	searchDB( const QString &str, const QStringList &categories, const QStringList &compatibilityBases, 
								const QStringList &contentTypes, DzSearchDBThread *thread = NULL, QObject *finishObj = NULL,
								QObject *progress = NULL );

	DzProductHolderContainerPtr	productSearchDB( const QString &str, const QStringList &categories, 
									const QStringList &compatibilityBases, const QStringList &contentTypes,
									QObject *finishObj = NULL, QObject *progress = NULL );
	DzProductHolderContainerPtr	storeSearch( const QString &str, const QStringList &types, 
									const QString &compatibilityBase, DzContentSearchOptions *options,
									QObject *finishObj = NULL, QObject *progress = NULL );

	QString	getDatabaseFilePath() const;
	bool	vacuumDatabase();

	void	markAllContentSeen( bool notify = true );
	void	syncFileMetadata( const QStringList &relativeFilePaths, bool prepend = false );
	void	syncProductMetadata( const DzDBObjectBasePtrList &productTables, bool prepend = false );
	void	prependToMetadataSyncList( const QString &productGuid );
	void	prependToMetadataSyncList( const QStringList &productGuidList );
	void	processSyncList();

	QStringList	processDBMetaFile( const QString &productRelativePath, bool runSilent = false, bool isVendor = false, bool markNew = true );
	void	queueDBMetaFile( const QString &productRelativePath );
	QStringList	getDBMetaFileQueue();
	void	processDBMetaFileQueue();
	void	clearDBMetaFileQueue();
	void	reimportDBMetaFiles();

#ifndef Q_MOC_RUN
	static
#endif
	void getBaseAndRelativePath( const QString& absolutePath,QString& rPath, QString& basePath );

#ifndef Q_MOC_RUN
	static
#endif
	QString	getAssetUriForNode( DzNode *node );
#ifndef Q_MOC_RUN
	static
#endif
	QString	getCompatibilityBasePathForNode( DzNode *node );

	QStringList	getRelativePaths( const QString &absolutePath, bool useImportFolders ) const;

	QString	getTypeForNode( const DzNode *node ) const;
	QString	getTypeForContentFile( const QString fullPath ) const;
	bool	isClothingType( const QString &type ) const;
	bool	isFigureType( const QString &type ) const;
	bool	isHairType( const QString &type ) const;
	bool	isPresetType( const QString &type ) const;
	bool	isPresetForFigureType( const QString &type ) const;
	bool	isPropType( const QString &type ) const;
	bool	isFollowingType( const QString &type ) const;
	bool	isReplaceableType( const QString &type ) const;
	bool	isNeedsBaseFigureType( const QString &type ) const;

signals:
	void	categoryUpdate( QVariantList idPath );
	void	containerUpdate( QVariantList idPath );

	void	markFoldersContainingNewContentChanged();
	void	showLargeIconsChanged();
	void	showExtensionsChanged();
	void	showAssetToolTipChanged();
	void	itemsPerPageChanged( int newPerPage );
	void	typeListChanged();
	void	compatibilityBaseListChanged();
	void	basePathsChanged();
	void	storeListChanged();

private slots:
	void	poserDirsChanged();
	void	importDirsChanged();
	void	contentDirsChanged();
	void	folderTreeChanged();
	void	categoryChanged();
	void	productChanged();
	void	appClosing();
	void	removeFromSyncList( const QString &guid );
	void	syncThreadFinished();
	void	readContentTypes();
	void	readCompatibilityTypes();
	void	readRootCategories();
	void	addImportFolder( const QString &path, DzTopLevelAssetContainer *container, const QStringList &filters ) const;
	void	addPoserFolder( const QString &path, DzTopLevelAssetContainer *container ) const;
	void	addStudioContentFolder( const QString &path, DzTopLevelAssetContainer *container ) const;

private:

	static void	setUpCriteriaForStudioFiles( SearchOptions &opts, DzDBCriteria &criteria );
	static void	setUpCriteriaForPoserFiles( SearchOptions &opts, DzDBCriteria &criteria );
	
	void	setUpStudioSearchFolders( SearchOptions &opts, DzSearchFileThread *setupThread, bool scan, bool markNew, bool addToUnassigned, bool onlyNewToUnassigned );
	void	buildSearchFromSubFolders( const QString &path, const QStringList &filter, DzSearchFileThread *setupThread, 
				bool addBasePath, bool scan, bool studio, bool markNew, bool addToUnassigned, bool onlyNewToUnassigned ) const;
	void	setUpImportSearchFolders( DzSearchFileThread *setupThread, bool scan, bool markNew, bool addToUnassigned, bool onlyNewToUnassigned );
	void	setUpPoserSearchFolders( SearchOptions opts, DzSearchFileThread *setupThread, bool scan, bool markNew, bool addToUnassigned, bool onlyNewToUnassigned );

	DzFolderAssetContainer*	doDirFolderCommon( const QString &path, DzTopLevelAssetContainer *container, bool basePath ) const;

	void	processPoserPathForSearch( const QString &inPath, SearchOptions opts, DzSearchFileThread *setupThread, bool scan, bool markNew, bool addToUnassigned, bool onlyNewToUnassigned );
	void	buildPoserFileFilter( const QString &name, QStringList &filter ) const;
	void	buildExportFilter( QStringList &ext ) const;
	void	buildStudioFilterList( QStringList &filter, bool scene, bool script ) const;
	void	addPoserFolderToThread( const QString &workingPath, const QString &search, SearchOptions opts, SearchOption opt, DzSearchFileThread *setupThread, 
				bool scan, bool markNew, bool addToUnassigned,bool onlyNewToUnassigned) const;
	

	void	readFromSyncFile();
	void	writeToSyncFile();
	void	runNextProductSync();

	void		finishBackProg();
	static void	buildChildListRecurse( DzDBCategoriesTable *catTab, QVariantList &childList );
	void		addProductToList( QString guid, DzDBObjectBasePtrList &prods, QString date );
	void		cleanUpProductVendorInfo( DzDBProductTable *productTable );

	DzDBProductTablePtr	popTopSyncProduct();
	DzDBProductTablePtr	peekTopSyncProduct();

	QImage	readPixmapfromType( const QString & type );

	struct	Data; 
	Data	*m_data;
};

extern DZ_EXPORT DzAssetMgr *dzAssetMgr;

class DzSyncProductDlg : public DzBasicDialog
{
	Q_OBJECT
public:
	DzSyncProductDlg( QWidget *parent, const DzDBProductTablePtrList &prodList );
	~DzSyncProductDlg();
	DzDBProductTablePtrList getSelectedProducts();
public slots:
	int		getDialogUseState();
protected:
	virtual void	accept();
	virtual void	reject();
private:
	void	getModel();

	struct	Data; 
	Data	*m_data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( DzAssetMgr::SearchOptions )

#endif // DAZ_ASSET_MGR_H
