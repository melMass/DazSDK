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
	Defines the DzTBlockArray template class.
**/

#ifndef DAZ_T_BLOCK_ARRAY_H
#define DAZ_T_BLOCK_ARRAY_H

/******************************
	Include files
******************************/

#include "dzgeneraldefs.h"

/*******************************
	Definitions
*******************************/

#define DZ_BLOCK_ARRAY_GROW_SIZE 16

/*******************************
	Class definitions
*******************************/

template <class DataType>
class DzTBlockArray {
public:
	DzTBlockArray( int bSize = 32 );
	~DzTBlockArray();

	//
	// MANIPULATORS
	//

	DzTBlockArray<DataType>&	operator=( const DzTBlockArray<DataType> &from );
	DataType&		operator[]( int i );
	DataType&		at( int i );
	void			append( const DataType &obj );
	void			append( int num, const DataType *obj );
	int				appendIfUnique( const DataType &obj );
	void			removeByIndex( int index, int num = 1 );
	void			removeFromEnd( int num = 1 );
	bool			remove( const DataType &obj );
	void			clear( bool freeMem = false );

	//
	// ACCESSORS
	//

	const DataType&	operator[]( int i ) const;
	const DataType&	at( int i ) const;
	int				count() const { return ( m_curBlockIdx * m_blockSize ) + m_nBlockItems; }
	int				find( const DataType obj ) const;
	void			copyToArray( DataType *array ) const;
	int				getBlockSize()	{ return m_blockSize; }

protected:
	//
	// DATA MEMBERS
	//

	int			m_nBlocks, m_nBlockSlots, m_blockSize, m_curBlockIdx, m_nBlockItems;
	DataType	**m_blocks;

private:

	bool		addBlocks( int num );
};

/******************************************************************************/
template <class DataType>
DzTBlockArray<DataType>::DzTBlockArray( int bSize ) :
	m_nBlockItems( 0 ), m_blocks( NULL ), m_nBlocks( 0 ),
	m_curBlockIdx( 0 ), m_nBlockSlots( 0 )
{
	int		size = 1;

	// Round the block size to the next larger power of two.
	while( size < bSize )
		size = size << 1;

	m_blockSize = size;
	addBlocks( 1 ); // Need to have a block to start with.
}

/******************************************************************************/
template <class DataType>
DzTBlockArray<DataType>::~DzTBlockArray()
{
	if( m_blocks ) {
		for( int i = 0; i < m_nBlocks; ++i )
			delete [] m_blocks[i];
		dzFree( (void*) m_blocks );
	}
}

/******************************************************************************/
template <class DataType>
DzTBlockArray<DataType>& DzTBlockArray<DataType>::operator=( const DzTBlockArray<DataType> &from )
{
	int i, num = from.count();

	//m_blockSize = from.m_blockSize;

	clear( true );

	for( i = 0; i < num; ++i )
		append( from[i] );

	return *this;
}

/******************************************************************************/
template <class DataType>
DataType& DzTBlockArray<DataType>::operator[]( int i )
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTBlockArray::operator[]" );
		return m_blocks[0][0];
	}

	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
DataType& DzTBlockArray<DataType>::at( int i )
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTBlockArray::at()" );
		return m_blocks[0][0];
	}

	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
void DzTBlockArray<DataType>::append( const DataType &obj )
{
	if( m_nBlockItems >= m_blockSize ) {
		m_curBlockIdx++;
		if( m_curBlockIdx >= m_nBlocks )
			addBlocks( 1 );
		m_nBlockItems = 0;
	}

	m_blocks[m_curBlockIdx][m_nBlockItems++] = obj;
}

/******************************************************************************/
template <class DataType>
void DzTBlockArray<DataType>::append( int num, const DataType *obj )
{
	if( num < 1 ){
		DZ_WARNING( "Less than one item specified to add in DzTBlockArray::append()" );
		return;
	}

	for( int i = 0; i < num; ++i )
		append( obj[i] );
}

