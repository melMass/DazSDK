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
	Defines the DzPlugin class.
**/

#ifndef DAZ_PLUGIN_H
#define DAZ_PLUGIN_H

/*****************************
	Include files
*****************************/

#include "dzversion.h"
#include "dzclassfactory.h"
#include "dzregistration.h"
#include "dzactivationpolicy.h"

/*****************************
	Type definitions
*****************************/

typedef QListIterator<DzClassFactory*> DzClassFactoryIterator;

/****************************
	Forward declarations
****************************/

class DzClassFactory;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPlugin : public QObject {
	Q_OBJECT
	friend class DzPluginMgr;
	friend class DzPluginHelper;
	friend class DzPluginsWizardFrame;
public:

	enum	Status { Loaded, RequiresRestart, ManuallyDisabled, EvaluationInvalid, Failed };

	DzPlugin( const QString &name, const QString &author = QString::null,
			const QString &desription = QString::null, unsigned short major = 0,
			unsigned short minor = 0, unsigned short rev = 0, unsigned short build = 0 );
	virtual ~DzPlugin();

	//
	// MANIPULATORS
	//

	void	addClassFactory( DzClassFactory *factory );
	void	addIOClassRegistration( const QString& typeTag, QMetaObject const* ioMeta, QMetaObject const* classMeta );

	//
	// ACCESSORS
	//

	DzClassFactoryIterator getFactories() const;
	void	registerAssetIOClasses() const;

public slots:

	QString		getName() const;
	QString		getDescription() const;
	QString		getAuthor() const;
	DzVersion	getVersion() const;
	QString		getVersionString() const;
	QString		getFilename() const;
	bool		isRegistered() const;
	bool		isActivated() const;
	QString		getEvaluationInformation() const;
	bool		validateSerialNumber( const QString &serialNumber, bool saveIfValid ) const;
	DzPlugin::Status	getStatus() const;
	QString		getStatusString() const;
	QString		getStatusInformation() const;
	QIcon		getStatusIcon() const;
	bool		getLoadOnStart() const;

protected:

	virtual void	startup();
	virtual void	shutdown();
	void			setFileName( const QString &filename );
	void			setDescription( const QString &description );
	void			setAuthor( const QString &author );
	void			setVersion( unsigned short major, unsigned short minor, unsigned short rev, unsigned short build );
	void			setActivationPolicy( const DzGuid &guid, DzActivationPolicy *policy );
	void			addRegistrationPrefix( const QString &prefix, const QString &version, const QString &description );
	DzRegistration&	getRegistration() const;
	void			setStatus( Status status, const QString &information );
	void			setLoadOnStart( bool load );
private:
	struct	Data;
	Data	*m_data;
};

class DzPluginHelper {
protected:
	DzPluginHelper( DzPlugin *plugin ) : m_plugin( plugin ) { }

	void	setDescription( const QString &str ) { m_plugin->setDescription( str ); }
	void	setAuthor( const QString &str ) { m_plugin->setAuthor( str ); }
	void	setVersion( unsigned short major, unsigned short minor, unsigned short rev, unsigned short build ) { m_plugin->setVersion( major, minor, rev, build ); }
	void	setActivationPolicy( const DzGuid &guid, DzActivationPolicy *policy ) { m_plugin->setActivationPolicy( guid, policy ); }
	void	addRegistrationPrefix( const QString &prefix, const QString &version, const QString &description ) { m_plugin->addRegistrationPrefix( prefix, version, description ); }

private:
	DzPlugin	*m_plugin;
};

/*****************************
	Macros
*****************************/

#ifndef Q_MOC_RUN

// Macros for defining plug-in exports
// This installs the DllMain function that Windows requires for plug-ins.
#ifdef Q_OS_WIN32

#include <windows.h>

#define DZ_PLUGIN_DEFINITION( pluginName ) \
BOOL WINAPI DllMain( HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved )	\
{	\
	switch( fdwReason ) {		\
	case DLL_PROCESS_ATTACH:	\
		break;					\
	case DLL_THREAD_ATTACH:		\
		break;					\
	case DLL_THREAD_DETACH:		\
		break;					\
	case DLL_PROCESS_DETACH:	\
		break;					\
	}							\
	return TRUE;				\
} \
 \
static DzPlugin s_pluginDef( pluginName ); \
__declspec(dllexport) DzVersion getSDKVersion() { return DZ_SDK_VERSION; } \
__declspec(dllexport) DzPlugin *getPluginDefinition() { return &s_pluginDef; }

#define DZ_CUSTOM_PLUGIN_DEFINITION( pluginClass ) \
BOOL WINAPI DllMain( HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved )	\
{	\
	switch( fdwReason ) {		\
	case DLL_PROCESS_ATTACH:	\
		break;					\
	case DLL_THREAD_ATTACH:		\
		break;					\
	case DLL_THREAD_DETACH:		\
		break;					\
	case DLL_PROCESS_DETACH:	\
		break;					\
	}							\
	return TRUE;				\
} \
 \
