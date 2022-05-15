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
	Defines the DzIntPropertySlider class.
**/

#ifndef DAZ_INT_PROPERTY_SLIDER_H
#define DAZ_INT_PROPERTY_SLIDER_H

/*****************************
	Include files
*****************************/

#include "dznumericpropertywgt.h"
#include "dzintslider.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzIntPropertySlider : public DzIntSlider {
	Q_OBJECT
public:
	DzIntPropertySlider( QWidget *parent, const QString &name = QString::null );
	~DzIntPropertySlider();

	void			setPropHidden( bool onOff );
	bool			isPropHidden() const;

	void			setLocked( bool onOff );
	bool			isLocked() const;

	void			setIsMouseOverType( bool onOff );
	bool			isMouseOverType() const;

	void			setIndent( int indent );

	void			setLayout( DzNumericPropertyWgt::NumericLayout layout );
	void			setMap( const DzTexture *map, bool indeterminate );

signals:

	void			mapChanged( const DzTexture *map );

protected:

	virtual void	resizeEvent( QResizeEvent *e );
	virtual void	enterEvent( QEvent *e );
	virtual void	leaveEvent( QEvent *e );
	virtual void	timerEvent ( QTimerEvent * );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual QSize	calcMinSize() const;
	virtual QRect	calcSliderRect() const;
	virtual QRect	calcTextRect() const;
	virtual QRect	calcEditRect() const;
	virtual QRect	calcLabelRect() const;

private:

	void			updateImageMenuGeom();
	void			addImageMenu();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_INT_PROPERTY_SLIDER_H