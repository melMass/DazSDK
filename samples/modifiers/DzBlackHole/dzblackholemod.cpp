/**********************************************************************
	Copyright (c) 2002-2020 Daz 3D, Inc. All Rights Reserved.

	This file is part of the Daz Studio SDK.

	This file may be used only in accordance with the Daz Studio SDK
	license provided with the Daz Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of Daz 3D, Inc, except as explicitly
	allowed in the Daz Studio SDK license.

	See http://www.daz3d.com to contact Daz 3D, Inc or for more
	information about the Daz Studio SDK.
**********************************************************************/
/*****************************
	Include files
*****************************/
#include "dzfacetmesh.h"
#include "dzinfile.h"
#include "dzobject.h"
#include "dzscene.h"

#include "dzblackholenode.h"
#include "dzblackholemod.h"

/*****************************
   File Section IDs
*****************************/
#define DZ_BLACK_HOLE_NODE_SECTION		0x0200
#define DZ_BLACK_HOLE_RADIUS_SECTION	0x0201

///////////////////////////////////////////////////////////////////////
// DzBlackHoleMod
///////////////////////////////////////////////////////////////////////

/**
**/
DzBlackHoleMod::DzBlackHoleMod() : m_radius( 1.0f ), m_node( NULL )
{
}

/**
**/
DzBlackHoleMod::~DzBlackHoleMod()
{
}

/**
**/
void DzBlackHoleMod::loadSection( DzInFile* file, short sectionID )
{
	switch( sectionID )
	{
	case DZ_BLACK_HOLE_NODE_SECTION:
		file->readPointer();
		break;
	case DZ_BLACK_HOLE_RADIUS_SECTION:
		file->readFloat( m_radius );
		break;
	default:
		DzWSModifier::loadSection( file, sectionID );
		break;
	}
}

/**
**/
void DzBlackHoleMod::setPointer( const DzInFile* file, short sectionID, short pointerID, DzBase* ptr )
{
	if ( sectionID == DZ_BLACK_HOLE_NODE_SECTION )
	{
		setNode( DZ_ASSERT_CAST( ptr, DzBlackHoleNode ) );
	}
	else
	{
		DzWSModifier::setPointer( file, sectionID, pointerID, ptr );
	}
}

/**
**/
DzError DzBlackHoleMod::apply( DzVertexMesh &geom, DzNode &node )
{
	DzVec3 wsPos;
	DzMatrix3 wsScale;
	DzQuat wsRot;

	m_node->getWSTransform( wsPos, wsRot, wsScale );
	wsRot.invert();
	wsScale = wsScale.inverse();

	const int nVerts = geom.getNumVertices();
	DzPnt3* verts = geom.getVerticesPtr();
	const float radius = m_radius;

	for ( int i = 0; i < nVerts; i++, verts++ )
	{
		DzVec3 vec = *verts;
		vec -= wsPos;
		vec = wsRot.multVec( vec );
		vec *= wsScale;

		const float dist = vec.length() / radius;
		if ( dist < 1.0f )
		{
			vec = *verts;
			vec = wsPos - vec;
			vec *= (1.0f - dist);
			(*verts)[0] += vec.m_x;
			(*verts)[1] += vec.m_y;
			(*verts)[2] += vec.m_z;
		}
	}

	return DZ_NO_ERROR;
}

/**
**/
DzError DzBlackHoleMod::applyInverse( DzVertexMesh &geom, DzNode &node )
{
	// needs to be implemented
	return DZ_NO_ERROR;
}

/**
**/
void DzBlackHoleMod::setNode( DzBlackHoleNode* node )
{
	if( m_node == node )
	{
		return;
	}

	if( m_node )
	{
		disconnect( m_node, SIGNAL(transformChanged()), this, SLOT(updateTransform()) );
		disconnect( m_node, SIGNAL(radiusChanged()), this, SLOT(updateRadius()) );
	}

	m_node = node;

	if( m_node )
	{
		DzConnect( m_node, SIGNAL(transformChanged()), this, SLOT(updateTransform()) );
		DzConnect( m_node, SIGNAL(radiusChanged()), this, SLOT(updateRadius()) );

		m_radius = m_node->getRadius();
	}
}


/**
**/
void DzBlackHoleMod::updateTransform()
{
	DzNodeListIterator nodeIt( dzScene->nodeListIterator() );
	while ( nodeIt.hasNext() )
	{
		if ( DzObject* obj = nodeIt.next()->getObject() )
		{
			obj->invalidateCache();
		}
	}
}

/**
**/
void DzBlackHoleMod::updateRadius()
{
	if( m_node )
	{
		m_radius = m_node->getRadius();
	}

	updateTransform();
}

#include "moc_dzblackholemod.cpp"
