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
#ifndef DAZ_GRAFTING_FIGURE_SHAPE_H
#define DAZ_GRAFTING_FIGURE_SHAPE_H


/*****************************
	Include files
*****************************/
#ifndef DSON_IO
#include "dzfacetshape.h"
#else
#include "dztsharedpointer.h"
#endif

/*****************************
	Class definitions
*****************************/

struct DZ_EXPORT DzGraftingPnt
{
	int m_srcIndex;
	int m_tgtIndex;
};

class DzGraftObject;
typedef DzTSharedPointer<DzGraftObject> DzGraftObjectPtr;
typedef QList<DzGraftObjectPtr> DzGraftObjectList;
typedef QListIterator<DzGraftObjectPtr> DzGraftObjectIterator;

#ifndef DSON_IO

class DZ_EXPORT DzGraftingFigureShape : public DzFacetShape {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzGraftingFigureShape();
	virtual ~DzGraftingFigureShape();

	//
	// REIMLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;
	virtual void	finalize( DzNode &node, DzGeometry &wsGeom, bool isRender, bool allowResChange = true );
	virtual void	finalize( DzNode &node, DzGeometry &wsGeom, DzGeometry &assemblyGeom, bool isRender, bool allowResChange = true );
	virtual void	draw( const DzDrawStyle &style, const DzGeometry *wsGeom, const DzNode *node ) const;
	virtual void	render( const DzRenderSettings &settings, const DzGeometry *wsGeom, const DzNode *node ) const;
	virtual void	drawPickSelectionMap( const DzSelectionMap *map, const DzFacetMesh *wsGeom ) const;
	virtual void	drawPickSelectionMap( const DzSelectionMap *map, const DzFacetMesh *wsGeom, const QString &prefix, int foffset ) const;
	virtual void	setFacetsForNodeVisibility( DzNode *node, DzFacetMesh *mesh, bool isRender );
	virtual DzVertexMesh*	getModifiableGeom( bool isRender, DzVertexMesh *currentCache = NULL ) const;

	virtual bool			hasAssemblyGeometry() const;
	virtual DzGeometry*		getAssemblyGeometry() const;
	virtual DzVertexMesh*	getModifiableAssemblyGeom( bool isRender ) const;
	virtual	void			getAllRenderAssemblyPrioritizedMaterials( DzMaterialPtrList &prioritizedMaterials ) const;

	void	addGraft( const DzGraftObjectPtr &graft );
	bool	removeGraft( DzGraftObjectPtr &graft );
	void	removeGraft( DzNode *node );
	void	clearGrafts();

	const int*	getOrignalToWeldMeshMap() const;
	const int*	getWeldMeshToOrginalMap() const;

	int      getNumActiveGrafts() const;
	DzNode*  getActiveGraftNode(int graftIndex) const;
	int      getActiveGraftVertexOffset(int graftIndex) const;
public slots:

	//
	// ACCESSORS
	//

	virtual void	setFacetMesh( DzFacetMesh *mesh );

	void				updateBuilder();
	virtual DzMaterial*	getAssemblyMaterial( int which ) const;
	virtual int			getNumAssemblyMaterials() const;
	virtual int			findAssemblyMaterialIndex( const DzMaterial *mat ) const;
	bool				hasWeldedFollowers() const;
	
protected:

	virtual void	updateUVs();
	virtual void	setFacetsForNodeVisibility( DzNode *node, DzFacetMesh *mesh, bool isRender, const QString& prefix ) const;
	virtual void	setVisiblityFlagsOnSubdividedMesh( DzFacetMesh * mesh );

private slots:
	void	visChanged();

public:
	DzGraftingFigureShape( DzInFile *infile );
	DzGraftingFigureShape( DzFacetShapeBC *helper, DzInFile *file ); //internal use only

private:

	struct	Data;
	Data	*m_data;

	void	buildFigureBuilder();
	void	connectFigure( DzGraftObject *obj );
	void	disconnectFigure( DzGraftObject *obj );
	void	clearBuilder();
	void	drawBuilderRegionV( const DzFaceGroup *group, const DzFacetMesh *cachedGeom, int nodeIndex, const quint8 *regionMap,int offset ) const;
	void	drawStandardShapePick( const DzShape *shape, const DzSelectionMap *map, const DzFacetMesh  *wsGeom, const QString &prefix, int foffset ) const;
	void	drawOffsetRegionV( const DzFaceGroup *group, const DzFacetMesh *cachedGeom, int nodeIndex, const quint8 *regionMap, int foffset ) const;
	void	drawGraftBasePickSelectionMap( const DzSelectionMap *set, const DzFacetMesh *wsGeom, const QString &prefix, int foffset ) const;
	void	validateBuilder() const;
};
#endif //DSON_IO

#endif // DAZ_GRAFTING_FIGURE_SHAPE_H
