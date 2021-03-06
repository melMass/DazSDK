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
	Defines the DzStringPropertyWgt class.
**/

#ifndef DAZ_STRING_PROPERTY_WGT_H
#define DAZ_STRING_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzbasicpropertywgt.h"

/****************************
	Forward declarations
****************************/

class DzTimeRange;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStringPropertyWgt : public DzBasicPropertyWgt {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzStringPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStringPropertyWgt();

	//
	// MANIPULATORS
	//

	virtual DzError addProperty( DzProperty *prop );
	virtual void	removeAllProperties();
	
public slots:
	virtual bool	doOptionsDialog();

protected:
	//
	// MANIPULATORS
	//
	
	virtual void	showEvent( QShowEvent *e );
	void			setValue( const QString &val );

protected slots:
	virtual void	updateFromList();

private slots:
	void	propertyChangeNotify();
	void	applyStringToProperties();
	
private:
	
	void	updateValue();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STRING_PROPERTY_WGT_H
