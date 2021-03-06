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
	Defines the DzTSortedArray template class.
**/

#ifndef DAZ_T_SORTED_ARRAY_H
#define DAZ_T_SORTED_ARRAY_H

/******************************
	Include files
******************************/

#include "dzgeneraldefs.h"

/******************************
	Forward declarations
******************************/

template <class DataType> class DzTArray;
template <class DataType> class DzTBlockArray;
template <class DataType> class DzTSimpleArray;

/*******************************
	Class definitions
*******************************/
template <class DataType>
class DzTSortedArray {
public:
	//
	// CREATORS
	//

	DzTSortedArray( int bSize = 16 );
	DzTSortedArray( const DzTSortedArray<DataType> &obj );
	DzTSortedArray( const DzTArray<DataType> &obj );
	DzTSortedArray( const DzTBlockArray<DataType> &obj );
	DzTSortedArray( const DzTSimpleArray<DataType> &obj );
	virtual ~DzTSortedArray();

	//
	// MANIPULATORS
	//

	DzTSortedArray<DataType>&	operator=( const DzTSortedArray<DataType> &from );
	DzTSortedArray<DataType>&	operator=( const DzTArray<DataType> &obj );
	DzTSortedArray<DataType>&	operator=( const DzTBlockArray<DataType> &obj );
	DzTSortedArray<DataType>&	operator=( const DzTSimpleArray<DataType> &obj );

	DataType&		operator[]( int i );
	DataType&		at( int i ) { return m_items[i]; }
	int				add( const DataType obj );
	void			removeByIndex( int index, int num = 1 );
	void			removeFromEnd( int num = 1 );
	bool			remove( const DataType obj );
	void			clear() { m_nItems = 0; }
	void			setCount( int num );
	void			preSize( int num );
	void			freeUnusedMemory();

	//
	// ACCESSORS
	//

	const DataType&	operator[]( int i ) const { return m_items[i]; }
	const DataType&	at( int i ) const { return m_items[i]; }

	int				count() const { return m_nItems; }
	bool			isEmpty() const { return (m_nItems < 1); }
	int				getSize() const;
	int				find( const DataType obj ) const;
	bool			findIndex( const DataType obj, int &index ) const;
	const DataType*	getValues() const { return m_items; }
	DataType*		getValuesUnlocked() const { return m_items; }
	void			setGrowSize( int num ) { m_blockGrowSize = num; }
	int				getGrowSize()	{ return m_blockGrowSize; }

protected:

	int				m_nItems, m_nSlots, m_blockGrowSize;
	DataType		*m_items;

private:

