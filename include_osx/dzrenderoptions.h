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
	Defines the DzRenderOptions class.
**/

#ifndef DAZ_RENDER_OPTIONS_H
#define DAZ_RENDER_OPTIONS_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QSize;
class DzRenderer;
class DzTimeRange;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRenderOptions : public QObject {
	Q_OBJECT
	Q_ENUMS( RenderType )
	Q_ENUMS( RenderImgTarget )
	Q_ENUMS( RenderMovTarget )
	Q_ENUMS( RenderStyle )
	Q_ENUMS( PixelFilter )
	Q_PROPERTY( RenderImgTarget renderImgToId READ getRenderImgToId WRITE setRenderImgToId )
	Q_PROPERTY( RenderMovTarget renderMovToId READ getRenderMovToId WRITE setRenderMovToId )
	Q_PROPERTY( QString renderImgFilename READ getRenderImgFilename WRITE setRenderImgFilename )
	Q_PROPERTY( QString renderMovFilename READ getRenderMovFilename WRITE setRenderMovFilename )
	Q_PROPERTY( QString renderSerFilename READ getRenderSerFilename WRITE setRenderSerFilename )
	Q_PROPERTY( QString lastRenderImgFilename READ getLastRenderImgFilename )
	Q_PROPERTY( QString lastRenderMovFilename READ getLastRenderMovFilename )
	Q_PROPERTY( QString lastRenderSerFilename READ getLastRenderSerFilename )
	Q_PROPERTY( bool renderViewport READ renderViewport WRITE setRenderViewport )
	Q_PROPERTY( bool isAspectConstrained READ isAspectConstrained WRITE setAspectConstrain )
	Q_PROPERTY( double aspect READ getAspect )
	Q_PROPERTY( QSize imageSize READ getImageSize WRITE setImageSize )
	Q_PROPERTY( RenderType renderType READ renderType WRITE setRenderType )
	Q_PROPERTY( RenderStyle renderStyle READ getRenderStyle WRITE setRenderStyle )
	Q_PROPERTY( int rayTraceDepth READ rayTraceDepth WRITE setRayTraceDepth )
	Q_PROPERTY( int openGLPasses READ openGLPasses WRITE setOpenGLPasses )
	Q_PROPERTY( bool useGLSL READ useGLSL WRITE setUseGLSL )
	Q_PROPERTY( bool isCurrentFrameRender READ isCurrentFrameRender WRITE setRenderCurrentFrame )
	Q_PROPERTY( DzTime getStartTime READ getStartTime WRITE setStartTime ) //Deprecated, use startTime
	Q_PROPERTY( DzTime startTime READ getStartTime WRITE setStartTime )
	Q_PROPERTY( DzTime getEndTime READ getEndTime WRITE setEndTime ) //Deprecated, use endTime
	Q_PROPERTY( DzTime endTime READ getEndTime WRITE setEndTime )
	Q_PROPERTY( bool useMotionBlur READ useMotionBlur WRITE setUseMotionBlur )
	Q_PROPERTY( int motionBlurPct READ getMotionBlurPct WRITE setMotionBlurPct )
	Q_PROPERTY( int motionBlurSamples READ getMotionBlurSamples WRITE setMotionBlurSamples )
	Q_PROPERTY( double motionBlurOffset READ getMotionBlurOffset WRITE setMotionBlurOffset )
	Q_PROPERTY( int xPixelSamples READ getXPixelSamples WRITE setXPixelSamples )
	Q_PROPERTY( int yPixelSamples READ getYPixelSamples WRITE setYPixelSamples )
	Q_PROPERTY( int shadowSamples READ getShadowSamples WRITE setShadowSamples )
	Q_PROPERTY( double shadingRate READ getShadingRate WRITE setShadingRate )
	Q_PROPERTY( bool doubleSided READ getDoubleSided WRITE setDoubleSided )
	Q_PROPERTY( double gain READ getGain WRITE setGain )
	Q_PROPERTY( double gamma READ getGamma WRITE setGamma )
	Q_PROPERTY( PixelFilter pixelFilter READ getPixelFilter WRITE setPixelFilter )
	Q_PROPERTY( double xFilterWidth READ getXFilterWidth WRITE setXFilterWidth )
	Q_PROPERTY( double yFilterWidth READ getYFilterWidth WRITE setYFilterWidth )
	Q_PROPERTY( bool showPreview READ getShowPreview WRITE setShowPreview )
public:

	enum RenderType			{ ScreenShot = 0, HardwareAssisted = 1, Software = 2 };
	enum RenderImgTarget	{ ActiveView = 0, NewWindow = 1, DirectToFile = 2 };
	enum RenderMovTarget	{ MovieFile = 0, ImageSeries = 1 };
	enum RenderStyle		{ Normal = 0, Cartoon = 1 };
	enum PixelFilter		{ Box = 0, Triangle = 1, CatmullRom = 2, Gaussian = 3, Sinc = 4 };

	//
	// CREATORS
	//

	DzRenderOptions();
	virtual ~DzRenderOptions();

	//
	// MANIPULATORS
	//

