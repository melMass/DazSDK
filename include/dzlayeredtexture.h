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

#ifndef DAZ_LAYERED_TEXTURE_H
#define DAZ_LAYERED_TEXTURE_H

/*****************************
	Include files
*****************************/

#include "dztexture.h"
#include "dztypes.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzTextureLayer;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLayeredTexture : public DzTexture, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	Q_PROPERTY( QSize size READ getSize WRITE setSize )
	friend class DzImageMgr;
protected:
	//
	// CREATORS
	//

	DzLayeredTexture( const QString &name, const QString &path );
	~DzLayeredTexture();

public:

	virtual AssetType		getAssetType() const;
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();

	virtual bool	getImageData( QImage &image ) const;
	bool					isSavedToTemp();

	DzTextureLayerListIterator	textureLayerIterator() const;

	void	setSize( const QSize &size );
	QSize	getSize() const;

	void	setSourceDSI(const QString& path);

public slots:

	int		getNumLayers() const;

	bool	removeLayer( int index );
	bool	removeLayer( DzTextureLayer *layer );
	void	removeAllLayers();
	void	addLayer( DzTextureLayer *layer );
	void	insertLayer( int index, DzTextureLayer *layer );
	bool	moveLayer( int fromIndex, int toIndex );
	bool	replaceLayer( DzTextureLayer *oldLayer, DzTextureLayer *newLayer );
	int		findLayer( DzTextureLayer *layer ) const;


	DzTextureLayer*	getLayer( int index ) const;
	DzTextureLayer*	takeLayer( int index );

	void	beginEditing();
	void	endEditing();
	void	copyFrom( const DzLayeredTexture *texture );

	QString	getSourceDSI()const;

signals:

	void	assetModified();
	void	assetWasSaved();

	void	layerListChanged();
	void	aboutToRemoveLayers( int index, int count );
	void	layersRemoved( int index, int count );
	void	aboutToInsertLayers( int index, int count );
	void	layersInserted( int index, int count );
	void	sizeChanged( const QSize &size );

private:

	struct	Data;
	Data	*m_data;
};

/*****************************
	Type definitions
*****************************/

typedef DzTSharedPointer<DzLayeredTexture>	DzLayeredTexturePtr;

#endif // DAZ_LAYERED_TEXTURE_H
