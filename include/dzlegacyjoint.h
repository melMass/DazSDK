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
	Defines the DzLegacyJoint class.
**/

#ifndef DAZ_LEGACY_JOINT_H
#define DAZ_LEGACY_JOINT_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"

/****************************
	Forward declarations
****************************/

class DzBoolProperty;
class DzObject;
class DzVec3;
class DzVertexMesh;
class IDzLegacyBindingTransformSource;
struct DzLegacyBoneVertex;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLegacyJoint : public DzElement {
	Q_OBJECT
	Q_PROPERTY( bool bending READ bendingOn WRITE setBending )
	friend class DzLegacyBinding;
	friend class DzLegacyJointFactory;
public:
	//
	// CREATORS
	//

	DzLegacyJoint();
	virtual ~DzLegacyJoint();

	//
	// MANIPULATORS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	setStorablePaths( const QString &path );

	DzError	apply( DzObject* obj, DzVertexMesh &geom, DzNode &node );
	DzError	applyInverse( DzObject* obj, DzVertexMesh &geom, DzNode &node );

	void	setBending( bool onOff );
	
	DzError	apply( DzObject* obj, DzVertexMesh &geom, DzNode &node, bool scaleOnly, IDzLegacyBindingTransformSource* transform=NULL );

public slots:

	void	setBone( DzNode *bone, bool createAlais=true );
	void	setGroupName( const QString &groupName );
	void	addJointParam( DzLegacyJointParam *param );

public:
	//
	// ACCESSORS
	//

	virtual void	save( DzOutFile *file ) const;
	bool			bendingOn() const;

	DzLegacyJointParamListIterator	jointParamsIterator() const;
	DzVec3	getScaledOrigin(IDzLegacyBindingTransformSource* transform=NULL);

public slots:

	DzNode*				getBone() const;
	QString				getGroupName() const;
	QObjectList			getJointParams() const;
	int					getNumParams() const;
	DzLegacyJointParam*	getParam( int which ) const;
	DzLegacyJointParam*	findJointParam( const QString &name ) const;
	DzBoolProperty*		getBendControl() const;
	void				jointScaleChanged();
	bool				removeJointParam( DzLegacyJointParam *item );
	DzLegacyJoint*		deepCopy()const;

	static DzLegacyJoint*	findJoint( const DzNode *bone );
signals:

	void	currentValueChanged();
	void	boneChanged( DzNode *newBone );
	void	groupNameChanged( const QString &newGroupName );

protected:
	DzLegacyJoint( const DzInFile *file );

private:
	void	init( bool doCreateProperties );
	void	createProperties();
	void	bindToFigureSpace( DzVertexMesh &geom, DzNode &node, const DzLegacyBoneVertex* mask, 
		int maskCount, bool scaleOnly = false, IDzLegacyBindingTransformSource* transform = NULL );
	void	bindToFigureSpaceInverse( DzVertexMesh &geom, DzNode &node, const DzLegacyBoneVertex* mask, int maskCount );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LEGACY_JOINT_H
