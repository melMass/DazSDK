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
	Defines the DzIntSlider class.
**/

#ifndef DAZ_INT_SLIDER_H
#define DAZ_INT_SLIDER_H

/*****************************
	Include files
*****************************/

#include "dzslider.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzIntSlider : public DzSlider {
	Q_OBJECT
	Q_ENUMS( ObjectState )
public:

	//
	// CREATORS
	//

	DzIntSlider( QWidget *parent, const QString &name = QString::null );
	virtual ~DzIntSlider();

	//
	// MANIPULATORS
	//

	void			setValue( int val );
	void			setSensitivity( int val );
	void			setMin( int min );
	void			setMax( int max );
	void			setMinMax( int min, int max );
	void			setIndeterminate( bool onOff, const QString &text = QString::null );
	void			setDisplayAsPercent( bool onOff );
	virtual void	setPosition( float pos );
	virtual void	step( bool positive );

	//
	// ACCESSORS
	//

	int				getValue() const;
	int				getSensitivity() const;
	int				getScaleFactor() const;
	int				getMin() const;
	int				getMax() const;
	bool			getIndeterminate() const;
	QString			getIndeterminateText() const;
	bool			getDisplayAsPercent() const;

	virtual float	getPosition() const;

signals:

	void			valueChanged( int val );

protected:

	virtual void	startSpinnerDrag( int pos );
	virtual void	dragSpinner( int delta );
	virtual void	endSpinnerDrag();
	virtual void	textChanged( const QString &text );
	virtual void	updateText();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_INT_SLIDER_H
