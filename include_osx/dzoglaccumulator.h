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
	Defines the DzOGLAccumulator class.
**/

#ifndef DAZ_OGL_ACCUMULATOR_H
#define DAZ_OGL_ACCUMULATOR_H

/****************************
	Include files
****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QImage;
class QRect;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzOGLAccumulator {
public:
	//
	// CREATORS
	//

	DzOGLAccumulator( const QRect &window );
	~DzOGLAccumulator();

	void	accumulate( float multiplier );
	void	drawPixels();
	QImage	getImage();

private:

	QImage	getImageFromBuffer( float *data );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_OGL_ACCUMULATOR_H
