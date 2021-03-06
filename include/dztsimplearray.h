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
	Defines the DzTSimpleArray template class.
**/

#ifndef DAZ_T_SIMPLE_ARRAY_H
#define DAZ_T_SIMPLE_ARRAY_H

/******************************
	Include files
******************************/

#include "dztsortedarray.h"

/*******************************
	Class definitions
*******************************/
template <class DataType>
class DzTSimpleArray {
public:
	//
	// CREATORS
	//

	DzTSimpleArray( int bSize = 16 );
	DzTSimpleArray( const DzTSimpleArray<DataType> &obj );
	~DzTSimpleArray();

	//
	// MANIPULATORS
	//

	DzTSimpleArray<DataType>&	operator=( const DzTSimpleArray<DataType> &from );
	DzTSimpleArray<DataType>&	operator=( const DzTSortedArray<DataType> &from );

	DataType&		at( int i );
	DataType&		operator[]( int i );
	bool			append( const DataType obj );
	bool			append( int num, const DataType *obj );
	bool			append( const DzTSimpleArray<DataType> &from );
	void			appendIfUnique( const DataType obj ) { if( find( obj ) < 0 ) append( obj ); }
	bool			insert( int i, const DataType obj );
	void			removeByIndex( int index, int num = 1 );
	void			removeFromEnd( int num = 1 );
	bool			remove( const DataType obj );
	void			clear() { m_nItems = 0; }
	bool			setCount( int num, bool keepExisting = true );
	bool			preSize( int num, bool keepExisting = true );
	void			freeUnusedMemory();
	void			setGrowSize( int num ) { m_blockGrowSize = num; }

	//
	// ACCESSORS
	//

	const DataType&			at( int i ) const;
	const DataType&			operator[]( int i ) const;
	inline int				count() const { return m_nItems; }
	int						getSize() const;
	int						find( const DataType obj ) const;
	inline const DataType*	getValues() const { return m_items; }
	inline DataType*		getValuesUnlocked() const { return m_items; }
	int						getGrowSize() const	{ return m_blockGrowSize;}

protected:
	//
	// DATA MEMBERS
	//

	int				m_nItems, m_nSlots, m_blockGrowSize;
	DataType		*m_items;

	void			copyValues( const DzTSimpleArray<DataType> &from );
	void			copyValues( const DzTSortedArray<DataType> &from );

private:

	bool			addSpace( int num, bool keepExisting = true );
};

/******************************************************************************/
template <class DataType>
DzTSimpleArray<DataType>::DzTSimpleArray( int bSize ) : m_blockGrowSize( bSize ),
	m_nItems( 0 ), m_items( NULL ), m_nSlots( 0 )
{
	if( m_blockGrowSize <= 0 ){
		DZ_WARNING( "Invalid block grow size specified in DzTSimpleArray::DzTSimpleArray()" );
		m_blockGrowSize = 1;
	}
}

/******************************************************************************/
template <class DataType>
DzTSimpleArray<DataType>::DzTSimpleArray( const DzTSimpleArray<DataType> &obj ) :
	m_nItems( 0 ), m_items( NULL ), m_nSlots( 0 )
{
	m_blockGrowSize = obj.m_blockGrowSize;

	append( obj.count(), obj.getValues() );
}

/******************************************************************************/
template <class DataType>
DzTSimpleArray<DataType>::~DzTSimpleArray()
{
	if( m_items )
		dzFree( (void*) m_items );
}

/******************************************************************************/
template <class DataType>
DzTSimpleArray<DataType>& DzTSimpleArray<DataType>::operator=( const DzTSimpleArray<DataType> &from )
{
	copyValues( from );
	return *this;
}

/******************************************************************************/
template <class DataType>
DzTSimpleArray<DataType>& DzTSimpleArray<DataType>::operator=( const DzTSortedArray<DataType> &from )
{
	copyValues( from );
	return *this;
}

/******************************************************************************/
template <class DataType>
DataType& DzTSimpleArray<DataType>::at( int i )
{
	if( i < 0 || i >= m_nItems ) {
		if( m_nItems == 0 )
			throw "Illegal array index in DzTSimpleArray::at()";
		else {
			DZ_WARNING( "Illegal array index in DzTSimpleArray::at()" );
			return m_items[0];
		}
	}
	return m_items[i];
}

/******************************************************************************/
template <class DataType>
DataType& DzTSimpleArray<DataType>::operator[]( int i )
{
	if( i < 0 || i >= m_nItems ) {
		if( m_nItems == 0 )
			throw "Illegal array index in DzTSimpleArray::operator[]";
		else {
			DZ_WARNING( "Illegal array index in DzTSimpleArray::operator[]" );
			return m_items[0];
		}
	}
	return m_items[i];
}

/******************************************************************************/
template <class DataType>
bool DzTSimpleArray<DataType>::append( const DataType obj )
{
	if( m_nItems >= m_nSlots ) {
		if( !addSpace( m_blockGrowSize ) )
			return false;
	}

	m_items[m_nItems++] = obj;

	return true;
}

