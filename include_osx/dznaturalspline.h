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
	Defines the DzNaturalSpline class.
**/

#ifndef DAZ_NATURAL_SPLINE_H
#define DAZ_NATURAL_SPLINE_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/****************************
	Forward declarations
****************************/

class DzOutFile;
class DzInFile;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNaturalSpline : public DzBase {
	Q_OBJECT
public:

	DzNaturalSpline();
	DzNaturalSpline( const DzNaturalSpline &spline );
	virtual ~DzNaturalSpline();

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	save( DzOutFile *file ) const;

	DzNaturalSpline	&operator=( const DzNaturalSpline &object);

public slots:

	void	clear();
	int		getNumPoints();
	void	setX( int index, float x );
	void	setY( int index, float y );
	void	insertPoint( float x, float y);
	void	deletePoint( int index );
	double	getValue( float x );
	double	getX( int index );
	double	getY( int index );
	void	getMinMax( float &min, float &max );
	double	getMax();
	double	getMin();

signals:

	void	splineChanged();

private:

	void	update();
	float	computeValue( float x );
	void	computeExtrema();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NATURAL_SPLINE_H
