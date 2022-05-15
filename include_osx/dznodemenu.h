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
	Defines the DzNodeMenu class.
**/

#ifndef DAZ_NODE_MENU_H
#define DAZ_NODE_MENU_H

/*****************************
	Include files
*****************************/

#include "dzstyledbutton.h"
#include "dznodeselectioninterface.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNodeMenu : public DzStyledButton, public DzNodeSelectionInterface {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzNodeMenu( QWidget *parent = NULL, const QString &name = QString::null, bool showNone = true );
	virtual ~DzNodeMenu();

	//
	// Accessors
	//

	bool	getIndeterminate() const;
	bool	getShowNone() const;

	//
	// Manipulators
	//

	void	setShowNone( bool showNone );

	///////////////////////////////////
	// from DzNodeSelectionInterface
	virtual void		clear();
	virtual void		setIndeterminate();
	virtual void		selectNode( DzNode *obj );
	virtual DzNode*		getCurrent() const;

signals:

	void	selectionChanged( DzNode *newObject );
	void	aboutToShowMenu();

protected:

	virtual void	setNodes( const DzNodeList &nodes );

protected slots:

	void	showMenu();
	void	selectItem( QAction *which );
	void	updateMenu();

protected:
	////////////////////////
	// from QAbstractButton

	virtual void	showEvent( QShowEvent *e );

private slots:

	void	removeNode( DzNode *node );

private:

	void	updateSelection();
	void	updateList();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NODE_MENU_H