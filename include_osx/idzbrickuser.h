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
	Defines the interface for DzShaderBrick users.
**/

#ifndef DZ_IDZBRICKUSER_H
#define DZ_IDZBRICKUSER_H
/*****************************
	Include files
*****************************/

#include <QtCore/QUuid>

#include "dzshaderbrick.h"

/*****************************
	Forward declarations
*****************************/

class DzBrickSet;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT IDzBrickUser
{
	friend class DzBrickSet;
public:
	virtual void release()=0;
	virtual bool allowBrick(DzShaderBrick* brick)=0;
	virtual DzBrickMap getBrickMap() const = 0;
	virtual DzElement*	toElement() = 0;
	virtual const DzElement* toElement() const =0;
	virtual void  addChildToElement(DzElement* element) = 0;
	virtual IDzBrickUser* makeNew() const= 0;
	
//The following must be implemented as slots on a DzElement drived class
public slots:
	virtual QString					getExtension() const= 0;
	virtual QString					getDisplayName() const=0;
	virtual QString					getBrickUserName() const=0;
	virtual void					setBrickUserName(const QString& name)=0;
	virtual int						getNumBrickSets() const = 0;
	virtual DzBrickSet*				getBrickSet(int i) const = 0;
	virtual unsigned int			addBrick(DzShaderBrick* brick) = 0;
	virtual DzShaderBrick*			getBrick(unsigned int id) const = 0;
	virtual QVariantList			getBrickIDs() const = 0;
	virtual void					getBrickIDs(QList<unsigned int>& ids) const = 0;
	virtual void					deleteBrick(unsigned int id) = 0;
	virtual void					deleteBrick(DzShaderBrick* brick) = 0;
	virtual void					deleteAllBricks() = 0;
	virtual void					invalidateSets()=0;
	virtual void					moveBrick(unsigned int id,IDzBrickUser* newOwner)=0;
	virtual void					applyToScene()=0;
	virtual QList<IDzBrickUser*>	fromScene()=0;
	virtual QUuid					getIdentifier() const=0;
	virtual void					setIdentifier(const QUuid& ident)=0;
	virtual void					updateIdentifierOnSetInvalidate(bool onOff)=0;
	virtual bool					isInEditMode() const=0;
	virtual void					startEditMode()=0;
	virtual void					endEditMode()=0;

	virtual bool					usesLocalShaderSpace() const=0;

protected slots:
	virtual void					removeSet(DzBrickSet* set)=0;
	virtual void					brickIDChanged(int oldID)=0;
//The following must be implemented as signals on a DzElement drived class
signals:
	virtual void				brickRemoved(DzShaderBrick* brick)=0;
	virtual void				generateFilesStarted()=0;
	virtual void				generateFilesFinished()=0;

};

typedef QList<IDzBrickUser*> DzBrickUserList;
typedef QListIterator<IDzBrickUser*> DzBrickUserListIterator;

Q_DECLARE_METATYPE(IDzBrickUser*);
Q_DECLARE_INTERFACE(IDzBrickUser,"IDzBrickUser")

#endif //DZ_IDZBRICKUSER_H