	void	setRenderImgToId( RenderImgTarget tgt );
	void	setRenderMovToId( RenderMovTarget tgt );
	void	setRenderImgFilename( const QString &filename );
	void	setRenderMovFilename( const QString &filename );
	void	setRenderSerFilename( const QString &filename );
	void	setRenderViewport( bool onOff );
	void	setAspectConstrain( bool onOff );
	void	setImageSize( const QSize &size );
	void	setRenderCurrentFrame( bool onOff );
	void	setStartTime( DzTime time );
	void	setEndTime( DzTime time );
	void	setUseMotionBlur( bool onOff );
	void	setMotionBlurPct( int val );
	void	setMotionBlurOffset( double val );
	void	setRenderType( RenderType type );
	void	setRenderStyle( RenderStyle style );
	void	setRayTraceDepth( int val );
	void	setOpenGLPasses( int nPasses );
	void	setUseGLSL( bool onOff );
	void	setPixelSamples( int xSamples, int ySamples );
	void	setMotionBlurSamples(int samples);
	void	setXPixelSamples( int xSamples );
	void	setYPixelSamples( int ySamples );
	void	setShadowSamples( int samples );
	void	setShadingRate( double size );
	void	setDoubleSided( bool onOff );
	void	setGain( double gain );
	void	setGamma( double gamma );
	void	setPixelFilter( PixelFilter filter );
	void	setXFilterWidth( double width );
	void	setYFilterWidth( double width );
	void	setShowPreview(bool onoff);

	virtual void	copyFrom( const DzRenderOptions *opt );

public slots:

	void	setAspectRatio( float widthRatio, float heightRatio );
	
	virtual void	applyChanges();
	virtual void	resetOptions();
	virtual void	restoreDefaultSettings();
	virtual void	setToDefaults();

	//
	// ACCESSORS
	//

public:

	void			getPixelSamples( int &xSamples, int &ySamples ) const;
	void			getAspectRatio( float &widthRatio, float &heightRatio ) const;
	RenderImgTarget	getRenderImgToId() const;
	RenderMovTarget	getRenderMovToId() const;
	QString			getRenderImgFilename() const;
	QString			getRenderMovFilename() const;
	QString			getRenderSerFilename() const;
	QString			getLastRenderImgFilename() const;
	QString			getLastRenderMovFilename() const;
	QString			getLastRenderSerFilename() const;
	bool			renderViewport() const;
	bool			isAspectConstrained() const;
	double			getAspect() const;
	QSize			getImageSize() const;
	RenderType		renderType() const;
	RenderStyle		getRenderStyle() const;
	int				rayTraceDepth() const;
	int				openGLPasses() const;
	bool			useGLSL() const;
	bool			isCurrentFrameRender() const;
	DzTime			getStartTime() const;
	DzTime			getEndTime() const;
	bool			useMotionBlur() const;
	int				getMotionBlurPct() const;
	double			getMotionBlurOffset() const;
	int				getXPixelSamples() const;
	int				getMotionBlurSamples() const;
	int				getYPixelSamples() const;
	int				getShadowSamples() const;
	double			getShadingRate() const;
	bool			getDoubleSided() const;
	double			getGain() const;
	double			getGamma() const;
	PixelFilter		getPixelFilter() const;
	double			getXFilterWidth() const;
	double			getYFilterWidth() const;
	bool			getShowPreview() const;

signals:

	void	aspectChanged( double val );
	void	aspectChanged( float w, float h );
	void	renderImgTargetChanged( DzRenderOptions::RenderImgTarget id );
	void	renderMovTargetChanged( DzRenderOptions::RenderMovTarget id );
	void	renderImgFilenameChanged( const QString &filename );
	void	renderMovFilenameChanged( const QString &filename );
	void	renderSerFilenameChanged( const QString &filename );
	void	renderViewportChanged( bool onOff );
	void	aspectConstrainChanged( bool onOff );
	void	imageSizeChanged( const QSize &size );
	void	renderTypeChanged( DzRenderOptions::RenderType type );
	void	renderStyleChanged( DzRenderOptions::RenderStyle style );
	void	rayTraceDepthChanged( int depth );
	void	openGLPassesChanged( int passes );
	void	useGLSLChanged( bool onOff );
	void	renderCurrentFrameChanged( bool onOff );
	void	startTimeChanged( DzTime time );
	void	endTimeChanged( DzTime time );
	void	useMotionBlurChanged( bool onOff );
	void	motionBlurPctChanged( int pct );
	void	motionBlurOffsetChanged( double offset );
	void	motionBlurSamplesChanged(int samples );
	void	xPixelSamplesChanged( int samples );
	void	yPixelSamplesChanged( int samples );
	void	shadowSamplesChanged( int samples );
	void	shadingRateChanged( double rate );
	void	doubleSidedChanged( bool onOff );
	void	gainChanged( double gain );
	void	gammaChanged( double gamma );
	void	pixelFilterChanged( DzRenderOptions::PixelFilter filter );
	void	xFilterWidthChanged( double width );
	void	yFilterWidthChanged( double width );
	void	showPreviewChanged( bool onoff );
	void	settingsChanged();
	void	defaultsRestored();

protected:
	virtual QString getStoredSettingsPath() const;

private slots:

	void	startup();
	void	updateRange( const DzTimeRange &range );

private:

	void	checkRange();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_RENDER_OPTIONS_H
