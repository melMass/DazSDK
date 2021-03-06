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
	Defines the DzBoolPropertyWgt class.
**/

#ifndef DAZ_BOOL_PROPERTY_WGT_H
#define DAZ_BOOL_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzbasicpropertywgt.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBoolPropertyWgt : public DzBasicPropertyWgt {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzBoolPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzBoolPropertyWgt();

	//
	// MANIPULATORS
	//

	//////////////////////////
	// from DzPropertyWgt

	virtual DzError addProperty( DzProperty *prop );
	virtual void	removeAllProperties();

	void			setButtonText( const QString &trueText, const QString &falseText );

public slots:
	virtual bool	doOptionsDialog();

protected:

	virtual void	showEvent( QShowEvent *e );

protected slots:
	virtual void	updateFromList();

private slots:

	void	propertyChangeNotify();
	void	toggleValue();

private:
	void	updateValue();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BOOL_PROPERTY_WGT_H


