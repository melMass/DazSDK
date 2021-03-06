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
#pragma once

/*****************************
	Include files
*****************************/

#include "dzassetextraobjectio.h"
#include "dzfacetmesh.h"
#include "dzfacetshape.h"
#include "idzsceneasset.h"

/****************************
	Test Script
****************************/

/* Test by executing in the Script IDE 

var oNode = new DzNode();
oNode.name = "NurbNode";

var oObject = new DzObject();
oObject.name = "NurbObject";
oNode.setObject( oObject );

var oShape = new MyNurbShape();
oObject.addShape( oShape );

var oGeometry = oShape.getGeometry();
oGeometry.setupExample();

Scene.addNode( oNode );

*/

/****************************
	Forward declarations
****************************/

class DzVertexMesh;
class MyNurbGeometry;

/*****************************
	Class definitions
*****************************/

class MyNurbShape : public DzShape {
	Q_OBJECT
public:

	MyNurbShape( MyNurbGeometry* geom = 0 );
	~MyNurbShape();

	virtual DzGeometry*		getGeometry() const;
	virtual DzVertexMesh*	getModifiableGeom( bool isRender, DzVertexMesh* currentCache = NULL ) const;
	virtual void			draw( const DzDrawStyle &style, const DzGeometry* wsGeom, const DzNode* node ) const;
	virtual void			render( const DzRenderSettings &settings, const DzGeometry* wsGeom, const DzNode* node ) const;
	virtual void			invalidateWorkingMesh();

private:

	struct	Data; 
	Data	*m_data;
};


 class MyNurbGeometry : public DzVertexMesh, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	friend class MyNurbGeometryIO;
public:

	MyNurbGeometry();
	~MyNurbGeometry();

	// DzSceneAsset
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;

	virtual DzVertexMesh*	makeCopy( bool shareVerts = false, bool shareFacets = true ) const;
	virtual bool			copyFrom( DzVertexMesh* mesh, bool shareVerts = false, bool shareFacets = false );

	void					tesselate( DzFacetMesh* mesh );

public slots:

	void					setupExample();

	virtual DzBox3			getGroupBoundingBox( const QString &groupName ) const;
	virtual DzOrientedBox3	getGroupOrientedBox( const QString &groupName, const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale ) const;
	virtual DzBox3			getGroupBoundingBox( const QString &groupName, const DzMatrix3 &transform ) const;
	virtual DzOrientedBox3	getGroupOrientedBox( const QString &groupName, const DzMatrix3 &transform, const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale ) const;
	virtual bool			hasMultipleLOD() const;
	virtual int				getNumLODs() const;
	virtual QString			getLODName( int which ) const;

	virtual DzMap*			getUVs() const;
	virtual int				getNumUVSets() const;
	virtual DzUVSet*		getUVSet( int which ) const;

signals:

	void	assetModified();
	void	assetWasSaved();

private:
	struct Data;
	Data* m_data;
};


class MyNurbGeometryIO : public DzExtraGeometryIO {
	Q_OBJECT
public:

	MyNurbGeometryIO();
	~MyNurbGeometryIO();

	// DzExtraGeometryIO
	virtual DzGeometry*			createGeometry() const;
	virtual DzShape*			createShape( DzGeometry* geometry ) const;
	virtual DzError				writeExtraDefinition( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzError				writeExtraInstance( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem* parentItem );
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem* parentItem );
	virtual DzError				applyDefinitionToObject( QObject* object, const DzFileIOSettings* opts ) const;
	virtual DzError				applyInstanceToObject( QObject* object, const DzFileIOSettings* opts ) const;

	// for reading
	struct		Context;
	Context		*m_context;
};


 struct MyNurbGeometryIO::Context {
	Context( DzAssetFile &file ) :
		m_file( file ),
		m_dimensionU( 0 ),
		m_dimensionV( 0 )
	{}

	DzAssetFile    &m_file;
	int             m_dimensionU;
	int             m_dimensionV;
	QVector<DzVec3> m_points;
	QVector<float>  m_weights;
	QVector<float>  m_knotVectorUs;
	QVector<float>  m_knotVectorVs;
};


class ReadMyNurbGeometry : public DzAssetJsonObject {
public:

	ReadMyNurbGeometry( MyNurbGeometryIO::Context* context ) :
		DzAssetJsonObject( context->m_file ), m_context( context )
	{}

	virtual bool				addMember( const QString &name, double val );
	virtual DzAssetJsonItem*	startMemberArray( const QString &name );

	MyNurbGeometryIO::Context	*m_context;
};


class ReadMyNurbPoints : public DzAssetJsonArray {
public:

	ReadMyNurbPoints( MyNurbGeometryIO::Context* context ) :
		DzAssetJsonArray( context->m_file ), m_context( context )
	{}

	virtual DzAssetJsonItem*	startArray();

	MyNurbGeometryIO::Context	*m_context;
};


class ReadMyNurbPoint : public DzAssetJsonArray {
public:

	ReadMyNurbPoint( MyNurbGeometryIO::Context* context ) :
		DzAssetJsonArray( context->m_file ), m_context( context ), m_i( 0 )
	{}

	virtual bool				addItem( double val );

	MyNurbGeometryIO::Context	*m_context;
	int m_i;
};


class ReadMyNurbKnots : public DzAssetJsonArray {
public:
	ReadMyNurbKnots( MyNurbGeometryIO::Context* context )
		: DzAssetJsonArray( context->m_file ), m_context( context )
	{}

	virtual DzAssetJsonItem*	startArray();

	MyNurbGeometryIO::Context	*m_context;
};


class ReadMyNurbKnot : public DzAssetJsonArray {
public:
	ReadMyNurbKnot( MyNurbGeometryIO::Context* context )
		: DzAssetJsonArray( context->m_file ), m_context( context ), m_i( 0 )
	{}

	virtual bool				addItem( double val );

	MyNurbGeometryIO::Context	*m_context;
	int m_i;
};
