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
	Defines the DzFacetMesh class.
**/

#ifndef DAZ_FACET_MESH_H
#define DAZ_FACET_MESH_H

/*****************************
	Include files
*****************************/
#include <QtCore/QPair>
#include "dzface.h"
#include "dztsimplearray.h"
#include "dztypes.h"
#include "dzvertexmesh.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzFaceGroup;
class DzFaceGroupList;
class DzMaterialFaceGroup;
class DzMaterialFaceGroupList;
class DzFacetMeshBC;
class DzFacetSet;
class DzSubDMap;

/*****************************
	Class definitions
*****************************/

class DzFacetMesh;
typedef DzTSharedPointer<DzFacetMesh> DzFacetMeshPtr;

class DZ_EXPORT DzFacetMesh : public DzVertexMesh, public DzSceneAsset {
	Q_OBJECT
	Q_ENUMS( SubDEdgeInterpolation )
	Q_INTERFACES( IDzSceneAsset )
	friend class DzFacetMeshBC;
public:
	enum SubDEdgeInterpolation { SoftCornersEdges = 0, SharpCornersEdges, SharpEdges };

	DzFacetMesh();
	virtual ~DzFacetMesh();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzBox3			getGroupBoundingBox( const QString &groupName ) const;
	virtual DzBox3			getGroupBoundingBox( DzFaceGroup *grp ) const;
	virtual DzOrientedBox3	getGroupOrientedBox( const QString &groupName, const DzVec3 &pos, const DzQuat &rot,
								const DzVec3 &scale ) const;
	virtual DzBox3			getGroupBoundingBox( const QString &groupName, const DzMatrix3 &transform ) const;
	virtual DzOrientedBox3	getGroupOrientedBox( const QString &groupName, const DzMatrix3 &transform,
								const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale ) const;
	virtual DzBox3			getSelectedFacetBoundingBox() const;
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;
#ifndef DSON_IO
	virtual void			startLoad( const DzInFile *file );
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );
	virtual DzError			finishLoad( const DzInFile *file );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			writeData( DzOutFile *file ) const;
#endif
	virtual void			setStorablePaths( const QString &path );
	virtual DzVertexMesh*	makeCopy( bool shareVerts = false, bool shareFacets = true ) const;
	virtual bool			copyFrom( DzVertexMesh *mesh, bool shareVerts = false, bool shareFacets = true );
	virtual void			beginEdit( bool enableUndo = true );
	virtual void			finishEdit();
	virtual void			cancelEdit();
	virtual bool			hasMultipleLOD() const;
	virtual int				getNumLODs() const;
	virtual QString			getLODName( int index ) const;
	virtual DzMap*			getUVs() const;
	virtual int				getNumUVSets() const;
	virtual DzUVSet*		getUVSet( int index ) const;

	QList< QPair<QString,QString> > getWeldedGroups()const;
	void					clearWeldedGroups();
	void					setWeldedGroups(const QList< QPair<QString,QString> >& welds);

	void					setLegacyGroups(const QStringList& groups);
	QStringList				getLegacyGroups()const;
	void					clearLegacyGroups();

	void					setLegacyFullAltGroup(const QString& groups);
	QString					getLegacyFullAltGroup()const;
	
#ifndef DSON_IO
	DzFacetMeshPtr			buildWorkingMeshForShape( DzShape* shape, int activeFacetSet );
#endif

	static const QString	c_defaultFaceGroupName;

