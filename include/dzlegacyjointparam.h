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
	Defines the DzLegacyJointParam class.
**/

#ifndef DAZ_LEGACY_JOINT_PARAM_H
#define DAZ_LEGACY_JOINT_PARAM_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"
#include "dzmatrix4.h"

/****************************
	Forward declarations
****************************/

class DzGeometry;
class DzLegacyJointSphere;
class DzVertexMesh;
class DzWeightMap;
struct DzLegacyBoneVertex;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLegacyJointParam : public DzElement {
	Q_OBJECT
	Q_PROPERTY( ParamType type READ type )
	Q_PROPERTY( ParamAxis axis READ getAxis WRITE setAxis )
	Q_PROPERTY( bool flipped READ isFlipped WRITE setFlipped )
	Q_PROPERTY( bool applyMatrices READ applyMatrices WRITE setApplyMatrices )
	Q_PROPERTY( DzMatrix4 dynamicMatrix READ getDynamicMatrix WRITE setDynamicMatrix )
	Q_PROPERTY( DzMatrix4 staticMatrix READ getStaticMatrix WRITE setStaticMatrix )
	Q_ENUMS( ParamType ParamAxis )
	friend class DzLegacyJointRotator;
	friend class DzLegacyJointScalor;
public:
	enum ParamType { Rotation, Scale };
	enum ParamAxis { X = 0, Y = 1, Z = 2, XY = 3, XZ = 4, YZ = 5 };

	DzLegacyJointParam();
	DzLegacyJointParam( DzBone *driver, ParamAxis axis );
	virtual ~DzLegacyJointParam();

	//////////////////////////////
	// from DzBase

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		postLoadFile( const DzInFile *file );
	virtual void		save( DzOutFile *file ) const;
	virtual void		setStorablePaths( const QString &path );

	virtual ParamType	type() const = 0;	
	virtual DzLegacyJointParam* deepCopy() const=0;

	void				getMatrices( DzMatrix4 &dynamicMat, DzMatrix4 &staticMat ) const;

	void				setApplyMatrices( bool onOff );
	bool				applyMatrices() const;

	void				setAxis( ParamAxis axis );
	ParamAxis			getAxis() const;

	void				setDynamicMatrix( const DzMatrix4 &mat, bool makeDefault = false );
	void				setStaticMatrix( const DzMatrix4 &mat, bool makeDefault = false );
	DzMatrix4			getDynamicMatrix() const;
	DzMatrix4			getStaticMatrix() const;
	DzLegacyJointSphere*	getDynamicSphere() const;
	DzLegacyJointSphere*	getStaticSphere() const;
	bool				hasSpheres()const;
	void				setFlipped( bool onOff );
	bool				isFlipped() const;
	void				invalidateWeights();

public slots:
	DzError				setLabel( const QString &name );
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();

	void				setDriver( DzBone *driver );
	void				setMatrices( const DzMatrix4 &dynamicMat, const DzMatrix4 &staticMat, bool makeDefault = false );

	DzBone*				getDriver() const;
	const DzWeightMap*	getWeights( DzNode &node ) const;
	const DzWeightMap*	getWeights( DzBone* bone, DzNode &node, DzVertexMesh &preWeightGeom, const DzLegacyBoneVertex* vertMask, int maskCount ) const;
	virtual	void		getRiggingProperties( DzPropertyList &list, bool includeSpheres = false );
	void				addWeightMap( DzWeightMap *map );
	int					getNumWeightMaps();
	DzWeightMap*		getWeightMap( int i );
	void				removeWeightMap( int i );

	void				setOverrideWeightMap( DzWeightMap *map );
	DzWeightMap*		getOverrideWeightMap() const;

	DzLegacyJoint*		getJoint() const;

signals:
	void				bindingChanged();
	void				removed( DzLegacyJointParam *param );
	
protected:
	DzLegacyJointParam( const DzInFile *file );

	void			createSpheres();
	virtual void	updateWeights( DzBone* bone, DzWeightMap &map, const DzNode &node, const DzGeometry &geom, const DzLegacyBoneVertex* vertMask, int maskCount ) = 0;
	float			getMatSphereWeight( const DzVec3 &pos ) const;
	void			copyGeneralValues( DzLegacyJointParam* tgt )const;

	DzBone		*m_driver;
	bool		m_applyMats;
	ParamAxis	m_axis;

protected slots:

	void	needUpdate();
	void	updateMaps();
	void	driverRemoved();

private:
	void	validateWeights( DzBone* bone, DzNode &node, DzVertexMesh &preWeightGeom, const DzLegacyBoneVertex* vertMask, int maskCount );
	void	createDefaultWeightMap();
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LEGACY_JOINT_PARAM_H
