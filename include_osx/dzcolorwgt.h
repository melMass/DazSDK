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
	Defines the DzColorWgt class.
**/

#ifndef DAZ_COLOR_WGT_H
#define DAZ_COLOR_WGT_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzColorWgt : public QWidget {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzColorWgt( const QColor &initColor, QWidget *parent, const QString &name = QString::null );
	virtual ~DzColorWgt();

	//
	// MANIPULATORS
	//

	void	setValue( const QColor &val );
	void	setIndeterminate( bool onOff );

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

	/////////////////////////
	// from QWidget

	virtual void	paintEvent( QPaintEvent *e );
	virtual void	leaveEvent( QEvent *e );
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual QSize	sizeHint() const;

private slots:

	void	beginLineEdit( int xPos );
	void	finishLineEdit();

private:

	void	startSpinnerDrag( const QPoint &pos );
	void	dragSpinner( const QPoint &pos );
	void	endSpinnerDrag( bool accept );
	void	pickColor();

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_COLOR_WGT_H


