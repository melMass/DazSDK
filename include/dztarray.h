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
	Defines the DzTArray Template class.
**/

#ifndef DAZ_T_ARRAY_H
#define DAZ_T_ARRAY_H

/******************************
	Include files
******************************/

#include "dzgeneraldefs.h"


/*******************************
	Class definitions
*******************************/

template <class DataType>
class DzTArray {
public:
	//
	// CREATORS
	//

	DzTArray( int bSize = 8 );
	DzTArray( const DzTArray<DataType> &obj );
	virtual ~DzTArray();

	//
	// MANIPULATORS
	//

	DzTArray<DataType>&	operator=( const DzTArray<DataType> &from );
	DataType&		at( int i );
	DataType&		operator[]( int i );
	void			append( const DataType &obj );
	void			appendBlank();
	void			append( int num, const DataType *obj );
	int				appendIfUnique( const DataType &obj );
	void			insert( int i, const DataType &obj );
	virtual void	removeByIndex( int index, int num = 1 );
	void			removeFromEnd( int num = 1 );
	bool			remove( const DataType &obj );
	virtual void	clear() { m_nItems = 0; }
	virtual void	clearAndFree();
	bool			setCount( int num, bool keepExisting = true );
	bool			preSize( int num, bool keepExisting = true );

	//
	// ACCESSORS
	//

	const DataType&	at( int i ) const;
	const DataType&	operator[]( int i ) const;
	int				count() const { return m_nItems; }
	bool			isEmpty() const { return (m_nItems < 1); }
	int				find( const DataType &obj ) const;
	const DataType*	getValues() const { return m_items; }
	DataType*		getValuesUnlocked() const { return m_items; }
	int				size() const { return m_nItems * sizeof( DataType); }
	int				slotSize() const { return m_nSlots * sizeof( DataType); }

protected:
	//
	// DATA MEMBERS
	//

	int				m_nItems, m_nSlots, m_blockGrowSize;
	DataType		*m_items;

	void			copyValues( const DzTArray<DataType> &from );

private:

	bool			addSpace( int num, bool keepExisting = true );
};

/******************************************************************************/
template <class DataType>
DzTArray<DataType>::DzTArray( int bSize )
	: m_nItems(0),
	m_nSlots(0),
	m_blockGrowSize(bSize),
	m_items(0)
{
	if( m_blockGrowSize <= 0 ){
		DZ_WARNING( "Invalid block size specified in DzTArray::DzTArray()" );
		m_blockGrowSize = 1;
	}
}

/******************************************************************************/
template <class DataType>
DzTArray<DataType>::DzTArray( const DzTArray<DataType> &obj )
	: m_nItems(0),
	m_nSlots(0),
	m_blockGrowSize(obj.m_blockGrowSize),
	m_items(0)
{
	if( m_blockGrowSize <= 0 )
	{
		DZ_WARNING( "Invalid block size specified in DzTArray::DzTArray()" );
		m_blockGrowSize = 1;
	}

	if( obj.m_nItems > 0 )
		append( obj.m_nItems, obj.m_items );
}

/******************************************************************************/
template <class DataType>
DzTArray<DataType>::~DzTArray()
{
	delete [] m_items;
}

/******************************************************************************/
template <class DataType>
DzTArray<DataType>& DzTArray<DataType>::operator=( const DzTArray<DataType> &from )
{
	clear();
	if( from.m_nItems > 0 )
		append( from.m_nItems, from.m_items );

	m_blockGrowSize = from.m_blockGrowSize;

	return *this;
}

/******************************************************************************/
template <class DataType>
DataType& DzTArray<DataType>::at( int i )
{
	if( i >= m_nItems || i < 0 ){
		DZ_WARNING( "Index out of range in DzTArray::at()" );
		return m_items[0];
	}

	return m_items[i];
}

