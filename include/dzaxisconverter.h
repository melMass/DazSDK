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

#ifndef DAZ_AXIS_CONVERTER_H
#define DAZ_AXIS_CONVERTER_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward Declarations
*****************************/

class DzFileIOSettings;
class DzVec3;

/*****************************
	Constants
*****************************/
///
///	Keys for DzFileIOSettings
///	

//Axis Definitions: Acceptable values are "X", "Y", or "Z"... Case Insensitive
#define DZ_AXIS_CONVERTER_LAT_AXIS				"LatAxis"
#define DZ_AXIS_CONVERTER_VERT_AXIS				"VertAxis"
#define DZ_AXIS_CONVERTER_DEPTH_AXIS			"DepthAxis"

//Axis Inversions: Acceptable values are true or false
#define DZ_AXIS_CONVERTER_INVERT_LAT_AXIS		"InvertLatAxis"
#define DZ_AXIS_CONVERTER_INVERT_VERT_AXIS		"InvertVertAxis"
#define DZ_AXIS_CONVERTER_INVERT_DEPTH_AXIS		"InvertDepthAxis"

//Scale Factor: Any float value larger than DZ_AXIS_CONVERTER_TOLERANCE
#define DZ_AXIS_CONVERTER_SCALE					"Scale"

//Tolerance for the scale value
#define DZ_AXIS_CONVERTER_TOLERANCE		0.00000000001f

class DZ_EXPORT DzAxisConverter
{
public:
	//
	// Enumerated Types
	//
	enum Axis
	{
		X_Axis = 0,
		Y_Axis,
		Z_Axis,
		INVALID_AXIS
	};

	enum ConversionType
	{
		Import = 0,
		Export
	};

public:
	//
	// Constructors
	//
	DzAxisConverter( ConversionType type );
	DzAxisConverter( ConversionType type, DzFileIOSettings *settings );

	virtual ~DzAxisConverter();

	//
	// Manipulators
	//
	void	setConversion( const DzFileIOSettings *settings );
	bool	setAxes( Axis lat, Axis vert, Axis depth );
	bool	setAxes( const QString &lat, const QString &vert, const QString &depth );
	bool	setScaleFactor( float scale );
	void	setInvertLatAxis( bool invert );
	void	setInvertVertAxis( bool invert );
	void	setInvertDepthAxis( bool invert );
	void	setConversionType( ConversionType type );

	//
	// Accessors
	//
	void	getConversion( DzFileIOSettings *settings ) const;
	void	getAxes( Axis &lat, Axis &vert, Axis &depth ) const;
	float	getScaleFactor() const;
	bool	getInvertLatAxis() const;
	bool	getInvertVertAxis() const;
	bool	getInvertDepthAxis() const;

	ConversionType	getConversionType() const;
	
	//
	// Utilities
	//
	void	convertOrientation( DzVec3 &vec ) const;
	void	convertOrientation( DzPnt3 &pnt ) const;
	void	convertOrientation( float &x, float &y, float &z ) const;

	static Axis		convertStringToAxis( const QString &axisString );
	static QString	convertAxisToString( Axis axis );

private:
	bool	validateAxisSettings();
	void	importConversion( float &x, float &y, float &z ) const;
	void	exportConversion( float &x, float &y, float &z ) const;

	//
	// DATA MEMBERS
	//

	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_AXIS_CONVERTER_H
