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
	Defines the DzFacetShape class.
**/

#ifndef DAZ_FACET_SHAPE_H
#define DAZ_FACET_SHAPE_H

/*****************************
	Include files
*****************************/

#include "dzshape.h"
#include "dztarray.h"

/****************************
	Forward declarations
****************************/

class DzFaceGroup;
class DzFacetMesh;
class DzFacetShapeBC;
class DzIntProperty;
class DzObject;
class DzSceneShader;
class DzSelectionMap;
class DzSubDPointsPolysBuffer;
class DzRenderMotionBlurSample;

typedef QList<DzRenderMotionBlurSample> DzRenderMotionBlurSampleList;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFacetShape : public DzShape {
	Q_OBJECT
	friend class DzFacetShapeFactory;
public:
	//
	// CREATORS
	//

	DzFacetShape();
	virtual ~DzFacetShape();

	//
	// REIMPLEMENTATIONS
	//
	virtual void			startLoad( const DzInFile *file );
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID,
								DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setStorablePaths( const QString &path );
	virtual void			save( DzOutFile *file ) const;
	virtual DzVertexMesh*	getModifiableGeom( bool isRender, DzVertexMesh *currentCache = NULL ) const;
	virtual void			draw( const DzDrawStyle &style, const DzGeometry *wsGeom,
								const DzNode *node ) const;
	virtual void			render( const DzRenderSettings &settings, const DzGeometry *wsGeom,
								const DzNode *node ) const;


	virtual void	invalidateWorkingMesh();

	//
	// MANIPULATORS
	//

	void	cacheBumpMapData();
	void	freeBumpMapCache();

	static bool	doTriUndoWarning();
	static void	triangulateMesh( DzNode *node );

	struct	Data;
public slots:

	virtual void setFacetMesh( DzFacetMesh *geom );
	void	rebuildBaseMap( int whichUVSet );

	//
	// ACCESSORS
	//

	virtual DzGeometry*		getGeometry() const;
	DzFacetMesh*			getFacetMesh() const;
	virtual DzFacetShape*	createShapeFromGroup( const QString &groupName ) const;

	DzEnumProperty*	getLODControl()const;
	DzEnumProperty*	getSubDInterpolateLevelControl()const;
	DzIntProperty*	getSubDLevelControl()const;
	virtual bool	hasMultipleLOD() const;
	virtual bool	hasDifferentRenderThanDraw() const;
	bool			isSubDivisionActive()const;
	bool			isLodActive() const;

	virtual void	prefixPropertyLabels( const QString &prefix );
	virtual void	hideProperties( bool onOff );
	virtual void	setFacetsForNodeVisibility( DzNode *node, DzFacetMesh *mesh, bool isRender );
	
public:
	DzFacetShape( DzFacetShapeBC *helper, DzInFile *file ); //internal use only

protected:
	DzFacetShape( DzInFile *file );

	virtual	void	finalize( DzNode &node, DzGeometry &wsGeom, bool isRender, bool allowResChange = true );

	virtual void	setVisiblityFlagsOnSubdividedMesh( DzFacetMesh * mesh );
	virtual void	updateSmoothing();
	virtual void	updateUVs();

	virtual DzVertexMesh*	getWorkingMesh() const;

protected slots:

	void	updateSubDEnabled();
	void	updateInterpLevel();
	void	updateLODs();
	void	updateLODControl();
	void	updateSubDControl();
	void	endManip();

protected:

	virtual void	updateWorkingMesh();

	virtual void	drawPickSelectionMap( const DzSelectionMap *map, const DzFacetMesh *cachedGeom ) const;
	virtual void	drawPickNodes( const DzNode *node, const DzFacetMesh *cachedGeom ) const;
	virtual void	drawPickMaterials( const DzFacetMesh *cachedGeom ) const;
	virtual void	drawPickFaces( const DzFacetMesh *cachedGeom ) const;
	virtual void	drawMaterialGroup( int which, const DzDrawStyle &style, const DzFacetMesh *cachedGeom ) const;
	virtual void	drawTextured( const DzMaterial *mat, const DzFaceGroup *group, const DzDrawStyle &style, const DzFacetMesh *cachedGeom ) const;
	virtual void	drawSceneShaded( const DzMaterial *mat, const DzFaceGroup *group, const DzDrawStyle &style, const DzFacetMesh *cachedGeom ) const;
	virtual void	drawSmoothShaded( const DzMaterial *mat, const DzFaceGroup *group, const DzDrawStyle &style, const DzFacetMesh *cachedGeom ) const;
	virtual void	drawWireFrame( const DzMaterial *mat, const DzFaceGroup *group, bool useMaterial, const DzFacetMesh *cachedGeom ) const;

	void	drawV( const DzFaceGroup *grp, const DzFacetMesh *cachedGeom ) const;
	void	drawRegionV( const DzFaceGroup *group, const DzFacetMesh *cachedGeom, int nodeIndex, const quint8 *regionMap ) const;
	void	drawNV( const DzFaceGroup *grp, const DzFacetMesh *cachedGeom ) const;
	void	drawNTV( const DzFaceGroup *grp, const DzFacetMesh *cachedGeom ) const;
	void	drawNTTV( const DzFaceGroup *grp, const DzFacetMesh *cachedGeom ) const;
	void	drawBNTTV( const DzFaceGroup *grp, DzSceneShader *shader, const DzFacetMesh *cachedGeom ) const;

private:
	void	createProperties();
	void	buildBumpVecCache();
	void	setUpAndDoSubDRender( bool needTrans, DzRenderSettings const &settings, DzTArray<DzMaterialPtr> &mats, 
				const QVector<DzSubDPointsPolysBuffer*>& buffers, QVector<float>& times, 
				const DzRenderMotionBlurSampleList& samples) const;

	void	setUpAndDoSubDRender( DzRenderSettings const &settings, DzTArray<DzMaterialPtr> &mats, 
				DzSubDPointsPolysBuffer &dppBuffer, const DzMatrix3& worldSpace,bool isNormalPass ) const;
	void	setupSubDMaterials( DzRenderSettings const &settings, DzMaterialPtrList &prioritizedMaterials, DzTArray<DzMaterialPtr> &mats, bool& needTrans ) const;

	void	setBakeMaterial( DzRenderSettings const &settings,bool isNormalPass,DzMaterialPtr &mat ) const;
	void	init();
	void	getMaterialMapsSubD(const DzFacetMesh *cachedGeom, DzTArray<int> &map, DzTArray<DzMaterialPtr> &mats, bool& hasCurves ) const;

	void	bake( const DzRenderSettings &settings, const DzGeometry *wsGeom, const DzNode *node ) const;
	void	textureConvert( const DzRenderSettings &settings, const DzGeometry *wsGeom, const DzNode *node ) const;	
	void	renderCurves( DzFacetMesh const* localMesh, const DzRenderSettings &settings, DzMatrix3 inWorldMatrix ) const;

	static void triangulateObject( DzObject *obj );
	//
	// DATA MEMBERS
	//

	friend struct	Data;
	Data	*m_data;
};

#endif // DAZ_FACET_SHAPE_H
