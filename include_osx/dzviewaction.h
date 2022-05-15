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
	Defines the DzViewAction class.
**/

#ifndef DAZ_VIEW_ACTION_H
#define DAZ_VIEW_ACTION_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzCamera;
class DzUndoStackHold;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzViewAction {
public:

	enum ActionType { ORBIT_ACTION, ROTATE_ACTION, BANK_ACTION, PAN_ACTION, DOLLY_ACTION,
						ZOOM_D_ACTION, ZOOM_F_ACTION };

	DzViewAction( DzCamera *camera, ActionType action );
	~DzViewAction();

	//
	// MANIPULATORS
	//

	void	doMove( int mouseDX, int mouseDY );

private:

	void	doZoomF( int mouseDX, int mouseDY );
	void	doZoomD( int mouseDX, int mouseDY );
	void	doDolly( int mouseDX, int mouseDY );
	void	doPan( int mouseDX, int mouseDY );
	void	doOrbit( int mouseDY, int mouseDX );
	void	doRotate( int mouseDY, int mouseDX );
	void	doBank( int mouseDX, int mouseDY );
	float	getPanFactor();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_VIEW_ACTION_H