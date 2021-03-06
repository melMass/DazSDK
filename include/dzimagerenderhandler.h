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
	Defines the DzImageRenderHandler class.
**/

#ifndef DAZ_IMAGE_RENDER_HANDLER_H
#define DAZ_IMAGE_RENDER_HANDLER_H

/*****************************
	Include files
*****************************/

#include "dzrenderhandler.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzImageRenderHandler : public DzRenderHandler {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzImageRenderHandler( const QSize &size, DzTime renderTime, const QString &filename );
	DzImageRenderHandler( const QSize &size, DzTime startingTime, int numFrames,
							const QString &filename, bool isMovie );
	virtual ~DzImageRenderHandler();

	virtual void	passData( const DzRenderData &data );

public slots:
	void	setCreateThumbnail(bool createThumb);
	bool	getCreateThumbnail();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	beginRender();
	virtual void	finishRender();
	virtual void	beginFrame( int frame );
	virtual void	finishFrame();

	virtual QSize	getSize() const;
	virtual DzTime	getStartingTime() const;
	virtual int		getNumFrames() const;

private:
	void	saveRender( const QString &filename, bool isMovie, bool warnOnFail );

	QString	frameNumberString() const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_IMAGE_RENDER_HANDLER_H
