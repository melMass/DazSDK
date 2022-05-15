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
	Defines the DzShape class.
**/

#ifndef DAZ_SHAPE_H
#define DAZ_SHAPE_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"
#include "dzmaterial.h"

/****************************
	Forward declarations
****************************/

class DzGeometry;
class DzVertexMesh;
class DzWeightMap;
class DzAbstractShapeInstance;

typedef QList<DzAbstractShapeInstance*> DzAbstractShapeInstanceList;
typedef QListIterator<DzAbstractShapeInstance*> DzAbstractShapeInstanceListIterator;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzShape : public DzElement {
	Q_OBJECT
	friend class DzObject;
	friend class MaterialListUndoItem;
public:
	//
	// CREATORS
	//

	DzShape();
	virtual ~DzShape();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;
	virtual void	setStorablePaths( const QString &path );

	//
	// ACCESSORS
	//

	DzNode*	getNode();
	void	getAllMaterials( DzMaterialPtrList &matPtrs ) const;
	void	getAllSelectedMaterials( DzMaterialPtrList &matPtrs ) const;
	void			getAllRenderPrioritizedMaterials( DzMaterialPtrList &prioritizedMaterials ) const;
	virtual	void	getAllRenderAssemblyPrioritizedMaterials( DzMaterialPtrList &prioritizedMaterials ) const;
	void	getRenderPrioritizedMaterials( const DzMaterialPtrList &inputMaterials, DzMaterialPtrList &prioritizedMaterials ) const;

	virtual DzVertexMesh*	getModifiableGeom( bool isRender, DzVertexMesh *currentCache = NULL ) const = 0;

	virtual void	draw( const DzDrawStyle &style, const DzGeometry *wsGeom,
						const DzNode *node ) const = 0;
	virtual void	render( const DzRenderSettings &settings, const DzGeometry *wsGeom,
						const DzNode *node ) const = 0;
	int					getNumLeafRegions() const;
	DzGeometryRegion*	getLeafRegion( int index ) const;
	int					getNumFacetToRegionLeafValues() const;
	const quint8*		getFacetToLeafMap() const;
	static DzShape*		getCurrentShapeForNode( const DzNode *node );

	DzRigidityGroupList	getRigidityGroups()const;
	DzRigidityGroupListIterator rigidityGroupIterator()const;

	DzAbstractShapeInstanceList	getShapeInstance()const;
	DzAbstractShapeInstanceListIterator shapeInstancesIterator()const;

public slots:

	DzError			createMaterial( const QString &name );
	DzError			addMaterial( DzMaterial *mat );
	DzError			insertMaterial( DzMaterial *newmat, int index = -1 );
	DzError			removeMaterial( DzMaterial *mat );
	DzError			replaceMaterial( DzMaterial *current, DzMaterial *newMat );
	void			clearMaterialSelection();
	virtual DzError	removeMaterialByName( const QString &material, const QString &defaultMaterial = QString::null );

	QObjectList		getAllMaterials() const;
	int				getNumMaterials() const;
	virtual int		getNumAssemblyMaterials() const;
	DzMaterial*		getMaterial( int which ) const;
	virtual DzMaterial*	getAssemblyMaterial( int which ) const;
	DzMaterial*		findMaterial( const QString &name ) const;
	int				findMaterialIndex( const QString &name ) const;
	int				findMaterialIndex( const DzMaterial *mat ) const;
	virtual int		findAssemblyMaterialIndex( const DzMaterial *mat ) const;
	QObjectList		getAllSelectedMaterials() const;
	int				getNumSelectedMaterials() const;
	DzMaterial*		getSelectedMaterial( int which ) const;
	QObjectList		getAllRenderPrioritizedMaterials() const;
	virtual bool	hasMultipleLOD() const { return false; }
	virtual bool	hasDifferentRenderThanDraw() const { return false; }

	virtual DzGeometry*	getGeometry() const = 0;
	virtual bool		hasAssemblyGeometry()const;
	virtual DzGeometry* getAssemblyGeometry()const;
	virtual DzVertexMesh* getModifiableAssemblyGeom( bool isRender ) const;

	virtual void		rebuildBaseMap( int whichUVSet );

	DzGeometryRegion*	getGeometryRegion() const;
	void				moveGeometryRegion( DzShape *newShape );
	void				setGeometryRegion( DzGeometryRegion *region );

	void				setGeometryRegionSelection( DzGeometryRegion *sel );
	DzGeometryRegion*	getGeometryRegionSelection() const;
	void				setGeometryRegionLeafSelection( DzGeometryRegion *sel );
	DzGeometryRegion*	getGeometryRegionLeafSelection() const;	
	DzGeometryRegion*	findLeafRegion( const QString &regionName );

	int					getNumRigidityGroups()const;
	void				addRigidityGroup(DzRigidityGroup* group);
	void				removeRigidityGroup(DzRigidityGroup* group);
	DzRigidityGroup*	getRigidityGroup(int which)const;
	DzRigidityGroup*	findRigidityGroup( const QString& group ) const;

	int							getNumShapeInstances()const;
	void						addShapeInstance(DzAbstractShapeInstance* instance);
	bool						removeShapeInstance(DzAbstractShapeInstance* instance);
	DzAbstractShapeInstance*	getShapeInstance(int which)const;

	void				setRigidityMap(DzWeightMap* map);
	DzWeightMap*		getRigidityMap()const;
	void				modifyGeometryAsset();	

	virtual bool		mergesSnapGeometry() const;

	virtual void		invalidateWorkingMesh() = 0;

signals:

	void	materialAdded( DzMaterial *mat );
	void	materialRemoved( DzMaterial *mat );
	void	materialListChanged();
	void	materialSelected( DzMaterial *mat );
	void	materialUnselected( DzMaterial *mat );
	void	materialSelectionChanged();
	void	materialChanged();
	void	invalidateGeomCaches();
	void	geomChanged();
	void	assemblyChanged();
	void	geomTopologyChanged();
	void	uvsChanged();
	void	smoothingChanged();
	void	geometryRegionChanged();
	void	geometryRegionSelectionChanged();
	void	rigidityGroupListChanged();
	void	rigidityMapChanged();

protected slots:

	virtual void	updateUVs();
	virtual void	updateSmoothing(); 

protected:

	virtual	void	finalize( DzNode &node, DzGeometry &wsGeom, bool isRender, bool allowResChange = true ) { }
	virtual	void	finalize( DzNode &node, DzGeometry &wsGeom, DzGeometry &assemblyGeom, bool isRender, bool allowResChange = true ) { }

private slots:

	void	updateMaterialSelection( DzMaterial *mat, bool onOff );
	void	updateGeom();
	void	updateMaterials();
	void	updateRegionMap();
	
private:
	void	buildRegionMaps() const;
	void	buildRegionMapsRecurse( DzGeometryRegion *region ) const;
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SHAPE_H
