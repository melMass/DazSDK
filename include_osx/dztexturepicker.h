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
	Defines the DzTexturePicker class.
**/

#ifndef DAZ_TEXTURE_PICKER_H
#define DAZ_TEXTURE_PICKER_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzTexture;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTexturePicker : public QObject {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzTexturePicker();
	virtual ~DzTexturePicker();

public slots:

	//
	// ACCESSORS
	//

	virtual QString		getDescription() const = 0;
	virtual DzTexture*	getTexture( DzTexture *curTexture ) const = 0;
};

#endif // DAZ_TEXTURE_PICKER_H