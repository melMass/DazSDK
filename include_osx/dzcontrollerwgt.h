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
	Defines the DzControllerWgt class.
**/

#ifndef DAZ_CONTROLLER_WGT_H
#define DAZ_CONTROLLER_WGT_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzerrorcodes.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzController;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzControllerWgt : public QWidget {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzControllerWgt( QWidget *parent = 0, const char *name = 0 );
	virtual ~DzControllerWgt();

	//
	// MANIPULATORS
	//

	virtual DzError	addController( DzController *ctrl );
	virtual void	removeAllControllers();
	virtual bool	doOptionsDialog() = 0;
	virtual void	resetControllers();

	//
	// ACCESSORS
	//

	int				getNumControllers() const;
	DzController*	getController( int which ) const;

	DzControllerListIterator	getControllers() const;

private slots:

	void			removeDeletedController( QObject *ctrl );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_CONTROLLER_WGT_H
