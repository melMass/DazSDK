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
	Defines the DzStringProperty class.
**/

#ifndef DAZ_STRING_PROPERTY_H
#define DAZ_STRING_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzproperty.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStringProperty : public DzProperty {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzStringProperty();
	DzStringProperty( const QString &name, bool isUserProperty );
	virtual ~DzStringProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();
	virtual void		copyFrom( DzProperty *prop );
	virtual QString		getWidgetClass(bool styled=true) const;
	virtual bool		isNumeric() const { return false; }
	virtual bool		isAlias() const;
	virtual DzProperty*	getAliasTarget() const;
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

	virtual DzPropertyClipboard*	copyToClipboard() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual bool	setValue( const QString &val );

	//
	// ACCESSORS
	//

	virtual QString	getValue() const;
	virtual bool	currentValueIsDefaultValue() const;

protected:

	struct	Data;

	DzStringProperty( const DzStringProperty* sprop );
	DzStringProperty( DzStringProperty::Data *data );
	DzStringProperty( const QString &name, bool isUserProperty, DzStringProperty::Data *data );
};

class DZ_EXPORT DzStringPropertyClipboard : public DzPropertyClipboard {
	Q_OBJECT
	friend class DzStringProperty;
public:
	virtual ~DzStringPropertyClipboard();

public slots:
	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzStringPropertyClipboard( const DzStringProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STRING_PROPERTY_H
