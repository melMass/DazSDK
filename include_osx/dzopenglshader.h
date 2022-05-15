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
	Defines the DzOpenGLShader class.
**/

#ifndef DAZ_OPENGL_SHADER_H
#define DAZ_OPENGL_SHADER_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/****************************
	Forward declarations
****************************/

class QString;
class QStringList;
class DzCamera;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzOpenGLShader : public DzBase {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzOpenGLShader();
	virtual ~DzOpenGLShader();

	//
	// MANIPULATORS
	//

	void	setVertexShader( const QString &code, bool isFile = false );
	void	setFragmentShader( const QString &code, bool isFile = false );

	//
	// ACCESSORS
	//

	virtual void	setGL( const DzCamera *cam ) const;
	virtual void	unsetGL() const;

	bool	isValid() const;
	void	setUniform1f( const char *name, float val ) const;
	void	setUniform1i( const char *name, int val ) const;
	int		getUniformLocation( const char *name ) const;
	int		getAttributeLocation( const char *name ) const;
	bool	doTestCompile( QString *output = NULL );

protected:

	static void		triggerRedraw();

private:

	bool	compile( QString *output = NULL );
	void	flagRecompile();
	QString readFromFile( const QString &filename );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_OPENGL_SHADER_H
