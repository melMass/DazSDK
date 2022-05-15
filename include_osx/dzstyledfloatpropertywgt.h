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
	Defines the DzStyledFloatPropertyWgt class.
**/

#ifndef DAZ_STYLED_FLOAT_PROPERTY_WGT_H
#define DAZ_STYLED_FLOAT_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstylednumericpropertywgt.h"
#include "dzfloatpropertyslider.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledFloatPropertyWgt : public DzStyledNumericPropertyWgt {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzStyledFloatPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledFloatPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	removeAllProperties();

	//internal
	virtual void	setPropertyList( const DzPropertyList &list );
	virtual void	clearPropertyList();

public slots:

	void			setValue( float val );
	virtual bool	doOptionsDialog();

protected:

	virtual void	updateValue();
	virtual QString	getValueEditText() const;
	virtual void	valueTextChanged( const QString &text );

private slots:

	void	propertyChangeNotify();
	void	propStateChangeNotify();
	void	startEdit();
	void	finishEdit();
	void	cancelEdit();
	void	validateMapChange( const DzTexture *map );
	void	sliderChangedByUser( float newVal );

private:

	void	updateStyleDrawFlags();

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzStyledFloatPropertySlider : public DzFloatPropertySlider
{
	Q_OBJECT
public:
	DzStyledFloatPropertySlider(QWidget *parent = NULL);
	~DzStyledFloatPropertySlider();
	virtual int		getEndWidthPixelMetric() const;
	virtual int		getSliderThicknessPixelMetric() const;

	virtual	void	setSliderOrientation( Qt::Orientation orient );
	virtual Qt::Orientation getSliderOrientation() const;
	void			setShowHighlight( bool onOff );

protected:
	virtual void	paintEvent( QPaintEvent *e );
	virtual QSize	calcMinSize() const;
	virtual QRect	calcSliderRect() const;

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STYLED_FLOAT_PROPERTY_WGT_H
