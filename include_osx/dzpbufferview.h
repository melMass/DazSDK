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
	Defines the DzPBufferView class.
**/

#ifndef DAZ_PBUFFER_VIEW_H
#define DAZ_PBUFFER_VIEW_H

/*****************************
	Include files
*****************************/

#include <QtCore/QObject>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QImage;
class QRect;
class QPoint;
class QSize;
class QColor;
class DzNode;
class DzMaterial;
class DzCamera;
class DzDrawStyle;
class DzRenderHandler;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPBufferView : public QObject {
	Q_OBJECT
public:

	DzPBufferView();
	DzPBufferView( const QSize &size );
	virtual ~DzPBufferView();

public slots:

	//
	// MANIPULATORS
	//

	bool			redraw( bool drawGizmos );
	void			resize( const QSize &size );
	void			setDrawStyle( DzDrawStyle *style );
	void			setBackground( const QColor &color );
	void			setFloorOn( bool onOff );
	void			setAxesOn( bool onOff );
	void			setCamera( DzCamera *cam );
	void			aimCamera();
	void			frameCamera();
	void			resetCamera();
	DzNode*			pickOnNode( const QPoint &pnt );
	DzMaterial*		pickOnMaterial( const QPoint &pnt );
	int				pickOnGizmo( const QPoint &pnt );

	//
	// ACCESSORS
	//

	bool			isValid() const;
	QSize			size() const;
	DzDrawStyle*	getDrawStyle() const;
	QColor			getBackground() const;
	bool			getFloorOn() const;
	bool			getAxesOn() const;
	DzCamera*		getCamera() const;

	bool			hardwareRender( DzRenderHandler *handler ) const;
	bool			renderThumbnail( DzRenderHandler *handler ) const;

	const QImage&	getImage() const;

signals:

	void	sizeChanged( const QSize &size );
	void	activeCameraChanged( DzCamera *cam );
	void	viewChanged();
	void	drawStyleChanged( DzDrawStyle *style );
	void	backgroundColorChanged( const QColor &color );
	void	floorOnChanged( bool onOff );
	void	axesOnChanged( bool onOff );

private:

	void	init( const QSize &size );
	QImage	getImageGL( const QSize &size, const QRect &rect, bool drawGizmos );
	void	drawGL( const QRect &rect, bool drawGizmos );
	void	drawFloor();
	void	drawCenterAxes();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PBUFFER_VIEW_H
