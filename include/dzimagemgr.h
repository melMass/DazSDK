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
	Defines the DzImageMgr class.
**/

#ifndef DAZ_IMAGE_MGR_H
#define DAZ_IMAGE_MGR_H

/*****************************
	Include files
*****************************/

#include <QtCore/QThread>
#include <QtCore/QHash>
#include <QtCore/QSize>

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class QImage;

class DzAppSettingsMgr;
class DzClassFactory;
class DzFileFilter;
class DzImageExporter;
class DzImageImporter;
class DzLayeredImage;
class DzLayeredTexture;
class DzRenderer;
class DzTexture;
class DzTexturePicker;
class DzUri;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzImageMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
	friend class DzTexture;
	friend class DzImageInternalClassFactory;
	friend class DzImageRequestThread;
private:
	//
	// CREATORS
	//

	DzImageMgr();
	~DzImageMgr();

public:

	bool	event( QEvent *e );

public slots:
	//
	// MANIPULATORS
	//

	DzError	loadImage( const QString &filename, QImage &img, int importerIdx = -1 );
	QImage	loadImage( const QString &filename );
	DzError	saveImage( const QString &filename, const QImage &image, int exporterIdx = -1 );

	DzError	loadLayeredImage( const QString &filename, DzLayeredImage *img, int importerIdx = -1 );
	DzError	saveLayeredImage( const QString &filename, const DzLayeredImage *image, int exporterIdx = -1 );

	void	setImageOpenPath( const QString &path );
	void	setImageSavePath( const QString &path );
	void	prepareAllImages( const DzRenderer *r );
	void	imagePrepared( const DzTexture *img, const QString &tempName );
	void	deleteUnusedTextureObjects();
	void	refresh();

	//
	// ACCESSORS
	//

	int			getNumImages() const;
	DzTexture*	getImage( int which ) const;
	DzTexture*	getImage( const QString &fullPath ) const;
	DzTexture*	findImage( const QString &fullPath ) const;
	DzTexture*	findImageByName( const QString &name ) const;

	DzLayeredTexture*	findLayeredTexture( const DzUri &uri ) const;
	DzLayeredTexture*	createLayeredTexture( const QString &name ) const;

	QString		getImageOpenPath() const;
	QString		getImageSavePath() const;

	QString		getUniqueImageName( const QString &name ) const;

	void		beginEditingImage( );
	void		finishedEditingImage( DzTexture *img );

	// Backward compatibility only
	bool		findLayerImageFiles( const QString &filename ) const;
	QString		findLayerImageFile( const QString &path, bool askUser ) const;
	
public:
	//
	// STATIC
	//

	static int	getNumImporters();
	static int	getNumExporters();
	static void	getImporterInfo( int i, QStringList &extensions,
					QString &description );
	static void	getExporterInfo( int i, QString &extension,
					QString &description );

	static DzImageImporter*	findImporter( const QString &filename );
	static DzImageExporter*	findExporter( const QString &filename );
	static int				findExporterIndex( const QString &filename );

	static void	makeImportFileFilter( DzFileFilter &filter,
					const QString &defaultFilter = QString::null,
					bool makeAllFilesEntry = true );
	static void	makeExportFileFilter( DzFileFilter &filter,
					const QString &defaultFilter = QString::null );

	static int				getNumTexturePickers();
	static QString			getTexturePickerDescription( int which );
	static DzTexturePicker*	getTexturePicker( int which );

	static bool		loadPngIcon( const QString &path, const QSize &size, QImage &image );
	static bool		loadRsrIcon( const QString &path, const QSize &size, QImage &image );

	void	requestPreviewIcon( QObject *toNotify, const QString &relativePath, int width, int height );
	void	requestAssetIcon( QObject *toNotify, const QString &fullPath, int width, int height );

	void	setAutoRefreshOn( bool onOff );
	void	toggleAutoRefresh();
	bool	isAutoRefreshOn() const;
	void	removeImage( DzTexture *img );

	QString	saveTemporaryImageToDataFolder( const QString &tempFilename, const QString &preferedName );

signals:

	void	imageListChanged();
	void	autoRefreshChanged( bool onOff );

protected:

	virtual void	timerEvent( QTimerEvent *e );
	static void		addClass( DzClassFactory *type );
	void			addImage( DzTexture *img );
	void			addImageToPrepCue( DzTexture *img );

private slots:

	void	startImagePrep();
	void	appStarted();
	void	pauseImagePrep();
	void	restartImagePrep();

private:
	struct DzImageRequest;

	DzTexture*		getNextPrepImage();
	
	bool			popImageRequest( DzImageRequest &data );
	void			pushImageRequest( const DzImageRequest &data );
	static QImage	generateImage( const QString &absPath, int width, int height );
	
	struct	Data;
	Data	*m_data;
};

inline uint qHash( const QSize &key )
{
	qint64 top = key.width();
	qint64 bottom = key.height();
	return ::qHash( (top<<32) + bottom ); 
}

class DZ_EXPORT DzImageRequestThread : public QThread
{
	Q_OBJECT
	friend class DzImageMgr;
	friend struct DzImageMgrData;
public:
	virtual void run();

signals:
	void imageIsReady( QImage image, QSize size, QString relPath );

private:
	DzImageRequestThread();
	virtual ~DzImageRequestThread();

	struct	Data;
	Data*	m_data;
};

#endif // DAZ_IMAGE_MGR_H
