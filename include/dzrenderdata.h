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
	Defines the DzRenderData class.
**/

#ifndef DAZ_RENDER_DATA_H
#define DAZ_RENDER_DATA_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class QImage;
class QPainter;
class DzRenderBucket;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRenderData {
public:
	DzRenderData();
	DzRenderData( int x, int y, int w, int h );
	DzRenderData( int x, int y, int w, int h, unsigned char *imgData );
	DzRenderData( int x, int y, const QImage &img );
	DzRenderData( const DzRenderData &data );
	~DzRenderData();

	void	setPos( int x, int y );
	void	setX( int x );
	void	setY( int y );
	bool	create( int w, int h );

	DzRenderData&			operator=( const DzRenderData &data );

	unsigned char*			data();
	const unsigned char*	data() const;

	int		getWidth() const;
	int		getHeight() const;

	int		getX() const;
	int		getY() const;

	bool	copyToImage( QImage &img, int xOffset = 0, int yOffset = 0 ) const;
	bool	drawToPainter( QPainter &painter, int xOffset = 0, int yOffset = 0,
				bool useAlpha = false ) const;

private:
	bool	transferDataToImage( QImage &img, int xOffset, int yOffset, int maxW, int maxH ) const;

	DzRenderBucket	*m_bucket;
};

#endif // DAZ_RENDER_DATA_H