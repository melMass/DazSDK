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
	Defines the DzBone class.
**/

#ifndef DAZ_BONE_H
#define DAZ_BONE_H

/*****************************
	Include files
*****************************/

#include "dznode.h"
#include "dzcustomdata.h"

/****************************
	Definitions
****************************/

#define DZ_POSER_IK_TARGET_FLAG_ID		0x0010

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBone : public DzNode {
	Q_OBJECT
	friend class DzFollowHelper;
	friend class DzBoneFactory;
public:
	//
	// CREATORS/DESTROYERS
	//

	DzBone();
	virtual ~DzBone();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			setStorablePaths( const QString &path );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setName( const QString &name );
	virtual void			save( DzOutFile *file ) const;
	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;
	virtual DzBox3			getWSBoundingBox() const;
	virtual DzOrientedBox3	getWSOrientedBox() const;
	virtual void			drawGeometry( const DzDrawStyle &style ) const;
	virtual DzQuat			getOrientation( bool defaultVal = false ) const;
	virtual DzVec3			getOrigin( bool defaultVal = false ) const;
	virtual DzVec3			getEndPoint( bool defaultVal = false ) const;

	static void				drawBone( const DzBone *bone, const DzDrawStyle &style );

public slots:

	DzBone*			getFollowBone() const;
	DzMatrix3		getBoneLocalScale( DzTime tm ) const;

signals:

	void			followBoneChanged( DzBone *newFollowBone );

protected:
	DzBone( const DzInFile *file );

	virtual void	calcLocalTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaultVals = false ) const;
	virtual void	calcWSTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaultVals = false ) const;

	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;

private slots:

	void			removeFollowBone();

private:
	
	DzMatrix3		calcLocalScale( DzTime tm, bool defaultVals= false ) const;
	void			setFollowBone( DzBone *node );
	void			getWSRootNodeTransform( DzTime tm, DzNode *parent, DzVec3 &pos,
						DzQuat &rot, DzMatrix3 &scale, bool defaultVals = false  ) const;
	bool			getChainTransform( DzTime tm, DzNode *chainParent, DzNode *chainTarget,
						DzVec3 &localPos, DzQuat &localRot, DzMatrix3 &localScale ) const;
	DzQuat			getEndPointRotation( DzTime tm, const DzVec3 &wsPos, const DzQuat &wsRot, const DzMatrix3 &wsScale, bool defaultVal = false ) const;
	static void		drawBone( const DzBone *bone, const DzRotationOrder &rotOrder, float length, bool isCurrent, const DzDrawStyle &style );
	static void		drawSolidBone( const DzBone *bone, const DzRotationOrder &rotOrder, float length, bool isCurrent, const DzDrawStyle &style );
	void			riggingBoundingBox( DzBox3 &bbox ) const;
	
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPoserIKTargetFlag : public DzElementData {
	Q_OBJECT
public:

	DzPoserIKTargetFlag() : DzElementData( "PoserIKTarget", true ) { }
	virtual DzElementData* duplicate( DzElement* owner ) const;
};

class DZ_EXPORT DzPoserNonPropagatingScaleFlag : public DzElementData {
	Q_OBJECT
public:

	DzPoserNonPropagatingScaleFlag();
	static QString dataItemName();
	virtual DzElementData* duplicate( DzElement* owner ) const;
};

class DZ_EXPORT DzPoserPropagatingScaleFlag : public DzElementData {
	Q_OBJECT
public:

	DzPoserPropagatingScaleFlag();
	static QString dataItemName();
	virtual DzElementData* duplicate( DzElement* owner ) const;
};

#endif // DAZ_BONE_H
