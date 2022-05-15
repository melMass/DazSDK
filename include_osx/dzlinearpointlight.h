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
	Defines the DzLinearPointLight class.
**/

#ifndef DAZ_LINEAR_POINT_LIGHT_H
#define DAZ_LINEAR_POINT_LIGHT_H

/*****************************
	Include files
*****************************/

#include "dzpointlight.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLinearPointLight : public DzPointLight {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzLinearPointLight();
	virtual ~DzLinearPointLight();
	
	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection(DzInFile *file,short sectionID);
	virtual void	postLoadFile(const DzInFile *file);
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save(DzOutFile *file) const;
	virtual void	draw( const DzDrawStyle &style ) const;

	virtual void	create( const DzRenderSettings &settings, const QString &shadowMap ) const;
	virtual QPixmap	getPixmap(QStyle::State state = QStyle::State_None) const;
	virtual QIcon	getIcon() const;

public slots:
	DzFloatProperty*	getFallOffStartControl() const;
	DzFloatProperty*	getFallOffEndControl() const;

protected:

	virtual void	setGLLighting( const DzDrawStyle &style, int pass = 0, int totalPasses = 1 );
	virtual void	unsetGLLighting( const DzDrawStyle &style );

	void	drawLinearPointerRepresentation() const;
	void	drawLightGeometry() const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LINEAR_POINT_LIGHT_H
