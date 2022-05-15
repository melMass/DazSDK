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
	Defines the DzStyledIntPropertyWgt class.
**/

#ifndef DAZ_STYLED_INT_PROPERTY_WGT_H
#define DAZ_STYLED_INT_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstylednumericpropertywgt.h"
#include "dzintpropertyslider.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledIntPropertyWgt : public DzStyledNumericPropertyWgt {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStyledIntPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledIntPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	removeAllProperties();
	
public slots:

	void			setValue( int val );
	virtual bool	doOptionsDialog();

protected:

	virtual void	updateValue();
	virtual void	valueTextChanged( const QString &text );
	virtual QString getValueEditText() const;

private slots:

	void	propertyChangeNotify();
	void	propStateChangeNotify();
	void	startEdit();
	void	finishEdit();
	void	cancelEdit();
	void	validateMapChange( const DzTexture *map );
	void	sliderChangedByUser( int newVal );

private:

	struct	Data;
	Data	*m_data;
};

struct DzStyledIntPropertySliderData;
class DZ_EXPORT DzStyledIntPropertySlider : public DzIntPropertySlider
{
	Q_OBJECT
public:
	DzStyledIntPropertySlider(QWidget *parent = NULL);
	~DzStyledIntPropertySlider();

	virtual int		getEndWidthPixelMetric() const;
	virtual int		getSliderThicknessPixelMetric() const;

	virtual	void	setSliderOrientation(Qt::Orientation orient);
	virtual Qt::Orientation getSliderOrientation() const;

protected:
	virtual void	paintEvent( QPaintEvent *e );
	virtual QSize	calcMinSize() const;
	virtual QRect	calcSliderRect() const;

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STYLED_INT_PROPERTY_WGT_H