public slots:

	//
	// MANIPULATORS
	//

	void	setNumFacets( int nFacets );
	DzError	preSizeFacets( int nFacets );
	void	removeFacet( int faceIdx );
	void	removeFacets( DzFaceGroup *faces, bool removeVerts = true );
	void	removeAllFacets();
	void	removeAllFacets(bool removeMats,bool removeGroups);
	void	addFacet( const int vertIdx[4], const int uvwIdx[4], unsigned char flags = 0 );
	void	addFacet( QVariantList vertIdx, QVariantList uvwIdx, unsigned char flags = 0 );

	void	selectFacets( DzFaceGroup *grp );
	void	deselectFacets( DzFaceGroup *grp );
	void	hideFacets( DzFaceGroup *grp );
	void	showFacets( DzFaceGroup *grp );
	void	invertFacetSelection();
	void	selectAllFacets();
	void	deselectAllFacets();
	void	growFacetSelection();
	void	shrinkFacetSelection();
	void	selectConnectedFacets();
	void	hideSelectedFacets();
	void	invertHiddenFacets();
	void	hideAllFacets();
	void	showAllFacets();
	void	lockSelectedFacets();
	void	invertLockedFacets();
	void	lockAllFacets();
	void	unlockAllFacets();

	int		activateMaterial( const QString &name );
	void	activateMaterial( int index );
	int		createMaterialGroup( const QString &name );
	void	addSelectedFacetsToMaterialGroup( int index );

	int		activateFaceGroup( const QString &name );
	void	activateFaceGroup( int index );
	bool	createFaceGroup( const QString &name );
	void	addSelectedFacetsToGroup( const QString &groupName );

	DzError	removeFacetGroup( const QString &name, const QString &defaultGrp = QString::null );
	DzError	removeMaterialGroup( int removeIdx, int defaultGrp );

	void	applyUVSet( DzUVSet *uvSet );
	void	setUVList( DzMap *map );
	void	addUVSet( DzUVSet *uvSet );
	void	insertUVSet( int idx, DzUVSet *uvSet );
	void	removeUVSet( DzUVSet *uvSet );
	void	removeUVSet( int index );
	void	removeAllUVSets();

	void	setSubDEdgeInterpolation( SubDEdgeInterpolation interp );
	void	subdivideCatmullClark( int level, DzSubDMap *map = NULL );

	void	enableSubDivision( bool onOff );

	int		createFacetSet( const QString &name );
	void	setActiveFacetSet( int index );
	bool	setActiveFacetSet( const QString &name );
	void	setActiveSetToBase();

	void	renameFacetSet( int index, const QString &name );
	bool	removeFacetSet( int index );
	void	moveFacetSet( int from, int to );

	//
	// ACCESSORS
	//

	int		getNumFacets() const;
	DzFacet	getFacet( int index ) const;

	int		getNumNormals() const;
	DzVec3	getNormal( int index ) const;

	int		getNumEdges() const;
	DzEdge	getEdge( int index ) const;

	int				getNumFaceGroups() const;
	DzFaceGroup*	getFaceGroup( int index ) const;
	DzFaceGroup*	findFaceGroup( const QString &name, int *index = NULL ) const;

	int				getNumMaterialGroups() const;
	DzMaterialFaceGroup*	getMaterialGroup( int index ) const;
	DzMaterialFaceGroup*	findMaterialGroup( const QString &name, int *index = NULL ) const;

	int		getNumFacetSets() const;
	QString	getFacetSetName( int index ) const;
	int		findFacetSet( const QString &name ) const;
	int		getActiveFacetSet() const;
	QString	getActiveFacetSetName() const;
	int		getBaseFacetSet() const;

	bool	isBaseActive() const;
		
	int		findUVSetIndexByLabel( const QString &label ) const;

	bool	isSubDivisionEnabled() const;
	int		getCurrentSubDivisionLevel() const;

	SubDEdgeInterpolation	getSubDEdgeInterpolation() const;

	void	updateVertexFlags();
	void	invalidateVBOs( bool clearVBOs = false );
	void	invalidateVBOs( bool vertexes, bool normals, bool uvs );
	void	invalidateFacetGroups();
	void	applySmoothing( float angle );

	DzError	weldGroups( DzFaceGroup* tgtGrp, DzFaceGroup* weldGrp, QVector<int>& weldMap );
	DzError	weldGroupsByMap( DzFaceGroup* tgtGrp, DzFaceGroup* weldGrp, const QVector<int>& weldMap );

	DzFacetMesh*	triangulate() const;
	DzFacetMeshPtr	removeUnusedVertice() const;
	DzFacetMeshPtr	removeHiddenFacets() const;

	virtual bool	modifyAsset();
	virtual bool	modifyAsset( const DzUri &newUri );

