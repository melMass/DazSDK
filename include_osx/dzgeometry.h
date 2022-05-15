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
	Defines the DzGeometry class.
**/

#ifndef DAZ_GEOMETRY_H
#define DAZ_GEOMETRY_H

/*****************************
	Include files
*****************************/

#include "dzbox3.h"
#include "dzmap.h"
#include "dzorientedbox3.h"
#include "dzstorable.h"

/****************************
	Forward declarations
****************************/

class DzMatrix3;
class DzNode;
class DzUVSet;
class DzVertexMap;
class DzVertexMesh;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzGeometry : public DzStorable {
	Q_OBJECT
public:

	DzGeometry();
	virtual ~DzGeometry();

	//
	// REIMPLEMENTATIONS
	//

	virtual QString	getExtension() const { return "dso"; }
	virtual QString	getFiletype() const { return "Object Geometry"; }

public slots:

	//
	// MANIPULATORS
	//

	virtual void	transform( const DzMatrix3 &matrix ) = 0;
	virtual void	translate( const DzVec3 &vec ) = 0;
	virtual void	rotate( const DzQuat &rot ) = 0;
	virtual void	scale( const DzVec3 &vec ) = 0;
	virtual void	scale( float scalar ) = 0;
	virtual void	beginEdit( bool enableUndo = true ) = 0;
	virtual void	cancelEdit() = 0;
	virtual void	finishEdit() = 0;

public:

	//
	// ACCESSORS
	//

	virtual DzVertexMesh*	makeCopy( bool shareVerts = false, bool shareFacets = true ) const = 0;
	virtual bool			copyFrom( DzVertexMesh *mesh, bool shareVerts = false, bool shareFacets = true ) = 0;

	static DzGeometry*		getCurrentGeometryForNode( const DzNode *node );

public slots:

	virtual DzVertexMap*	vertexMapFromImage( const QImage &img, DzMap::MapType type = DzMap::FLOAT_MAP ) const = 0;
	virtual DzBox3			getBoundingBox() const = 0;
	virtual DzOrientedBox3	getOrientedBox( const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale ) const = 0;
	virtual DzBox3			getGroupBoundingBox( const QString &groupName ) const = 0;
	virtual DzOrientedBox3	getGroupOrientedBox( const QString &groupName, const DzVec3 &pos, const DzQuat &rot,
								const DzVec3 &scale ) const = 0;
	virtual DzBox3			getGroupBoundingBox( const QString &groupName, const DzMatrix3 &transform ) const = 0;
	virtual DzOrientedBox3	getGroupOrientedBox( const QString &groupName, const DzMatrix3 &transform,
								const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale ) const = 0;
	virtual int				getNumVertices() const = 0;
	virtual DzPnt3*			getVerticesPtr() const = 0;
	virtual bool			isEmpty() const = 0;
	virtual bool			hasMultipleLOD() const = 0;
	virtual int				getNumLODs() const = 0;
	virtual QString			getLODName( int which ) const = 0;

	virtual DzMap*			getUVs() const = 0;
	virtual int				getNumUVSets() const = 0;
	virtual DzUVSet*		getUVSet( int which ) const = 0;
	virtual quint64			getUniqueId()const=0;

signals:

	void	needRebuild( bool onOff );
	void	visibilityChanged();
	void	lodsChanged();

protected:

	DzGeometry( const DzGeometry &geom );

private:

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzGeometry> DzGeometryPtr;
Q_DECLARE_METATYPE( DzGeometryPtr );

#endif // DAZ_GEOMETRY_H
