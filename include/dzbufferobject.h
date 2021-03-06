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

#ifndef DAZ_BUFFER_OBJECT_H
#define DAZ_BUFFER_OBJECT_H

/*****************************
	Include files
*****************************/

#include "dzopengl.h"
#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/*****************************
	Definitions
*****************************/

#define DZBO_TEMPLATE template<GLenum target, GLenum binding> 

/*****************************
	Class definitions
*****************************/

DZBO_TEMPLATE 
class DzBufferObject: public DzRefCountedItem
{ 
public: 
	//
	// CREATORS
	//

	DzBufferObject();
	DzBufferObject( GLsizeiptrARB size, const void *data = NULL, GLenum usage = GL_STREAM_DRAW_ARB ); 
	~DzBufferObject(); 

	//
	// MANIPULATORS
	//

	bool			setData( GLsizeiptrARB size, const void *data = NULL, GLenum usage = GL_STREAM_DRAW_ARB ) const; 
	bool			replaceData( GLsizeiptrARB size, const void *data, GLintptrARB offset = 0 ) const; 

	void*			map( GLenum access ) const; 
	bool			unmap() const; 
	void*			getMappedData() const; 
	bool			isMapped() const; 

	bool			bind() const;
	
	//
	// ACCESSORS
	//

	GLsizeiptrARB	getSize() const; 
	GLenum			getUsageType() const; 
	GLenum			getAccessType() const; 

	bool			isValid();
	GLuint			getID() const;
	bool			getData( GLsizeiptrARB size, void *data, GLintptrARB offset ) const; 

	int				getDataSize();

	//
	// STATIC
	//

	static bool		isSupported();
	static bool		isBuffer( GLuint id );
	static GLuint	getCurrent(); 
	static bool		bind( GLuint id );
	static void		unbind();

private: 

	bool			getParameter( GLenum name, GLint &parameter ) const;

	//
	// DATA MEMBERS
	//

	GLuint			m_id;
}; 


typedef DzBufferObject<GL_ARRAY_BUFFER_ARB,GL_ARRAY_BUFFER_BINDING_ARB> DzVertexBuffer; 
typedef DzBufferObject<GL_ELEMENT_ARRAY_BUFFER_ARB,GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB> DzIndexBuffer; 

typedef DzTSharedPointer<DzVertexBuffer>	DzVertexBufferPtr;
typedef DzTSharedPointer<DzIndexBuffer>		DzIndexBufferPtr;

/**
**/
DZBO_TEMPLATE 
DzBufferObject<target, binding>::DzBufferObject()
	: DzRefCountedItem(),
	m_id(0)
{
	GLenum	error;

	glGenBuffersARB( 1, &m_id );

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error generating GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
}

