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
	Defines the DzTSharedPointer template class.
**/

#ifndef DAZ_T_SHARED_POINTER_SCRIPT_WRAPPER_H
#define DAZ_T_SHARED_POINTER_SCRIPT_WRAPPER_H

/******************************
	Include files
******************************/

#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/*******************************
	Class definitions
*******************************/

template <class DataType>
class DzTSharedPointerScriptWrapper : public QObject 
{
public:
	template <typename T> inline void qt_check_for_QOBJECT_macro(const T &_q_argument) const
	{ int i = qYouForgotTheQ_OBJECT_Macro(this, &_q_argument); i = i; }
	
	static const QMetaObject staticMetaObject;
	virtual const QMetaObject *metaObject() const;
	virtual void *qt_metacast(const char *_clname);

	static inline QString tr(const char *s, const char *c = 0)
	{ return staticMetaObject.tr(s, c); }
	static inline QString trUtf8(const char *s, const char *c = 0)
	{ return staticMetaObject.trUtf8(s, c); }
	static inline QString tr(const char *s, const char *c, int n)
	{ return staticMetaObject.tr(s, c, n); }
	static inline QString trUtf8(const char *s, const char *c, int n)
	{ return staticMetaObject.trUtf8(s, c, n); } 

	virtual int qt_metacall(QMetaObject::Call _c, int _id, void **_a);

public:

	DzTSharedPointerScriptWrapper(DzTSharedPointer<DataType> ptr)
		:m_ptr(ptr)
	{
		assert(static_cast<DzRefCountedItem*>(ptr.operator->()) || 1);
	}

	operator DataType *() const { return m_ptr; };
	virtual ~DzTSharedPointerScriptWrapper(){}

private:
	static const uint qt_meta_data[];

private:
	DzTSharedPointer<DataType> m_ptr;
};

template <class DataType>
const uint DzTSharedPointerScriptWrapper<DataType>::qt_meta_data[] = {
	// content:
	2,		// revision
	0,		// classname
	0, 0,	// classinfo
	0, 0,	// methods
	0, 0,	// properties
	0, 0,	// enums/sets
	0, 0,	// constructors

	0		// eod
};

template <class DataType>
const QMetaObject DzTSharedPointerScriptWrapper<DataType>::staticMetaObject = 
{
	{ 
		&DataType::staticMetaObject, 
		"DzTSharedPointerScriptWrapper\0",
		qt_meta_data, 
		0 
	}
};

template <class DataType>
const QMetaObject *DzTSharedPointerScriptWrapper<DataType>::metaObject() const
{
	if(m_ptr)
		return m_ptr->metaObject();

	return &DzTSharedPointerScriptWrapper<DataType>::staticMetaObject;
}

template <class DataType>
int DzTSharedPointerScriptWrapper<DataType>::qt_metacall( QMetaObject::Call _c, int _id, void **_a )
{
	if(!m_ptr)
		return -1;

	return m_ptr->qt_metacall(_c,_id,_a);
}

template <class DataType>
void* DzTSharedPointerScriptWrapper<DataType>::qt_metacast( const char *_clname )
{
	if(!m_ptr)
		return NULL;

	return m_ptr->qt_metacast(_clname);
}

#endif // DAZ_T_SHARED_POINTER_SCRIPT_WRAPPER_H