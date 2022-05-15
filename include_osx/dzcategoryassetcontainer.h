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
	Defines the DzCategoryAssetContainer class.
**/

#ifndef DAZ_CATEGORY_ASSET_CONTAINER_H
#define DAZ_CATEGORY_ASSET_CONTAINER_H

/*****************************
	Include files
*****************************/

#include "dzabstractassetcontainer.h"

/*****************************
	Forward declare
*****************************/

class DzDBCategoriesTable;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzCategoryAssetContainer : public DzAbstractAssetContainer 
{
	Q_OBJECT
public:
	DzCategoryAssetContainer( DzDBCategoriesTable *table, DzAbstractAssetContainer *owner = NULL );

	virtual ~DzCategoryAssetContainer();

	virtual bool	getCanCopyContainers() const;

	virtual void	loadMetadata( DzAsset *asset );
	virtual bool	updateMetadata( DzAsset *asset );

	virtual bool	showAsNew();
	static void		buildAssets( DzAbstractAssetContainer *container, const DzDBObjectBasePtrList &list, DzAssetList &assetList );

public slots:
	virtual bool	renameChildContainer( DzAbstractAssetContainer *container, const QString &name );
	virtual bool	removeChildContainer( DzAbstractAssetContainer *container );
	virtual bool	createNewChildContainer( const QString &containerName );
	virtual bool	insertChildContainer( DzAbstractAssetContainer *container );
	virtual bool	moveFromParent( DzAbstractAssetContainer *child );
	virtual bool	ignoreAssetConflicts();
	virtual bool	removeAssetCausesDelete();

	virtual bool	hasAsset( const DzAsset *asset );
	virtual bool	removeAsset( DzAsset *asset );
	virtual bool	insertAsset( const DzAsset *asset );

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

#ifndef Q_MOC_RUN
	static
#endif 
	DzPixmapPair			getIconForStandardCategory( DzCategoryAssetContainer *folder );
	DzDBCategoriesTable*	getCategoryTable();

private:
	void	init( DzAbstractAssetContainer *owner );
	void	buildAssets();

	void	buildChildContainers();
	DzCategoryAssetContainer*	createChildContainer( DzDBCategoriesTable *categoryTable );
	
	struct	Data;
	Data* m_data;
};

typedef DzTSharedPointer<DzCategoryAssetContainer> DzCategoryAssetContainerPtr;
Q_DECLARE_METATYPE(DzCategoryAssetContainerPtr);

#endif // DAZ_CATEGORY_ASSET_CONTAINER_H
