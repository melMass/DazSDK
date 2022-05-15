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
	Defines the interface for scene assets.
**/

#ifndef I_DZ_SCENE_ASSET_H
#define I_DZ_SCENE_ASSET_H

/*****************************
	Include files
*****************************/

#include "dzclassfactory.h"

/*****************************
	Forward declarations
*****************************/

class DzAuthor;
class DzInFile;
class DzOutFile;
class DzSceneAssetFileInfoData;
class DzUri;
class DzVersion;

struct DzSceneAssetData;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSceneAssetFileInfo {
	friend class DzSceneAsset;
public:
	DzSceneAssetFileInfo( const DzSceneAssetFileInfo &info );
	DzSceneAssetFileInfo( DzSceneAssetFileInfoData *data );
	~DzSceneAssetFileInfo();

	DzUri		getUri() const;
	DzAuthor	getContributor() const;
	DzVersion	getRevision() const;
	QDateTime	getModifiedDate() const;
	
	DzSceneAssetFileInfo&	operator=( const DzSceneAssetFileInfo &info );
	void		copyDataTo(DzSceneAssetFileInfoData *data)const;

private:
	DzSceneAssetFileInfoData	*m_data;
};

class DZ_EXPORT IDzSceneAsset {
public:
	enum AssetType { GeometryAsset, NodeAsset, UVSetAsset, ModifierAsset, MaterialAsset, TextureAsset, SceneAsset };

	virtual bool					modifyAsset() = 0;
	virtual bool					modifyAsset( const DzUri &newUri ) = 0;
	virtual void					assetLoaded() = 0;
	virtual void					assetSaved() = 0;

	virtual QString					getAssetId() const = 0;
	virtual bool					matchesAssetId(const QString& assetID, bool checkSource) const=0;
	virtual void					setAssetId(const QString& assetID) = 0;
	virtual DzUri					getAssetUri() const = 0;
	virtual AssetType				getAssetType() const = 0;
	virtual bool					assetNeedSave() const = 0;
	virtual DzSceneAssetFileInfo	getAssetFileInfo() const = 0;
	virtual const QObject*			toQObject() const = 0;
	virtual QObject*				toQObject() = 0;
	virtual DzUri					getSource() const = 0;
	virtual int						getFallBackOffset()const=0;
	virtual void					setFallBackOffset(int offset)=0;

protected:
//signals:  This should be implemented as a signal.
	virtual void assetModified()=0;
	virtual void assetWasSaved()=0;

protected:
	virtual ~IDzSceneAsset();
};

Q_DECLARE_METATYPE( IDzSceneAsset* )
Q_DECLARE_INTERFACE( IDzSceneAsset, "IDzSceneAsset" )

class DZ_EXPORT DzSceneAsset : public IDzSceneAsset {
	friend struct DzSceneAssetData;
protected:
	DzSceneAsset();
	~DzSceneAsset();

#ifndef DSON_IO
	bool	loadAssetSection( DzInFile *file, short sectionID );
	void	saveAsset( DzOutFile *file ) const;
#endif

public:
	virtual bool					modifyAsset();
	virtual bool					modifyAsset( const DzUri &newUri );
	virtual void					assetLoaded();
	virtual void					assetSaved();
	virtual DzUri					getAssetUri() const;
	virtual bool					assetNeedSave() const;
	virtual DzSceneAssetFileInfo	getAssetFileInfo() const;
	virtual QString					getAssetId() const;
	virtual bool					matchesAssetId(const QString& assetID, bool checkSource) const;
	virtual void					setAssetId(const QString& assetID);
	virtual DzUri					getSource() const;
	virtual int						getFallBackOffset()const;
	virtual void					setFallBackOffset(int offset);

private:
	static DzSceneAssetFileInfoData*		getFileInfoData(const DzSceneAssetFileInfo* info);
	static const DzSceneAssetFileInfoData*	getConstFileInfoData(const DzSceneAssetFileInfo* info);
	DzSceneAssetData	*m_data;
};

#endif // I_DZ_SCENE_ASSET_H