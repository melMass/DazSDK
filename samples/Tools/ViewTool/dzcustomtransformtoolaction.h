/**********************************************************************
	Copyright (c) 2002-2020 Daz 3D, Inc. All Rights Reserved.

	This file is part of the Daz Studio SDK.

	This file may be used only in accordance with the Daz Studio SDK
	license provided with the Daz Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of Daz 3D, Inc, except as explicitly
	allowed in the Daz Studio SDK license.

	See http://www.daz3d.com to contact Daz 3D, Inc or for more
	information about the Daz Studio SDK.
**********************************************************************/
#pragma once

/*****************************
	Include files
*****************************/

#include "dzaction.h"

/*****************************
	Class definitions
*****************************/
/**
	Our new action inherits from DzViewToolAction so that it will automatically
	be added to the '&Tools' menu when the plugin is loaded the first time. It
	also inherits from DzViewToolAction so that it will toggle on/off activation
	of our view tool in the interface.
**/
class DzCustomTransformToolAction : public DzViewToolAction {
	Q_OBJECT
public:

	// Constructor
	DzCustomTransformToolAction();

	// ViewTool defaults:
	//virtual QString	getActionGroup() const;			return tr( "Viewport Tools" );
	//virtual QString	getDefaultMenuPath() const;		return tr( "&Tools" );
	//virtual QString	getDefaultToolBar() const;		return tr( "Tools" );
	virtual QKeySequence	getDefaultAccel() const;

protected:

	void	initIcons();
	void	getRawIconPixmap( QString &iconBaseName, QPixmap &basePixmap ) const;
	void	makeIconVariants( QIcon &icon, QPixmap &mainPixmap );

private slots:

	void	handleInterfaceColorsChanged();
};
