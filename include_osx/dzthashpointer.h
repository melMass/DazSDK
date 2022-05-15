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
	Defines the DzTHashPointer template class.
**/

#ifndef DAZ_T_WEAK_POINTER_H
#define DAZ_T_WEAK_POINTER_H

/******************************
	Include files
******************************/

#include <QtCore/QPointer>

#include "dzgeneraldefs.h"

/*******************************
	Class definitions
*******************************/

template <class DataType>
class DzTHashPointer
{
public:
	DzTHashPointer() : m_ptr(NULL), m_void(NULL){}
	DzTHashPointer(DataType *ptr) : m_ptr(ptr), m_void(ptr){}
	DzTHashPointer(const DzTHashPointer<DataType> &obj) : m_ptr(obj.m_ptr), m_void(obj.m_void){}

	DzTHashPointer<DataType>& operator= (const DzTHashPointer<DataType> &obj) 
	{
		if (*this != obj)
		{
			m_ptr = obj->m_ptr;
			m_void = obj->m_void;
		}
		
		return *this;
	}
	
	DzTHashPointer<DataType>& operator= (DataType *ptr)
	{
		if (m_ptr != ptr)
		{
			m_ptr = ptr;
			m_void = ptr;
		}

		return *this;
	}

	bool operator==(const DzTHashPointer<DataType> &obj) const 
	{
		return (m_void == obj.m_void);
	}

	bool operator==(const DataType *ptr) const
	{
		return m_void == ptr;
	}

	bool operator!=(const DzTHashPointer<DataType> &obj) const
	{
		return !(*this == obj);
	}

	bool operator!=(const DataType *ptr) const
	{
		return m_void != ptr;
	}

	bool operator!() const
	{
		return m_void == NULL;
	}

	operator DataType *() const
	{
		return m_ptr;
	}

	DataType* operator->()
	{
		return m_ptr;
	}

	const DataType* operator->() const
	{
		return m_ptr;
	}

	DataType* data()
	{
		return m_ptr;
	}

	const DataType* data() const
	{
		return m_ptr;
	}

	void* internalData()
	{
		return m_void;
	}

	const void* internalData() const
	{
		return m_void;
	}

private:
	QPointer<DataType>	m_ptr;
	void				*m_void;
};

template <class DataType> 
inline uint qHash(const DzTHashPointer<DataType> &key)
{
	return qHash(key.internalData());
}

#endif //DAZ_T_WEAK_POINTER_H