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
	Defines the DzAsset class.
**/

#ifndef DAZ_ASSET_H
#define DAZ_ASSET_H

/*****************************
	Include files
*****************************/

#include "dzrefcounteditem.h"
#include "dztypes.h"

/*****************************
	Forward declare
*****************************/

class DzAbstractAssetContainer;
class DzAssetMetadata;
class DzDBContentInstanceTable;
class QIcon;
class QImage;
class QPixmap;
class QSize;
class QStyleOption;
class QUrl;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAsset : public QObject, public DzRefCountedItem 
{
	Q_PROPERTY( QVariant assetID READ getAssetID )
	Q_PROPERTY( QString assetName READ getAssetName )
	Q_PROPERTY( QPixmap icon READ getIconPixmap )
	Q_PROPERTY( QPixmap smallIcon READ getSmallIconPixmap )
	Q_PROPERTY( QString url READ getUrlString )
	Q_PROPERTY( QByteArray urlEncoded READ getUrlEncoded )
	Q_PROPERTY( QString companionPath READ getCompanionPath )
	Q_PROPERTY( bool hasCompanionScript READ hasCompanionScript )
	Q_PROPERTY( bool isNative READ isNative )
	Q_PROPERTY( bool isScript READ isScript )
	Q_OBJECT

public:
	DzAsset( DzAbstractAssetContainer *owner = NULL );
	DzAsset( const DzAsset *asset, DzAbstractAssetContainer *owner = NULL );
	virtual ~DzAsset();
	
	QString		getAssetName() const;
	void		setAssetName( const QString &name );

	QVariant	getAssetID() const;
	void		setAssetID( const QVariant &var );

	QPixmap		getIconPixmap() const;
	QPixmap		getSmallIconPixmap() const;	
	void		setIconImage( const QImage &icon );
	QIcon		getIcon();

	QByteArray	getUrlEncoded() const;
	QString		getUrlString() const;
	QUrl		getUrl() const;
	void		setUrl( const QUrl &url );

	bool		isNative() const;
	bool		isScript() const;
	bool		currentFileExists() const;
	bool		hasCompanion() const;
	bool		companionIsScript() const;
	bool		hasCompanionScript() const;  // keep for compatiblity
	QString		getCompanionPath() const;

	static void	setAssetImageCacheSize(int sizeInBytes);
	static void clearImageCache();

public slots:
	DzAssetMetadata*			getMetadata();
	DzAbstractAssetContainer*	getOwner() const;

	bool	rename( const QString &name );
	bool	loadDefaultIcon(bool delayLoad);

	int		getNumInstances();
	void	addInstance( DzDBContentInstanceTable *ins );

	DzDBContentInstanceTable*	getInstance( int index );
	DzDBContentInstanceTable*	getPriorityInstance();

	bool	removeInstance( int index );
	void	setPriority( int index );
	bool	prioritySet();

	QString	getAsLocalFile() const;
	QString	getRelativeFilePath();
	void	forceImageReload();

signals:
	void	assetImageChanged( DzAsset *asset );

private slots:
	void	imageReady(QImage image, QSize size, QString path);

private:
	void	updateFromInstance( DzDBContentInstanceTable *ins );

	QPixmap	decorateIconPixmap( const QPixmap &iconPixmap, const QStyleOption *option );

	static void		insertAssetImage( const QString &key, QImage *image );
	static void		removeAssetImage( const QString &key );
	static QImage*	getAssetImage( const QString &key );

	struct	Data;
	Data* m_data;
};

Q_DECLARE_METATYPE( DzAssetPtr );
Q_DECLARE_METATYPE( DzAssetList );

#endif // DAZ_ASSET_H
