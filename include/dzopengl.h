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
	Defines the DzOpenGL class.
**/

#ifndef DAZ_OPENGL_H
#define DAZ_OPENGL_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

#ifdef Q_OS_WIN
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#else
#include <gl/glew.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtOpenGL/qgl.h>
#include <QtOpenGL/QGLBuffer>
#include <QtOpenGL/QGLColormap>
#include <QtOpenGL/QGLFramebufferObject>
#include <QtOpenGL/QGLPixelBuffer>
#include <QtOpenGL/QGLShaderProgram>

/****************************
	Definitions
****************************/

/**
	@sdk
	This is the minimum version of OpenGL supported by DAZ Studio.
**/
#define DZ_MIN_OPEN_GL_VERSION	1.3f

/****************************
	Forward declarations
****************************/

class DzPBuffer;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzOpenGL : public QObject {
	Q_OBJECT
	Q_ENUMS( OGLTexQuality )
	friend class DzApp;
private:
	//
	// CONSTRUCTORS
	//

	enum	StartMode { OGLNormal, OGLSafe, OGLOff };

	DzOpenGL( StartMode mode );
	~DzOpenGL();

public:

	enum OGLTexQuality	{ OGLLow = 0, OGLMed = 1, OGLHigh = 2, OGLBest = 3 };

public slots:
	//
	// MANIPULATORS
	//

	void	setMultisampleEnabled( bool onOff );
	void	setTextureQuality( OGLTexQuality quality );
	void	setDisplayOptimizationEnabled( bool onOff ); 
	void	setBoundingBoxActiveOpacity( float opacity );
	void	setBoundingBoxInactiveOpacity( float opacity );
	void	setBoundingBoxEdgeLength( float length );
	void	setWireframeOpacity( float opacity );
	void	setSubDivisionWireOpacity( float opacity );
	void	setDrawNodeHighlight( bool onOff );

	//
	// ACCESSORS
	//

#ifndef Q_MOC_RUN
	static
#endif
	bool	isOGLInitialized();
	bool	getDrawNodeHighlight() const;

	double	getOpenGLVersion() const;
	int		getMajorVersion() const;
	int		getMinorVersion() const;
	int		getReleaseNumber() const;
	bool	isOGLExtensionSupported( const QString &extension ) const;
	bool	isOGLShaderLanguageSupported() const;
	int		getNumOGLExtensions() const;
	bool	isShadowingSupported() const;
	bool	isMultisampleSupported() const;
	bool	isMultisampleEnabled() const;
	bool	isVBOSupported() const;
	int		getNumLights() const;
	int		getMaxTextureUnits() const;
	int		getMaxTextureSize() const;
	int		getDepthBufferBits() const;
	int		getNumAuxBuffers() const;
	int		getTextureQualityMaxSize() const;
	bool	isDisplayOptimizationEnabled() const;
	float	getBoundingBoxActiveOpacity() const;
	float	getBoundingBoxInactiveOpacity() const;
	float	getBoundingBoxEdgeLength() const;
	float	getWireframeOpacity() const;
	float	getSubDivisionWireOpacity() const;

	OGLTexQuality	getTextureQuality() const;
	DzPBuffer*		getPBuffer() const;

signals:

	void	multisampleEnabled( bool onOff );
	void	textureQualityChanged( DzOpenGL::OGLTexQuality quality );
	void	displayOptimizationEnabled( bool onOff );
	void	boundingBoxActiveOpacityChanged( float value );
	void	boundingBoxInactiveOpacityChanged( float value );
	void	boundingBoxEdgeLengthChanged( float value );
	void	wireframeOpacityChanged( float value );
	void	subDivisionWireOpacityChanged( float value );
	void	drawNodeHighlightChanged( bool onOff );

private:
	// Called to initialize all available OpenGL extensions.
	void	initOGLExtensions();
	void	initOGLSafe();
	void	getOGLSettings();
	void	parseVersion();

	struct	Data;
	Data	*m_data;
};

extern DZ_EXPORT DzOpenGL *dzOGL;

#endif // DAZ_OPENGL_H
