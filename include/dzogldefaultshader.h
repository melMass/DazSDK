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
	Defines the DzOGLDefaultShader class.
**/

#ifndef DAZ_OPENGL_DEFAULT_SHADER_H
#define DAZ_OPENGL_DEFAULT_SHADER_H

/*****************************
	Include files
*****************************/

#include "dzsceneshader.h"

/****************************
	Forward declarations
****************************/

class DzSpotLight;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzOGLDefaultShader : public DzSceneShader {
	Q_OBJECT
public:

	DzOGLDefaultShader();

	///////////////////////////////
	// from DzSceneShader:

	virtual void	setGL( const DzCamera *cam ) const;
	virtual void	setCurrentMaterial( const DzMaterial *mat ) const;
	virtual void	unsetCurrentMaterial() const;

	bool	needsBump() const;
	void	setSTVectors( const DzPnt3 &svec, const DzPnt3 &tvec );
	void	setShadowMap( int idx, int mapSize ) const;
	void	clearShadowMap() const;

private:

	void			getVariableLocations();

	void			setTextureMap( int idx ) const;
	void			setOpacityMap( int idx ) const;
	void			setBumpMap( int idx, int size ) const;

	void			clearTextureMap() const;
	void			clearOpacityMap() const;
	void			clearBumpMap() const;

	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzOGLDistantLightShader : public DzOGLDefaultShader {
	Q_OBJECT
public:
	DzOGLDistantLightShader();
};


class DZ_EXPORT DzOGLSpotLightShader : public DzOGLDefaultShader {
	Q_OBJECT
public:
	DzOGLSpotLightShader();

	///////////////////////////////
	// from DzSceneShader:

	virtual void	setGL( const DzCamera *cam ) const;

	void	setLight( DzSpotLight *light );
	void	setCone( float inside, float outside ) const;

private:

	DzSpotLight	*m_light;
};


class DZ_EXPORT DzOGLPointLightShader : public DzOGLDefaultShader {
	Q_OBJECT
public:
	DzOGLPointLightShader();
};

#endif // DAZ_OPENGL_DEFAULT_SHADER_H