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
	Defines the DzEnumSlider class.
**/

#ifndef DAZ_ENUM_SLIDER_H
#define DAZ_ENUM_SLIDER_H

/*****************************
	Include files
*****************************/

#include "dzintslider.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzEnumSlider : public DzIntSlider {
	Q_OBJECT
	Q_ENUMS( ObjectState )
public:

	//
	// CREATORS
	//

	DzEnumSlider( QWidget *parent, const QString &name = QString::null );
	virtual ~DzEnumSlider();

	//
	// MANIPULATORS
	//

	void	clear();
	int		addItem( const QString &label );
	void	removeItem( int which );
	void	renameItem( int which, QString &label );
	void	moveItem( int which, int idx );

	//
	// ACCESSORS
	//

	int		getNumValues() const;
	QString	getItem( int which ) const;

protected:

	virtual void	updateText();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_ENUM_SLIDER_H
