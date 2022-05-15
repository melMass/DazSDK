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

#ifndef DAZ_WEIGHT_COLOR_TABLE_H
#define DAZ_WEIGHT_COLOR_TABLE_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward Declarations
*****************************/

class DzColorGradient;

/*****************************
	Class Definitions
*****************************/

class DZ_EXPORT DzWeightColorTable : public QObject {
	Q_OBJECT
public:
	DzWeightColorTable();
	~DzWeightColorTable();

	DzColorGradient*		getColorGradient() const;

	const unsigned char*	getRedVals() const;
	const unsigned char*	getGreenVals() const;
	const unsigned char*	getBlueVals() const;

signals:

	void	gradientChanged();

private slots:

	void	updateGradient();

private:

	void	buildColorTable();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_WEIGHT_COLOR_TABLE_H
