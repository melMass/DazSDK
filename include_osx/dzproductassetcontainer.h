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
	Defines the DzProductAssetContainer class.
**/

#ifndef DAZ_PRODUCT_ASSET_CONTAINER_H
#define DAZ_PRODUCT_ASSET_CONTAINER_H

/*****************************
	Include files
*****************************/

#include "dzabstractassetcontainer.h"
#include "dztypes.h"

/*****************************
	Forward declare
*****************************/

class DzAsset;
class DzDBProductTable;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzProductAssetContainer : public DzAbstractAssetContainer 
{
	Q_PROPERTY(double price READ getPrice WRITE setPrice)
	Q_PROPERTY(double salePrice READ getSalePrice WRITE setSalePrice)
	Q_PROPERTY(double platinumPrice READ getPlatinumPrice WRITE setPlatinumPrice)
	Q_PROPERTY(QString description READ getDescription WRITE setDescription)
	Q_PROPERTY(QString artists READ getArtists WRITE setArtists)
	Q_OBJECT

public:
	DzProductAssetContainer( DzDBProductTable *table, DzAbstractAssetContainer *owner = NULL );
	DzProductAssetContainer( const DzProductAssetContainer *other );
	virtual ~DzProductAssetContainer();

	QString	getArtists() const;
	void	setArtists( const QString &artists );

	double	getPrice() const;
	void	setPrice( double price );

	double	getSalePrice() const;
	void	setSalePrice( double price );

	double	getPlatinumPrice() const;
	void	setPlatinumPrice( double price );

	QString	getDescription() const;
	void	setDescription( const QString &des );
	
	virtual bool	getCanCopyContainers() const;

	virtual void	loadMetadata( DzAsset *asset );
	virtual bool	updateMetadata( DzAsset *asset );

	virtual bool	showAsNew();
	static void		buildAssets( DzAbstractAssetContainer *container, const DzDBObjectBasePtrList &list, DzAssetList &assetList );

public slots:
	void	setIconSize( const QSize &size );
	QSize	getIconSize();
	void	setURL( const QString &url );
	QString	getURL() const;

	virtual	bool	initChildren();
	virtual bool	renameChildContainer( DzAbstractAssetContainer *container, const QString &name );
	virtual bool	removeChildContainer( DzAbstractAssetContainer *contianer );
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

	virtual bool		getChildContainers( DzAbstractAssetContainerList &list );
	virtual bool		getAssets( DzAssetList &list );
	virtual int			getNumAssets();
	virtual DzAssetPtr	getAsset( int index );

	virtual bool	update();
	virtual bool	updateAssets();
	virtual bool	updateChildren();

	virtual DzDBProductTable*	getProductTable() const;
	virtual QString				getSupportFile() const;

	bool	loadDefaultIcon();
	void	setIconImage( QImage &map );

#ifndef Q_MOC_RUN
	static
#endif 
	DzPixmapPair	getIconForStandardCategory( DzProductAssetContainer *folder );
#ifndef Q_MOC_RUN
	static
#endif 
	QSize	getDefualtStoreIconSize();
private:
	void	init( DzAbstractAssetContainer *owner );
	void	buildAssets();
	bool	loadIconAsImg( const QString &path, QImage &img, const QString &ext );
	void	getPixmapsFromImage( QImage &img, QPixmap &map, QPixmap &smallMap );
	QIcon	getDecoratedIcon( QImage img );

	struct	Data;
	Data*	m_data;
};

typedef DzTSharedPointer<DzProductAssetContainer> DzProductAssetContainerPtr;
Q_DECLARE_METATYPE(DzProductAssetContainerPtr);

class DZ_EXPORT DzParentProductContainer : public DzAbstractAssetContainer {
	Q_OBJECT
public:
	DzParentProductContainer( QString name, DzAbstractAssetContainer *owner = NULL );

	virtual ~DzParentProductContainer();

	virtual bool	getCanCopyContainers() const;

	virtual void	loadMetadata( DzAsset *asset);
	virtual bool	updateMetadata( DzAsset *asset);

	virtual bool	showAsNew();

public slots:

	virtual bool	renameChildContainer( DzAbstractAssetContainer *container, const QString &name );
	virtual bool	removeChildContainer( DzAbstractAssetContainer *container );
	virtual bool	createNewChildContainer( const QString &containerName );
	virtual bool	insertChildContainer( DzAbstractAssetContainer *container );
	virtual bool	moveFromParent( DzAbstractAssetContainer *child );

	virtual bool	removeAsset( DzAsset *asset );
	virtual bool	insertAsset( const DzAsset *asset );
	virtual bool	hasAsset( const DzAsset *asset );

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

	virtual bool	hasChildContainers() const;
	virtual bool	updateChildren();

private:
	void	buildChildContainers();

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzParentProductContainer> DzParentProductContainerPtr;
Q_DECLARE_METATYPE(DzParentProductContainerPtr);

#endif // DAZ_PRODUCT_ASSET_CONTAINER_H
