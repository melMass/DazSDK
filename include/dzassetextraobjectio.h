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

#ifndef DAZ_ASSET_EXTRA_OBJECT_IO_H
#define DAZ_ASSET_EXTRA_OBJECT_IO_H

/****************************
	Include files
****************************/

#include <QtCore/QObject>

#include "dzassetjsonitem.h"
#include "dzerrorcodes.h"
#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzAssetOutFile;
class DzFileIOSettings;
class DzObject;
class DzSettings;
class IDzJsonIO;
class DzBase;
class DzGeometry;

/****************************
	Class definitions
****************************/
class DzAssetExtraObjectIO;
typedef DzTSharedPointer<DzAssetExtraObjectIO> DzAssetExtraObjectIOPtr;

class DZ_EXPORT DzAssetExtraObjectIO : public QObject, public DzRefCountedItem {
	Q_OBJECT
public:
	DzAssetExtraObjectIO();
	virtual ~DzAssetExtraObjectIO();

	virtual DzError writeExtraDefinition( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts ) const = 0;
	virtual DzError writeExtraInstance( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts ) const = 0;
	
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem *parentItem ) = 0;
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem *parentItem ) = 0;

	virtual DzError	applyDefinitionToObject( QObject *object, const DzFileIOSettings *opts ) const = 0;
	virtual DzError	applyInstanceToObject( QObject *object, const DzFileIOSettings *opts ) const = 0;
			
	virtual DzError resolveInstance( QObject *object, const DzFileIOSettings *opts ) const;
	virtual DzError finalizeInstance( QObject *object, const DzFileIOSettings *opts ) const;
	virtual bool shouldWrite( QObject *object, const DzFileIOSettings *opts ) const;

	QObject*	findObjectInstance( const DzUri &uri )const;
	DzUri		getAssetInstanceUri( DzBase *base )const;
	
	QObject*	createOwnedAsset( const DzUri &uri ) const;
	DzUri		getAssetDefinitionUri( DzBase *base ) const;

	virtual void getOwnedAssets(QObject *object, QList< IDzSceneAsset* > &assets);

	DzUri		getReadAssetUri()const;
	void		setReadAssetUri(const QString& fileUri, const QString& id);

private:
	struct Data;
	Data* m_data;
};

class DZ_EXPORT DzAssetExtraApplyToObjectIO : public DzAssetExtraObjectIO {
	Q_OBJECT
public:
	virtual ~DzAssetExtraApplyToObjectIO();
	virtual DzError	applyDefinitionToObject( QObject *object, const DzFileIOSettings *opts ) const;
};

class DZ_EXPORT DzExtraMaterialIO : public DzAssetExtraObjectIO {
	Q_OBJECT
public:
	virtual ~DzExtraMaterialIO();
	virtual void		setIncludeProperties( DzPropertyList *includeProps ) = 0;
	virtual DzMaterial*	createMaterial() const = 0;
	virtual bool		needToReplaceMaterial(const DzMaterial* currentMaterial);
};

class DZ_EXPORT DzExtraNodeIO : public DzAssetExtraObjectIO {
	Q_OBJECT
public:
	virtual ~DzExtraNodeIO();
	virtual DzNode*	createNode() const = 0;
};

class DZ_EXPORT DzExtraModifierIO : public DzAssetExtraObjectIO {
	Q_OBJECT
public:
	virtual ~DzExtraModifierIO();
	virtual DzModifier*	createModifier(const QString& name, DzObject *tgtObject)const=0;
};

class DZ_EXPORT DzExtraElementDataIO : public DzAssetExtraObjectIO {
	Q_OBJECT
public:
	virtual ~DzExtraElementDataIO();
	virtual DzElementData*	createDataItem(DzElement* element, const DzFileIOSettings *opts)const=0;
	virtual DzError writeExtraDefinition( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem *parentItem );
	virtual DzError applyDefinitionToObject( QObject *object, const DzFileIOSettings *opts )const;
};

class DZ_EXPORT DzExtraSceneDataIO : public DzAssetExtraObjectIO {
	Q_OBJECT
public:
	virtual ~DzExtraSceneDataIO();

	virtual DzSceneData*	createDataItem(const DzFileIOSettings *opts)const=0;
	virtual DzError writeExtraDefinition( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem *parentItem );
	virtual DzError applyDefinitionToObject( QObject *object, const DzFileIOSettings *opts )const;
};
typedef DzTSharedPointer<DzExtraSceneDataIO> DzExtraSceneDataIOPtr;

