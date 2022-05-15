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
	Defines the DzTextureLayer class.
**/

#ifndef DAZ_TEXTURE_LAYER_H
#define DAZ_TEXTURE_LAYER_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class DzLayeredTexture;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTextureComponent : public QObject {
	Q_OBJECT
	Q_ENUMS( Rotation )
	Q_PROPERTY( bool enabled READ isEnabled WRITE setEnabled )
	Q_PROPERTY( bool flippedHorizontal READ isFlippedHorizontal WRITE flipHorizontal )
	Q_PROPERTY( bool flippedVertical READ isFlippedVertical WRITE flipVertical )
	Q_PROPERTY( bool invert READ isInverted WRITE invert )
	Q_PROPERTY( float opacity READ getOpacity WRITE setOpacity )
	Q_PROPERTY( float xScale READ getXScale WRITE setXScale )
	Q_PROPERTY( float yScale READ getYScale WRITE setYScale )
	Q_PROPERTY( QColor color READ getColor WRITE setColor )
	Q_PROPERTY( QPoint offset READ getOffset WRITE setOffset )
	Q_PROPERTY( int xOffset READ getXOffset WRITE setXOffset )
	Q_PROPERTY( int yOffset READ getYOffset WRITE setYOffset )
	Q_PROPERTY( Rotation rotation READ getRotation WRITE setRotation )
	friend class DzLayeredTexture;
public:

	enum Rotation { RotNone = 0, Rot90 = 90, Rot180 = 180, Rot270 = 270 };

	DzTextureComponent();
	virtual ~DzTextureComponent();

	void	setEnabled( bool onOff );
	bool	isEnabled() const;

	void	setLabel( const QString &label );
	QString	getLabel() const;

	void	setColor( const QColor &color );
	QColor	getColor() const;

	void	setImage( const QString &filename );
	QString	getImage() const;

	void	flipHorizontal( bool onOff = true );
	void	flipVertical( bool onOff = true );
	bool	isFlippedHorizontal() const;
	bool	isFlippedVertical() const;

	void	invert( bool onOff = true );
	bool	isInverted() const;

	void	setOffset( const QPoint &pnt );
	void	setXOffset( int val );
	void	setYOffset( int val );
	QPoint	getOffset() const;
	int		getXOffset() const;
	int		getYOffset() const;

	void	setScale( float xScale, float yScale );
	void	setXScale( float scale );
	void	setYScale( float scale );
	float	getXScale() const;
	float	getYScale() const;

	void	setOpacity( float val );
	float	getOpacity() const;

	void		setRotation( Rotation rotation );
	Rotation	getRotation() const;

	bool	getImageData( QImage &image ) const;

public slots:

	void	flip( bool horizontal, bool vertical );

	virtual void	copyFrom( const DzTextureComponent *comp );

signals:

	void	dataChanged();
	void	enabledChanged( bool onOff );
	void	labelChanged( const QString &label );
	void	colorChanged( const QColor &color );
	void	imageChanged( const QString &filename );
	void	flippedHorizontalChanged( bool onOff );
	void	flippedVerticalChanged( bool onOff );
	void	invertedChanged( bool onOff );
	void	offsetChanged( const QPoint &offset );
	void	scaleChanged( float x, float y );
	void	opacityChanged( float opacity );
	void	rotationChanged( DzTextureComponent::Rotation rotation );

protected:

	void	beginEditing();
	void	endEditing();

	void	rotate90( QImage &image ) const;
	void	rotate180( QImage &image ) const;
	void	rotate270( QImage &image ) const;

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzTextureMask : public DzTextureComponent {
	Q_OBJECT
	friend class DzTextureLayer;
public:

	DzTextureMask();
	virtual ~DzTextureMask();
};

class DZ_EXPORT DzTextureLayer : public DzTextureComponent {
	Q_OBJECT
	Q_ENUMS( BlendMode )
	Q_PROPERTY( BlendMode blendMode READ getBlendMode WRITE setBlendMode )
	friend class DzLayeredTexture;
public:

	enum BlendMode { BlendAlpha, BlendAdd, BlendSubtract, BlendMultiply };

	DzTextureLayer();
	virtual ~DzTextureLayer();

	virtual void	copyFrom( const DzTextureComponent *comp );

	void		setBlendMode( BlendMode mode );
	BlendMode	getBlendMode() const;

public slots:

	void			setMask( DzTextureMask *mask );
	DzTextureMask*	getMask() const;

signals:

	void	blendModeChanged( DzTextureLayer::BlendMode mode );
	void	aboutToChangeMask( DzTextureMask *oldMask, DzTextureMask *newMask );
	void	maskChanged( DzTextureMask *oldMask, DzTextureMask *newMask );

protected:

	bool	apply( QImage &image );

private:

	bool	blendImage( QImage &dest, const QImage &src, float mask );
	bool	blendImage( QImage &dest, const QImage &src, const QImage &mask );
	bool	blendColor( QImage &dest, float mask );
	bool	blendColor( QImage &dest, const QImage &mask );

	void	alphaBlend( QRgb &dest, QRgb src, float mask );
	void	addBlend( QRgb &dest, QRgb src, float mask );
	void	subBlend( QRgb &dest, QRgb src, float mask );
	void	multBlend( QRgb &dest, QRgb src, float mask );

	float	calcMaskVal( QRgb mask );
};

#endif // DAZ_IMAGE_LAYER_H
