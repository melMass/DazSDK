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
	Defines the DzNumericController class.
**/

#ifndef DAZ_NUMERIC_CONTROLLER_H
#define DAZ_NUMERIC_CONTROLLER_H

/*****************************
	Include files
*****************************/

#include "dzcontroller.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNumericController : public DzController {
	Q_OBJECT
public:

	DzNumericController( ControllerEffect effect );
	virtual ~DzNumericController();

public slots:

	virtual double	apply( double val, DzTime tm, bool local ) const = 0;
	virtual double	applyInverse( double val, DzTime tm, bool local ) const { return val; }
};

#endif // DAZ_NUMERIC_CONTROLLER_H
