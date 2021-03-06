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
	Defines the DzAbstractAssetContainer class.
**/

#ifndef DAZ_ABSTRACT_ASSET_CONTAINER_H
#define DAZ_ABSTRACT_ASSET_CONTAINER_H

/*****************************
	Include files
*****************************/

#include <QtCore/QPair>
#include <QtCore/QVariant>

#include "dzasset.h"
#include "dzrefcounteditem.h"
#include "dztypes.h"

/*****************************
	Forward declare
*****************************/

class QAbstractItemModel;
class QPixmap;

typedef QPair<QPixmap,QPixmap> DzPixmapPair;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAbstractAssetContainer : public QObject, public DzRefCountedItem 
{
	Q_PROPERTY( QVariant id READ getID )
	Q_PROPERTY( QIcon icon READ getIcon )
	Q_PROPERTY( QString tooltip READ getToolTip )
	Q_PROPERTY( bool canCopyContainers READ getCanCopyContainers )
	Q_PROPERTY( bool canInsertSubContainer READ canAddSubContainer )
	Q_PROPERTY( bool canDeleteContainer READ canDelete )
	Q_PROPERTY( bool canRenameContainer READ canRename )
	Q_PROPERTY( bool canModifyAssets READ canModAssets )
	Q_PROPERTY( int useCount READ getUseCount WRITE setUseCount )
	Q_OBJECT

public:
	DzAbstractAssetContainer( DzAbstractAssetContainer *owner = NULL, const QString &name = QString() );
	virtual ~DzAbstractAssetContainer();
	
	QVariant	getID() const;
	void		setID( const QVariant &id );

	int			getUseCount() const;
	void		setUseCount( int count );

	QIcon		getIcon() const;
	void		setIcon( const QIcon &icon );

	QString		getToolTip() const;
	void		setToolTip( const QString &tip );

	bool		canAddSubContainer() const;
	bool		canDelete() const;
	bool		canRename() const;
	bool		canModAssets() const;

	void		setCanAddSubContainer( bool yesNo );
	void		setCanDelete( bool yesNo );
	void		setCanRename( bool yesNo );
	void		setCanModifyAssets( bool yesNo );
	void		addConnectedModel( const QAbstractItemModel *model );
	bool		isConnectedToModel( const QAbstractItemModel *model ) const;

	virtual bool	removeAssetCausesDelete(); 
	virtual void	loadMetadata( DzAsset *asset ) = 0;
	virtual bool	updateMetadata( DzAsset *asset ) = 0;
	virtual bool	getCanCopyContainers() const = 0;

	virtual void	standardPasteAssets( DzAssetList list, bool copy, DzAbstractAssetContainer *from );
	virtual bool	showAsNew();

	static DzAbstractAssetContainer*	assetContainerValid( void *ptr );

public slots:
	
	virtual QSize	getChildIconSize();
	virtual QSize	getSmallChildIconSize();

	virtual DzAbstractAssetContainer*	getOwner() const;

	virtual QString	getContainerName() const;
	virtual bool	rename( const QString &name );
	
	virtual bool	isFileSystemBased() const;

	virtual bool	renameChildContainer( DzAbstractAssetContainer *container, const QString &name ) = 0;
	virtual bool	removeChildContainer( DzAbstractAssetContainer *container ) = 0;
	virtual bool	createNewChildContainer( const QString &containerName ) = 0;
	virtual bool	insertChildContainer( DzAbstractAssetContainer *container ) = 0;
	virtual bool	moveFromParent( DzAbstractAssetContainer *child ) = 0;
	
	virtual bool	hasAsset( const DzAsset *asset ) = 0;
	virtual bool	removeAsset( DzAsset *asset ) = 0;
	virtual bool	insertAsset( const DzAsset *asset ) = 0;
	virtual bool	renameAsset( DzAsset *asset, const QString &newAssetName ) = 0;
	virtual bool	removeAssetOnCut( DzAbstractAssetContainer *toContainer );
	virtual bool	ignoreAssetConflicts();
	
	virtual int		getNumChildContainers() const = 0;
	virtual DzAbstractAssetContainerPtr	getChildContainer( int index ) = 0;
	
	virtual bool	getChildContainers( DzAbstractAssetContainerList &list ) = 0;
	virtual bool	getAssets( DzAssetList &list ) = 0;
	virtual int		getNumAssets() = 0;
	virtual DzAssetPtr	getAsset( int index ) = 0;

	virtual bool	initChildren() = 0;
	virtual bool	update() = 0;
	virtual bool	updateAssets() = 0;
	virtual bool	clearRebuildableAssets();

	virtual bool	hasChildContainers() const;
	
	virtual QObjectList	getChildContainers();
	virtual QObjectList	getAssets();

	virtual void			setContainerName( const QString &name );
	virtual QVariantList	getIDPath() const;
	virtual QString			getSupportFile() const;

signals:
	
	void beginChildContainerRemove( DzAbstractAssetContainer *con, int start, int end );
	void endChildContainerRemove();
	void beginChildContainerAdd( DzAbstractAssetContainer *con, int start, int end );
	void endChildContainerAdd();

	void	childContainerAboutToBeRemoved( DzAbstractAssetContainerPtr childContainer );
	void	childContainerRemoved( DzAbstractAssetContainerPtr childContainer );

	void	beginAssetRemove( int start,int end );
	void	endAssetRemove();
	void	beginAssetAdd( int start, int end );
	void	endAssetAdd();

	void	assetIconChanged( DzAsset *asset );

#ifndef Q_MOC_RUN
public:
#endif
	void	assetRenamed( DzAsset *asset, int index );

public:
	virtual void	setOwner( DzAbstractAssetContainer *newOwner );	

private:
	struct	Data;
	Data*	m_data;
};

Q_DECLARE_METATYPE( DzAbstractAssetContainerPtr );

#endif // DAZ_ABSTRACT_ASSET_CONTAINER_H
