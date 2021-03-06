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
	Defines the DzNodeListView class.
**/

#ifndef DAZ_NODE_LIST_VIEW_H
#define DAZ_NODE_LIST_VIEW_H

/*****************************
	Include files
*****************************/

#include <QtGui/QTreeView>

#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzNodeListItem;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNodeListFilter {
public:
	DzNodeListFilter();
	virtual ~DzNodeListFilter();

	virtual void	nodeAddStarting();
	virtual bool	acceptNode( DzNode *node ) = 0;
	virtual void	nodeAddEnded();
};

class DZ_EXPORT DzNodeListView : public QTreeView {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzNodeListView( QWidget *parent, const QString &name = QString::null, const QString &nodeType = "DzNode", 
					bool allowNone = false, QAbstractItemView::SelectionMode mode = QAbstractItemView::SingleSelection, 
					DzNodeListFilter *filter=NULL );

	~DzNodeListView();

	void		setSelectedNode( DzNode *node );
	DzNode*		getSelectedNode() const;
	DzNodeList	getSelectedNodes() const;
	void		setFilter( DzNodeListFilter *filter);

signals:
	void		selectionChanged();

private:
	void	addNodeTree( DzNode *node );
	void	populateViewFromScene();
	void	addNodeItemRecurse( DzNodeListItem *parent, DzNode *node );
	bool	setSelectedRecurse( DzNodeListItem *it, DzNode *node );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NODE_LIST_VIEW_H
