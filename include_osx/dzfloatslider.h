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
	Defines the DzFloatSlider class.
**/

#ifndef DAZ_FLOAT_SLIDER_H
#define DAZ_FLOAT_SLIDER_H

/*****************************
	Include files
*****************************/

#include "dzslider.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFloatSlider : public DzSlider {
	Q_OBJECT
	Q_ENUMS( ObjectState )
public:

	//
	// CREATORS
	//

	DzFloatSlider( QWidget *parent, const QString &name = QString::null );
	virtual ~DzFloatSlider();

	//
	// MANIPULATORS
	//
	void	setValue( float val );
	void	setSensitivity( float val );
	void	setMin( float min );
	void	setMax( float max );
	void	setMinMax( float min, float max );
	void	setIndeterminate( bool onOff, const QString &text = QString::null );
	void	setDisplayAsPercent( bool onOff );

	//
	// ACCESSORS
	//

	float	getValue() const;
	float	getSensitivity() const;
	float	getScaleFactor() const;
	float	getMin() const;
	float	getMax() const;
	bool	getIndeterminate() const;
	bool	getDisplayAsPercent() const;

	//
	// REIMPLEMENTATIONS
	//

	virtual void	setPosition( float pos );
	virtual void	step( bool positive );
	virtual float	getPosition() const;

signals:

	void	valueChanged( float val );

protected:

	virtual void	startSpinnerDrag( int pos );
	virtual void	dragSpinner( int delta );
	virtual void	endSpinnerDrag();
	virtual void	textChanged( const QString &text );

private:

	void	updateText();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FLOAT_SLIDER_H


