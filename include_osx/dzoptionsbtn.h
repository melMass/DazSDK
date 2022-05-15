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
	Defines the DzOptionsBtn class.
**/

#ifndef DAZ_OPTIONS_BUTTON_H
#define DAZ_OPTIONS_BUTTON_H

/*****************************
	Include files
*****************************/

#include "dzstyledbutton.h"

/*****************************
	Forward declarations
*****************************/

class QMenu;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzOptionsBtn : public DzStyledButton {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzOptionsBtn( QWidget *parent, const QString &name );
	virtual ~DzOptionsBtn();

	//
	// MANIPULATORS
	//

	void	setMenu( QMenu *menu );

	//
	// ACCESSORS
	//

	QMenu*	getMenu() const;

protected slots:

	void	showOptions();

private:
	//
	// DATA MEMBERS
	//

	QMenu	*m_menu;
};

#endif // DAZ_OPTIONS_BUTTON_H


