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
	Defines the DzMouseButton class.
**/

#ifndef DAZ_MOUSE_BUTTON_H
#define DAZ_MOUSE_BUTTON_H

/*****************************
	Include files
*****************************/

#include "dzstyledbutton.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMouseButton : public DzStyledButton {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzMouseButton( QWidget *parent, const QString &name, bool isDragButton = false );
	DzMouseButton( QWidget *parent, const QString &name, const QPixmap &icon, bool isDragButton = false );
	DzMouseButton( QWidget *parent, const QString &name, const QPixmap &icon, const QPixmap &altIcon,
		bool isDragButton = false );
	DzMouseButton( QWidget *parent, const QString &name, const QPixmap &defaultPix,
		const QPixmap &disablePix, const QPixmap &hilightPix, bool isDragButton = false );
	DzMouseButton( QWidget *parent, const QString &name, const QPixmap &defaultPix,
		const QPixmap &disablePix, const QPixmap &hilightPix, const QPixmap &defaultAlt,
		const QPixmap &disableAlt, const QPixmap &hilightAlt, bool isDragButton = false );
	virtual ~DzMouseButton();

	virtual QSize	sizeHint() const;

public slots:
	//
	// MANIPULATORS
	//

	void	setPixmaps( const QPixmap &defaultPix, const QPixmap &disablePix,
				const QPixmap &hilightPix );
	void	setPixmaps( const QPixmap &icon );

	void	setAltPixmaps( const QPixmap &defaultPix, const QPixmap &disablePix,
				const QPixmap &hilightPix );
	void	setAltPixmaps( const QPixmap &icon );

signals:

	void	rightClicked();
	void	pressed( Qt::MouseButton btn );
	void	dragged( const QPoint &pnt );

protected:
	//
	// MANIPULATORS
	//

	////////////////////////
	// from QWidget

	virtual void	enterEvent( QEvent *e );
	virtual void	leaveEvent( QEvent *e );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual void	tabletEvent( QTabletEvent *event );

private:
	void	blendImageData( unsigned int *back, unsigned int *overlay,
				const QColor &overlayColor, unsigned int *destData, int total );
	void	getDisabledIcon( const QImage &icon, QImage &disabled );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MOUSE_BUTTON_H


