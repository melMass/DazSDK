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
	Defines the DzTopLevelAssetContainer class.
**/

#ifndef DAZ_TOPLEVEL_ASSET_CONTAINER_H
#define DAZ_TOPLEVEL_ASSET_CONTAINER_H

/*****************************
	Include files
*****************************/

#include "dzabstractassetcontainer.h"
#include "dzproductassetcontainer.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTopLevelAssetContainer : public DzAbstractAssetContainer 
{
	Q_OBJECT
public:
	DzTopLevelAssetContainer(QString name,DzTopLevelAssetContainer *owner=NULL);

	virtual ~DzTopLevelAssetContainer();

	virtual bool	getCanCopyContainers() const;

	virtual void	loadMetadata( DzAsset *asset );
	virtual bool	updateMetadata( DzAsset *asset );

	virtual bool	showAsNew();

public slots:

	virtual bool	renameChildContainer(DzAbstractAssetContainer *container,const QString &name);
	virtual bool	removeChildContainer(DzAbstractAssetContainer *contianer);
	virtual bool	createNewChildContainer(const QString &containerName);
	virtual bool	insertChildContainer(DzAbstractAssetContainer *contianer);
	virtual bool	moveFromParent(DzAbstractAssetContainer *child);

	virtual bool	removeAsset(DzAsset *asset);
	virtual bool	insertAsset(const DzAsset *asset);
	virtual bool	hasAsset(const DzAsset *asset);

	virtual bool	renameAsset(DzAsset *asset,const QString &newAssetName);
	virtual int		getNumChildContainers() const;

	virtual DzAbstractAssetContainerPtr	getChildContainer(int index);

	virtual bool	getChildContainers(DzAbstractAssetContainerList &list);
	virtual bool	getAssets(DzAssetList &list);
	virtual int		getNumAssets();

	virtual DzAssetPtr	getAsset(int index);

	virtual bool	initChildren();
	virtual bool	update();
	virtual bool	updateAssets();

private:

	struct	Data;
	Data*	m_data;
};

typedef DzTSharedPointer<DzTopLevelAssetContainer> DzTopLevelAssetContainerPtr;
Q_DECLARE_METATYPE(DzTopLevelAssetContainerPtr);

class DZ_EXPORT DzProductHolderContainer : public DzTopLevelAssetContainer
{
	Q_OBJECT
public:
	DzProductHolderContainer(QString name,DzTopLevelAssetContainer *owner=NULL);
	virtual ~DzProductHolderContainer();
public slots :
	virtual QSize getChildIconSize();
	bool insertChildProductContainer(const DzProductAssetContainerPtr &container);
private:
	struct	Data;
	Data*	m_data;
};

typedef DzTSharedPointer<DzProductHolderContainer> DzProductHolderContainerPtr;
Q_DECLARE_METATYPE(DzProductHolderContainerPtr);

class DZ_EXPORT DzSearchContainer : public DzTopLevelAssetContainer 
{
	Q_OBJECT
public:
	DzSearchContainer(QString name = QString(),DzTopLevelAssetContainer *owner=NULL);

	virtual ~DzSearchContainer();

	virtual bool	getCanCopyContainers() const;
	DzAssetList&	getAssetList();

public slots:

	virtual bool	removeAsset(DzAsset *asset);
	virtual bool	insertAsset(const DzAsset *asset);
	virtual bool	insertAsset(const DzAssetPtr asset);
	virtual bool	insertAssets(const DzAssetList &assets);
	virtual bool	hasAsset(const DzAsset *asset);

	virtual bool	renameAsset(DzAsset *asset,const QString &newAssetName);
	virtual bool	getAssets(DzAssetList &list);
	virtual bool	updateAssets();
	virtual int		getNumAssets();

	virtual DzAssetPtr	getAsset(int index);

private:

	struct	Data;
	Data*	m_data;
};

typedef DzTSharedPointer<DzSearchContainer> DzSearchContainerPtr;
Q_DECLARE_METATYPE(DzSearchContainerPtr);

#endif // DAZ_TOPLEVEL_ASSET_CONTAINER_H
