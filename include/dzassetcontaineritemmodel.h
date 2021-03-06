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
	Defines the DzAssetContainerItemModel class.
**/

#ifndef DAZ_ASSET_CONTAINER_ITEM_MODEL_H
#define DAZ_ASSET_CONTAINER_ITEM_MODEL_H

/*****************************
	Include files
*****************************/

#include <QtCore/QAbstractItemModel>

#include "dzmimedata.h"
#include "dztypes.h"

/*****************************
	Forward declare
*****************************/

class DzMarkableAssetContainerColumnView;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAssetContainerItemModel : public QAbstractItemModel 
{
	Q_OBJECT
public:
	DzAssetContainerItemModel( QObject *parent = NULL );
	virtual ~DzAssetContainerItemModel();

	bool		hasChildren( const QModelIndex &parent = QModelIndex() ) const;
	QModelIndex	index( int row, int col, const QModelIndex &index = QModelIndex() ) const;
	QModelIndex	parent( const QModelIndex &index ) const;

	int			getIndexInParent( DzAbstractAssetContainer *container ) const;
	int			rowCount( const QModelIndex &index ) const;
	int			columnCount( const QModelIndex &index ) const;

	virtual QVariant	data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
	Qt::ItemFlags		flags( const QModelIndex &index ) const;
	bool				setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole );

	void	addTopLevelContainer( DzAbstractAssetContainerPtr container );
	int		getNumTopLevelContainers() const;

	DzAbstractAssetContainerPtr	removeTopLevelContainer( int index );
	DzAbstractAssetContainerPtr	getTopLevelContainer( int index ) const;

	QMimeData*	mimeData( const QModelIndexList &indexes ) const;

	virtual Qt::DropActions supportedDropActions() const;
	virtual QStringList		mimeTypes() const;
	virtual bool			dropMimeData( const QMimeData *data, Qt::DropAction action, 
										int row, int column, const QModelIndex &parent );

	DzAbstractAssetContainer*	containerFromIndex( const QModelIndex &index ) const;
	QModelIndex					getIndexFromPath( QVariantList idPath, bool tryHierarchy=false );
	DzAbstractAssetContainerPtr	getContainerFromPath( QVariantList idPath, QModelIndex &index, int &rowID );

public slots:
	
	void	blockContainerUpdate();
	void	unblockContainerUpdate();
	bool	isUpdateBlocked() const;
	void	updateContainer( QVariantList idPath );
	void	updateContainerData( QVariantList idPath );
	void	updateData( QModelIndex index );
	bool	isNew( QModelIndex index ) const;
	void	causeReset();

private slots:
	
	void	containerAboutToBeAdded( DzAbstractAssetContainer *container, int childIndexStart, int childIndexEnd );
	void	containerAdded();
	
	void	containerAboutToBeRemoved( DzAbstractAssetContainer *container, int childIndexStart, int childIndexEnd );
	void	containerRemoved();

signals:

	void	fetchingRows() const;
	void	rowFetchFinished() const;
	void	aboutToUpdateContainer( DzAbstractAssetContainer *container );
	void	containerUpdated( DzAbstractAssetContainer *container );

private:

	bool	doContainerDrop( const QMimeData *data, DzAbstractAssetContainerPtr dropContainer );
	bool	doAssetDrop( const QMimeData *data, DzAbstractAssetContainerPtr dropContainer );
	void	connectContainer( DzAbstractAssetContainer *child ) const;

	DzAbstractAssetContainerPtr	getContainerFromPath( DzAbstractAssetContainerPtr parent,
									QVariantList idPath, QModelIndex &parentIndex, int &rowID );

	struct	Data; 
	Data* m_data;
};

class DZ_EXPORT DzAbstractContainerListMime : public DzMimeData {
public:
	DzAbstractContainerListMime( const DzAbstractAssetContainerList &list );

	static QByteArray	encode( const DzAbstractAssetContainerList &list );
	static void			decode( const QMimeData *src, DzAbstractAssetContainerList &list );

	static const QString	s_mimeType;
};

class DZ_EXPORT DzMarkableAssetContainerItemModel : public DzAssetContainerItemModel {
	Q_OBJECT
public:
	DzMarkableAssetContainerItemModel( QObject *parent = NULL );
	virtual ~DzMarkableAssetContainerItemModel();

	virtual QVariant	data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
	void				setView( DzMarkableAssetContainerColumnView *view );

private:
	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_ASSET_CONTAINER_ITEM_MODEL_H
