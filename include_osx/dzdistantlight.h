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
	Defines the DzDistantLight class.
**/

#ifndef DAZ_DISTANT_LIGHT_H
#define DAZ_DISTANT_LIGHT_H

/*****************************
	Include files
*****************************/

#include "dzlight.h"

/****************************
	Forward declarations
****************************/

class DzColorProperty;

/*****************************
	Definitions
*****************************/

// Defines for Illumination property
#define DZ_ILLUMINATION_OFF				0
#define DZ_ILLUMINATION_DIFFUSE_ONLY	1
#define DZ_ILLUMINATION_SPECULAR_ONLY	2
#define DZ_ILLUMINATION_ON				3

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDistantLight : public DzLight {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzDistantLight();
	virtual ~DzDistantLight();

	////////////////////////////
	// Reimplemented

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	setGL( int width, int height, const QRect &view, int pass = 0, int totalPasses = 1, bool depthOfField = false );
	virtual void	setGLShadow( int pass, int totalPasses, int *shadowMapSize = NULL );
	virtual void	unsetGLShadow();
	virtual void	save( DzOutFile *file ) const;
	virtual void	setProjection( const DzRenderSettings &settings, float width, float height ) const { }
	virtual void	create( const DzRenderSettings &settings, const QString &shadowMap ) const;
	virtual void	setShadowTransform( const DzRenderSettings &settings, const DzCamera *camera ) const;
	virtual void	draw( const DzDrawStyle &style ) const;
	virtual void	reset() { }
	virtual void	setFocalDistance( double dist ) { }
	virtual void	setFocalLength( float dist ) { }
	virtual void	aimAt( const DzVec3 &pos ) { }
	virtual void	frame( const DzBox3 &box, float aspect ) { }

public slots:

	double				getNearClippingPlane() const;
	double				getFarClippingPlane() const;
	virtual DzVec3		getWSDirection() const;
	virtual QColor		getDiffuseColor() const;
	virtual bool		isOn() const;

	double				getIntensity() const;
	DzEnumProperty*		getIlluminationControl() const;
	DzFloatProperty*	getShadowSoftnessControl() const;
	DzFloatProperty*	getShadowBiasControl() const;
	DzColorProperty*	getDiffuseColorControl() const;
	DzFloatProperty*	getIntensityControl() const;

protected:

	virtual void	setGLLighting( const DzDrawStyle &style, int pass = 0, int totalPasses = 1 );
	virtual void	unsetGLLighting( const DzDrawStyle &style );

	void	setGLShadowMap( const DzDrawStyle &style );
	void	unsetGLShadowMap( const DzDrawStyle &style );
	virtual DzBox3	calcLocalBoundingBox() const;

private:
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DISTANT_LIGHT_H
