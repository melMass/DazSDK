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
	Defines the DzVertexMesh class.
**/

#ifndef DAZ_VERTEX_SHAPE_H
#define DAZ_VERTEX_SHAPE_H

/*****************************
	Include files
*****************************/
#ifndef DSON_IO
#include "dzbufferobject.h"
#endif

#include "dzgeometry.h"
#include "dzpair.h"
#include "dztblockarray.h"
#include "dztsortedarray.h"

/****************************
	Definitions
****************************/

// Vertex Flags
#define DZ_VERTEX_DEFAULT	0x00
#define DZ_VERTEX_SELECTED	0x01
#define DZ_VERTEX_UNUSED	0x02
#define DZ_VERTEX_LOCKED	0x04

/****************************
	Forward declarations
****************************/

class DzVec3;
class DzVertexGroup;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzVertexMesh : public DzGeometry {
	Q_OBJECT
public:
	DzVertexMesh();
	virtual ~DzVertexMesh();

	//
	// REIMPLEMENTATIONS
	//

#ifndef DSON_IO
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual DzError			finishLoad( const DzInFile *file );
	virtual void			writeData( DzOutFile *file ) const;
#endif
	virtual void			beginEdit( bool enableUndo = true );
	virtual void			finishEdit();
	virtual void			cancelEdit();
//	virtual void			cacheForModifier();
	virtual void			transform( const DzMatrix3 &matrix );
	virtual void			translate( const DzVec3 &vec );
	virtual void			rotate( const DzQuat &rot );
	virtual void			scale( const DzVec3 &vec );
	virtual void			scale( float scalar );
	virtual void			clearAll();
	virtual DzBox3			getBoundingBox() const;
	virtual DzOrientedBox3	getOrientedBox( const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale ) const;
	virtual bool			isEmpty() const;
	virtual DzVertexMap*	vertexMapFromImage( const QImage &img,
								DzMap::MapType type = DzMap::FLOAT_MAP ) const;
	virtual bool			copyFrom( DzVertexMesh *mesh, bool shareVerts = false, bool shareFacets = true );

public slots:

	//
	// MANIPULATORS
	//

	int		addVertex( float x, float y, float z );
	int		addVertex( const DzVec3 &pnt );
	void	addVerticesFromMesh( const DzVertexMesh *mesh );
	void	setVertex( int index, const DzVec3 &pnt );
	void	removeVertices( const DzTSortedArray<int> &vertIndices );
	void	selectVertex( int which, bool onOff = true );
	void	selectAllVertices( bool onOff = true );
	bool	createVertexGroup( const QString &name ) { return false; }
	void	addToVertexGroup( const QString &name ) { }
	void	activateVertexGroup( const QString &name );
	void	deactivateVertexGroup( const QString &name );
	void	deactivateAllVertexGroups();
	DzPnt3*	setVertexArray( int numVerts );
	DzError	preSizeVertexArray( int numVerts );

	//
	// ACCESSORS
	//

	int						getNumVertices() const;
	DzVec3					getVertex( int idx ) const;
	DzPnt3*					getVerticesPtr() const;
	int						getNumVertexGroups() const;
	const DzVertexGroup*	getVertexGroup( int which ) const;
	bool					isVertexSelected( int which ) const;
	int						getNumActiveVertexGroups() const;
	const DzVertexGroup*	getActiveVertexGroup( int which ) const;
#ifndef DSON_IO
	DzVertexBuffer*			getVertexBuffer() const;
#endif

public:

	unsigned char	getVertexFlag( int idx ) const;
	unsigned char*	getVertexFlagsPtr() const;
	virtual quint64	getUniqueId()const;
	quint64			getCopyID()const;
	void			incrementMeshVersion()const;

signals:

	void	topologyChanged();
	void	vertexSelectionChanged();

protected:

	DzVertexMesh( const DzVertexMesh &mesh, bool shareVertList = true );
	void	shareVertList( DzVertexMesh *mesh ) const;

#ifndef DSON_IO
	void	writeVertexData( DzOutFile *file ) const;
	void	updateVertexBufferObject( const DzTBlockArray<DzVertNTPair> *pairsVNTAdditional );
	void	clearVertexBuffer();
	void	prepareVertexBuffer();
#endif

private:

	void	makeVertsUnique();

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzVertexMesh> DzVertexMeshPtr;

#endif // DAZ_VERTEX_SHAPE_H
