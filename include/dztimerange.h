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
	Defines the DzTimeRange class.
**/

#ifndef DAZ_TIME_RANGE_H
#define DAZ_TIME_RANGE_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTimeRange {
public:
	//
	// CREATORS
	//

	DzTimeRange();
	DzTimeRange( DzTime start, DzTime end );
	DzTimeRange( const DzTimeRange &interval );

	//
	// MANIPULATORS
	//

	void	setStart( DzTime t );
	void	setEnd( DzTime t );
	void	setEnds( DzTime start, DzTime end );
	void	include( DzTime t );
	void	include( const DzTimeRange &interval );
	void	intersect( const DzTimeRange &interval );
	void	extendEndsBy( DzTime val );
	void	makeEmpty();
	void	operator-=( const DzTime tm );
	void	operator+=( const DzTime tm );

	//
	// ACCESSORS
	//

	DzTime	getStart() const;
	DzTime	getEnd() const;
	DzTime	getDuration() const;
	bool	isEmpty() const;
	bool	isIncluded( DzTime t ) const;
	bool	isIncluded( const DzTimeRange &iv ) const;
	bool	overlaps( const DzTimeRange &iv ) const;
	bool	operator==( const DzTimeRange &obj ) const;
	bool	operator!=( const DzTimeRange &obj ) const;
	bool	operator<( const DzTimeRange &obj ) const;
	bool	operator>( const DzTimeRange &obj ) const;

	DzTimeRange	operator-( const DzTime tm ) const;
	DzTimeRange	operator+( const DzTime tm ) const;

private:

	DzTime	m_start, m_end;
};

Q_DECLARE_METATYPE( DzTimeRange );

#define DZ_ETERNITY ( DzTimeRange( DZ_MIN_TIME, DZ_MAX_TIME ) )

#endif // DAZ_TIME_RANGE_H