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
	Defines the DzFaceGroup class.
**/

#ifndef DAZ_FACE_GROUP_H
#define DAZ_FACE_GROUP_H

/*****************************
	Include files
*****************************/

#include "dzindexlist.h"
#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/*****************************
	Definitions
*****************************/

/** The default Smoothing Angle for DzPolyMesh objects */
#define DZ_DEFAULT_SMOOTH_ANGLE	89.9f

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFaceGroup : public DzIndexList, public DzRefCountedItem {
	Q_OBJECT
public:
	//
	// CREATION/DESTRUCTION
	//

	DzFaceGroup( const QString &name = QString::null );
	DzFaceGroup( const DzFaceGroup &grp );
	virtual ~DzFaceGroup();

	//
	// MANIPULATORS
	//

//	void	setUseVBORendering( bool use );

public slots:

	//
	// ACCESSORS
	//

//	DzFacetMesh*	getOwner() const;

public:
//	void	clearPrimIndexBuffers();
//	void	setPrimIndexBuffers( DzTArray<DzPrimIndexBuffer> &primIndexBuffer );

//	int		getNumVerts() const;
//	void	getVertices( DzTSortedArray<int> &verts ) const;
//	void	getBoundaryVertices( DzTSortedArray<int> &verts ) const;
//	void	getEdges( DzTSortedArray<DzIndexedVertexPair> &edges ) const;
//	bool	getUseVBORendering() const;

//	const DzTArray<DzPrimIndexBuffer>*	getPrimIndexBuffers() const;

private:

	bool	removeFace( int faceIdx, DzIndexList *faces, bool updateIndices );
//	void	getAllEdges( DzTSortedArray<DzIndexedVertexPair> &edges ) const;

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzFaceGroup>	DzFaceGroupPtr;

class DZ_EXPORT DzMaterialFaceGroup : public DzFaceGroup {
	Q_OBJECT
public:
	//
	// CREATION/DESTRUCTION
	//
	DzMaterialFaceGroup( const QString &name = QString::null );
	DzMaterialFaceGroup( const DzMaterialFaceGroup &grp );
	virtual ~DzMaterialFaceGroup();

public slots:
	void setRenderAsCurve(bool onOff);
	bool getShouldRenderAsCurve()const;

private:
	struct	Data;
	Data	*m_data;
};
typedef DzTSharedPointer<DzMaterialFaceGroup>	DzMaterialFaceGroupPtr;

class DZ_EXPORT DzIndexedVertexPair {
public:
	DzIndexedVertexPair();
	DzIndexedVertexPair( int idx1, int idx2 );

	void		setVerts( int idx1, int idx2 );
	bool		operator==( const DzIndexedVertexPair &item ) const;
	DZ_EXPORT friend bool	operator<( const DzIndexedVertexPair &left, const DzIndexedVertexPair &right );

	int	m_vert1, m_vert2, m_useCount, m_firstFaceIdx;
};


#endif // DAZ_FACE_GROUP_H
