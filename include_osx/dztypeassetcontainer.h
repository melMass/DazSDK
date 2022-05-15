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
	Defines the DzTypeAssetContainer class.
**/

#ifndef DAZ_TYPE_ASSET_CONTAINER_H
#define DAZ_TYPE_ASSET_CONTAINER_H

/*****************************
	Include files
*****************************/

#include "dzabstractassetcontainer.h"
#include "dztypes.h"

/*****************************
	Forward declare
*****************************/

class DzAsset;
class DzTypeAssetContainer;

typedef DzTSharedPointer<DzTypeAssetContainer> DzTypeAssetContainerPtr;

/*****************************
	Class definitions
*****************************/
typedef QList<DzTypeAssetContainerPtr> DzTypeAssetContainerPtrList; 
typedef QListIterator<DzTypeAssetContainerPtr> DzTypeAssetContainerPtrIterator;

class DZ_EXPORT DzTypeAssetContainer : public DzAbstractAssetContainer 
{
	Q_OBJECT
	Q_PROPERTY(QVariant data READ data WRITE setData )
public:
	DzTypeAssetContainer( const QString &typePath, DzAbstractAssetContainer *owner=NULL );

	virtual ~DzTypeAssetContainer();

	virtual bool	getCanCopyContainers() const;

	virtual void	loadMetadata( DzAsset *asset );
	virtual bool	updateMetadata( DzAsset *asset );

	virtual bool	showAsNew();
	static void		buildAssets( DzAbstractAssetContainer *container, const DzDBObjectBasePtrList &list, DzAssetList &assetList );

	QVariant	data() const;
	void		setData( const QVariant &data );

	void	setContentTypeMode( bool onOff );
	bool	getContentTypeMode() const;

public slots:
	virtual QVariantList	getIDPath() const;

	void	clear( bool firstCall );
	QString	getTypeName() const;
	int		addChildContainer( const QString &childType );
	int		addChildContainer( const DzTypeAssetContainerPtr &childType );

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

	bool	insertToSpecificType( const DzAsset *asset, const QString &type );

	virtual bool	renameAsset( DzAsset *asset, const QString &newAssetName );

	virtual int		getNumChildContainers() const;
	virtual DzAbstractAssetContainerPtr	getChildContainer( int index );

	virtual bool	getChildContainers( DzAbstractAssetContainerList &list );
	virtual bool	getAssets( DzAssetList &list );
	virtual int		getNumAssets();
	virtual DzAssetPtr	getAsset( int index );

	virtual bool	update();
	virtual bool	updateAssets();
	virtual bool	updateChildren();
	DzTypeAssetContainer*	findChildContainer( const QString &typeStr );

#ifndef Q_MOC_RUN
	static
#endif 
	DzPixmapPair	getIconForStandardCategory( DzTypeAssetContainer *folder );

	QString	getTextPath( bool ignoreRoot = true ) const;
	bool	initChildren();

signals:
	void	aboutToClear();

private:
	void	init( DzAbstractAssetContainer *owner );
	bool	insertAssetInternal( const QString &typeStr, const DzAsset *asset );
	DzTypeAssetContainer*	findChildContainer( QStringList &list );

	struct	Data;
	Data* m_data;
};

Q_DECLARE_METATYPE(DzTypeAssetContainerPtr);

#endif // DAZ_TYPE_ASSET_CONTAINER_H
