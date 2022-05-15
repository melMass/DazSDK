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
	Defines the DzSkeleton class.
**/

#ifndef DAZ_SKELETON_H
#define DAZ_SKELETON_H

/*****************************
	Include files
*****************************/

#include "dznode.h"

/****************************
	Forward declarations
****************************/

class DzColorProperty;
class DzFollowHelper;
class DzSkeletonProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSkeleton : public DzNode {
	Q_OBJECT
	friend class DzSkeletonFactory;
	friend class DzFollowHelper;
public:
	//
	// CREATORS
	//

	DzSkeleton();
	virtual ~DzSkeleton();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );

	virtual	DzError			finishLoad( const DzInFile *file );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	virtual void			setStorablePaths( const QString &path );
	virtual QPixmap			getPixmap(QStyle::State state = QStyle::State_None) const;
	virtual QIcon			getIcon() const;
	virtual void			render( const DzRenderSettings &settings ) const;
	virtual void			setObject( DzObject *object );

	DzFollowHelper*			getFollowHelper()const;
public slots:

	//
	// MANIPULATORS
	//
	virtual void	setFollowTarget( DzSkeleton *skeleton );
	virtual void	invalidateBoundingBoxes(bool checkSkeleton = true);

public:

	//
	// ACCESSORS
	//

	void	getAllBones( DzBoneList &bones ) const;
	
public slots:

	DzSkeleton*			getFollowTarget() const;
	DzSkeletonProperty*	getFollowControl() const;
	QObjectList			getAllBones() const;
	DzBone*				findBone( const QString &name ) const;
	DzBone*				findBoneByLabel( const QString &label ) const;
	QString				findUniqueBoneName( const QString &desiredName ) const;
	void				setDrawGLBones(bool onOff);
	bool				getDrawGLBones() const;
	DzBoolProperty*		getDrawGLBonesControl() const;
	DzColorProperty*	getGLBonesColorControl() const;
	DzFloatProperty*	getGLBonesFillOpacityControl() const;
	DzEnumProperty*		getGLBonesEdgeStyleControl() const;
	DzFloatProperty*	getGLBonesEdgeOpacityControl() const;
	virtual void		update( bool isRender = false );
	void				clearGeneratedMorphs();

signals:

	void	followTargetChanged( DzSkeleton *skeleton );
	void	updateAutoFollowForScale( DzSkeleton* tgtSkeleton );

protected:

	DzSkeleton( const DzInFile *file );

	virtual void	makePureVirtual() = 0;
	
	virtual void	addFollower( DzSkeleton *newFollower );
	virtual void	removeFollower( DzSkeleton *oldFollower );
	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;	

private slots:

	void	updateFollowControl();
	void	changeFollowTarget();
	void	stopFollowing();
	void	setBoneVis();
	void	setBoneSel();
	void	clearOldFollowLinks();
	void	invalidateBoneBoundingBoxes();
	void	skelParentChanged();

private:

	void	init( bool doCreateProperties );
	void	createProperties();
	void	getAllNodesRecurse( const DzNode *node, DzNodeList &nodes ) const;
	void	getAllBonesRecurse( const DzNode *node, DzBoneList &bones ) const;
	DzBone*	findBoneRecurse( const DzNode *node, const QString &name ) const;
	DzBone*	findBoneByLabelRecurse( const DzNode *node, const QString &lbl ) const;
	void	invalidateBoneBoundingBoxesRecurse( DzNode *node );

	virtual DzFollowHelper*	createFollowHelper();
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SKELETON_H
