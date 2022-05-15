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
	Defines the DzFloatPropertyWgt class.
**/

#ifndef DAZ_FLOAT_PROPERTY_WGT_H
#define DAZ_FLOAT_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dznumericpropertywgt.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFloatPropertyWgt : public DzNumericPropertyWgt {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzFloatPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzFloatPropertyWgt();

	//
	// ACCESSORS
	//

	void	setIsMouseOverSlider( bool onOff );
	bool	isMouseOverSlider() const;

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError addProperty( DzProperty *prop );
	virtual void	removeAllProperties();
	virtual void	showControlOnly( bool onOff );
	virtual void	setLevel( int level );
	void			setOrientation( Qt::Orientation orient );

public slots:

	void			setValue( float val );
	virtual bool	doOptionsDialog();

protected slots:

	virtual void	updateLabel();

protected:

	virtual void	paintEvent( QPaintEvent *e );	// overrides DzNumericPropertyWgt
	virtual void	setLayout( NumericLayout layout );
	virtual void	setMap( const DzTexture *map, bool indeterminate );
	virtual void	updateValue();

private slots:

	void	propertyChangeNotify();
	void	propStateChangeNotify();
	void	startEdit();
	void	finishEdit();
	void	cancelEdit();

private:
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FLOAT_PROPERTY_WGT_H