public:
	virtual void	applyUVSets( DzUVSetListIterator uvSetIt );

	virtual DzFacet*		getFacetsPtr() const;
	virtual unsigned char*	getFacetFlagsPtr() const;
	virtual DzPnt3*		getNormalsPtr() const;
	virtual DzEdge*		getEdgesPtr() const;

	void			getBoundaryVertices( DzTSortedArray<int> &verts ) const;
	DzFacetMesh*	createCopyForFacetSet( int facetSetIndex, bool shareFacetList = false, bool shareVertList = false ) const;
	void			applySmoothing( const DzTArray<float> &angles );
	void			applySmoothing( const QVector<float> &angles );
	DzFacetMesh*	createMeshFromGroup( DzFaceGroup *group,
						DzTSimpleArray<int> *materialMap = NULL ) const;
	DzFacetMesh*	createMeshFromGroups( const QList<DzFaceGroup*> &groups,
						DzTSimpleArray<int> *materialMap = NULL ) const;
	DzFacetMesh*	createAlternateUVMesh( DzUVSet *uvSet ) const;
	DzFacetMesh*	createAlternateUVMesh( DzUVSetListIterator uvSetIt ) const;

	void			getVerticesForGroup( DzFaceGroup *group, DzTSortedArray<int> &verts ) const;
	void			getBoundaryVerticesForGroup( DzFaceGroup *group, DzTSortedArray<int> &verts ) const;
	void			getAllEdgesForGroup( DzFaceGroup *group, DzTSortedArray<int> &edges ) const;
	void			getEdgesForGroup( DzFaceGroup *group, DzTSortedArray<int> &edges ) const;
	DzFacetSet*		getFacetSet(int i)const;
	DzFacetSet*		getSubDFacetCacheSet(int i)const;
	int				getNumSubDFacetCache()const;
	bool			copyFacetSetGroups( DzFacetSet *src, DzFacetSet *tgt );
	void			resetEdges();
	void			deactivateFaceGroup();
	void			deactivateMaterialGroup();
	QString			calcGeometryStorableName(bool forAssetPath=false) const;

signals:

	void	uvListChanged();
	void	subDivisionEnabled( bool onOff );
	void	assetModified();
	void	assetWasSaved();

protected:

	DzFacetMesh( const DzFacetMesh &mesh, bool shareVertList = true, bool shareFacetList = true );
	DzFacetMesh( const DzFacetMesh &mesh, int activeListIdx, bool shareVertList = true, bool shareFacetList= true );

	void	generateDefaultUVs(DzFacetSet *set);
	void	generateDefaultUVMap( DzFacetSet *set);
	void	setBaseFacetSet( DzFacetSet *set );
	void	finishGeometryChange();
	void	finishGeometryLoad();
	void	appendFacet(const DzFacet& facet);

private:

	void	updateNormals();
	void	removeFacetFromLists( int faceIdx );
	void	setNeedFullVBOUpdate();
	int		getMaxNormalIndex();
	void	subdivideCatmullClark( DzSubDMap *map, bool addVerts );
#ifndef DSON_IO
	void	writeAllFacetSetData( DzOutFile *file) const;
	void	writeFacetSetData( DzFacetSet *facetSet, DzOutFile *file ) const;
	void	loadFacetSetSection( DzInFile *file );
#endif
	void	weldGroupByMap( DzFaceGroup* weldGrp, const int* vertMap );

private slots:
	void	cleanupMeshCache();

public:
#ifndef DSON_IO
	DzFacetMesh(DzFacetMeshBC* helper, DzInFile* file ); //internal use only
#endif
	void setBCUVs( DzMap* oldUVMap ); //internal use only

private:
	QString calcFaceGroupStr( DzFaceGroupList* faceGroups ) const;
	QString calcFaceGroupStr( DzMaterialFaceGroupList* faceGroups ) const;
	struct	Data;
	Data	*m_data;
};



#endif // DAZ_FACET_MESH_H
