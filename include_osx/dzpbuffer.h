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
	Defines the DzPBuffer class.
**/

#ifndef DAZ_PBUFFER_H
#define DAZ_PBUFFER_H

/*****************************
	Include files
*****************************/

#include <QtCore/QObject>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QColor;
class QImage;
class QRect;
class QSize;
class DzColor;
class DzCamera;
class DzDrawStyle;
class DzRenderHandler;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPBuffer : public QObject {
	Q_OBJECT
	friend class DzPBufferMgr;
public:

	DzPBuffer();
	~DzPBuffer();

	//
	// REIMPLEMENTATIONS
	//

	bool	event( QEvent *e );

	//
	// MANIPULATORS
	//

	bool	makeCurrent();
	bool	hardwareRender( DzRenderHandler *handler, DzCamera *camera );
	bool	renderThumbnail( DzRenderHandler *handler, DzCamera *camera );
	QImage	getCurrentImage( const QRect &rect );

public slots:

	void	setEnabled( bool onOff );
	void	setMaxSize( int maxSize );
	bool	initBuffer();

	//
	// ACCESSORS
	//

	bool	isValid() const;
	int		getHeight() const;
	int		getWidth() const;
	bool	isEnabled() const;
	bool	isSupported() const;
	int		getMaxSize() const;

private:

	bool	render( DzRenderHandler *handler, DzCamera *camera, bool isThumbnail );
	void	drawScene( DzCamera *camera, DzDrawStyle &style, const QColor &backColor, const QSize &size, const QRect &rect );
	bool	createBuffer();
	void	initializeGL();
	void	setGLOptions();
	void	freeBuffer();
	void	doPolySort( DzDrawStyle &style, DzCamera *camera );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PBUFFER_H
