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
	Defines the DzClassFactory class.
**/

#ifndef DAZ_CLASS_FACTORY_H
#define DAZ_CLASS_FACTORY_H

/*****************************
	Include files
*****************************/
#ifndef DSON_IO
#include <QtScript/QScriptEngine>
#else
#include <QtCore/QObject>
#include <QtCore/QVariant>
#endif

#include "dzguid.h"
#include "dztsharedpointerscriptwrapper.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzClassFactory {
public:
	//
	// CREATORS
	//

	DzClassFactory( QMetaObject const *mo, const DzGuid &classID );
	virtual ~DzClassFactory();

	//
	// ACCESSORS
	//

	virtual QObject*	createInstance( const QVariantList &args ) const = 0;
	virtual QObject*	createInstance() const = 0;
#ifndef  DSON_IO
	virtual QObject*	createInstance( QScriptContext *context ) const;
	virtual void		registerClass( QScriptEngine *engine ) const;
#endif
	QMetaObject const*	metaObject() const;
	const char*			className() const;
	bool				provides( const char *className ) const;
	DzGuid				classID() const;
#ifndef  DSON_IO
	static void			registerEnumsOnClass( QScriptEngine *engine, const QMetaObject *meta, QScriptValue &value );
#endif
	
protected:

	static bool	argToBool( const QVariant &arg, bool &val, bool canConvert = true );
#ifndef  DSON_IO
	static bool	argToColor( const QVariant &arg, QColor &val, bool canConvert = true );
	static bool	argToSize( const QVariant &arg, QSize &val, bool canConvert = true );
#endif
	static bool	argToDouble( const QVariant &arg, double &val, bool canConvert = true );
	static bool	argToInt( const QVariant &arg, int &val, bool canConvert = true );
	static bool	argToString( const QVariant &arg, QString &val, bool canConvert = true );
	static bool	argToObject( const QVariant &arg, QObject **obj, const char *className = NULL );

private:
	QMetaObject const	*m_metaObject;
	DzGuid				m_classID;
};

template <class ClassType>
class DzTCustomClassFactory : public DzClassFactory {
public:
	DzTCustomClassFactory( unsigned int id
#ifndef  DSON_IO
		, QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership
#endif
		) : 
		DzClassFactory( &ClassType::staticMetaObject, DzGuid::fromLegacyClassID( id ) )
#ifndef  DSON_IO
		,m_ownwership( ownership )
#endif
	{
		s_instance = this;
	}

	DzTCustomClassFactory( const DzGuid &guid
#ifndef  DSON_IO
		, QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership
#endif
		) : 
		DzClassFactory( &ClassType::staticMetaObject, guid )
#ifndef  DSON_IO
		,m_ownwership( ownership )
#endif
	{
		s_instance = this;
	}

#ifndef  DSON_IO
	static QScriptValue	objectCreateFromScript( QScriptContext *context, QScriptEngine *engine )
	{
		if( s_instance )
		{
			QScriptValue val = engine->newQObject( s_instance->createInstance( context ), s_instance->m_ownwership );
			DzClassFactory::registerEnumsOnClass( engine, &ClassType::staticMetaObject, val );
			return val;
		}
		return QScriptValue();
	}

	static QScriptValue objectToScript( QScriptEngine *engine, ClassType* const &in )
	{
		QScriptValue val = engine->newQObject( in );
		DzClassFactory::registerEnumsOnClass( engine, &ClassType::staticMetaObject, val );
		return val;
	}

	static void objectFromScript( const QScriptValue &object, ClassType* &out )
	{
		out = qobject_cast<ClassType*>( object.toQObject() );
	}

	virtual void registerClass( QScriptEngine *engine ) const
	{
		DzClassFactory::registerClass( engine );
		qScriptRegisterMetaType<ClassType*>( engine, objectToScript, objectFromScript );

		QScriptValue ctor = engine->newFunction( objectCreateFromScript );
		QScriptValue mo = engine->newQMetaObject( metaObject(), ctor );
		engine->globalObject().setProperty( className(), mo );
	}
#endif

protected:
	static DzTCustomClassFactory<ClassType>	*s_instance;
#ifndef  DSON_IO
	QScriptEngine::ValueOwnership					m_ownwership;
#endif
};

template <class ClassType>
DzTCustomClassFactory<ClassType> *DzTCustomClassFactory<ClassType>::s_instance = NULL;

