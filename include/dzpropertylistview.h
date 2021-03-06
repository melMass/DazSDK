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
	Defines the DzPropertyListView class.
**/

#ifndef DAZ_PROPERTY_LIST_VIEW_H
#define DAZ_PROPERTY_LIST_VIEW_H

/*****************************
	Include files
*****************************/

#include <QtGui/QScrollArea>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzProperty;
class DzPropertyGroup;
class DzPropertyGroupTree;
class DzWidgetGroup;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPropertyListView : public QScrollArea {
	Q_OBJECT
	friend class DzWidgetListLayout;
public:
	//
	// CREATORS
	//

	DzPropertyListView( QWidget *parent, const QString &name = QString::null );
	virtual ~DzPropertyListView();
	virtual void	clear();
	bool			addPropertyTree( DzPropertyGroupTree *tree, bool showHidden = false );
	bool			addPropertyGroup( DzPropertyGroup *group, bool showHidden = false );
	bool			addProperty( DzProperty *prop );
	void			setNewGroupsCollapsed(bool open);

protected:

	void	resizeEvent( QResizeEvent *e );

private:

	QWidget*		centralWidget() const;
	DzWidgetGroup*	getGroup( const QString &name );
	bool			addPropertyGroupRecurse( DzPropertyGroup *root, bool showHidden );
	bool			addPropertyToGroup( DzProperty *prop, DzWidgetGroup *widGroup );
	bool			moveWidgetListGroupToEnd( DzWidgetGroup *widgetListGroup );
	void			resetLayout();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PROPERTY_LIST_VIEW_H
