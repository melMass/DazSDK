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
	Defines the DzLight class.
**/

#ifndef DAZ_LIGHT_H
#define DAZ_LIGHT_H

/*****************************
	Include files
*****************************/

#include "dzcamera.h"

/*****************************
	Definitions
*****************************/
// Only use 7 of the 8 available lights here so that we can reserve
// light0 for OGL rendering.
#define DZ_MAX_OPENGL_LIGHTS			7

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLight : public DzCamera {
	Q_OBJECT
	Q_ENUMS( ShadowType )
public:

	enum ShadowType {
		None,
		DeepShadowMap,
		Raytraced
	};

	//
	// CREATORS
	//

	DzLight();
	virtual ~DzLight();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		postLoadFile( const DzInFile *file );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		reset() { }
	virtual void		setFocalDistance( double dist ) { }
	virtual void		setFocalLength( double dist ) { }
	virtual void		aimAt( const DzVec3 &pos ) { }
	virtual void		frame( const DzBox3 &box, float aspect ) { }
	virtual void		save( DzOutFile *file ) const;
	virtual void		draw( const DzDrawStyle &style ) const;
	virtual QPixmap		getPixmap(QStyle::State state = QStyle::State_None) const;
	virtual QIcon		getIcon() const;

	virtual void	setProjection( const DzRenderSettings &settings, float width, float height ) const { }
	virtual void	create( const DzRenderSettings &settings, const QString &shadowMap ) const = 0;
	virtual void	setShadowTransform( const DzRenderSettings &settings, const DzCamera *camera ) const = 0;
	virtual bool	canViewThrough() const { return true; }
	virtual double	getFocalDistance() const { return 1.0; }
	virtual double	getFocalLength() const { return 1.0f; }

	//
	// MANIPULATORS
	//

	void			setGLLight( const DzDrawStyle &style, int pass = 0, int totalPasses = 1, bool useIndexZero = false );
	void			unsetGLLight( const DzDrawStyle &style );
	virtual void	setGLShadow( int pass, int totalPasses, int *shadowMapSize = NULL ) = 0;
	virtual void	unsetGLShadow() = 0;


	//
	// ACCESSORS
	//

	int	getOGLLightIndex() const;

public slots:

	virtual bool	isDirectional() const { return true; }
	virtual DzVec3	getWSDirection() const;
	virtual bool	isAreaLight() const { return false; }
	virtual QColor	getDiffuseColor() const = 0;
	virtual bool	isOn() const = 0;
	ShadowType		getShadowType() const;
	DzEnumProperty*	getShadowTypeControl() const;

	virtual bool		shouldSortOnLoad() const;

protected:

	virtual void	setGLLighting( const DzDrawStyle &style, int pass = 0, int totalPasses = 1 ) = 0;
	virtual void	unsetGLLighting( const DzDrawStyle &style ) = 0;
	int				getLightIndex() const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LIGHT_H
