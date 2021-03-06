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
	Defines the Dz3DViewRenderHandler class.
**/

#ifndef DAZ_3D_VIEW_RENDER_HANDLER_H
#define DAZ_3D_VIEW_RENDER_HANDLER_H

/*****************************
	Include files
*****************************/

#include "dzimagerenderhandler.h"

/****************************
	Forward declarations
****************************/

class DzViewport;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT Dz3DViewRenderHandler : public DzImageRenderHandler {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	Dz3DViewRenderHandler( DzViewport *view, DzTime startTime, const QString &filename );
	virtual ~Dz3DViewRenderHandler();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	beginFrame( int frame );
	virtual void	finishFrame();
	virtual void	passData( const DzRenderData &data );

private:

	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_3D_VIEW_RENDER_HANDLER_H