/******************************************************************************/
template <class DataType>
bool DzTSimpleArray<DataType>::append( int num, const DataType *obj )
{
	if( num < 0 ){
		DZ_WARNING( "Less than one item specified for adding in DzTSimpleArray::append()" );
		return true;
	}

	if( ( m_nItems + num ) > m_nSlots ) {
		int		blockSize = num;

		if( num < m_blockGrowSize )
			blockSize = m_blockGrowSize;

		if( !addSpace( blockSize ) )
			return false;
	}
	memcpy( &(m_items[m_nItems]), obj, num * sizeof( DataType ) );
	m_nItems += num;

	return true;
}

/******************************************************************************/
template <class DataType>
bool DzTSimpleArray<DataType>::append( const DzTSimpleArray<DataType> &from )
{
	return append( from.m_nItems, from.m_items );
}

/******************************************************************************/
template <class DataType>
bool DzTSimpleArray<DataType>::insert( int where, const DataType obj )
{
	if( m_nItems >= m_nSlots ) {
		if( !addSpace( m_blockGrowSize ) )
			return false;
	}

	if( where >= m_nItems )
		return append( obj );

	memmove( &(m_items[where+1]), &(m_items[where]), ( m_nItems - where )
		* sizeof( DataType ) );
	m_items[where] = obj;
	m_nItems++;

	return true;
}

/******************************************************************************/
template <class DataType>
void DzTSimpleArray<DataType>::removeByIndex( int index, int num )
{
	if( index < 0 || index >= m_nItems ){
		DZ_WARNING( "Index out of range in DzTSimpleArray::removeByIndex()" );
		return;
	}

	if( index + num > m_nItems ){
		DZ_WARNING( "Too many items specified for remove in DzTSimpleArray::removeByIndex()" );
		num = m_nItems - index;
	}

	memmove( &(m_items[index]), &(m_items[index+num]), ( m_nItems - index - num )
		* sizeof( DataType ) );
	m_nItems -= num;
}

/******************************************************************************/
template <class DataType>
void DzTSimpleArray<DataType>::removeFromEnd( int num )
{
	if( num > m_nItems ){
		DZ_WARNING( "Too many items specified for remove in DzTSimpleArray::removeFromEnd()" );
		num = m_nItems;
	}

	m_nItems -= num;
}

/******************************************************************************/
template <class DataType>
bool DzTSimpleArray<DataType>::remove( const DataType obj )
{
	int result = find( obj );
	if( result < 0 )
		return false;

	removeByIndex( result );

	return true;
}

/******************************************************************************/
template <class DataType>
bool DzTSimpleArray<DataType>::setCount( int num, bool keepExisting )
{
	if( num < 0 ){
		DZ_WARNING( "Count less than 0 specifed in DzTSimpleArray::setCount()" );
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
bool DzTSimpleArray<DataType>::preSize( int num, bool keepExisting )
{
	bool	status = true;

	if( num < 0 ){
		DZ_WARNING( "Count less than 0 specifed in DzTSimpleArray::preSize()" );
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
void DzTSimpleArray<DataType>::freeUnusedMemory()
{
	if( m_nItems < m_nSlots ) {
		DataType *newItems = (DataType*) dzMalloc( m_nItems * sizeof( DataType ) );

		memcpy( newItems, m_items, m_nItems * sizeof( DataType ) );
		if( m_items )
			dzFree( (void*) m_items );
		m_items = newItems;
		m_nSlots = m_nItems;
	}
}

/******************************************************************************/
template <class DataType>
const DataType& DzTSimpleArray<DataType>::at( int i ) const
{
	if( i < 0 || i >= m_nItems ) {
		if( m_nItems == 0 )
			throw "Illegal array index in DzTSimpleArray::at()";
		else {
			DZ_WARNING( "Illegal array index in DzTSimpleArray::at()" );
			return m_items[0];
		}
	}
	return m_items[i];
}

/******************************************************************************/
template <class DataType>
const DataType& DzTSimpleArray<DataType>::operator[]( int i ) const
{
	if( i < 0 || i >= m_nItems ) {
		if( m_nItems == 0 )
			throw "Illegal array index in DzTSimpleArray::operator[]";
		else {
			DZ_WARNING( "Illegal array index in DzTSimpleArray::operator[]" );
			return m_items[0];
		}
	}
	return m_items[i];
}

/******************************************************************************/
template <class DataType>
int DzTSimpleArray<DataType>::find( const DataType obj ) const
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
int DzTSimpleArray<DataType>::getSize() const
{
	int	size = 0;

	size += m_nSlots * sizeof( DataType );
	size += 4 * 4;

	return size;
}

/******************************************************************************/
template <class DataType>
void DzTSimpleArray<DataType>::copyValues( const DzTSimpleArray<DataType> &from )
{
	clear();

	append( from.count(), from.getValues() );

	m_blockGrowSize = from.m_blockGrowSize;
}

/******************************************************************************/
template <class DataType>
void DzTSimpleArray<DataType>::copyValues( const DzTSortedArray<DataType> &from )
{
	clear();

	append( from.count(), from.getValues() );
}

/******************************************************************************/
template <class DataType>
bool DzTSimpleArray<DataType>::addSpace( int num, bool keepExisting )
{
	DataType *newItems = (DataType*) dzMalloc( ( m_nSlots + num ) * sizeof( DataType ) );

	if( keepExisting && m_items )
		memcpy( newItems, m_items, m_nItems * sizeof( DataType ) );

	if( m_items )
		dzFree( (void*) m_items );
	m_items = newItems;
	m_nSlots += num;

	return true;
}

#endif // DAZ_T_SIMPLE_ARRAY_H
