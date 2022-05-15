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
	Defines the DzPathItemModel class.
**/

#ifndef DAZ_PATH_ITEM_MODEL_H
#define DAZ_PATH_ITEM_MODEL_H

/*****************************
	Include files
*****************************/

#include <QtCore/QAbstractItemModel>

#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/*****************************
	Class definitions
*****************************/

class DzHierarchyPath;
typedef DzTSharedPointer<DzHierarchyPath> DzHierarchyPathPtr;

class DZ_EXPORT DzHierarchyPath : public DzRefCountedItem {
public:
	DzHierarchyPath( DzHierarchyPath *parent );
	DzHierarchyPath( const QString &str, DzHierarchyPath *parent );
	virtual ~DzHierarchyPath();

	QString	getText() const;

	int		getNumChildren() const;

	DzHierarchyPathPtr	getChild( int i ) const;
	DzHierarchyPathPtr	removeChild( int i );

	int		addChild( const DzHierarchyPathPtr &path );
	int		addChild( const QString &str );
	int		indexOf( const DzHierarchyPathPtr &path ) const;
	int		indexOf( const QString &path ) const;
	bool	removeChild( const DzHierarchyPathPtr &path );
	void	clear();

	DzHierarchyPath*	parent() const;

	QString	getTextPath( bool ignoreRoot = true ) const;
	void	getLeafChildren( QList<DzHierarchyPathPtr> &list ) const;
	void	addNullAtEachLevel( const QString &nullText );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPathItemModel : public QAbstractItemModel {
	Q_OBJECT
public:
	DzPathItemModel( QObject *parent = NULL );
	virtual ~DzPathItemModel();

	bool			hasChildren( const QModelIndex &parent = QModelIndex() ) const;
	QModelIndex		index( int row, int col, const QModelIndex &index = QModelIndex() ) const;
	QModelIndex		parent( const QModelIndex &index ) const;
	int				rowCount( const QModelIndex &index ) const;
	int				columnCount( const QModelIndex &index ) const;
	QVariant		data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
	Qt::ItemFlags	flags( const QModelIndex &index ) const;


	void	setPaths( QStringList list );
	void	clearPaths();

	DzHierarchyPath*	pathFromIndex( const QModelIndex &index ) const;

	void	setIncludeNullItem( bool trueFalse );
	void	setNullText( const QString &text );
	QString	getNullText() const;

	QModelIndex	getIndexForPath( const QString &path );

private:
	
	struct	Data;
	Data* m_data;
};

#endif // DAZ_PATH_ITEM_MODEL_H
