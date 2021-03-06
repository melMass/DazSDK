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

#ifndef DAZ_T_SHARED_POINTER_H
#define DAZ_T_SHARED_POINTER_H

/******************************
	Include files
******************************/

#include "dzgeneraldefs.h"

/*******************************
	Class definitions
*******************************/

template <class DataType>
class DzTSharedPointer {
public:
	DzTSharedPointer() : m_ptr( NULL ) { }
	DzTSharedPointer( DataType *ptr ) : m_ptr( ptr ) {
		if( m_ptr )
			m_ptr->ref();
	}

	DzTSharedPointer( const DzTSharedPointer<DataType> &obj ) : m_ptr( obj.m_ptr ) {
		if( m_ptr )
			m_ptr->ref();
	}

	~DzTSharedPointer() {
		if( m_ptr )
			m_ptr->unref();
	}

	DzTSharedPointer<DataType>&	operator=( const DzTSharedPointer<DataType> &obj ) { return *this = obj.m_ptr; }
	DzTSharedPointer<DataType>&	operator=( DataType *ptr ) 
	{
		if( m_ptr == ptr )
			return *this;
		DataType	*old = m_ptr;
		if( ptr )
			ptr->ref();
		
		m_ptr = ptr;
		
		if( old )
			old->unref();

		return *this;
	}

	bool	isUnique() { return m_ptr ? (m_ptr->getRefCount() < 2) : true; }
	bool	operator==( const DzTSharedPointer<DataType> &obj ) const { return (m_ptr == obj.m_ptr); }
	bool	operator==( const DataType *ptr ) const { return (m_ptr == ptr); }
	bool	operator!=( const DzTSharedPointer<DataType> &obj ) const { return !(m_ptr == obj.m_ptr); }
	bool	operator!=( const DataType *ptr ) const { return !(m_ptr == ptr); }
	bool	operator!() const { return (m_ptr == NULL); }
	operator DataType *() const { return m_ptr; }
	DataType*		operator->() { return m_ptr; }
	const DataType*	operator->() const { return m_ptr; }
	DataType&		operator*() { return *m_ptr; }
	const DataType&	operator*() const { return *m_ptr; }

private:
	DataType	*m_ptr;
};

#endif // DAZ_T_SHARED_POINTER_H