/******************************************************************************/
template <class DataType>
int DzTBlockArray<DataType>::appendIfUnique( const DataType &obj )
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
void DzTBlockArray<DataType>::removeByIndex( int index, int num )
{
	int	cnt = count();
	int	nItems;

	if( index < 0 || index >= cnt ){
		DZ_WARNING( "Invalid starting index specified in DzTBlockArray::removeByIndex()" );
		return;
	}

	if( index + num > cnt ){
		DZ_WARNING( "Too many items specified for removal in DzTBlockArray::removeByIndex()" );
		num = cnt - index;
	}

	nItems = cnt - num;
	for( int i = index; i < nItems; ++i )
		(*this)[i] = (*this)[i+num];

	m_nBlockItems -= num;

	while( m_nBlockItems <= 0 && m_curBlockIdx > 0 ){
		m_curBlockIdx--;
		m_nBlockItems += m_blockSize;
	}

	if( m_nBlockItems < 0 )
		m_nBlockItems = 0;
}

/******************************************************************************/
template <class DataType>
bool DzTBlockArray<DataType>::remove( const DataType &obj )
{
	int result = find( obj );
	if( result < 0 )
		return false;

	removeByIndex( result );

	return true;
}

/******************************************************************************/
template <class DataType>
void DzTBlockArray<DataType>::clear( bool freeMem )
{
	if( freeMem ) {
		for( int i = 0; i < m_nBlocks; ++i ) {
			delete [] m_blocks[i];
			m_blocks[i] = NULL;
		}
		m_nBlocks = 0;
	}
	m_curBlockIdx = 0;
	m_nBlockItems = 0;

	// must have at least one block
	if( freeMem )
		addBlocks( 1 );
}

/******************************************************************************/
template <class DataType>
const DataType& DzTBlockArray<DataType>::operator[]( int i ) const
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTBlockArray::operator[]" );
		return m_blocks[0][0];
	}

	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
const DataType& DzTBlockArray<DataType>::at( int i ) const
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTBlockArray::at()" );
		return m_blocks[0][0];
	}
	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
int DzTBlockArray<DataType>::find( const DataType obj ) const
{
	/*int	i, j;
	DataType		*ptr;

	for( i = 0; i < m_curBlockIdx - 1; i++ ) {
		ptr = m_blocks[i];
		for( j = 0; j < m_blockSize; ++j ) {
			if( obj == ptr[j] )
				return ( j + i * m_blockSize );
		}
	}
	ptr = m_blocks[m_curBlockIdx];
	for( j = 0; j < m_nBlockItems; ++j ) {
		if( obj == ptr[j] )
			return ( j + m_curBlockIdx * m_blockSize );
	}
	return -1; this code seems to be doing no good, we'll try the high-level way for now */

	int	i, num = count();

	for( i = 0; i < num; i++ ){
		if( (*this)[i] == obj )
			return i;
	}

	return -1;
}

/******************************************************************************/
template <class DataType>
void DzTBlockArray<DataType>::copyToArray( DataType *array ) const
{
	int	i, num = m_nBlocks - 1;

	for( i = 0; i < num; i++ ){
		memcpy( array, m_blocks[i], m_blockSize * sizeof( DataType ) );
		array += m_blockSize;
	}

	if( m_nBlocks > 0 )
		memcpy( array, m_blocks[m_nBlocks - 1], m_nBlockItems * sizeof( DataType ) );
}

/******************************************************************************/
template <class DataType>
bool DzTBlockArray<DataType>::addBlocks( int num )
{
	int	i;

	if( m_nBlocks + num >= m_nBlockSlots ) {
		m_nBlockSlots += ( num > DZ_BLOCK_ARRAY_GROW_SIZE ? num : DZ_BLOCK_ARRAY_GROW_SIZE );
		DataType **newBlocks = (DataType**) dzMalloc( m_nBlockSlots * sizeof( DataType* ) );

		if( m_blocks ) {
			memcpy( newBlocks, m_blocks, m_nBlocks * sizeof( DataType* ) );
			dzFree( (void*) m_blocks );
		}
		m_blocks = newBlocks;
	}

	for( i = m_nBlocks; i < m_nBlocks + num; ++i ) {
		m_blocks[i] = new DataType[m_blockSize];
		// Make sure the memory allocation was successful.
		if( !m_blocks[i] ) {
			m_nBlockSlots -= num;
			throw "Out of memory in DzTBlockArray::addBlocks";
		}
	}
	m_nBlocks += num;

	return true;
}

#endif // DAZ_T_BLOCK_ARRAY_H
