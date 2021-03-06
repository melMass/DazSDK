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
	Defines the DzAssetItemModel class.
**/

#ifndef DAZ_ASSET_ITEM_MODEL_H
#define DAZ_ASSET_ITEM_MODEL_H

/*****************************
	Include files
*****************************/

#include <QtCore/QAbstractListModel>

#include "dzmimedata.h"
#include "dztypes.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAssetItemModel : public QAbstractListModel 
{
	Q_OBJECT
public:
	DzAssetItemModel( QObject *parent = NULL );
	virtual ~DzAssetItemModel();

	void	setContainer( DzAbstractAssetContainerPtr container );

	DzAbstractAssetContainerPtr	getContainer() const;

	int			rowCount( const QModelIndex &index ) const;
	QVariant	data( const QModelIndex &index, int role = Qt::DisplayRole ) const;

	int				getIndex( int row ) const;
	Qt::ItemFlags	flags( const QModelIndex  &index ) const;
	bool			setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole );

	QMimeData*				mimeData( const QModelIndexList &indexes ) const;
	virtual Qt::DropActions	supportedDropActions() const;
	virtual QStringList		mimeTypes() const;
	virtual bool			dropMimeData( const QMimeData *data, Qt::DropAction action, 
								int row, int column, const QModelIndex &parent );

	DzAssetPtr	getAsset( QModelIndex index );

public slots:
	int		getTotalNumberOfAssets() const;
	void	updateAssets();
	
	void	showExtensions( bool onOff );
	bool	isExtensionShown() const;

	bool	showAssetToolTip();
	void	setShowAssetToolTip( bool onOff );
	
	void	setShowSimpleToolTip( bool onOff );
	bool	showSimpleToolTip() const;

	QString	getTooltipData( DzAsset *file ) const;

	bool	isNew( QModelIndex index ) const;
	void	setItemsPerPage( int itemsPerPage );
	int		getItemsPerPage() const;
	int		getCurrentPage() const;
	void	setCurrentPage( int page );
	int		getNumPages() const;

private slots:
	void endAssetAdd();
	void endAssetRemove();
	void beginAssetRemove( int start,int end );
	void beginAssetAdd( int start, int end );
	void assetIconChanged( DzAsset *asset);

signals:
	void assetCountChanged();

private:
	QString getAssetDisplayName( DzAssetPtr asset ) const;

	struct	Data; 
	Data*	m_data;
};

class DZ_EXPORT DzAssetListMime : public DzMimeData {
public:
	DzAssetListMime( const DzAssetList &list );

	static QByteArray	encode( const DzAssetList &list );
	static void			decode( const QMimeData *src, DzAssetList &list );

	static const QString	s_mimeType;
};

#endif // DAZ_ASSET_ITEM_MODEL_H
