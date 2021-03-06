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
	Defines the DzFacetMeshBC, DzPolyMeshBC, DzSubDMeshBC and DzMRMMeshBC classes.
**/

#ifndef DAZ_FACET_MESH_BC_H
#define DAZ_FACET_MESH_BC_H

/*****************************
	Include files
*****************************/

#include "dzfacetmesh.h"

/*****************************
	Class definitions
*****************************/

struct DzLegacyPolygonInfo;

class DZ_EXPORT DzFacetMeshBC : public QObject {
	Q_OBJECT
	friend class DzFacetMesh;
public:
	DzFacetMeshBC();
	virtual ~DzFacetMeshBC();

	virtual bool	loadSection( DzInFile *file, short sectionID );
	virtual bool	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	finishLoad( const DzInFile *file );

	void			appendFacet(const DzFacet& facet);
	void			setVersion( DzVersion version );
	DzVersion		getVersion()const;
	
	struct	BaseData;
protected:
	DzFacetMesh* getFacetMesh() const;

	DzFacetMeshBC(BaseData* data);
	BaseData *m_baseData;

private:
	void setFacetMesh( DzFacetMesh *facetMesh );
};

class DZ_EXPORT DzPolyMeshBC : public DzFacetMeshBC {
	Q_OBJECT
public:
	DzPolyMeshBC();
	virtual ~DzPolyMeshBC();

	virtual bool	loadSection( DzInFile *file, short sectionID );
	virtual bool	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	finishLoad( const DzInFile *file );

protected:
	DzPolyMeshBC(DzFacetMeshBC::BaseData* data);

private:
	void	loadFacetSet( DzInFile *file );
	void	loadTriangles( DzInFile *file );
	void	loadQuads( DzInFile *file );
	void	loadPolys( DzInFile *file );
	void	loadTQPGroups( DzInFile *file );
	void	loadFacetGroups( DzInFile *file);
	void	loadBetaFaceSection( DzInFile *file );
	void	loadBetaFaceGroupSection( DzInFile *file );
	void	loadTrianglesBC( DzInFile *file );
	void	loadQuadsBC( DzInFile *file );
	void	loadPolysBC( DzInFile *file );
	void	loadFacets( DzInFile *file);
	void	fixNGonUVIndexes( const QList<DzLegacyPolygonInfo> &list, DzFacetSet* set );

protected:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzSubDMeshBC : public DzFacetMeshBC {
	Q_OBJECT
public:
	virtual bool	loadSection( DzInFile *file, short sectionID );
};

class DZ_EXPORT DzMRMMeshBC : public DzPolyMeshBC {
	Q_OBJECT
public:
	DzMRMMeshBC();
	virtual ~DzMRMMeshBC();

	virtual bool	loadSection( DzInFile *file, short sectionID );
	virtual bool	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	finishLoad( const DzInFile *file );

protected:
	struct	MRMData;
	MRMData	*m_dataMRM;
};

#endif // DAZ_FACET_MESH_BC_H