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
	Defines the DzNumericPropertyWgt class.
**/

#ifndef DAZ_NUMERIC_PROPERTY_WGT_H
#define DAZ_NUMERIC_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzpropertywgt.h"

/****************************
	Forward declarations
****************************/

class DzTexture;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNumericPropertyWgt : public DzPropertyWgt {
	Q_OBJECT
public:

	enum NumericLayout { NLNonMappable = 0, NLMapped, NLNotMapped, NLNeedsMap };
	enum MapDisplay { PropertyDependent, AlwaysDisplayMap, NeverDisplayMap };

	//
	// CREATORS
	//

	DzNumericPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzNumericPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );

public slots:

	//
	// MANIPULATORS
	//

	void			setMapDisplay( MapDisplay mode );

	//
	// ACCESSORS
	//

	MapDisplay		getMapDisplay() const;

protected slots:

	virtual void	updateValue();
	virtual void	updateLabel() = 0;
	void			changeMap( const DzTexture *map );
	virtual void	updateFromList();

protected:

	virtual void	showEvent( QShowEvent *e );
	virtual void	paintEvent( QPaintEvent *e );
	void			addWidget( QWidget *wgt );

	virtual void	setLayout( NumericLayout layout ) = 0;
	virtual void	setMap( const DzTexture *map, bool indeterminate ) = 0;

private:

	void	updateLayout( NumericLayout layout );
	void	addImageMapMenu();
	void	addTieWgt();
	void	addLabel();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NUMERIC_PROPERTY_WGT_H
