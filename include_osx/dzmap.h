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
	Defines the DzMap class.
**/

#ifndef DAZ_MAP_H
#define DAZ_MAP_H

/*****************************
	Include files
*****************************/

#include "dztsharedpointer.h"
#include "dzstorable.h"
#include "dzvec3.h"

/****************************
	Forward declarations
****************************/

class DzMap;
class DzGeometry;

/****************************
	Type Definitions
****************************/

typedef DzTSharedPointer<DzMap> DzMapPtr;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMap : public DzStorable {
	Q_OBJECT
	Q_ENUMS( MapType )
public:

	enum MapType { FLOAT_MAP = 0, FLOAT2_MAP, FLOAT3_MAP, INT_MAP, SHORT_MAP };

	//
	// CREATORS/DESTRUCTORS
	//

	DzMap( MapType mapType = FLOAT_MAP );
	virtual ~DzMap();

	//
	// REIMPLEMENTATIONS
	//

#ifndef DSON_IO
	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	postLoadFile( const DzInFile *file );
#endif

	//
	// MANIPULATORS
	//

	void	setDefaultPnt2Value( const DzPnt2 defaultVal );
	void	setDefaultPnt3Value( const DzPnt3 defaultVal );
	void	appendPnt2Value( const DzPnt2 val );
	void	appendPnt2Values( int num, const DzPnt2 *vals );
	void	appendPnt3Value( const DzPnt3 val );
	void	setPnt2Value( int idx, const DzPnt2 val );
	void	setPnt3Value( int idx, const DzPnt3 val );
	void	reorderEntries( DzGeometry *geom, const int *newIndices );

public slots:

	void	setLabel( const QString &label );
	void	setDefaultFloatValue( float defaultVal );
	void	setDefaultPnt2Vec( const DzVec3 &defaultVal );
	void	setDefaultPnt3Vec( const DzVec3 &defaultVal );
	void	setDefaultIntValue( int defaultVal );
	void	setDefaultShortValue( short defaultVal );
	void	appendFloatValue( float val );
	void	appendPnt2Vec( const DzVec3 &val );
	void	appendPnt3Vec( const DzVec3 &val );
	void	appendIntValue( int val );
	void	appendShortValue( short val );
	void	setFloatValue( int idx, float val );
	void	setPnt2Vec( int idx, const DzVec3 &val );
	void	setPnt3Vec( int idx, const DzVec3 &val );
	void	setIntValue( int idx, int val );
	void	setShortValue( int idx, short val );
	void	setNumValues( int num );
	void	preSize( int num );
	void	clearAllData();
	void	setMapType( MapType mapType, bool keepData = false );

public:

	//
	// REIMPLEMENTATIONS
	//

	virtual QString	getExtension() const { return "dsv"; }
	virtual QString	getFiletype() const { return "Vertex Map"; }

	//
	// ACCESSORS
	//

	const float*	getPnt2Value( int idx ) const;
	const float*	getPnt3Value( int idx ) const;

public slots:

	QString		getLabel() const;
	MapType		getType() const;
	int			getNumValues() const;
	int			getNumDimensions() const;
	double		getFloatValue( int idx ) const;
	DzVec3		getPnt2Vec( int idx ) const;
	DzVec3		getPnt3Vec( int idx ) const;
	int			getIntValue( int idx ) const;
	short		getShortValue( int idx ) const;
	DzGeometry*	getOrderingGeometry() const;

public:

	float*	getFloatArrayPtr() const;
	DzPnt2*	getPnt2ArrayPtr() const;
	DzPnt3*	getPnt3ArrayPtr() const;
	int*	getIntArrayPtr() const;
	short*	getShortArrayPtr() const;

signals:

	void	mapModified();
	void	labelChanged();

protected:
	//
	// REIMPLEMENTATIONS
	//
#ifndef DSON_IO
	virtual void	writeData( DzOutFile *file ) const;
#endif

private:

	void	addSpace( int size );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MAP_H
