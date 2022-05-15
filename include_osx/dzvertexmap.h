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
	Defines the DzVertexMap class.
**/

#ifndef DAZ_VERTEX_MAP_H
#define DAZ_VERTEX_MAP_H

/*****************************
	Include files
*****************************/

#include "dzmap.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzVertexMap;
class DzUVSet;
class DzGeometry;
class DzDctVertexData;

/****************************
	Type Definitions
****************************/

typedef DzTSharedPointer<DzVertexMap> DzVertexMapPtr;
typedef DzTSharedPointer<DzUVSet> DzUVSetPtr;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDctVertex {
public:
	DzDctVertex();
	DzDctVertex( int vertexIdx );
	DzDctVertex( const DzDctVertex &vert );
	~DzDctVertex();

	DzDctVertex&	operator=( const DzDctVertex &vert );

	void	setIndex( int vertIdx );

	void	setFacetMapIdx( int facetIdx, int mapIdx );
	void	removeFacet( int facetIdx );

	bool	isValid() const;

	int		getIndex() const;

	int		findFacet( int facetIdx ) const;
	int		getNumFacets() const;
	int		getNumMapIndices() const;
	int		getFacetIndex( int which ) const;
	int		getMapIndex( int which ) const;
	int*	getFacetIndices() const;
	int*	getMapIndices() const;

	DzDctVertex deepCopy()const;

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzVertexMap : public DzMap {
	Q_OBJECT
	Q_PROPERTY( bool discontinuous READ isDiscontinuous )
public:

	//
	// CREATORS/DESTRUCTORS
	//

	DzVertexMap( MapType mapType = FLOAT_MAP );
	virtual ~DzVertexMap();

	//
	// REIMPLEMENTATIONS
	//
#ifndef DSON_IO
	virtual void	loadSection( DzInFile *file, short sectionID );
#endif

	//
	// MANIPULATORS
	//

	void	addDctPnt2Value( int vertexIdx, int facetIdx, const DzPnt2 val );
	void	addDctPnt3Value( int vertexIdx, int facetIdx, const DzPnt3 val );
	void	copyFrom( DzVertexMap const*other, bool deepCopyDct = false );
	void	combineMap( int vertCount, DzVertexMap const* other, int otherCount, int otherFacetOffset );

public slots:

	void	setVertCount( int vertCount );
	void	addDctFloatValue( int vertexIdx, int facetIdx, float val );
	void	addDctPnt2Vec( int vertexIdx, int facetIdx, const DzVec3 &val );
	void	addDctPnt3Vec( int vertexIdx, int facetIdx, const DzVec3 &val );
	void	addDctIntValue( int vertexIdx, int facetIdx, int val );
	void	addDctShortValue( int vertexIdx, int facetIdx, short val );
	void	clearDiscontinuousData();
	int		getNumDiscontinuousVerts() const;
	void	setDctIndex( int vertexIdx, int facetIdx, int mapIdx );
	void	preSizeDiscontinuous( int disconCount );
	void	squeezeDiscontinuous();
	void	updateDctValue( int vertIdx, int mapIdx, int facetIdx );

	//
	// ACCESSORS
	//

	int		getVertCount() const;
	int		getMapIndex( int vertexIdx, int facetIdx ) const;

public:

	bool	isDiscontinuous() const;

	DzDctVertex*	getDiscontinuousVerts() const;
	DzDctVertex		findDiscontinuousVertex( int vertexIdx ) const;
	DzDctVertex*	findDiscontinuousVertexPtr( int vertexIdx ) const;

protected:
	//
	// REIMPLEMENTATIONS
	//
	void			deepCopyAndAppendDiscontinuous(DzVertexMap const* other);

#ifndef DSON_IO
	virtual void	writeData( DzOutFile *file ) const;
#endif

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzUVSet : public DzVertexMap, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
public:

	//
	// CREATORS/DESTRUCTORS
	//

	DzUVSet();
	virtual ~DzUVSet();

	//
	// REIMPLEMENTATIONS
	//

	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;
#ifndef DSON_IO
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );
#endif

protected:

#ifndef DSON_IO
	virtual void			writeData( DzOutFile *file ) const;
#endif

signals:
	void	assetModified();
	void	assetWasSaved();

};

#endif // DAZ_VERTEX_MAP_H
