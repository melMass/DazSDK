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
	Defines the DzTexture class.
**/

#ifndef DAZ_TEXTURE_H
#define DAZ_TEXTURE_H

/*****************************
	Include files
*****************************/

#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class QImage;
class QPixmap;
class QSize;
class QRect;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTexture : public QObject, public DzRefCountedItem {
	Q_OBJECT
	friend class DzImageMgr;
protected:
	//
	// CREATORS
	//

	DzTexture( const QString &filename );
	virtual ~DzTexture();

public:

	//
	// MANIPULATORS
	//

	void	setTempFilename( const QString &filename );
	void	changeSource( const QString &filename );

	//
	// ACCESSORS
	//

	void	setGLTexture() const;
	void	setGLTransparency() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual void	refresh();

	//
	// ACCESSORS
	//

	QString	getFilename() const;
	QString	getTempFilename() const;
	QSize	getGLTextureSize() const;
	QSize	getGLAlphaTextureSize() const;
	QSize	getOriginalImageSize() const;
	QPixmap	getPreviewPixmap( int width, int height ) const;
	QPixmap	getPreviewPixmap( const QSize &size ) const;

	virtual bool	getImageData( QImage &image ) const;

signals:

	void	drawnDataChanged();
	void	tempFilenameChanged( const QString &filename );

protected slots:

	void	invalidate();

private:

	int		getOGLIndex() const;
	int		getOGLAlphaIndex() const;
	void	setGLImage( bool isAlpha ) const;
	void	createOpenGLTexture( bool isAlpha ) const;
	void	testTextureSize( int &width, int &height ) const;
	QImage	generateTransMap( QImage &image, int width, int height, int widthSkip, int heightSkip ) const;
	void	flattenAlpha( QImage &image ) const;
	QPixmap	generatePixmap( int width, int height ) const;

	struct	Data;
	Data	*m_data;
};

/*****************************
	Type definitions
*****************************/

typedef DzTSharedPointer<DzTexture>	DzTexturePtr;

/*****************************
	Related Functions
*****************************/

QImage	tileGLImages( const QList<QImage> &images, int nWidthImages, int nHeightImages );
void	copyPixels( QImage &dest, int dx, int dy, const QImage &src );

#endif // DAZ_TEXTURE_H
