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
	Defines the DzRotationOrder class.
**/

#ifndef DAZ_ROTATION_ORDER_H
#define DAZ_ROTATION_ORDER_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRotationOrder {
public:

	enum RotOrder { XYZ = 0, XZY, YXZ, YZX, ZXY, ZYX };
	typedef int AxisOrder[3];

	DzRotationOrder();
	DzRotationOrder( RotOrder order );
	DzRotationOrder( AxisOrder order );
	DzRotationOrder( int firstAxis, int secondAxis, int thirdAxis );
	DzRotationOrder( const DzRotationOrder &order );

	void			setOrder( RotOrder order );
	void			setOrder( AxisOrder order );
	void			setOrder( int firstAxis, int secondAxis, int thirdAxis );
	DzRotationOrder	&operator=( const DzRotationOrder &order );

	RotOrder		order() const;
	void			getAxisOrder( AxisOrder order ) const;
	int				operator[]( int which ) const;
	bool			operator==( const DzRotationOrder &order ) const;
	bool			operator!=( const DzRotationOrder &order ) const;

	QString			toString() const;

	static DzRotationOrder	fromString( const QString &str, bool *ok = NULL );
	static DzRotationOrder	xyz();
	static DzRotationOrder	xzy();
	static DzRotationOrder	yxz();
	static DzRotationOrder	yzx();
	static DzRotationOrder	zxy();
	static DzRotationOrder	zyx();

private:
	RotOrder		m_order;
};

Q_DECLARE_METATYPE( DzRotationOrder );

#endif // DAZ_ROTATION_ORDER_H