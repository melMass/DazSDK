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
	Defines the DzNodeBtn class.
**/

#ifndef DAZ_NODE_BUTTON_H
#define DAZ_NODE_BUTTON_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"
#include "dzstyledbutton.h"

/****************************
	Forward declarations
****************************/

class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNodeBtn : public DzStyledButton {
	Q_OBJECT
public:

	DzNodeBtn( QWidget *parent = NULL, const QString &name = QString::null );
	virtual ~DzNodeBtn();

public slots:

	void	setNode( DzNode *node );
	void	setIndeterminate();
	DzNode*	getNode() const;

signals:

	void	selectionChanged( DzNode *newObject );

protected slots:

	void	showMenu();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NODE_BUTTON_H