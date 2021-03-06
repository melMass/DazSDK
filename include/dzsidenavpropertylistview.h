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

#ifndef DZ_SIDENAV_PROPERTY_LIST_VIEW_H
#define DZ_SIDENAV_PROPERTY_LIST_VIEW_H

/*****************************
	Include files
*****************************/

#include <QtGui/QListView>
#include <QtGui/QStyledItemDelegate>

#include "dzpropertylistitemmodel.h"

/*****************************
	Forward declarations
*****************************/

class DzPropertyListItemModel;
class DzPropertyWgt;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSideNavPropertyListView : public QListView
{
	Q_OBJECT
public:
	DzSideNavPropertyListView(QWidget *parent = 0);
	~DzSideNavPropertyListView();

	DzPropertyListItemModel *	getModel();
	void						addProperty( DzProperty *prop);
	void						clearProperties();
	void						setLastEditor( QWidget *editor );
	void						getPropertySelections( DzPropertyList &selected, DzPropertyList &unselected,
														const QModelIndex &root = QModelIndex(), bool selectedAll = false );

	bool						isEditing() const;
public slots:
	void setFilterString( const QString &str);
	void setViewIconMode();
	void setViewListMode();
protected slots:
	void	itemClicked( const QModelIndex &index );
	void	itemEntered( const QModelIndex &index );

	void	checkEdit();
	void	doubleClickItem( const QModelIndex &item );
	void	itemDataChanged( const QModelIndex &item1,const QModelIndex &item2 );

protected:
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *event );
	virtual void    scrollContentsBy(int dx, int dy);
	virtual void	styleChange( QStyle &oldStyle);

signals:
	void	propertyHiddenStateChange();
private:
	void	finishEdit();
	
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPropertyListItemDelegate : public QStyledItemDelegate
{	
	Q_OBJECT
public:
	DzPropertyListItemDelegate( DzSideNavPropertyListView *parent );
	virtual ~DzPropertyListItemDelegate();
	
	void	setCardMode( bool onOff );	
	bool	isCardMode();
	void	paint ( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

	virtual QSize	sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;

	DzPropertyWgt*	getPropertyWgt( DzPropertyListNodePtr node ) const;
	QWidget*		createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
	void			setEditorData( QWidget *editor, const QModelIndex &index) const;
	
	void	updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

protected slots:
	void updateControlOnlySettings();
private:
	struct	Data;
	Data	*m_data;
};

uint qHash( const QPointer<DzProperty> &key );

class DZ_EXPORT DzPropertyListEditorHelper : public QObject
{	
	Q_OBJECT
public:
	DzPropertyListEditorHelper( QObject *parent );
	~DzPropertyListEditorHelper();

public slots:
	void	propertyValueChanged();
	void	addProperty( DzProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif