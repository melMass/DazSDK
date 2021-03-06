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
	Defines the DzAssetIOMgr class.
**/

#ifndef DAZ_ASSET_IO_MGR_H
#define DAZ_ASSET_IO_MGR_H

/****************************
	Include files
****************************/

#include <QtCore/QObject>

#include "dzerrorcodes.h"
#include "dzuri.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzAssetExtraObjectIO;
class DzAssetIOFilter;
class DzFileIOSettings;
class DzClassFactory;
class DzFigure;
class DzFileLoadFilter;
class DzMorphDeltas;
class DzAssetDFormZoneIO;
class DzBase;

typedef DzTSharedPointer<DzAssetExtraObjectIO> DzAssetExtraObjectIOPtr;
/****************************
	Class definitions
****************************/

class DZ_EXPORT DzAssetIOMgr : public QObject {
	Q_OBJECT
	Q_ENUMS( DzOpenMethod )
#ifndef DSON_IO
	friend class DzApp;
#else
	friend class DzDSONIO;
#endif
private:
	//
	// CREATORS
	//

	DzAssetIOMgr();
	~DzAssetIOMgr();

public:

	enum	DzOpenMethod { DefaultMethod = 0, OpenNew, MergeFile };
	//
	// MANIPULATORS
	//

#ifndef DSON_IO
	DzError		doFigureLoad( const QString &filePath, DzFigure **figure );
#endif
	
	DzError		loadMorphDeltas( DzMorphDeltas *deltas );

	static void	registerExtraObjectIO( const QString &typeTag, QMetaObject const *ioMeta, QMetaObject const *classMeta );
	static bool	isExtraObjectIODerived( QMetaObject const *meta );

	static DzAssetExtraObjectIOPtr createExtraObjectReader( const QString &tag );
	static DzAssetExtraObjectIOPtr createExtraObjectWriter( QObject *object, QString &tag );
	static DzAssetExtraObjectIOPtr createExtraObjectIO( const QMetaObject *meta, QString &tag );
	static bool		hasExtraObjectWriter( QObject *object );
	static QString	getAutoDataFolder();

	template <class T> 
	static inline DzAssetExtraObjectIOPtr createSuperClassExtraObjectIO(){
		QString tag;
		return createExtraObjectIO(T::staticMetaObject.superClass(), tag);
	}

	static QObject*	findObjectInstance( const DzUri &uri );
	static DzUri	getAssetInstanceUri( DzBase *base );
	static QObject* createAssetFromDefinition( const DzUri &uri );
	static DzUri	getAssetDefinitionUri( DzBase *base );
	static bool		allowModifyAsset();
	static bool		isReadingOrWriting();
	static void		setAllowAssetModifiyDuringIO( bool setOnOff );
	static bool		isAllowingAssetModifiyDuringIO();
	
	


public slots:

	DzError	doLoad( const QString &filePath, DzOpenMethod open = DefaultMethod, DzFileLoadFilter *filter = NULL );
#ifndef DSON_IO
	DzError	doSave( int filterIndex );
	DzError	doSave( int filterIndex, QString &filePath, QString dir = QString::null, QString category = QString::null );
	DzError	doSave( DzAssetIOFilter *filter, QString &filePath, bool saveOnly, QString dir = QString::null,
				QString category = QString::null );
	DzError doSaveWithOptions( DzAssetIOFilter *filter, DzFileIOSettings *options, bool saveOnly=false,  
				const QString& filePath= QString::null, QString startingDir = QString::null, QString category = QString::null );
	DzError	doSceneSave( QString &filePath, QString category = QString::null);
	DzError	doSceneSaveAs();
	DzError	doSceneSaveAs(QString &filePath, QString startingDir = QString::null, QString category = QString::null);
#endif
	//
	// ACCESSORS
	//

	QString	getSavePath() const;
	QString	getLoadPath() const;

	QString			getDSONAssetCachePath() const;
	void			setDSONAssetCachePath( const QString &cacheFullPath );
	QString			getDefaultDSONAssetCachePath() const;

	//
	// STATIC
	//

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		getNumFilters();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	QString	getFilterName( int i );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzAssetIOFilter*	getFilter( int i );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		findFilter( const QString &className );

signals:

	void	assetImportStarting();
	void	assetImported();
	void	assetSaved();

protected:

	static void	addClass( DzClassFactory *type );

private:
#ifndef DSON_IO
	void createMetaDataAndThumbnail( DzAssetIOFilter * filter, const QString& filePath, const QString &category );
#endif

	struct	Data;
	Data	*m_data;
};

extern DZ_EXPORT DzAssetIOMgr *dzAssetIOMgr;


class DZ_EXPORT DzAssetAllowModifiyAssetHold {

public:

	DzAssetAllowModifiyAssetHold();
	~DzAssetAllowModifiyAssetHold();

	void releaseLock();

private:
	struct	Data;
	Data	*m_data;
};
#endif // DAZ_ASSET_IO_MGR_H
