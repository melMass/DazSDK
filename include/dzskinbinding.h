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
	Defines the DzSkinBinding class.
**/

#ifndef DAZ_SKIN_BINDING_H
#define DAZ_SKIN_BINDING_H

/*****************************
	Include files
*****************************/

#include "dzbonebinding.h"
#include "dzmodifier.h"
#include "idzsceneasset.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT	DzLocalAccumulator {
public:
	DzLocalAccumulator();
	DzLocalAccumulator( const DzVertexMesh &geom );
	DzLocalAccumulator( const DzLocalAccumulator &accum );
	~DzLocalAccumulator();

	void	create( const DzVertexMesh &geom );

	DzError	accumulate( const DzLocalAccumulator &accum );
	DzError	accumulate( const DzBoneBinding *bind );
	DzError	accumulate( const DzWeightMap *xWeights, const DzWeightMap *yWeights, const DzWeightMap *zWeights );

	void	flush();

	DzLocalAccumulator&	operator=( const DzLocalAccumulator &accum );

	unsigned short*	getXWeights();
	unsigned short*	getYWeights();
	unsigned short*	getZWeights();

	bool					isValid() const;
	int						getNumVerts() const;
	const unsigned short*	getXWeights() const;
	const unsigned short*	getYWeights() const;
	const unsigned short*	getZWeights() const;

private:

	void	createInternal( const DzVertexMesh &geom );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzSkinBinding : public DzModifier, public DzSceneAsset {
	Q_OBJECT
	Q_ENUMS( PriorityType )
	Q_ENUMS( NormalizeType )
	Q_INTERFACES( IDzSceneAsset )
	friend class DzFigure;
	friend class DzSkinBindingFactory;
public:

	enum PriorityType { RootLowest = 0, RootHighest };
	enum NormalizeType { NormalizeNone = 0x00, NormalizeX = 0x01, NormalizeY = 0x02, NormalizeZ = 0x04, 
		NormalizeGeneral = 0x08, NormalizeScale = 0x10, NormalizeWeight = 0x0f, NormalizeAll = 0x1f };

	//
	// CREATORS
	//

	virtual ~DzSkinBinding();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			save( DzOutFile *file ) const;
	virtual void			setStorablePaths( const QString &path );
	virtual DzError			apply( DzVertexMesh &geom, DzNode &node );
	virtual DzError			applyInverse( DzVertexMesh &geom, DzNode &node );
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;
	virtual DzProperty *	findMatchingProperty(DzProperty *srcProp );

	//
	// Public helper
	//
	DzError				applyScale( DzVertexMesh &geom, DzNode &node );
	DzError				applyScale( DzVertexMesh &geom, DzNode &node, const DzBoneList& bones, 
									const QList<DzVec3>& scales, QVector<DzVec3>& scaledOrigins, bool atdefault = true );

	//
	// MANIPULATORS
	//

public slots:

	DzError	addBoneBinding( DzBoneBinding *binding );
	DzError	removeBoneBinding( int index );
	DzError	removeBoneBinding( DzBoneBinding *binding );
	void	removeAllBindings();

	DzError	normalize( PriorityType priority = RootLowest, NormalizeType which = NormalizeAll, bool respectLocking = false );
	DzError	normalize( DzNode *priority, NormalizeType which = NormalizeAll, bool respectLocking = false );
	DzError	normalize( DzBoneBinding *priority, NormalizeType which = NormalizeAll, bool respectLocking = false );
	DzError	normalize( DzBoneBinding *priority, DzBoneBinding *symmetry, NormalizeType which = NormalizeAll, bool respectLocking = false );
	
	DzError	convertToGeneralMaps( DzBoneBinding::LocalAveragingOption options = DzBoneBinding::DEFAULT_AVERAGE );
	DzError convertFromGeneralToLocal( );
	DzError buildGeneralWeightMaps( DzWeightMapList &normList, DzBoneBindingList &bindings, 
								DzBoneBinding::LocalAveragingOption options = DzBoneBinding::DEFAULT_AVERAGE);
public:

	//
	// ACCESSORS
	//

	DzBoneBindingListIterator	getBoneBindingIterator() const;
	bool						isLocal();
	bool						isGeneral();
	

public slots:

	int					getNumBoneBindings() const;
	DzBoneBinding*		getBoneBinding( int index ) const;
	DzBoneBinding*		findBoneBinding( DzNode *node ) const;
	DzBoneBinding*		findBoneBinding( const QString &boneName ) const;
	void				invalidate();
	void				invalidateAccumulation();

#ifndef Q_MOC_RUN
	static
#endif
	DzSkinBinding*		findSkin( const DzSkeleton *figure, int *index = NULL );
#ifndef Q_MOC_RUN
	static
#endif
	DzSkinBinding*		findSkinFromNode( DzNode *node );
#ifndef Q_MOC_RUN
	static
#endif
	bool				isSingleSkinFigure( DzNode *node );
	virtual bool		modifyAsset();
	virtual bool		modifyAsset( const DzUri &newUri );

protected:

	DzSkinBinding( DzFigure *owner );
	DzSkinBinding( DzInFile *file );

signals:

	void	boneBindingAdded( DzBoneBinding *binding );
	void	boneBindingRemoved( DzBoneBinding *binding );
	void	boneBindingListChanged();
	void	weightsChanged();
	void	weightListChanged();
	void	assetModified();
	void	assetWasSaved();
	void	normalized();

private slots:

	void	manipulationStarted();
	void	manipulationFinished();
	void	manipulationChanged();

private:

	DzError				applyLocal( DzVertexMesh &geom, DzNode &node );
	DzError				applyGeneral( DzVertexMesh &geom, DzNode &node );
	DzError				applyManipulationMode(DzVertexMesh &geom, DzNode &node);
	DzError				applyScaleInverse( DzVertexMesh &geom, DzNode &node );
	DzError				applyLocalInverse( DzVertexMesh &geom, DzNode &node );
	DzError				applyGeneralInverse( DzVertexMesh &geom, DzNode &node );
	void				initResult( const DzVertexMesh &geom, DzTSimpleArray<DzPnt3> &result );
	void				applyResult( DzVertexMesh &geom, const DzTSimpleArray<DzPnt3> &result );
	void				sortBindings();
	DzError				priorityNormalizeMaps( DzWeightMapPtr priority, DzWeightMapList &weights,bool respectLocking = false );
	
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SKIN_BINDING_H
