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
	Defines the DzRenderView class.
**/

#ifndef DAZ_RENDER_VIEW_H
#define DAZ_RENDER_VIEW_H

/*****************************
	Include files
*****************************/

#include "dzview.h"

/****************************
	Forward declarations
****************************/

class DzViewport;
class DzRenderData;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRenderView : public DzView {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzRenderView( DzViewport *viewport, int xOffset, int yOffset, const QString &name = QString::null );
	virtual ~DzRenderView();

	virtual QString	getDescription() const;
	virtual QPixmap	getIcon() const;

	void	beginFrame();
	void	finishFrame();
	void	passData( const DzRenderData &data );

protected:

	virtual void	paintEvent( QPaintEvent *event );
	virtual void	mousePressEvent( QMouseEvent *e );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_RENDER_VIEW_H