template <class ClassType>
class DzTClassFactory : public DzTCustomClassFactory<ClassType> {
public:
	DzTClassFactory( unsigned int id
#ifndef  DSON_IO
		, QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership
#endif
		) : 
		DzTCustomClassFactory<ClassType>( id
#ifndef  DSON_IO
			,ownership 
#endif
		) { }
	DzTClassFactory( const DzGuid &guid
#ifndef  DSON_IO
		, QScriptEngine::ValueOwnership ownership = QScriptEngine::QtOwnership
#endif
	) : 
	DzTCustomClassFactory<ClassType>( guid
#ifndef  DSON_IO
	,ownership 
#endif
	) { }

	virtual QObject*	createInstance( const QVariantList &args ) const
	{
		return createInstance();
	}

	virtual QObject*	createInstance() const
	{
		QObject *item = new ClassType;
		return item;
	}
};

//////////////////////////////////////////////////////////////////////////
template <class ClassType, class PtrType>
class DzTCustomRefCountedClassFactory : public DzClassFactory {
public:
	DzTCustomRefCountedClassFactory( const DzGuid &guid ) : 
		DzClassFactory( &ClassType::staticMetaObject, guid )
	{
		s_instance = this;
	}

#ifndef  DSON_IO
	static QScriptValue	objectCreateFromScript( QScriptContext *context, QScriptEngine *engine )
	{
		if( s_instance )
		{
			QScriptValue val = engine->newQObject( 
				new DzTSharedPointerScriptWrapper<ClassType>(
					qobject_cast<ClassType*>( s_instance->createInstance( context ))),
				QScriptEngine::ScriptOwnership );

			DzClassFactory::registerEnumsOnClass( engine, &ClassType::staticMetaObject, val );
			return val;
		}
		return QScriptValue();
	}

	static QScriptValue objectToScript( QScriptEngine *engine, ClassType* const &in )
	{
		QScriptValue val;
		if(in==NULL)
		{
			val = engine->nullValue();
		}
		else
		{
			val = engine->newQObject( new DzTSharedPointerScriptWrapper<ClassType>( in ) );
			DzClassFactory::registerEnumsOnClass( engine, &ClassType::staticMetaObject, val );
		}
		return val;
	}

	static void objectFromScript( const QScriptValue &object, ClassType* &out )
	{
		out = qobject_cast<ClassType*>( object.toQObject() );
	}

	static QScriptValue ptrToScript( QScriptEngine *engine, PtrType const &in )
	{
		QScriptValue val;
		if(in==NULL)
		{
			val = engine->nullValue();
		}
		else
		{
			val = engine->newQObject( new DzTSharedPointerScriptWrapper<ClassType>( in ) );
			DzClassFactory::registerEnumsOnClass( engine, &ClassType::staticMetaObject, val );
		}
		return val;
	}

	static void ptrFromScript( const QScriptValue &object, PtrType &out )
	{
		out = qobject_cast<ClassType*>( object.toQObject() );
	}

	virtual void registerClass( QScriptEngine *engine ) const
	{
		DzClassFactory::registerClass( engine );
		qScriptRegisterMetaType<ClassType*>( engine, objectToScript, objectFromScript );
		qScriptRegisterMetaType<PtrType>( engine, ptrToScript, ptrFromScript );

		QScriptValue ctor = engine->newFunction( objectCreateFromScript );
		QScriptValue mo = engine->newQMetaObject( metaObject(), ctor );
		engine->globalObject().setProperty( className(), mo );
	}
#endif

protected:
	static DzTCustomRefCountedClassFactory<ClassType,PtrType>	*s_instance;
};

template <class ClassType, class PtrType>
DzTCustomRefCountedClassFactory<ClassType,PtrType> *DzTCustomRefCountedClassFactory<ClassType,PtrType>::s_instance = NULL;

template <class ClassType, class PtrType>
class DzTRefCountedClassFactory : public DzTCustomRefCountedClassFactory<ClassType,PtrType> {
public:
	DzTRefCountedClassFactory( const DzGuid &guid ) : 
		DzTCustomRefCountedClassFactory<ClassType,PtrType>( guid ) 
	{ }

	virtual QObject*	createInstance( const QVariantList &args ) const
	{
		return createInstance();
	}

	virtual QObject*	createInstance() const
	{
		QObject *item = new ClassType;
		return item;
	}
};

template <class ClassType,class PtrType>
class DzTRefCountedAbstractFactory : public DzTCustomRefCountedClassFactory<ClassType,PtrType> {
public:
	DzTRefCountedAbstractFactory( const DzGuid &guid ) : 
		DzTCustomRefCountedClassFactory<ClassType,PtrType>( guid ) 
	{ }

	virtual QObject*	createInstance( const QVariantList &args ) const
	{
		return NULL;
	}

	virtual QObject*	createInstance() const
	{
		return NULL;
	}
};


#endif // DAZ_CLASS_FACTORY_H
