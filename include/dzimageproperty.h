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
	Defines the DzImageProperty class.
**/

#ifndef DAZ_IMAGE_PROPERTY_H
#define DAZ_IMAGE_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzproperty.h"

/*****************************
	Forward declarations
*****************************/

class DzTexture;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzImageProperty : public DzProperty {
	Q_OBJECT
	friend class DzImagePropUndoItem;
public:
	//
	// CREATORS
	//

	DzImageProperty();
	DzImageProperty( const QString &name, bool isUserProperty );
	virtual ~DzImageProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();
	virtual void		copyFrom( DzProperty *prop );
	virtual QString		getWidgetClass( bool styled = true ) const;
	virtual bool		isNumeric() const { return false; }
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

	virtual DzPropertyClipboard*	copyToClipboard() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual bool	setValue( const DzTexture *val );
	virtual bool	setValue( const QString &imgFile );

	//
	// ACCESSORS
	//

	virtual DzTexture*	getValue() const;
	virtual bool		currentValueIsDefaultValue() const;

protected:
	DzImageProperty( const DzImageProperty* iprop );
	struct	Data;
};

class DZ_EXPORT DzImagePropertyClipboard : public DzPropertyClipboard {
	Q_OBJECT
	friend class DzImageProperty;
public:
	virtual ~DzImagePropertyClipboard();

public slots:
	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzImagePropertyClipboard( const DzImageProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_IMAGE_PROPERTY_H
