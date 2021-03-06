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

#ifndef DAZ_PAIR_H
#define DAZ_PAIR_H

#include <QtCore/QPair>

/**
	Simple pair structure with the elements of the same type.
**/
template<typename Type>
struct DzPair
{
public:
	DzPair() {}
	DzPair(Type el1, Type el2):
		m_el1(el1),
		m_el2(el2)
	{}

	bool operator==( const DzPair &right) const
	{
		return (right.m_el1 == m_el1 && right.m_el2 == m_el2);
	}

	Type m_el1;
	Type m_el2;
};

typedef QPair<int, int> DzIntPair;

/** Complex pair of <vertex index> - <"normal index" - "uv texture coordinate index"> **/
typedef QPair<int, DzIntPair> DzVertNTPair;

#endif // DAZ_PAIR_H
