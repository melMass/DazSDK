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
	Defines the DzRotateTool class.
**/

#ifndef DAZ_ROTATE_TOOL_H
#define DAZ_ROTATE_TOOL_H

/*****************************
	Include files
*****************************/

#include "dztransformtool.h"

/****************************
	Forward declarations
****************************/

class DzCamera;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRotateTool : public DzTransformTool {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzRotateTool();
	virtual ~DzRotateTool();

	//
	// REIMPLEMENTATIONS
	//

	virtual bool	mousePress( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void	mouseRelease( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void	draw( const DzDrawStyle &style, Dz3DViewport *view ) const;
	virtual QString	whatsThisText() const;

private:

	void	drawViewCircles( DzNode *node, DzCamera *cam, float radius, bool picking ) const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_ROTATE_TOOL_H
