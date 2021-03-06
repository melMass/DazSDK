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
	Defines the DzViewRenderHandler class.
**/

#ifndef DAZ_VIEW_RENDER_HANDLER_H
#define DAZ_VIEW_RENDER_HANDLER_H

/*****************************
	Include files
*****************************/

#include "dzimagerenderhandler.h"

/****************************
	Forward declarations
****************************/

class DzRenderWindow;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzViewRenderHandler : public DzImageRenderHandler {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzViewRenderHandler( const QSize &size, DzTime time, const QString &filename, bool isSoftware );
	DzViewRenderHandler( const QSize &size, DzTime startingTime, int numFrames, const QString &filename, 
		bool isMovie, bool isSoftware );
	virtual ~DzViewRenderHandler();

	//
	// MANIPULATORS
	//

	virtual void	beginFrame( int frame );
	virtual void	finishFrame();
	virtual void	passData( const DzRenderData &data );
	virtual bool	isRendering();

public slots:
	void			renderCanceled();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_VIEW_RENDER_HANDLER_H