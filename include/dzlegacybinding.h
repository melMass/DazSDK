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
	Defines the DzLegacyBinding class.
**/

#ifndef DAZ_LEGACY_BINDING_H
#define DAZ_LEGACY_BINDING_H

/*****************************
	Include files
*****************************/

#include "dzmodifier.h"
#include "dzweightmap.h"
#include "idzsceneasset.h"
#include "dzvec3.h"
#include "dzquat.h"
#include "dzmatrix3.h"

/****************************
	Forward declarations
****************************/

class DzLegacyFigure;
class DzLegacyAlternateGeometry;
class IDzLegacyBindingTransformSource;
struct DzLegacyBoneVertex;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLegacyBinding : public DzModifier, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	friend class DzLegacyBindingFactory;
public:

	//
	// CREATORS
	//

	DzLegacyBinding();
	virtual ~DzLegacyBinding();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;
	virtual void	setStorablePaths( const QString &path );
	virtual DzError	apply( DzVertexMesh &geom, DzNode &node );	
	virtual DzError	apply( DzVertexMesh &geom, DzNode &node, IDzLegacyBindingTransformSource* transform );
	virtual DzError	applyInverse( DzVertexMesh &geom, DzNode &node );

	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;
	
	//
	// MANIPULATORS
	//
	DzError			applyScale( DzVertexMesh &geom, DzNode &node, IDzLegacyBindingTransformSource* transform=NULL );
public slots:

	DzError	addJoint( DzLegacyJoint *joint );
	DzError	removeJoint( int index );
	DzError	removeJoint( DzLegacyJoint *joint );
	void	removeAllJoints();

public:

	//
	// ACCESSORS
	//
	void buildGeneralWeightMaps( DzLegacyFigure *figure, QMap<DzBone*,DzWeightMapPtr> &bonemaps ) const;

	DzLegacyJointListIterator	getJointIterator() const;

public slots:

	int				getNumJoints() const;
	DzLegacyJoint*	getJoint( int index ) const;
	DzLegacyJoint*	findJoint( const DzNode *node ) const;
	DzLegacyJoint*	findJoint( const QString &boneName ) const;

	
	virtual bool		modifyAsset();
	virtual bool		modifyAsset( const DzUri &newUri );

	static DzLegacyBinding*	findBinding( const DzNode *node, int *index = NULL );
	static DzLegacyBinding*	findBinding( const DzLegacyAlternateGeometry *altGeom, int *index = NULL );

signals:

	void	jointAdded( DzLegacyJoint *joint );
	void	jointRemoved( DzLegacyJoint *joint );
	void	jointListChanged();
	void	assetModified();
	void	assetWasSaved();

protected:

	DzLegacyBinding( DzInFile *file );

private:
	bool	fullyBindToMap( const DzLegacyBoneVertex *vertMap, int vertCount, DzWeightMap* weightMap ) const;
	void	collectDrivenBendParamsForBone( const DzBone *bone, DzLegacyJointParamList &list ) const;
	void	copyParamWeightstoMap( DzWeightMap *map, const DzLegacyJointParamList &paramList, DzLegacyFigure *figure ) const;
	void	sortJoints();
	
	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT IDzLegacyBindingTransformSource
{
public:
	virtual ~IDzLegacyBindingTransformSource();
	
	virtual DzMatrix3 getWSTransform(DzNode* node)const=0;
	virtual DzQuat	  getWSRot(DzNode* node)const=0;

	virtual DzMatrix3 getLocalScale(DzNode* node)const=0;
	virtual DzQuat	  getLocalRot(DzNode* node)const=0;

	virtual float	  getXRot(DzNode* node)const=0;
	virtual float	  getYRot(DzNode* node)const=0;
	virtual float	  getZRot(DzNode* node)const=0;

	virtual float	  getXScale(DzNode* node)const=0;
	virtual float	  getYScale(DzNode* node)const=0;
	virtual float	  getZScale(DzNode* node)const=0;
	virtual float	  getGeneralScale(DzNode* node)const=0;

	virtual DzVec3	  getOrigin(DzNode* node)const=0;
	virtual DzVec3	  getEndPnt(DzNode* node)const=0;
};

#endif // DAZ_LEGACY_BINDING_H
