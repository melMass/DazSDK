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
	Defines the DzScaleTool class.
**/

#ifndef DAZ_SCALE_TOOL_H
#define DAZ_SCALE_TOOL_H

/*****************************
	Include files
*****************************/

#include "dztransformtool.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzScaleTool : public DzTransformTool {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzScaleTool();
	virtual ~DzScaleTool();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	draw( const DzDrawStyle &style, Dz3DViewport *view ) const;
	virtual QString	whatsThisText() const;

private:

	void	drawAxis( int axis, double length ) const;
	void	drawPlane( int axis, double length, bool drawLinesOnly ) const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SCALE_TOOL_H