/******************************************************************************/
template <class DataType>
DataType& DzTArray<DataType>::operator[]( int i )
{
	if( i >= m_nItems || i < 0 ){
		DZ_WARNING( "Index out of range in DzTArray::operator[]" );
		return m_items[0];
	}

	return m_items[i];
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::append( const DataType &obj )
{
	if( m_nItems >= m_nSlots ) {
		if( !addSpace( m_blockGrowSize ) )
			return;
	}

	m_items[m_nItems] = obj;
	m_nItems++;
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::appendBlank()
{
	if( m_nItems >= m_nSlots ) {
		if( !addSpace( m_blockGrowSize ) )
			return;
	}

	m_nItems++;
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::append( int num, const DataType *obj )
{
	int	i;

	if( num < 1 ){
		DZ_WARNING( "Less than one item specified for adding in DzTArray::append()" );
		return;
	}

	if( ( m_nItems + num ) > m_nSlots ) {
		if( num > m_blockGrowSize ) {
			if( !addSpace( num ) )
				return;
		}
		else {
			if( !addSpace( m_blockGrowSize ) )
				return;
		}
	}

	for( i = 0; i < num; i++ )
		m_items[m_nItems+i] = obj[i];

	m_nItems += num;
}

/******************************************************************************/
template <class DataType>
int DzTArray<DataType>::appendIfUnique( const DataType &obj )
{
	int	idx = find( obj );

	if( idx < 0 ){
		idx = count();
		append( obj );
	}

	return idx;
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::insert( int where, const DataType &obj )
{
	int	i;

	if( where < 0 ){
		DZ_WARNING( "Invalid index specified in DzTArray::insert()" );
		where = 0;
	}
	else if( where > m_nItems ){
		DZ_WARNING( "Invalid index specified in DzTArray::insert()" );
		where = m_nItems;
	}

	if( m_nItems >= m_nSlots ) {
		if( !addSpace( m_blockGrowSize ) )
			return;
	}

	for( i = m_nItems; i > where; i-- )
		m_items[i] = m_items[i-1];

	m_items[where] = obj;

	m_nItems++;
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::removeByIndex( int index, int num )
{
	int	i;

	if( index < 0 || index >= m_nItems ){
		DZ_WARNING( "Invalid starting index specified in DzTArray::removeByIndex()" );
		return;
	}

	if( index + num > m_nItems ){
		DZ_WARNING( "Too many items specified for removal in DzTArray::removeByIndex()" );
		num = m_nItems - index;
	}

	if( num > m_nItems )
		num = m_nItems;

	for( i = index; i < m_nItems - num; ++i )
		m_items[i] = m_items[i+num];
	m_nItems -= num;
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::removeFromEnd( int num )
{
	if( num > m_nItems ){
		DZ_WARNING( "Too many items specified for removal in DzTArray::removeFromEnd()" );
		num = m_nItems;
	}

	m_nItems -= num;
}

/******************************************************************************/
template <class DataType>
bool DzTArray<DataType>::remove( const DataType &obj )
{
	int result = find( obj );
	if( result < 0 )
		return false;

	removeByIndex( result );
	return true;
}

/******************************************************************************/
template <class DataType>
bool DzTArray<DataType>::setCount( int num, bool keepExisting )
{
	if( num < 0 ){
		DZ_WARNING( "Count less than 0 specifed in DzTArray::setCount()" );
		num = 0;
	}

	if( preSize( num, keepExisting ) ){
		m_nItems = num;
		return true;
	}

	return false;
}

/******************************************************************************/
template <class DataType>
bool DzTArray<DataType>::preSize( int num, bool keepExisting )
{
	bool	status = true;

	if( num < 0 ){
		DZ_WARNING( "Count less than 0 specifed in DzTArray::preSize()" );
		num = 0;
	}

	if( num > m_nSlots ) {
		if( ( num - m_nSlots ) > m_blockGrowSize )
			status = addSpace( num - m_nSlots, keepExisting );
		else
			status = addSpace( m_blockGrowSize, keepExisting );
	}

	return status;
}

/******************************************************************************/
template <class DataType>
const DataType& DzTArray<DataType>::at( int i ) const
{
	if( !(i < m_nItems && i > -1 ) ){
		DZ_WARNING( "Index out of range in DzTArray::at() const" );
		return m_items[0];
	}

	return m_items[i];
}

/******************************************************************************/
template <class DataType>
const DataType& DzTArray<DataType>::operator[]( int i ) const
{
	if( !(i < m_nItems && i > -1 ) ){
		DZ_WARNING( "Index out of range in DzTArray::operator[] const" );
		return m_items[0];
	}

	return m_items[i];
}

/******************************************************************************/
template <class DataType>
int DzTArray<DataType>::find( const DataType &obj ) const
{
	int		i;
	DataType	*ptr = m_items;

	for( i = 0; i < m_nItems; i++, ++ptr ) {
		if( obj == *ptr )
			return i;
	}
	return -1;
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::copyValues( const DzTArray<DataType> &from )
{
	clear();

	if( from.m_nItems > 0 )
		append( from.m_nItems, from.m_items );

	m_blockGrowSize = from.m_blockGrowSize;
}

/******************************************************************************/
template <class DataType>
bool DzTArray<DataType>::addSpace( int num, bool keepExisting )
{
	int			i;
	int			newSize;
	DataType	*ptr;

	if( num <= 0 ){
		DZ_WARNING( QString( "Invalid size '%1' passed to DzTArray::addSpace()" ).arg( num ) );
		return false;
	}

	newSize = m_nSlots + num;
	
	if ( newSize <= 0 )
	{
		DZ_WARNING( QString( "Invalid size '%1' passed to DzTArray::addSpace()" ).arg( num ) );
		return false;
	}
	
	DataType *newItems = new DataType[newSize];

	// Make sure the memory allocation was successful.
	m_nSlots = newSize;

	if( keepExisting ) {
		for( i = 0, ptr = m_items; i < m_nItems; ++i, ++ptr )
			newItems[i] = *ptr;
	}

	if( m_items )
		delete [] m_items;
	m_items = newItems;

	return true;
}

/******************************************************************************/
template <class DataType>
void DzTArray<DataType>::clearAndFree()
{
	delete [] m_items;
	m_items = 0;
	m_nItems = 0;
	m_nSlots = 0;
}

#endif // DAZ_T_ARRAY_H
