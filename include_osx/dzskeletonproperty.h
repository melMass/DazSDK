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
	Defines the DzSkeletonProperty class.
**/

#ifndef DAZ_SKELETON_PROPERTY_H
#define DAZ_SKELETON_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dznodeproperty.h"

/****************************
	Forward declarations
****************************/

class DzSkeleton;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSkeletonProperty : public DzNodeProperty {
	Q_OBJECT
	friend class DzSkeletonPropUndoItem;
public:
	//
	// CREATORS
	//

	DzSkeletonProperty();
	DzSkeletonProperty( const QString &name, bool canAnimate, bool isUserProperty );
	virtual ~DzSkeletonProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual QString		getWidgetClass(bool styled=true) const;
	virtual void		setDefaultValue( DzNode *val );
	virtual void		setValue( DzNode *val );
	virtual void		setValue( DzTime tm, DzNode *val );
	virtual void		setKeyValue( int which, DzNode *val );
	virtual bool		isAlias() const;
	virtual DzProperty*	getAliasTarget() const;
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

public slots:

	//
	// ACCESSORS
	//

	virtual DzSkeleton*	getSkeletonValue() const;

signals:
#ifndef Q_MOC_RUN
private:
#endif
	void	aboutToChange();

protected:
	DzSkeletonProperty( const DzSkeletonProperty* iprop );
	struct	Data;

protected slots:
	void	emitAboutToChange();
};

#endif // DAZ_SKELETON_PROPERTY_H
