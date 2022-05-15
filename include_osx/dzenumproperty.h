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
	Defines the DzEnumProperty class.
**/

#ifndef DAZ_ENUM_PROPERTY_H
#define DAZ_ENUM_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzintproperty.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzEnumProperty : public DzIntProperty {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzEnumProperty();
	DzEnumProperty( const QString &name, bool canAnimate, bool isUserProperty );
	virtual ~DzEnumProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;
	virtual bool		getMinMax( int &min, int &max ) const;
	virtual int			getDefaultValue() const;
	virtual int			getKeyValue( int i ) const;
	virtual int			getValue() const;
	virtual int			getValue( DzTime tm ) const;
	virtual QString		getWidgetClass(bool styled=true) const;
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

public slots:
	//
	// MANIPULATORS
	//

	virtual int		addItem( const QString &item, int index = -1 );
	virtual bool	removeItem( int index );
	virtual void	removeAllItems();
	virtual bool	replaceItem( int index, const QString &item );
	virtual bool	setValueFromString( const QString &str );
	virtual bool	setValueFromString( DzTime tm, const QString &str );

	//
	// ACCESSORS
	//

	virtual QString	getStringValue() const;
	virtual QString	getStringValue( DzTime tm ) const;
	virtual QString	getDefaultStringValue() const;
	virtual QString	getRawStringValue() const;
	virtual QString	getRawStringValue( DzTime tm ) const;
	virtual QString	getKeyStringValue( int i ) const;
	virtual int		getNumItems() const;
	virtual QString	getItem( int i ) const;
	virtual QString	getUniqueItemString( const QString &item ) const;
	virtual int		findItemString( const QString &str ) const;
	virtual bool	isCombinable( DzProperty *prop );
	virtual bool	doCurrentAttributesMatchDefinition() const;

signals:
#ifndef Q_MOC_RUN
private:
#endif
	void			itemListChanged();

protected slots:
	void			emitItemListChanged();

protected:
	DzEnumProperty(const DzEnumProperty* eprop);
	struct	Data;
};

#endif // DAZ_ENUM_PROPERTY_H