	bool			addSpace( int num );
	void			sort();
};

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>::DzTSortedArray( int bSize ) : m_blockGrowSize( bSize ),
	m_nItems( 0 ), m_items( NULL ), m_nSlots( 0 )
{
	if( m_blockGrowSize <= 0 ){
		DZ_WARNING( "Invalid block size specified in DzTSortedArray::DzTSortedArray()" );
		m_blockGrowSize = 1;
	}
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>::DzTSortedArray( const DzTSortedArray<DataType> &obj ) :
	m_blockGrowSize( obj.m_blockGrowSize ),
	m_nItems( 0 ), m_items( NULL ), m_nSlots( 0 )
{
	*this = obj;
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>::DzTSortedArray( const DzTArray<DataType> &obj ) :
	m_blockGrowSize( 16 ), m_nItems( 0 ), m_items( NULL ), m_nSlots( 0 )
{
	*this = obj;
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>::DzTSortedArray( const DzTBlockArray<DataType> &obj ) :
	m_blockGrowSize( 16 ), m_nItems( 0 ), m_items( NULL ), m_nSlots( 0 )
{
	*this = obj;
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>::DzTSortedArray( const DzTSimpleArray<DataType> &obj ) :
	m_blockGrowSize( 16 ), m_nItems( 0 ), m_items( NULL ), m_nSlots( 0 )
{
	*this = obj;
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>::~DzTSortedArray()
{
	if( m_items )
		dzFree( (void*) m_items );
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>& DzTSortedArray<DataType>::operator=( const DzTSortedArray<DataType> &from )
{
	int	i, *ptr;

	clear();
	if( m_nSlots < from.m_nSlots )
		addSpace( from.m_nSlots - m_nSlots );

	m_nItems = from.m_nItems;

	m_blockGrowSize = from.m_blockGrowSize;
	for( i = 0, ptr = m_items; i < m_nItems; ++i, ++ptr )
		m_items[i] = from.m_items[i];

	return *this;
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>& DzTSortedArray<DataType>::operator=( const DzTArray<DataType> &obj )
{
	const DataType	*items = obj.getValues();
	int				count = obj.count();

	if( m_nItems < count )
		addSpace( count - m_nItems );

	m_nItems = count;

	memcpy( m_items, items, sizeof( DataType ) * count );

	sort();

	return *this;
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>& DzTSortedArray<DataType>::operator=( const DzTBlockArray<DataType> &obj )
{
	int				count = obj.count();

	if( m_nItems < count )
		addSpace( count - m_nItems );

	m_nItems = count;

	obj.copyToArray( m_items );

	sort();

	return *this;
}

/******************************************************************************/
template <class DataType>
DzTSortedArray<DataType>& DzTSortedArray<DataType>::operator=( const DzTSimpleArray<DataType> &obj )
{
	const DataType	*items = obj.getValues();
	int				count = obj.count();

	if( m_nItems < count )
		addSpace( count - m_nItems );

	m_nItems = count;

	memcpy( m_items, items, sizeof( DataType ) * count );

	sort();

	return *this;
}

/******************************************************************************/
template <class DataType>
DataType& DzTSortedArray<DataType>::operator[]( int i )
{
	if( i < 0 || i >= m_nItems ){
		DZ_WARNING( "Index out of range in DzTSortedArray::operator[]" );
		return m_items[0];
	}

	return m_items[i];
}

/******************************************************************************/
template <class DataType>
int DzTSortedArray<DataType>::add( const DataType obj )
{
	int		index;
	bool	alreadyHere;

	// Find the slot that this item should be inserted at.
	alreadyHere = findIndex( obj, index );
	if( alreadyHere )
		return index;

	if( m_nItems >= m_nSlots )
		addSpace( m_blockGrowSize );

	// Insert the item into the list at the right index.
	memmove( &(m_items[index+1]), &(m_items[index]), ( m_nItems - index )
		* sizeof( DataType ) );
	m_items[index] = obj;
	m_nItems++;

	return index;
}

/******************************************************************************/
template <class DataType>
void DzTSortedArray<DataType>::removeByIndex( int index, int num )
{
	if( index < 0 || index >= m_nItems ){
		DZ_WARNING( "Index out of range in DzTSortedArray::removeByIndex()" );
		return;
	}

	if( index + num > m_nItems ){
		DZ_WARNING( "Too many items specified for remove in DzTSortedArray::removeByIndex()" );
		num = m_nItems - index;
	}

	memmove( &(m_items[index]), &(m_items[index+num]), ( m_nItems - index - num )
		* sizeof( DataType ) );
	m_nItems -= num;
}

/******************************************************************************/
template <class DataType>
void DzTSortedArray<DataType>::removeFromEnd( int num )
{
	if( num > m_nItems ){
		DZ_WARNING( "Too many items specified for remove in DzTSortedArray::removeFromEnd()" );
		num = m_nItems;
	}

	m_nItems -= num;
}

/******************************************************************************/
template <class DataType>
bool DzTSortedArray<DataType>::remove( const DataType obj )
{
	int result = find( obj );
	if( result < 0 )
		return false;

	removeByIndex( result );

	return true;
}

/******************************************************************************/
template <class DataType>
void DzTSortedArray<DataType>::setCount( int num )
{
	if( num < 0 ){
		DZ_WARNING( "Count less than 0 specifed in DzTArray::setCount()" );
		num = 0;
	}

	preSize( num );
	m_nItems = num;
}

/******************************************************************************/
template <class DataType>
void DzTSortedArray<DataType>::preSize( int num )
{
	if( num < 0 ){
		DZ_WARNING( "Count less than 0 specifed in DzTArray::preSize()" );
		num = 0;
	}

	if( num > m_nSlots ) {
		if( ( num - m_nSlots ) > m_blockGrowSize )
			addSpace( num - m_nSlots );
		else
			addSpace( m_blockGrowSize );
	}
}


/******************************************************************************/
template <class DataType>
void DzTSortedArray<DataType>::freeUnusedMemory()
{
	if( m_nItems < m_nSlots ) {
		DataType *newItems = (DataType*) dzMalloc( m_nItems * sizeof( DataType ) );

		// Make sure the memory allocation was successful.

		memcpy( newItems, m_items, m_nItems * sizeof( DataType ) );
		if( m_items )
			dzFree( (void*) m_items );
		m_items = newItems;
		m_nSlots = m_nItems;
	}
}

/******************************************************************************/
template <class DataType>
int DzTSortedArray<DataType>::find( const DataType obj ) const
{
	int		index;

	bool exists = findIndex( obj, index );

	return exists ? index : -1;
}

/******************************************************************************/
template <class DataType>
int DzTSortedArray<DataType>::getSize() const
{
	return m_nSlots * sizeof( DataType );
}

/******************************************************************************/
template <class DataType>
bool DzTSortedArray<DataType>::addSpace( int num )
{
	int			i;
	int			newSize;
	DataType	*ptr;

	newSize = m_nSlots + num;
	DataType *newItems = (DataType*) dzMalloc( newSize * sizeof( DataType ) );

	m_nSlots = newSize;

	for( i = 0, ptr = m_items; i < m_nItems; ++i, ++ptr )
		newItems[i] = *ptr;
	if( m_items )
		dzFree( (void*) m_items );
	m_items = newItems;

	return true;
}

/******************************************************************************/
template <class DataType>
bool DzTSortedArray<DataType>::findIndex( const DataType obj, int &index ) const
{
	int		left = 0, right = m_nItems - 1, x;

	while( right >= left ) {
		x = left + ( right - left ) / 2;
		if( m_items[x] == obj ) {
			index = x;
			return true;
		}
		if( obj < m_items[x] )
			right = x - 1;
		else
			left = x + 1;
	}
	index = left;
	return false;
}

/******************************************************************************/
template <class DataType>
void DzTSortedArray<DataType>::sort()
{
	int			i, ir, j, k;
	DataType	rra;
	DataType	*items = m_items;

	if( m_nItems < 2 )
		return;

	// Have to do this because the Numerical Recipes algorithms are all 1-based
	// instead of the C-standard 0-based.
	--items;

	k = (m_nItems >> 1) + 1;
	ir = m_nItems;

	// The index k will be decremented from its initial value down to 1 during the hiring (heap
	// creation) phase. Once it reaches 1, the index ir will be decremented from its initial value
	// down to 1 during the retirement-and-promotion (heap selection) phase.
	for( ;; ) {
		if( k > 1 ) // Still in hiring phase.
			rra = items[--k];
		else { // In retirement-and-promotion phase.
			rra = items[ir]; // Clear a space at end of array.
			items[ir] = items[1]; // Retire the top of the heap into it.
			if( --ir == 1 ) {
				// Done with the last promotion.
				items[1] = rra; //The least competent worker of all!
				break;
			}
		}
		// Whether in the hiring phase or promotion phase, we here set up to sift down
		// element rra to its proper level.
		i = k;
		j = k + k;
		while( j <= ir ) {
			if( j < ir && items[j] < items[j+1] )
				j++; // Compare to the better underling.
			if( rra < items[j] ) {
				// Demote rra.
				items[i] = items[j];
				i = j;
				j <<= 1;
			}
			else
				break; // Found rra’s level. Terminate the sift-down.
		}
		items[i] = rra; // Put rra into its slot.
	}
}

#endif // DAZ_T_SORTED_ARRAY_H
