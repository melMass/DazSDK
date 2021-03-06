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
	Defines the DzWeld class.
**/

#ifndef DAZ_WELD_H
#define DAZ_WELD_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/****************************
	Forward declarations
****************************/

class DzBone;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzWeld : public DzBase {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzWeld();
	DzWeld( DzBone *weldBone, DzBone *targetBone );
	virtual ~DzWeld();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;
	
public slots:

	void	setWeldBone( DzBone *weldBone );
	void	setTargetBone( DzBone *targetBone );

	//
	// ACCESSORS
	//

	DzBone*	getWeldBone() const;
	DzBone*	getTargetBone() const;

signals:
	void	weldBoneChanged();
	void	targetBoneChanged();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_WELD_H
