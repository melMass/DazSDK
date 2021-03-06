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
	Defines the DzColorProperty class.
**/

#ifndef DAZ_COLOR_PROPERTY_H
#define DAZ_COLOR_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzintproperty.h"

/*****************************
	Forward declarations
*****************************/

class QColor;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzColorProperty : public DzIntProperty {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzColorProperty();
	DzColorProperty( const QString &name, bool canAnimate, bool isUserProperty );
	DzColorProperty( const QString &name, bool canAnimate, bool isUserProperty,
		const QColor &initVal );
	virtual ~DzColorProperty();

	virtual void		copyFrom( DzProperty *prop );

	//
	// REIMPLEMENTATIONS
	//

	virtual int			getRawValue( DzTime tm ) const;
	virtual QString		getWidgetClass( bool styled = true ) const;
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

public slots:
	//
	// MANIPULATORS
	//
	virtual void	setIsClamped( bool val );
	virtual void	setIsModulo( bool val );
	virtual void	setMin( int min );
	virtual void	setMax( int max );
	virtual void	setMinMax( int min, int max );
	virtual void	setColorValue( const QColor &val );
	virtual void	setColorValue( DzTime tm, const QColor &val );
	virtual void	setDefaultColorValue( const QColor &val );
	virtual void	setKeyColorValue( int i, const QColor &val );

	//
	// ACCESSORS
	//

	virtual QColor	getColorValue() const;
	virtual QColor	getColorValue( DzTime tm ) const;
	virtual QColor	getDefaultColorValue() const;
	virtual QColor	getRawColorValue() const;
	virtual QColor	getRawColorValue( DzTime tm ) const;
	virtual QColor	getKeyColorValue( int i ) const;
	virtual bool	doCurrentAttributesMatchDefinition() const;

protected:	
	DzColorProperty(const DzColorProperty* eprop);
	struct	Data;
};

#endif // DAZ_COLOR_PROPERTY_H