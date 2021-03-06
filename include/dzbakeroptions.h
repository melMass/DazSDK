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
	Defines the DzBakerOptions class.
**/

#ifndef DAZ_BAKER_OPTIONS_H
#define DAZ_BAKER_OPTIONS_H

/*****************************
	Include files
*****************************/

#include "dzrenderoptions.h"

/****************************
	Forward declarations
****************************/

class DzMaterial;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBakerOptions : public DzRenderOptions {
	Q_OBJECT
	Q_ENUMS( BakerType )
	Q_PROPERTY( QString renderImgFilePath READ getRenderImgFilePath WRITE setRenderImgFilePath )
	Q_PROPERTY( QString imageType READ getImageType WRITE setImageType )
	Q_PROPERTY( bool autoBakeMode READ getAutoBakeMode WRITE setAutoBakeMode )
	Q_PROPERTY( int bakeMaterialsCount READ getBakeMaterialsCount )
	Q_PROPERTY( int curBakeMaterial READ getCurBakeMaterial WRITE setCurBakeMaterial )
	Q_PROPERTY( QString bakeMaterialName READ getBakeMaterialName )
	Q_PROPERTY( BakerType bakerType READ getBakerType WRITE setBakerType )
	Q_PROPERTY( bool bakeAsOneTexture READ getBakeAsOneTexture WRITE setBakeAsOneTexture )
	Q_PROPERTY( bool bakeSimultaneously READ getBakeSimultaneously WRITE setBakeSimultaneously )
	Q_PROPERTY( bool bakeNormalMap READ getBakeNormalMap WRITE setBakeNormalMap )

public:

	enum BakerType	{ Illumination = 0, Shader = 1, IllumShader = 2, None = 3 };

	//
	// CREATORS
	//

	DzBakerOptions();
	DzBakerOptions( const DzBakerOptions &opt );
	~DzBakerOptions();

	DzBakerOptions&	operator=( const DzBakerOptions &opt );

	//
	// MANIPULATORS
	//
	void	setBakerFilename( QString filename );
	void	setImageType( const QString &imagetype );
	void	setBakerType( BakerType type );
	void	setApplyToSurfaces(bool onOff );
	void	setRenderImgFilePath( QString path );
	void	setBucketSize( int size );
	void	setRenderOrder( QString order ); 
	void	setAutoBakeMode( bool autoBake );
	void	setCurBakeMaterial( int num );
	void	setBakeAsOneTexture( bool onoff );
	void	setBakeSimultaneously( bool onoff );
	void	setBakeNormalMap( bool onoff );

	void	copyFrom( const DzRenderOptions *opt );
	void	copyFrom( const DzBakerOptions *opt );

public slots:
	
	void	addBakeMaterialName( const QString &name );
	void	removeBakeMaterialName( const QString &name );
	bool	isABakeMaterial( const QString &name ) const;
	QString	getBakeMaterialName( int i ) const;
	void	clearBakeMaterials();

	void	applyChanges();
	void	resetOptions();
	void	setToDefaults();
	
	//
	// ACCESSORS
	//

public:

	QString			getBakerFilename() const;
	QString			getNormalBakerFilename() const;
	QString			getMaterialBakerFilename( const DzMaterial *material ) const;
	QString			getImageType() const;
	BakerType		getBakerType() const;
	QString			getBakerTypeString() const;
	bool			getApplyToSurfaces() const;
	QString			getRenderImgFilePath() const;
	int				getBucketSize() const;
	QString			getRenderOrder() const;
	bool			getAutoBakeMode() const;
	int				getBakeMaterialsCount() const;
	int				getCurBakeMaterial() const;
	QString			getBakeMaterialName() const;
	bool			getBakeAsOneTexture() const; 
	bool			getBakeSimultaneously() const; 
	bool			getBakeNormalMap() const; 

signals:

	void	imageTypeChanged( const QString &imagetype );
	void	bakerTypeChanged( DzBakerOptions::BakerType type );
	void	applyToSufaceChanged( bool onOff );

protected:
	QString getStoredSettingsPath() const;

private:

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BAKER_OPTIONS_H
