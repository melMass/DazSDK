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

#ifndef DAZ_PAGED_ASSET_CONTAINER_ITEM_MODEL_H
#define DAZ_PAGED_ASSET_CONTAINER_ITEM_MODEL_H

/*****************************
	Include files
*****************************/

#include <QtCore/QAbstractListModel>

#include "dzabstractassetcontainer.h"
#include "dztypes.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPagedAssetContainerItemModel : public QAbstractListModel 
{
	Q_OBJECT
public:
	DzPagedAssetContainerItemModel( QObject *parent = NULL );
	virtual ~DzPagedAssetContainerItemModel();

	void	setContainer( DzAbstractAssetContainerPtr container );
	DzAbstractAssetContainerPtr	getContainer() const;

	int			rowCount( const QModelIndex &index ) const;
	QVariant	data( const QModelIndex &index, int role = Qt::DisplayRole ) const;

	int				getIndex( int row ) const;
	Qt::ItemFlags	flags( const QModelIndex &index ) const;

public slots:
	int		getTotalNumberOfContainers() const;
	DzAbstractAssetContainerPtr	getChildContainer( QModelIndex index );
	void	updateContainers();

	void	setItemsPerPage( int itemsPerPage );
	int		getItemsPerPage() const;
	int		getCurrentPage() const;
	void	setCurrentPage( int page );
	int		getNumPages() const;
	void	setShowItemText( bool onOff );
	bool	showItemText();

	QRegExp	getFilterRegExp();
	void	setFilterRegExp( const QRegExp &regExp );
	bool	getFilteringContents();
	void	updateFilter();

private:
	struct	Data;
	Data*	m_data;
};

#endif // DAZ_PAGED_ASSET_CONTAINER_ITEM_MODEL_H