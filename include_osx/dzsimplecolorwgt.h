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
	Defines the DzSimpleColorWgt class.
**/

#ifndef DAZ_SIMPLE_COLOR_WGT_H
#define DAZ_SIMPLE_COLOR_WGT_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSimpleColorWgt : public QWidget {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzSimpleColorWgt( const QColor &initColor, QWidget *parent, const QString &name = QString::null );
	virtual ~DzSimpleColorWgt();

	//
	// MANIPULATORS
	//

	void	setValue( const QColor &val );
	void	setInderminate( bool onOff );

	//
	// ACCESSORS
	//

	QColor	getValue() const;
	bool	isIndeterminate() const;

signals:

	void	colorChanged( const QColor &color );
	void	editStart();
	void	editEnd();

protected:
	//
	// MANIPULATORS
	//

	virtual void	paintEvent( QPaintEvent *e );
	virtual void	mousePressEvent( QMouseEvent *e );

private:

	void	pickColor();

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SIMPLE_COLOR_WGT_H


