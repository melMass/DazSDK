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
	Defines the DzAssetJsonItem class.
**/

#ifndef DAZ_ASSET_JSON_ITEM_H
#define DAZ_ASSET_JSON_ITEM_H

/****************************
	Include files
****************************/

#include "dzuri.h"
#include "dzversion.h"

/****************************
	Forward declarations
****************************/

class DzAssetFile;
class DzSceneAssetFileInfo;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzAssetJsonItem {
public:
	DzAssetJsonItem( DzAssetFile &file );
	virtual ~DzAssetJsonItem();

	virtual DzAssetJsonItem*	startMemberObject( const QString &name );
	virtual DzAssetJsonItem*	startMemberArray( const QString &name );

	virtual DzAssetJsonItem*	startObject();
	virtual DzAssetJsonItem*	startArray();

	virtual void	finishObject( DzAssetJsonItem *item );
	virtual void	finishArray( DzAssetJsonItem *item );

	virtual bool	addMember( const QString &name, const QString &val );
	virtual bool	addMember( const QString &name, double val );
	virtual bool	addMember( const QString &name, bool val );
	virtual bool	addMemberNull( const QString &name );

	virtual bool	addItem( const QString &val );
	virtual bool	addItem( double val );
	virtual bool	addItem( bool val );
	virtual bool	addItemNull();

	virtual bool	isObject() const = 0;
	virtual bool	isArray() const = 0;

	virtual bool	skipObject();
	virtual bool	skipArray();

	DzUri			makeUri( const QString &uriStr ) const;
	
	DzVersion		getFileVersion()const;
	QString			getFileType()const;
	bool			getIsFilePreset()const;
	DzSceneAssetFileInfo*	getSceneAssetFileInfo()const;
	DzAssetFile&	getFile()const;

protected:

	void			warning( const QString &msg );
	void			error( const QString &msg );
	
	DzAssetFile		&m_file;
};

class DZ_EXPORT DzAssetJsonObject : public DzAssetJsonItem {
public:
	DzAssetJsonObject( DzAssetFile &file );
	virtual ~DzAssetJsonObject();

	virtual bool	isObject() const;
	virtual bool	isArray() const;
};

class DZ_EXPORT DzAssetJsonArray : public DzAssetJsonItem {
public:
	DzAssetJsonArray( DzAssetFile &file );
	virtual ~DzAssetJsonArray();

	virtual bool	isObject() const;
	virtual bool	isArray() const;
};

class DZ_EXPORT DzAssetJsonNullObject : public DzAssetJsonObject {
public:
	DzAssetJsonNullObject( DzAssetFile &file );
	virtual ~DzAssetJsonNullObject();

	virtual DzAssetJsonItem*	startMemberObject( const QString &name );
	virtual DzAssetJsonItem*	startMemberArray( const QString &name );

	virtual bool	addMember( const QString &name, const QString &val );
	virtual bool	addMember( const QString &name, double val );
	virtual bool	addMember( const QString &name, bool val );
	virtual bool	addMemberNull( const QString &name );
	virtual bool	skipObject();
};

class DZ_EXPORT DzAssetJsonNullArray : public DzAssetJsonArray {
public:
	DzAssetJsonNullArray( DzAssetFile &file );
	virtual ~DzAssetJsonNullArray();

	virtual DzAssetJsonItem*	startObject();
	virtual DzAssetJsonItem*	startArray();

	virtual bool	addItem( const QString &val );
	virtual bool	addItem( double val );
	virtual bool	addItem( bool val );
	virtual bool	addItemNull();
	virtual bool	skipArray();
};

#endif // DAZ_ASSET_JSON_ITEM_H