class DZ_EXPORT DzExtraGeometryIO : public DzAssetExtraObjectIO {
	Q_OBJECT
public:
	virtual ~DzExtraGeometryIO();

	virtual DzGeometry* createGeometry()const=0;
	virtual DzShape* createShape(DzGeometry*)const=0;
};



class DZ_EXPORT DzElementPropertyIOFilter
{
public:
	virtual ~DzElementPropertyIOFilter();
	virtual bool shouldWriteProperty( DzProperty *prop ) = 0;
};

class DZ_EXPORT DzElementPropertyValuesIO {
	friend class DzAssetElementPropertyValuesIO;
public:
	DzElementPropertyValuesIO();
	virtual ~DzElementPropertyValuesIO();

#ifndef DSON_IO
	static bool writeElementProperties( DzAssetOutFile *file, IDzJsonIO *io, DzElement *elem, DzElementPropertyIOFilter *filter = NULL );
	static bool writeProperties( DzAssetOutFile *file, IDzJsonIO *io, DzPropertyListIterator &propIt, DzElementPropertyIOFilter *filter );

	bool applyToElement( DzElement *elem, bool checkPrivateProperties, const DzFileIOSettings *opts ) const;
#endif
protected:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzElementPropertyValueIO {
	friend class DzAssetElementPropertyValueIO;
public:
	DzElementPropertyValueIO();
	virtual ~DzElementPropertyValueIO();

	static bool	writeProperty( DzAssetOutFile *file, IDzJsonIO *io, DzProperty *prop );
	static bool	writePropertyValue( DzAssetOutFile *file, IDzJsonIO *io, DzProperty *prop );

	QString	getPropertyName() const;
	bool	applyToProperty( DzProperty *prop, const DzFileIOSettings *opts ) const;
	void	setPropertyName( const QString &name );
protected:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzAssetElementPropertyValuesIO : public DzAssetJsonObject
{
public:
	DzAssetElementPropertyValuesIO(DzElementPropertyValuesIO *io, DzAssetJsonItem *parent);
	virtual ~DzAssetElementPropertyValuesIO();

	virtual DzAssetJsonItem*	startMemberObject( const QString &name );
	virtual DzAssetJsonItem*	startMemberArray( const QString &name );

	virtual bool	addMember( const QString &name, const QString &val );
	virtual bool	addMember( const QString &name, double val );
	virtual bool	addMember( const QString &name, bool val );
	virtual bool	addMemberNull( const QString &name );

	virtual void	finishObject( DzAssetJsonItem *item );
	virtual void	finishArray( DzAssetJsonItem *item );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzAssetElementPropertyValueIO : public DzAssetJsonObject
{
public:
	DzAssetElementPropertyValueIO(DzElementPropertyValueIO *io, DzAssetJsonItem *parent);
	virtual ~DzAssetElementPropertyValueIO();
	
	virtual DzAssetJsonItem*	startMemberObject( const QString &name );
	virtual DzAssetJsonItem*	startMemberArray( const QString &name );

	virtual bool	addMember( const QString &name, const QString &val );
	virtual bool	addMember( const QString &name, double val );
	virtual bool	addMember( const QString &name, bool val );
	virtual bool	addMemberNull( const QString &name );

	virtual void	finishObject( DzAssetJsonItem *item );
	virtual void	finishArray( DzAssetJsonItem *item );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzAssetSettingsIO : public DzAssetJsonObject
{
public:
	DzAssetSettingsIO( DzSettings *settings, DzAssetJsonItem *parent );
	virtual ~DzAssetSettingsIO();
	
	virtual DzAssetJsonItem*	startMemberObject( const QString &name );
	virtual DzAssetJsonItem*	startMemberArray( const QString &name );

	virtual bool	addMember( const QString &name, const QString &val );
	virtual bool	addMember( const QString &name, double val );
	virtual bool	addMember( const QString &name, bool val );
	virtual bool	addMemberNull( const QString &name );

	virtual void	finishObject( DzAssetJsonItem *item );
	virtual void	finishArray( DzAssetJsonItem *item );

protected:
	DzAssetSettingsIO( const QString &key, DzSettings *settings, DzAssetJsonItem *parent );

private:
	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzAssetSettingsValueArrayIO : public DzAssetJsonArray
{
public:
	DzAssetSettingsValueArrayIO(const QString& key, DzSettings *settings, DzAssetJsonItem *parent);
	virtual ~DzAssetSettingsValueArrayIO();
	
	virtual bool	addItem( const QString &val );
	virtual bool	addItem( double val );

private:
	struct Data;
	Data *m_data;
};

#endif // DAZ_ASSET_EXTRA_OBJECT_IO_H
