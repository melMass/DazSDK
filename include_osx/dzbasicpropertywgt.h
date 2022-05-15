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
	Defines the DzBasicPropertyWgt class.
**/

#ifndef DAZ_BASIC_PROPERTY_WGT_H
#define DAZ_BASIC_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzpropertywgt.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBasicPropertyWgt : public DzPropertyWgt {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzBasicPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzBasicPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	showControlOnly( bool onOff );
	virtual void	setLevel( int level );

protected:

	virtual void	paintEvent( QPaintEvent *e );

	void			addWidget( QWidget *widget );
	void			addLayout( QLayout *layout );
	void			updateFromList();

private slots:

	void			updateLabel();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BASIC_PROPERTY_WGT_H


