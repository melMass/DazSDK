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

#ifndef DAZ_VBO_PACK_H
#define DAZ_VBO_PACK_H

/*****************************
	Include files
*****************************/

#include "dztarray.h"
#include "dzbufferobject.h"

/*****************************
	Definitions
*****************************/

#define MAX_TEXTURE_UNITS_COUNT 8

/*****************************
	Class definitions
*****************************/

class DzVertexBufferInPack
{
public:
	DzVertexBufferInPack(DzVertexBuffer *vb, GLint size, GLenum type, GLsizei stride):
	m_vb(vb),
	m_size(size),
	m_type(type),
	m_stride(stride)
	{
	}

	DzVertexBuffer	*m_vb;
	GLint	m_size;
	GLenum	m_type;
	GLsizei	m_stride;
};

class DzVBOPack
{
public:
	DzVBOPack();
	~DzVBOPack();

	void setDrawMask(bool vertexes, bool normals, bool uvs);
	void setTexturesCount(int count) { m_texCount = count; }

	void drawPrimIndexBuffers(const DzTArray<DzPrimIndexBuffer> &primIndexBuffers);

	void draw(GLenum mode, DzIndexBuffer *ebo, unsigned count);

	void drawElements(GLenum mode, unsigned count, GLenum type, void *indexes);
	void draw(GLenum mode, unsigned char *indexes, unsigned count);
	void draw(GLenum mode, unsigned short *indexes, unsigned count);
	void draw(GLenum mode, unsigned int *indexes, unsigned count);

	void setVertexesVBO(DzVertexBuffer *vb, GLint vertexSize = 3,
				GLenum vertexType = GL_FLOAT, GLenum vertexStride = 0);
	void setNormalsVBO(DzVertexBuffer *vb, GLenum normalType = GL_FLOAT,
				GLenum normalStride = 0);
	void setUVsVBO(DzVertexBuffer *vb, int texLevel, GLint uvSize = 2,
				GLenum uvType = GL_FLOAT, GLenum uvStride = 0);

private:

	void bindVBOs();

private:
	DzVertexBufferInPack	*m_vertexesVBO;
	DzVertexBufferInPack	*m_normalsVBO;
	DzVertexBufferInPack	*m_uvsVBO[MAX_TEXTURE_UNITS_COUNT];

	bool	m_drawVertexes;
	bool	m_drawNormals;
	bool	m_drawUVs;

	unsigned	m_texCount;

	int		m_maxTextures;
};

#endif // DAZ_VBO_PACK_H
