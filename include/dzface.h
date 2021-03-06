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
	Defines the DzFacet and DzEdge class.
**/

#ifndef DAZ_FACE_H
#define DAZ_FACE_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Definitions
*****************************/

#define DZ_MAX_FACE_EDGES			255

// --------- Bit flags for the DzFace class
// Set if this face has at least one vertIdx/uvIdx pair that does not match.
#define DZ_ORPHAN_FACE_BIT			0x0001

// Bits for facet selection and hiding. These flags are masked on load and save.
#define DZ_HIDDEN_FACE_BIT			0x0002
#define DZ_SELECTED_FACE_BIT		0x0004
#define DZ_LOCKED_FACE_BIT			0x0008
#define DZ_FACET_FLAG_BITMASK		0x000e

// --------- Bit flags for the DzEdge class
#define DZ_SD_CAGE_EDGE_BIT			0x0001
#define DZ_SD_DISCONTINOUS_EDGE_BIT	0x0002

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzEdge {
public:
	DzEdge() : m_vert1( -1 ), m_vert2( -1 ), m_facetA( -1 ),
		m_facetB( -1 ), m_offsetA( -1 ), m_offsetB( -1 ),
		m_idx( -1 ), m_flags( 0 )
	{ }

	DzEdge( int v1, int v2 ) : m_facetA( -1 ), m_facetB( -1 ), 
		m_offsetA( -1 ), m_offsetB( -1 ), m_idx( -1 ), m_flags( 0 )
	{
		if( v1 < v2 ) { m_vert1 = v1; m_vert2 = v2; }
		else { m_vert1 = v2; m_vert2 = v1; }
	}

	DzEdge( const DzEdge &edge ) { *this = edge; }

	DzEdge	&operator=( const DzEdge &edge )
	{
		m_vert1 = edge.m_vert1; m_vert2 = edge.m_vert2;
		m_facetA = edge.m_facetA; m_facetB = edge.m_facetB;
		m_offsetA = edge.m_offsetA; m_offsetB = edge.m_offsetB;
		m_idx = edge.m_idx; m_flags = edge.m_flags;
		return *this;
	}

	bool	operator<( const DzEdge &edge ) const
	{
		if( m_vert1 < edge.m_vert1 ) return true;
		else if( m_vert1 == edge.m_vert1 ) return m_vert2 < edge.m_vert2;
		return false;
	}

	bool	operator==( const DzEdge &edge ) const
	{ return (m_vert1 == edge.m_vert1 && m_vert2 == edge.m_vert2); }

	bool	isOpenEdge() const
	{
		if( m_facetA >= 0 && m_facetB >= 0 )
			return false;
		return true;
	}

	int		m_vert1, m_vert2;
	int		m_facetA, m_facetB;
	int		m_idx;
	char	m_offsetA, m_offsetB;

	unsigned short	m_flags;
};

class DZ_EXPORT DzFacet {
public:
	DzFacet() { clear(); }
	DzFacet( const DzFacet &face ) { *this = face; }

	DzFacet	&operator=( const DzFacet &face )
	{
		m_materialIdx = face.m_materialIdx;
		m_faceGroupIdx = face.m_faceGroupIdx;
		m_vertIdx[0] = face.m_vertIdx[0]; m_vertIdx[1] = face.m_vertIdx[1];
		m_vertIdx[2] = face.m_vertIdx[2]; m_vertIdx[3] = face.m_vertIdx[3];
		m_uvwIdx[0] = face.m_uvwIdx[0]; m_uvwIdx[1] = face.m_uvwIdx[1];
		m_uvwIdx[2] = face.m_uvwIdx[2]; m_uvwIdx[3] = face.m_uvwIdx[3];
		m_normIdx[0] = face.m_normIdx[0]; m_normIdx[1] = face.m_normIdx[1];
		m_normIdx[2] = face.m_normIdx[2]; m_normIdx[3] = face.m_normIdx[3];
		m_edges[0] = face.m_edges[0]; m_edges[1] = face.m_edges[1];
		m_edges[2] = face.m_edges[2]; m_edges[3] = face.m_edges[3];
		m_cageIdx = face.m_cageIdx;
		return *this;
	}

	bool	operator==( const DzFacet &face ) const
	{
		if( m_materialIdx != face.m_materialIdx ) return false;
		if( m_faceGroupIdx != face.m_faceGroupIdx ) return false;
		if( m_vertIdx[0] != face.m_vertIdx[0] || m_vertIdx[1] != face.m_vertIdx[1] ||
			m_vertIdx[2] != face.m_vertIdx[2] || m_vertIdx[3] != face.m_vertIdx[3] )
			return false;
		if( m_uvwIdx[0] != face.m_uvwIdx[0] || m_uvwIdx[1] != face.m_uvwIdx[1] ||
			m_uvwIdx[2] != face.m_uvwIdx[2] || m_uvwIdx[3] != face.m_uvwIdx[3] )
			return false;
		if( m_normIdx[0] != face.m_normIdx[0] || m_normIdx[1] != face.m_normIdx[1] ||
			m_normIdx[2] != face.m_normIdx[2] || m_normIdx[3] != face.m_normIdx[3] )
			return false;
		if ( m_cageIdx != face.m_cageIdx )
			return false;
		return true;
	}

	void	clear()
	{
		m_materialIdx = 0;
		m_faceGroupIdx = 0;
		m_vertIdx[0] = m_vertIdx[1] = m_vertIdx[2] = m_vertIdx[3] = -1;
		m_uvwIdx[0] = m_uvwIdx[1] = m_uvwIdx[2] = m_uvwIdx[3] = -1;
		m_normIdx[0] = m_normIdx[1] = m_normIdx[2] = m_normIdx[3] = -1;
		m_edges[0] = m_edges[1] = m_edges[2] = m_edges[3] = -1;
		m_cageIdx = -1;
	}

	bool	isQuad() const { return (m_vertIdx[3] >= 0); }
	bool	isTri() const { return (m_vertIdx[3] < 0); }

	unsigned short	m_materialIdx;
	unsigned short	m_faceGroupIdx;
	int				m_vertIdx[4], m_uvwIdx[4], m_normIdx[4];
	int				m_edges[4], m_cageIdx;
};

Q_DECLARE_METATYPE( DzFacet );

#endif // DAZ_FACE_H
