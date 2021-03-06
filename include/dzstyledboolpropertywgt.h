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
	Defines the DzStyledBoolPropertyWgt class.
**/

#ifndef DAZ_STYLED_BOOL_PROPERTY_WGT_H
#define DAZ_STYLED_BOOL_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstylednumericpropertywgt.h"
#include "dzboolbutton.h"

/****************************
	Forward declarations
****************************/

class DzTexture;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledBoolPropertyWgt : public DzStyledNumericPropertyWgt {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStyledBoolPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledBoolPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	removeAllProperties();

	void			setButtonText( const QString &trueText, const QString &falseText );
	
public slots:
	void toggleValue();
	virtual bool	doOptionsDialog();

protected:

	virtual void	updateValue();
	virtual void	showEvent( QShowEvent *e );
	virtual void	updateFromList();

private slots:

	void	propertyChangeNotify();

private:

	struct	Data;
	Data	*m_data;
};

class DzStyledBoolPropertySlider : public DzBoolButton
{
	Q_OBJECT
public:
	DzStyledBoolPropertySlider(QWidget *parent = NULL);

	~DzStyledBoolPropertySlider();
protected:
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &oldStyle );
private:
	void	setStyledSize();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STYLED_BOOL_PROPERTY_WGT_H