static pluginClass s_pluginDef; \
__declspec(dllexport) DzVersion getSDKVersion() { return DZ_SDK_VERSION; } \
__declspec(dllexport) DzPlugin *getPluginDefinition() { return &s_pluginDef; }
#else

#define DZ_PLUGIN_DEFINITION( pluginName ) \
static DzPlugin s_pluginDef( pluginName ); \
extern "C" DzVersion getSDKVersion() { return DZ_SDK_VERSION; } \
extern "C" DzPlugin *getPluginDefinition() { return &s_pluginDef; }

#define DZ_CUSTOM_PLUGIN_DEFINITION( pluginClass ) \
static pluginClass s_pluginDef; \
extern "C" DzVersion getSDKVersion() { return DZ_SDK_VERSION; } \
extern "C" DzPlugin *getPluginDefinition() { return &s_pluginDef; }
#endif

#define DZ_PLUGIN_AUTHOR( author ) \
class DzPluginAuthor : public DzPluginHelper { \
public: \
	DzPluginAuthor( const QString &str ) : DzPluginHelper( &s_pluginDef ) \
		{ setAuthor( str ); } \
}; \
static DzPluginAuthor s_pluginAuthor( author );

#define DZ_PLUGIN_DESCRIPTION( description ) \
class DzPluginDesc : public DzPluginHelper { \
public: \
	DzPluginDesc( const QString &str ) : DzPluginHelper( &s_pluginDef ) \
		{ setDescription( str ); } \
}; \
static DzPluginDesc s_pluginDesc( description );

#define DZ_PLUGIN_VERSION( verMajor, verMinor, verRev, verBuild ) \
class DzPluginVersion : public DzPluginHelper { \
public: \
	DzPluginVersion( unsigned short major, unsigned short minor, unsigned short rev, unsigned short build ) : \
		DzPluginHelper( &s_pluginDef ) \
	{ setVersion( major, minor, rev, build ); } \
}; \
static DzPluginVersion s_pluginVersion( verMajor, verMinor, verRev, verBuild );


/*Standard exported plug-in class.*/
#define DZ_PLUGIN_CLASS_GUID_OWNED( typeName, guid, scriptOwnership ) \
Q_DECLARE_METATYPE(typeName*) \
static DzGuid	typeName##GUID( DzGuid::fromString( #guid ) ); \
class typeName##Factory : public DzTClassFactory<typeName> { \
public: \
	typeName##Factory() : DzTClassFactory<typeName>( typeName##GUID , scriptOwnership ) { \
		s_pluginDef.addClassFactory( this ); \
	} \
}; \
 \
static typeName##Factory typeName##ClassFactory;

/*Used for classes that wish to take arguments in their script constructors*/
#define DZ_PLUGIN_CUSTOM_CLASS_GUID_OWNED( typeName, guid, scriptOwnership ) \
Q_DECLARE_METATYPE(typeName*) \
static DzGuid	typeName##GUID( DzGuid::fromString( #guid ) ); \
class typeName##Factory : public DzTClassFactory<typeName> { \
public: \
	typeName##Factory() : DzTClassFactory<typeName>( typeName##GUID , scriptOwnership ) { \
		s_pluginDef.addClassFactory( this ); \
	} \
	virtual QObject*	createInstance( const QVariantList &args ) const;\
	virtual QObject*	createInstance() const;\
}; \
 \
static typeName##Factory typeName##ClassFactory;

/*Standard exported plug-in class.*/
#define DZ_PLUGIN_CLASS_GUID( typeName, guid )\
	DZ_PLUGIN_CLASS_GUID_OWNED( typeName,guid,QScriptEngine::QtOwnership )

#define DZ_PLUGIN_CUSTOM_CLASS_GUID( typeName, guid )\
	DZ_PLUGIN_CUSTOM_CLASS_GUID_OWNED( typeName,guid,QScriptEngine::QtOwnership )


/*Used to declare classes that can be used in script, but not created in script.*/
#define DZ_PLUGIN_ABSTRACT_CLASS_GUID( typeName, guid ) \
Q_DECLARE_METATYPE(typeName*) \
static DzGuid	typeName##GUID( DzGuid::fromString( #guid ) ); \
class typeName##Factory : public DzTCustomClassFactory<typeName> { \
public: \
	typeName##Factory() : DzTCustomClassFactory<typeName>( typeName##GUID ) { \
		s_pluginDef.addClassFactory( this ); \
	} \
	virtual QObject*	createInstance( const QVariantList &args ) const {return NULL;}\
	virtual QObject*	createInstance() const { return NULL; }\
}; \
 \
static typeName##Factory typeName##ClassFactory;

