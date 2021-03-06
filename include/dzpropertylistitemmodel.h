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

#ifndef DZ_PROPERTY_LIST_ITEM_MODEL_H
#define DZ_PROPERTY_LIST_ITEM_MODEL_H

/*****************************
	Include files
*****************************/
#include <QtCore/QAbstractItemModel>

#include "dzrefcounteditem.h"
#include "dztypes.h"

/*****************************
	Type definitions
*****************************/

class DzPropertyListNode;
typedef DzTSharedPointer<DzPropertyListNode> DzPropertyListNodePtr;
typedef QList<DzPropertyListNodePtr> DzPropertyListNodeList;
typedef QListIterator<DzPropertyListNodePtr> DzPropertyListNodeIterator;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPropertyListNode : public DzRefCountedItem
{
public:
	DzPropertyListNode( const QString &label );
	virtual ~DzPropertyListNode();
	QString getLabel() const;

	virtual int		getNumProperties() const;
	virtual void	addProperty( DzProperty *prop );
	virtual bool	removeProperty( DzProperty *prop );

	virtual DzPropertyList	getProperties() const;

	void	setLabel( const QString &newLabel );
	void	setNew( bool onOff );
	bool	isNew() const;

	virtual void	updateNew();

protected:
	bool m_new;
	bool m_newIsValid;
	QString m_label;
	QList< QPointer< DzProperty> >	m_properties;
};

Q_DECLARE_METATYPE(DzPropertyListNodePtr);

class DZ_EXPORT DzPropertyListItemModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	enum ExtendedRoles{ PropertyNodeRole=Qt::UserRole+1,SearchRole, NewRole };
	DzPropertyListItemModel( QObject *parent = 0 );
	~DzPropertyListItemModel();

	virtual QModelIndex		index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
	virtual QModelIndex		parent ( const QModelIndex &index ) const;
	virtual int				rowCount ( const QModelIndex &parent = QModelIndex() ) const;
	virtual int				columnCount ( const QModelIndex &parent = QModelIndex() ) const;
	virtual QVariant		data ( const QModelIndex &index, int role = Qt::DisplayRole ) const;

	DzPropertyListNodePtr	getPropertyNodeForIndex( const QModelIndex &index );
	QModelIndex				getIndexForNode( DzPropertyListNode *propNode );

	Qt::ItemFlags	flags( const QModelIndex &index ) const;

public slots:
	void	addProperty( DzProperty *prop);
	void	clearProperties();
protected:
	bool event( QEvent *eve );
private slots:
	void	propertyChanged();
	void	propertyLabelChanged( const QString &lbl );
	void	removeProp( DzProperty *prop );
signals:
	void	propertyHiddenStateChange();
private:
	void	processPropUpdates();
	void	processLabelUpdates();

	struct	Data;
	Data	*m_data;
};

#endif