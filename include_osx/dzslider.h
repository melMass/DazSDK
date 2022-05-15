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
	Defines the DzSlider class.
**/

#ifndef DAZ_SLIDER_H
#define DAZ_SLIDER_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSlider : public QWidget {
	Q_OBJECT
	Q_ENUMS( SliderState )
public:
	// Mouse/keyboard state values
	enum SliderState {
		None = 0x0000,
		Left = 0x0001,
		Right = 0x0002,
		Mid = 0x0004,
		Value = 0x0008,
		NoChange = 0x0010,
		PosMask = 0x000f
	};
	typedef uint SFlags;

	//
	// CREATORS
	//

	DzSlider( QWidget *parent, const QString &name = QString::null );
	virtual ~DzSlider();

public slots:
	//
	// MANIPULATORS
	//

	virtual void	setTextVisible( bool onOff );
	virtual void	setTextEditable( bool onOff );
	virtual void	setClamped( bool onOff );
	virtual void	setNoChange( bool onOff = true );
	virtual void	setPosition( float pos ) = 0;
	virtual void	setShowLabel( bool onOff );
	virtual void	setLabel( const QString &label );
	virtual void	step( bool positive ) = 0;

	//
	// ACCESSORS
	//

	virtual QString	getText() const;
	virtual bool	isTextVisible() const;
	virtual bool	isTextEditable() const;
	virtual bool	isClamped() const;
	bool			isInState( SFlags value ) const;
	virtual SFlags	getState() const;
	virtual float	getPosition() const = 0;
	virtual bool	showingLabel() const;
	virtual QString	getLabel() const;

	QRect	getSliderRect() const;
	QRect	getTextRect() const;
	QRect	getEditRect() const;
	QRect	getLabelRect() const;
	bool	isEditing() const;


	virtual int	getEndWidthPixelMetric() const;
	virtual int	getSliderThicknessPixelMetric() const;

	virtual Qt::Orientation	getSliderOrientation() const;

signals:

	void	editStart();
	void	editEnd();
	void	editCancelled();

protected:

	//
	// REIMPLEMENTATIONS
	//

	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual void	leaveEvent( QEvent *e );
	virtual void	timerEvent( QTimerEvent *e );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	resizeEvent( QResizeEvent *e );
	virtual void	tabletEvent( QTabletEvent *e );

	//
	// MANIPULATORS
	//

	void			showEdit( const QRect &rect );
	SliderState		getArea() const;

	virtual void	startSpinnerDrag( int pos ) = 0;
	virtual void	dragSpinner( int delta ) = 0;
	virtual void	endSpinnerDrag() = 0;
	virtual void	setText( const QString &text );
	virtual void	textChanged( const QString &text );
	//
	// ACCESSORS
	//

	virtual QSize	calcMinSize() const;
	virtual QRect	calcSliderRect() const;
	virtual QRect	calcTextRect() const;
	virtual QRect	calcEditRect() const;
	virtual QRect	calcLabelRect() const;

protected slots:

	void	updateMinSize();
	void	updateRect();

private slots:

	void	editBoxChange( const QString &text );
	void	finishEdit();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SLIDER_H


