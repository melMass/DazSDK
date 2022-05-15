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
	Defines the DzBoneBinding class.
**/

#ifndef DAZ_BONE_BINDING_H
#define DAZ_BONE_BINDING_H

/*****************************
	Include files
*****************************/

#include <QtCore/QHash>

#include "dzelement.h"
#include "dzmatrix3.h"
#include "dzweightmap.h"

/****************************
	Forward declarations
****************************/

class DzBulgeBinding;
class DzFigure;
class DzLocalAccumulator;
class DzVec3;
class DzVertexMesh;
class DzSkinBinding;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBoneBinding : public DzElement {
	Q_OBJECT
	friend class DzSkinBinding;
	Q_FLAGS( LocalAveragingOptions )
public:

	//
	// CREATORS
	//

	DzBoneBinding();
	virtual ~DzBoneBinding();

	enum LocalAveragingOption
	{
		FIRST_AXIS = 0x01,
		SECOND_AXIS = 0x02,
		THIRD_AXIS = 0x04,
		SCALE_MAP = 0x08,
		USE_GENERAL_MAP = 0x10,
		DEFAULT_AVERAGE = USE_GENERAL_MAP | SECOND_AXIS | THIRD_AXIS
	};
	Q_DECLARE_FLAGS( LocalAveragingOptions, LocalAveragingOption )

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;
	virtual void	setStorablePaths( const QString &path );

	void			calcScaledOrigin();
	DzVec3			calcScaledOrigin( QHash<DzNode*,DzVec3>* boneScaleMap, bool atDefault )const;

public slots:

	//
	// MANIPULATORS
	//

	DzError			setWeights( DzWeightMap *map );
	DzError			setScaleWeights( DzWeightMap *map );
	DzError			setLocalWeights( DzWeightMap *map, int axis );
	DzError			setBulgeBinding( DzBulgeBinding *bulge, int axis );

	void			setBone( DzBone *bone );
	void			setFigure( DzFigure *fig );
	void			setBindingMatrix( const DzMatrix3 &mat );
	void			invalidateWeights();
	void			setLocked( bool onOff );
	bool			isLocked()const;

public:

	//
	// ACCESSORS
	//

	void			getAllWeightMaps( DzWeightMapList &weightMaps ) const;
	DzWeightMapPtr	createAveragedGeneralMap( LocalAveragingOptions options = DEFAULT_AVERAGE );
	void			createManipulationModeMap( LocalAveragingOptions options = DEFAULT_AVERAGE );

	bool			appliedLocal() const;
	bool			appliedScale() const;

public slots:

	bool			hasLocalWeights() const;
	bool			hasBulgeWeights() const;
	DzNode*			getBone() const;
	DzMatrix3		getBindingMatrix() const;
	DzWeightMap*	getWeights() const;
	DzWeightMap*	getScaleWeights() const;
	DzWeightMap*	getLocalWeights( int axis ) const;
	DzBulgeBinding*	getBulgeBinding( int axis ) const;
	DzWeightMap*	getManipWeights()const;
	void			invalidateAccumulator();

	DzVec3			getScaledOrigin() const;

signals:

	void			boneChanged( DzNode *bone );
	void			weightsChanged();
	void			weightListChanged();
	void			bindingMatrixChanged();
	void			currentValueChanged();
	void			attributesChanged();
private slots:
	void			bulgeListChanged();
private:

	DzError			applyLocal( DzVertexMesh &geom, DzNode &node, DzSkinBinding *skin );
	DzError			applyLocalInverse( DzVertexMesh &geom, DzNode &node, DzSkinBinding *skin );
	
	DzLocalAccumulator	getAccumulator(DzVertexMesh &geom, DzSkinBinding *skin );
	void				buildAccumulator( DzVertexMesh &geom, DzSkinBinding *skin );
	void				accumulateChild( DzLocalAccumulator &childAccum );
	void				accumulateSelf( );

	void			setAppliedLocal( bool yesNo );
	void			setAppliedScale( bool yesNo );
		
	DzError			applyOffsetInverse( DzVertexMesh &geom, DzNode &node, DzLocalAccumulator &accum );

	struct	Data;
	Data	*m_data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( DzBoneBinding::LocalAveragingOptions )

#endif // DAZ_BONE_BINDING_H