/*Deprecated used only for old classes, use DZ_PLUGIN_CUSTOM_CLASS_GUID instead*/
#define DZ_PLUGIN_CUSTOM_CLASS_FACTORY( typeName, classID ) \
Q_DECLARE_METATYPE(typeName*) \
class typeName##Factory : public DzTClassFactory<typeName> { \
public: \
	typeName##Factory() : DzTClassFactory<typeName>( classID ) { \
		s_pluginDef.addClassFactory( this ); \
	} \
	virtual QObject*	createInstance( const QVariantList &args ) const;\
	virtual QObject*	createInstance() const;\
}; \
 \
static typeName##Factory typeName##ClassFactory;

/*Deprecated used only for old classes, use DZ_PLUGIN_CLASS_GUID instead*/
#define DZ_PLUGIN_CLASS_FACTORY( typeName, classID ) \
Q_DECLARE_METATYPE(typeName*) \
class typeName##Factory : public DzTClassFactory<typeName> { \
public: \
	typeName##Factory() : DzTClassFactory<typeName>( classID ) { \
		s_pluginDef.addClassFactory( this ); \
	} \
}; \
 \
static typeName##Factory typeName##ClassFactory;


#define DZ_PLUGIN_ACTIVATION_POLICY( guid, activationPolicy ) \
static DzGuid	s_pluginGUID( DzGuid::fromString( #guid ) ); \
class DzPluginActivation : public DzPluginHelper { \
public: \
	DzPluginActivation( DzActivationPolicy *policy ) : DzPluginHelper( &s_pluginDef ) \
		{ setActivationPolicy( s_pluginGUID, policy ); } \
}; \
static DzPluginActivation s_pluginActivation( activationPolicy );

#define DZ_PLUGIN_REGISTRATION_PREFIX( prefix, version, description ) \
class prefix##Registrar : public DzPluginHelper { \
public: \
	prefix##Registrar( const QString &prefixStr, const QString &versStr, const QString &descStr ) : DzPluginHelper( &s_pluginDef ) \
		{ addRegistrationPrefix( prefixStr, versStr, descStr ); } \
}; \
static prefix##Registrar prefix##ClassRegistrar( #prefix, version, description );


#define DZ_PLUGIN_REGISTER_EXTRA_OBJECT_READER(  prefix, tag, ioClass ) \
struct ioClass##AssetExtraObjectIORegistar { \
public: \
	ioClass##AssetExtraObjectIORegistar() \
		{ s_pluginDef.addIOClassRegistration( QString(prefix) + QString(tag), &ioClass::staticMetaObject, NULL); } \
}; \
static ioClass##AssetExtraObjectIORegistar ioClass##AssetExtraObjectIORegistarInstance;

#define DZ_PLUGIN_REGISTER_EXTRA_OBJECT_IO( prefix, tag, ioClass, itemClass ) \
struct ioClass##AssetExtraObjectIORegistar { \
public: \
	ioClass##AssetExtraObjectIORegistar() \
		{ s_pluginDef.addIOClassRegistration( QString(prefix) + QString(tag), &ioClass::staticMetaObject, &itemClass::staticMetaObject); } \
}; \
static ioClass##AssetExtraObjectIORegistar ioClass##AssetExtraObjectIORegistarInstance;

#define DZ_PLUGIN_REGISTER_MATERIAL_EXTRA_OBJECT_IO( tag, ioClass, itemClass ) \
	DZ_PLUGIN_REGISTER_EXTRA_OBJECT_IO( "studio/material/", tag, ioClass, itemClass );

#define DZ_PLUGIN_REGISTER_NODE_EXTRA_OBJECT_IO( tag, ioClass, itemClass ) \
	DZ_PLUGIN_REGISTER_EXTRA_OBJECT_IO( "studio/node/", tag, ioClass, itemClass );

#define DZ_PLUGIN_REGISTER_MODIFIER_EXTRA_OBJECT_IO( tag, ioClass, itemClass ) \
	DZ_PLUGIN_REGISTER_EXTRA_OBJECT_IO( "studio/modifier/", tag, ioClass, itemClass );

#define DZ_PLUGIN_REGISTER_GEOMETRY_EXTRA_OBJECT_IO( tag, ioClass, itemClass ) \
	DZ_PLUGIN_REGISTER_EXTRA_OBJECT_IO( "studio/geometry/", tag, ioClass, itemClass );

#define DZ_PLUGIN_REGISTER_ELEMENTDATA_EXTRA_OBJECT_IO( tag, ioClass, itemClass ) \
	DZ_PLUGIN_REGISTER_EXTRA_OBJECT_IO( "studio/element_data/", tag, ioClass, itemClass );

#define DZ_PLUGIN_REGISTER_SCENEDATA_EXTRA_OBJECT_IO( tag, ioClass, itemClass ) \
	DZ_PLUGIN_REGISTER_EXTRA_OBJECT_IO( "studio/scene_data/", tag, ioClass, itemClass );

//MOC_SKIP_END

#endif // Q_MOC_RUN
#endif // DAZ_PLUGIN_H