/**
**/
DZBO_TEMPLATE 
DzBufferObject<target, binding>::DzBufferObject( GLsizeiptrARB size, const void *data, GLenum usage )
	: DzRefCountedItem(),
	m_id(0)
{ 
	GLenum	error;

	glGenBuffersARB( 1, &m_id ); 
	error = glGetError();
	if( error == GL_NO_ERROR )
		setData( size, data, usage ); 
	else
		DZ_WARNING( QString( "Error generating GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
} 

/**
**/
DZBO_TEMPLATE 
DzBufferObject<target, binding>::~DzBufferObject()
{ 
	GLenum	error;
	
	glDeleteBuffersARB( 1, &m_id );

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error deleting GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
} 

/**
**/
DZBO_TEMPLATE 
inline int DzBufferObject<target, binding>::getDataSize()
{ 
	if( !bind() )
		return 0;

	int	sz = 0;

	glGetBufferParameterivARB( target, GL_BUFFER_SIZE_ARB, &sz );

	return sz;
} 

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target, binding>::isSupported()
{ 
	return dzOGL ? dzOGL->isVBOSupported() : false;
}

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target, binding>::isBuffer( GLuint id )
{
	return glIsBufferARB( id ) != GL_FALSE;
}

/**
**/
DZBO_TEMPLATE 
inline GLuint DzBufferObject<target, binding>::getCurrent()
{ 
	GLint value;

	glGetIntegerv( binding, &value ); 

	return GLuint( value ); 
}

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target, binding>::bind( GLuint id )
{
	GLenum			error;

	glBindBufferARB( target, id );
	error = glGetError();
	if( error == GL_NO_ERROR )
		return true;

	DZ_WARNING( QString( "Error binding GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
	return false;
}

/**
**/
DZBO_TEMPLATE 
inline void DzBufferObject<target, binding>::unbind()
{
	bind( 0 );
}

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target,binding>::isValid()
{
	return isBuffer( m_id );
}

/**
**/
DZBO_TEMPLATE 
inline GLuint DzBufferObject<target,binding>::getID() const 
{ 
	return m_id; 
}

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target,binding>::getData( GLsizeiptrARB size, void *data, GLintptrARB offset ) const
{ 
	GLenum	error;

	if( !bind() ) 
		return false;

	glGetBufferSubDataARB( target, offset, size, data ); 
	error = glGetError();
	if( error == GL_NO_ERROR )
		return true;

	DZ_WARNING( QString( "Error getting data from GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
	return false;
}

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target, binding>::setData( GLsizeiptrARB size, const void *data, GLenum usage ) const
{ 
	GLenum	error;

	if( !bind() ) 
		return false;

	glBufferDataARB( target, size, data, usage ); 
	error = glGetError();
	if( error == GL_NO_ERROR )
		return true;

	DZ_WARNING( QString( "Error setting data for GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
	return false;
} 

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target, binding>::replaceData( GLsizeiptrARB size, const void *data, GLintptrARB offset ) const
{ 
	GLenum			error;

	if( !bind() ) 
		return false;

	glBufferSubDataARB(target, offset, size, data); 
	error = glGetError();
	if( error == GL_NO_ERROR )
		return true;

	DZ_WARNING( QString( "Error replacing data for GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
	return false;
} 

/**
**/
DZBO_TEMPLATE 
inline void* DzBufferObject<target, binding>::map( GLenum access ) const
{
	GLenum	error;
	void	*data;

	if( !bind() ) 
		return NULL;

	data = glMapBufferARB(target, access);

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error mapping GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );

	return data;
} 

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target, binding>::unmap() const
{
	GLenum	error;
	bool	result;

	if( !bind() ) 
		return false;

	result = ( glUnmapBufferARB( target ) != GL_FALSE );

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error unmapping GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );

	return result;
} 

/**
**/
DZBO_TEMPLATE 
inline void* DzBufferObject<target, binding>::getMappedData() const
{ 
	GLenum	error;
	void	*value;

	glGetBufferPointervARB( target, GL_BUFFER_MAP_POINTER_ARB, &value ); 

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error getting mapped data from GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );

	return value; 
} 

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target,binding>::getParameter( GLenum name, GLint &parameter ) const
{ 
	GLenum	error;

	if( !bind() ) 
		return false;

	glGetBufferParameterivARB( target, name, &parameter ); 

	error = glGetError();
	if( error == GL_NO_ERROR )
		return true;

	DZ_WARNING( QString( "Error parameter from GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );
	return false;
} 

/**
**/
DZBO_TEMPLATE 
inline GLsizeiptrARB DzBufferObject<target, binding>::getSize() const
{ 
	GLenum	error;
	GLint	value;

	getParameter( GL_BUFFER_SIZE_ARB, value );

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error getting size of GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );

	return GLsizeiptrARB(value); 
} 

/**
**/
DZBO_TEMPLATE 
inline GLenum DzBufferObject<target,binding>::getUsageType() const
{ 
	GLenum	error;
	GLint	value;

	getParameter( GL_BUFFER_USAGE_ARB, value ); 

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error getting usage type of GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );

	return GLenum(value); 
} 

/**
**/
DZBO_TEMPLATE 
inline GLenum DzBufferObject<target,binding>::getAccessType() const
{ 
	GLenum	error;
	GLint	value; 

	getParameter( GL_BUFFER_ACCESS_ARB, value );

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error getting access type of GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );

	return GLenum(value); 
} 

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target,binding>::isMapped() const
{ 
	GLenum	error;
	GLint	value;

	getParameter( GL_BUFFER_MAPPED_ARB, value ); 

	error = glGetError();
	if( error != GL_NO_ERROR )
		DZ_WARNING( QString( "Error getting mapped state of GL Buffer Object: " ) + QString( (const char*) gluErrorString( error ) ) );

	return value != GL_FALSE; 
} 

/**
**/
DZBO_TEMPLATE 
inline bool DzBufferObject<target,binding>::bind() const 
{ 
	if( getCurrent() != m_id )
		return bind( m_id );

	return true;
}

#undef DZBO_TEMPLATE 

class DzPrimIndexBuffer
{
public:
	DzPrimIndexBuffer(): m_elCount(0), m_primType(GL_TRIANGLES), m_buffer(new DzIndexBuffer)
	{
	}

	DzPrimIndexBuffer(size_t size, GLenum primType, DzIndexBufferPtr buffer):
		m_elCount(size),
		m_primType(primType),
		m_buffer(buffer)
	{
	}

	size_t 				m_elCount;
	GLenum 				m_primType;
	DzIndexBufferPtr	m_buffer;
};

#endif // DAZ_BUFFER_OBJECT_H
