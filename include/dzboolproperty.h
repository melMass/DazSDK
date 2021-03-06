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
	Defines the DzBoolProperty class.
**/

#ifndef DAZ_BOOL_PROPERTY_H
#define DAZ_BOOL_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzintproperty.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBoolProperty : public DzIntProperty {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzBoolProperty();
	DzBoolProperty( const QString &name, bool canAnimate, bool isUserProperty, bool initVal = true );
	virtual ~DzBoolProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		setValue( DzTime tm, int val );
	virtual void		setKeyValue( int i, int val );
	virtual int			getValue( DzTime tm ) const;
	virtual int			getKeyValue( int i ) const;
	virtual QString		getWidgetClass( bool styled = true ) const;
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual void	setBoolValue( bool val );
	virtual void	setBoolValue( DzTime tm, bool val );
	virtual void	setDefaultBoolValue( bool val );
	virtual void	setKeyBoolValue( int i, bool val );

	//
	// ACCESSORS
	//

	virtual bool	getBoolValue() const;
	virtual bool	getBoolValue( DzTime tm ) const;
	virtual bool	getDefaultBoolValue() const;
	virtual bool	getRawBoolValue() const;
	virtual bool	getRawBoolValue( DzTime tm ) const;
	virtual bool	getKeyBoolValue( int i ) const;
	virtual bool	doCurrentAttributesMatchDefinition() const;
protected:	
	DzBoolProperty( const DzBoolProperty* bprop );
	struct	Data;
};

#endif // DAZ_BOOL_PROPERTY_H
