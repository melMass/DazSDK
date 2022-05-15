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
	Defines the DzRenderHandler class.
**/

#ifndef DAZ_RENDER_HANDLER_H
#define DAZ_RENDER_HANDLER_H

/*****************************
	Include files
*****************************/

#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QtCore/QEvent>

#include "dzrenderdata.h"

/*****************************
	Forward Declarations
*****************************/

class QSize;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRenderHandler : public QObject {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzRenderHandler();
	virtual ~DzRenderHandler();

	//
	// MANIPULATORS
	//

	////////////////////
	// from QObject

	virtual bool	event( QEvent *e );

public slots:

	virtual void	setBackColor( const QColor &color ) { m_backColor = color; }
	virtual void	setUseCropWindow( bool onOff ) { m_useCropWindow = onOff; }
	virtual void	setCropWindow( const QRect &window ) { m_cropWindow = window; }

public:

	virtual void	beginRender() = 0;
	virtual void	finishRender() = 0;
	virtual void	beginFrame( int frame ) = 0;
	virtual void	finishFrame() = 0;
	virtual void	passData( const DzRenderData &data ) = 0;

public slots:

	//
	// ACCESSORS
	//

	virtual QColor	getBackColor() const { return m_backColor; }
	virtual bool	getUseCropWindow() const { return m_useCropWindow; }
	virtual QRect	getCropWindow() const { return m_cropWindow; }
	virtual QSize	getSize() const = 0;
	virtual DzTime	getStartingTime() const = 0;
	virtual int		getNumFrames() const = 0;
signals:
	void			killRender();
protected:

	bool	m_useCropWindow;
	QColor	m_backColor;
	QRect	m_cropWindow;
};

class DZ_EXPORT DzRenderDataEvent : public QEvent {
public:
	DzRenderDataEvent( const DzRenderData &data );

	DzRenderData	getData() const;

private:

	DzRenderData	m_data;
};

#endif // DAZ_RENDER_HANDLER_H
