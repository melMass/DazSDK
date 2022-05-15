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
	Defines the DzTStack template class.
**/

#ifndef DAZ_T_STACK_H
#define DAZ_T_STACK_H

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
class DzTStack {
public:
	DzTStack( int bSize = 32 );
	~DzTStack();

	//
	// MANIPULATORS
	//

	DzTStack<DataType>&	operator=( const DzTStack<DataType> &from );
	DataType&		operator[]( int i );
	DataType&		at( int i );
	void			push( const DataType &obj );
	DataType&		pop();
	DataType&		current();
	void			clear( bool freeMem = false );

	//
	// ACCESSORS
	//

	const DataType&	operator[]( int i ) const;
	const DataType&	at( int i ) const;
	const DataType&	current() const;
	int				count() const { return (m_curBlockIdx * m_blockSize) + m_curItemIdx + 1; }
	bool			isEmpty() const { return (m_curItemIdx < 0); }
	int				getBlockSize()	{ return m_blockSize; }

protected:
	//
	// DATA MEMBERS
	//

	int			m_nBlocks, m_nBlockSlots, m_blockSize, m_curBlockIdx, m_curItemIdx;
	DataType	**m_blocks;

private:

	bool		addBlocks( int num );
};

/******************************************************************************/
template <class DataType>
DzTStack<DataType>::DzTStack( int bSize )
	: m_nBlocks( 0 ),
	m_nBlockSlots( 0 ),
	m_blockSize(0),
	m_curBlockIdx( 0 ),
	m_curItemIdx( -1 ),
	m_blocks( NULL )
{
	assert(bSize > 0 && "Block size should be a positive integer.");
	int		size = 1;

	// Round the block size to the next larger power of two.
	while( size < bSize )
		size = size << 1;

	m_blockSize = size;
	addBlocks( 1 ); // Need to have a block to start with.
}

/******************************************************************************/
template <class DataType>
DzTStack<DataType>::~DzTStack()
{
	if( m_blocks ) {
		for( int i = 0; i < m_nBlocks; ++i )
			dzFree( (void*) m_blocks[i] );
		dzFree( (void*) m_blocks );
	}
}

/******************************************************************************/
template <class DataType>
DzTStack<DataType>& DzTStack<DataType>::operator=( const DzTStack<DataType> &from )
{
	int i, num = from.count();

	//m_blockSize = from.m_blockSize;

	clear( true );

	for( i = 0; i < num; ++i )
		push( from[i] );

	return *this;
}

/******************************************************************************/
template <class DataType>
DataType& DzTStack<DataType>::operator[]( int i )
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTStack::operator[]" );
		return m_blocks[0][0];
	}

	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
DataType& DzTStack<DataType>::at( int i )
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTStack::at()" );
		return m_blocks[0][0];
	}

	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
void DzTStack<DataType>::push( const DataType &obj )
{
	m_curItemIdx++;
	if( m_curItemIdx >= m_blockSize ) {
		m_curBlockIdx++;
		if( m_curBlockIdx >= m_nBlocks )
			addBlocks( 1 );
		m_curItemIdx = 0;
	}

	m_blocks[m_curBlockIdx][m_curItemIdx] = obj;
}

/******************************************************************************/
template <class DataType>
DataType& DzTStack<DataType>::pop()
{
	if( m_curItemIdx < 0 ){
		DZ_WARNING( "Empty stack in DzTStack::pop()" );
		return m_blocks[0][0];
	}

	DataType	&ref = m_blocks[m_curBlockIdx][m_curItemIdx];

	m_curItemIdx--;
	if( m_curItemIdx < 0 ){
		if( m_curBlockIdx > 0 ){
			m_curItemIdx = m_blockSize-1;
			m_curBlockIdx--;
		}
	}

	return ref;
}

/******************************************************************************/
template <class DataType>
DataType& DzTStack<DataType>::current()
{
	if( m_curItemIdx < 0 ){
		DZ_WARNING( "Empty stack in DzTStack::current()" );
		return m_blocks[0][0];
	}

	return m_blocks[m_curBlockIdx][m_curItemIdx];
}

/******************************************************************************/
template <class DataType>
void DzTStack<DataType>::clear( bool freeMem )
{
	m_curBlockIdx = 0;
	m_curItemIdx = -1;

	if( freeMem ) {
		// must keep at least one block
		for( int i = 1; i < m_nBlocks; ++i ) {
			dzFree( (void*) m_blocks[i] );
			m_blocks[i] = NULL;
		}
		m_nBlocks = 1;
	}
}

/******************************************************************************/
template <class DataType>
const DataType& DzTStack<DataType>::operator[]( int i ) const
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTStack::operator[]" );
		return m_blocks[0][0];
	}

	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
const DataType& DzTStack<DataType>::at( int i ) const
{
	if( i >= count() || i < 0 ){
		DZ_WARNING( "Index out of range in DzTStack::at()" );
		return m_blocks[0][0];
	}
	return m_blocks[i/m_blockSize][i%m_blockSize];
}

/******************************************************************************/
template <class DataType>
const DataType& DzTStack<DataType>::current() const
{
	if( m_curItemIdx < 0 ){
		DZ_WARNING( "Empty stack in DzTStack::current()" );
		return m_blocks[0][0];
	}

	return m_blocks[m_curBlockIdx][m_curItemIdx];
}

/******************************************************************************/
template <class DataType>
bool DzTStack<DataType>::addBlocks( int num )
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
		m_blocks[i] = (DataType*) dzMalloc( m_blockSize * sizeof( DataType ) );
		// Make sure the memory allocation was successful.
		if( !m_blocks[i] ) {
			m_nBlockSlots -= num;
			throw "Out of memory in DzTStack::addBlocks";
		}
	}
	m_nBlocks += num;

	return true;
}

#endif // DAZ_T_STACK_H
