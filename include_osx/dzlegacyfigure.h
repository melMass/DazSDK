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
	Defines the DzLegacyFigure class.
**/

#ifndef DAZ_LEGACY_FIGURE_H
#define DAZ_LEGACY_FIGURE_H

/*****************************
	Include files
*****************************/

#include "dzskeleton.h"

/****************************
	Forward declarations
****************************/

class DzFaceGroup;
class DzFacetMesh;
class DzLegacyAlternateGeometry;
class DzPoserFigureBC;
struct DzBoneVertexMap;
struct DzGraftingPnt;

typedef QList<DzLegacyAlternateGeometry*> DzLegacyAlternateGeometryList;
typedef QListIterator<DzLegacyAlternateGeometry*> DzLegacyAlternateGeometryIterator;

/*****************************
	Class definitions
*****************************/
struct DZ_EXPORT DzLegacyBoneVertex
{
	int		m_figureVert;
	quint8	m_skipOnApply;
};

class DZ_EXPORT DzLegacyFigure : public DzSkeleton {
	Q_OBJECT
	friend class DzLegacyFigureFactory;
	friend class DzSkeletonFactory;
public:
	//
	// CREATORS
	//

	DzLegacyFigure();
	virtual ~DzLegacyFigure();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	virtual void			update( bool isRender = false );
	virtual void			setStorablePaths( const QString &path );
	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;

	DzLegacyAlternateGeometryIterator alternateGeometryIterator()const;

	int							getVertexMapCount( const DzBone *bone ) const;
	const DzLegacyBoneVertex*	getVertexMap( const DzBone *bone, int *count = 0 ) const;
	
	bool static		legacyBoneSortFunction( const DzBone *bone1, const DzBone *bone2 );	

public slots:

	//
	// MANIPULATORS
	//

	void	addWeld( DzWeld *weld );
	void	removeWeld( DzWeld *weld );
	void	removeAllWelds();
	void	applyWelds();

	int							getNumAlternateGeometries() const;
	DzLegacyAlternateGeometry*	getAlternateGeometry( int index ) const;
	DzLegacyAlternateGeometry*	findAlternateGeometry( const DzBone *bone ) const;
	DzLegacyAlternateGeometry*	findAlternateGeometry( const QString &boneName ) const;
	DzLegacyAlternateGeometry*	addAlternateGeometry( DzBone *bone, bool createAlais = true );
	bool						removeAlternateGeometry( DzLegacyAlternateGeometry *alt );

#ifndef Q_MOC_RUN
	static
#endif
	DzLegacyFigure*		convertPropToFigure( DzNode *srcNode, const QString &rootBoneName, bool inheritSkeleton = true );

public:

	//
	// ACCESSORS
	//

	DzWeldListIterator	weldListIterator() const;

public slots:

	int		getNumWelds() const;
	DzWeld*	getWeld( int which ) const;
	virtual void setObject( DzObject *object );
	bool	boneUsedByWeld( DzBone *bone );
	DzWeld*	findWeldByTargetBone(DzBone* target)const;
	DzWeld*	findWeldByWeldBone(DzBone* weldBone)const;
	void	invalidateVertexMaps();
	void	clearVertexMaps();

signals:

	void	weldListChanged();

protected:

	DzLegacyFigure( const DzInFile *file );

	virtual void	makePureVirtual() { };
	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;

private slots:

	void	weldBoneRemoved();
	void	rebuildGrafts();
	void	clearGeometryInformation();

public:
	DzLegacyFigure( DzPoserFigureBC *helper, DzInFile *file ); //internal use only
	DzError	setBoneVertexMaps( const DzBoneList& bones, const QList< QVector<DzLegacyBoneVertex> >& vertexMaps ); //internal use only

private:
	void	addAlternateInternal( DzLegacyAlternateGeometry *geom, bool addAsChild );
	void	buildVertexMasks();
	void	validateVertexMap() const;
	void	checkBoneInMap( const DzBone *bone, DzBoneVertexMap &map ) const;
	void	assignAltWelds();
	virtual DzFollowHelper*	createFollowHelper();
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzLegacyAlternateGeometry : public DzElement {
	Q_OBJECT
	friend class DzLegacyFigure;
public:
	DzLegacyAlternateGeometry();
	DzLegacyAlternateGeometry(DzInFile* file);
	virtual ~DzLegacyAlternateGeometry();

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;
	virtual void		setStorablePaths( const QString &path );
	virtual void		postLoadFile( const DzInFile *file );

	
	void				setOffset(int offset);
	int					getOffset() const;
	int					getTargetOffset() const;

public slots:
	DzBone*	getBone()const;
		
	DzLegacyFigure*	getFigure()const;
	DzObject*		getObject()const;

	virtual int						getNumGraftingPnts()const;
	virtual const DzGraftingPnt*	getGraftingPntsPtr()const;

	virtual int			getNumHiddenFacetsIndexes() const;
	virtual const int*	getHiddenFacetsIndexesPtr() const;

	void	copyJointFromBone();
	void	invalidateGeomInformation();
	
private:
	void			setFigure( DzLegacyFigure* figure );
	void			setBone( DzBone* bone );
	void			setObjectInternal( DzObject* object, bool onOff );
	DzFaceGroup*	findGroup()const;
	void			buildWelds();
	void			generateWeldMap( DzFacetMesh *weldGeom, DzFacetMesh *tgtGeom, DzFaceGroup* tgtGroup );

private slots:
	void	clearOldGeom();
	void	invalidateObject();

signals:
	void	drawnDataChanged();

private:
	void	setTarget(DzLegacyAlternateGeometry* geom);

	struct Data;
	Data *m_data;
};

#endif // DAZ_LEGACY_FIGURE_H
