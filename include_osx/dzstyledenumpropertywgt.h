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
	Defines the DzStyledEnumPropertyWgt class.
**/

#ifndef DAZ_STYLED_ENUM_PROPERTY_WGT_H
#define DAZ_STYLED_ENUM_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstylednumericpropertywgt.h"

/****************************
	Forward declarations
****************************/

class QComboBox;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledEnumPropertyWgt : public DzStyledNumericPropertyWgt {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStyledEnumPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledEnumPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//
	
	virtual DzError	addProperty( DzProperty *prop );

public slots:
	void			setValue( int val );
	void			updateList();
	virtual bool	doOptionsDialog();

protected slots:
	virtual void	updateFromList();
	
protected:
	virtual void	setMap( const DzTexture *map, bool indeterminate ){};
	virtual void	updateValue();
	

private slots:

	void	propertyChangeNotify();

private:
	struct	Data;
	Data	*m_data;
};

#endif //DAZ_STYLED_ENUM_PROPERTY_WGT_H