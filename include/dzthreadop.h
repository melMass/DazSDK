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
#ifndef DZ_THREAD_OP_H
#define DZ_THREAD_OP_H

/****************************
	Include files
****************************/

#include "dzgeneraldefs.h"

/****************************
	Class Definitions
****************************/

class DZ_EXPORT DzThreadOp {
public:
	DzThreadOp();
	virtual ~DzThreadOp();

	virtual void	run() = 0;
};

#endif // DZ_TIMER_H
