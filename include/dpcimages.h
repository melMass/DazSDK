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

	This file is part of the DAZ PreCompiler toolset which can be used
	to embed resources in your DAZ Studio plug-in.

	This header file declares the interface for embedded geometry
	objects created by calling dpc with the '-mode image' switch.
**/

#ifndef DPC_IMAGES_H
#define DPC_IMAGES_H

/*****************************
	Forward Declarations
*****************************/

class QImage;

/*****************************
	Function Declarations
*****************************/

QImage getEmbeddedImage( const char *name );

#endif // DPC_IMAGES_H