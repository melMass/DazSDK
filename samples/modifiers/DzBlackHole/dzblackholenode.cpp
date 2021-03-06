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
#include <math.h>

#include <QtGui/QPixmap>

#include "dzdrawstyle.h"
#include "dzfloatproperty.h"
#include "dzinfile.h"
#include "dzmatrix4.h"
#include "dzopengl.h"
#include "dzscene.h"

#include "dzblackholemod.h"
#include "dzblackholenode.h"

/*****************************
   Definitions
*****************************/
// File Section IDs
#define DZ_BLACK_HOLE_RADIUS_SECTION	0x0200

///////////////////////////////////////////////////////////////////////
// DzBlackHoleNode
///////////////////////////////////////////////////////////////////////

/**
**/
DzBlackHoleNode::DzBlackHoleNode()
{
	// Calling DzElement::addProperty() adds the property to the element, which takes ownership
	// of the property (DzElement is in charge of deleting this object). DzElement also is
	// responsible for saving and loading properties via the native file format. In this case,
	// when this class is loaded from a file, it's constructor will be called, creating a new
	// radius property. Then, when DzElement loads the properties from the file, it will delete
	// the existing radius property and replace it with the new one. We are responsible for updating
	// our local pointer when that happens.
	m_radius = new DzFloatProperty( "Radius", true, false, 100.0f );
	m_radius->setPath( "General/Misc" );
	addProperty( m_radius );

	DzConnect( m_radius, SIGNAL(currentValueChanged()), this, SIGNAL(radiusChanged()) );
	DzConnect( m_radius, SIGNAL(currentValueChanged()), this, SIGNAL(drawnDataChanged()) );
}

/**
**/
DzBlackHoleNode::~DzBlackHoleNode()
{
}

/**
**/
void DzBlackHoleNode::loadSection( DzInFile* file, short sectionID )
{
	if( sectionID == DZ_BLACK_HOLE_RADIUS_SECTION )
	{
		file->readPointer();
	}
	else
	{
		DzNode::loadSection( file, sectionID );
	}
}

/**
**/
void DzBlackHoleNode::setPointer( const DzInFile* file, short sectionID, short pointerID, DzBase* ptr )
{
	if( sectionID == DZ_BLACK_HOLE_RADIUS_SECTION )
	{
		// Here we match up our local radius pointer with the one read in from the file
		// by DzElement (DzElement has already deleted the one we created, see the comments
		// in the constructor). In this case, we chose to save a reference to the pointer in
		// the file, and then read it back in since this is a very fool-proof method.
		// Another approach would be to re-implement the postLoadFile() method in DzBlackHoleNode,
		// and search the property list to update the m_radius pointer - this method is completely
		// reasonable, and would even cut out a dozen bytes from the file footprint of the DzBlackHoleNode.
		m_radius = DZ_ASSERT_CAST( ptr, DzFloatProperty );
		DzConnect( m_radius, SIGNAL(currentValueChanged()), this, SIGNAL(radiusChanged()) );
		DzConnect( m_radius, SIGNAL(currentValueChanged()), this, SIGNAL(drawnDataChanged()) );
	}
	else
	{
		DzNode::setPointer( file, sectionID, pointerID, ptr );
	}
}

/**
**/
void DzBlackHoleNode::draw( const DzDrawStyle &style ) const
{
	// don't draw anything for renders, etc
	if( style.drawObjectsOnly() )
	{
		return;
	}

	glPushAttrib( GL_LIGHTING_BIT );
	glDisable( GL_LIGHTING );

	glPushMatrix();

	// draw our interactive representation

	DzVec3 wsPos;
	DzMatrix3 wsScale;
	DzQuat wsRot;

	getWSTransform( wsPos, wsRot, wsScale );
	glTranslatef( wsPos[0], wsPos[1], wsPos[2] );

	DzVec3 axis;
	float angle;
	wsRot.getValue( axis, angle );
	angle *= DZ_FLT_RAD_TO_DEG;
	glRotatef( -angle, axis[0], axis[1], axis[2] );

	glMultMatrixf( static_cast<const float*>(wsScale.matrix4()) );

	glColor3f( 0.0f, 0.0f, 0.0f );

	glBegin( GL_LINES );

	const float radius = m_radius->getValue();

	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, -radius, 0.0f );

	glVertex3f( 0.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, radius, 0.0f );

	const int sides = 12;
	const int segments = 6;
	const int numVerts = segments - 1;
	for( int i = 0; i < sides; i++ )
	{
		angle = DZ_FLT_2_PI * i / sides;
		const float x = sin( angle ) * radius;
		const float z = cos( angle ) * radius;

		for( int j = 0; j < numVerts; j++ )
		{
			angle = DZ_FLT_PI * (j + 1) / segments;
			const float y = -cos( angle ) * radius;
			const float cosVal = sin( angle );
			glVertex3f( 0.0f, 0.0f, 0.0f );
			glVertex3f( x * cosVal, y, z * cosVal );
		}
	}

	glEnd();

	glPopMatrix();
	glPopAttrib();
}

/**
**/
void DzBlackHoleNode::render( const DzRenderSettings &settings ) const
{
	// we never render anything
}

/**
**/
DzFloatProperty* DzBlackHoleNode::getRadiusControl() const
{
	return m_radius;
}

/**
**/
void DzBlackHoleNode::setRadius( float radius )
{
	return m_radius->setValue( radius );
}

/**
**/
float DzBlackHoleNode::getRadius() const
{
	return m_radius->getValue();
}

///////////////////////////////////////////////////////////////////////
// DzBlackHoleNodeIO
///////////////////////////////////////////////////////////////////////

/**
**/
DzBlackHoleNodeIO::DzBlackHoleNodeIO()
{
}

/**
**/
DzBlackHoleNodeIO::~DzBlackHoleNodeIO()
{
}

/**
**/
DzNode* DzBlackHoleNodeIO::createNode() const
{
	return new DzBlackHoleNode();
}

/**
**/
DzError DzBlackHoleNodeIO::writeExtraDefinition( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts )const
{
	return DZ_NO_ERROR;
}

/**
**/
DzError DzBlackHoleNodeIO::writeExtraInstance( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts )const
{
	return DZ_NO_ERROR;
}

/**
**/
DzAssetJsonObject* DzBlackHoleNodeIO::startDefinitionRead( DzAssetJsonItem* parentItem )
{
	return 0;
}

/**
**/
DzAssetJsonObject* DzBlackHoleNodeIO::startInstanceRead( DzAssetJsonItem* parentItem )
{
	return 0;
}

/**
**/
DzError DzBlackHoleNodeIO::applyDefinitionToObject( QObject* object, const DzFileIOSettings* opts )const
{
	return DZ_NO_ERROR;
}

/**
**/
DzError DzBlackHoleNodeIO::applyInstanceToObject( QObject* object, const DzFileIOSettings* opts )const
{
	DzBlackHoleNode* node = qobject_cast<DzBlackHoleNode*>( object );

	DzBlackHoleMod*	mod = new DzBlackHoleMod;
	mod->setNode( node );
	dzScene->addWSModifier( mod, 0 );

	return DZ_NO_ERROR;
}

/**
**/
void DzBlackHoleNodeIO::getOwnedAssets( QObject* object, QList< IDzSceneAsset* > &assets )
{
}

#include "moc_dzblackholenode.cpp"
