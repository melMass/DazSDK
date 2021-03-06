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
	Defines the DzLegacyCurve class.
**/

#ifndef DAZ_LEGACY_CURVE_H
#define DAZ_LEGACY_CURVE_H

/*****************************
	Include files
*****************************/

#include "dzlegacyjointparam.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLegacyCurve : public DzLegacyJointParam {
	Q_OBJECT
public:
	DzLegacyCurve();
	DzLegacyCurve( DzBone *driver, DzLegacyJointParam::ParamAxis axis );
	virtual ~DzLegacyCurve();

	virtual ParamType			type() const { return DzLegacyJointParam::Rotation; }
	virtual DzLegacyJointParam*	deepCopy() const;

protected:

	virtual void	updateWeights( DzBone* bone, DzWeightMap &map, const DzNode &node, const DzGeometry &geom, const DzLegacyBoneVertex* vertMask, int maskCount ) { }

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LEGACY_CURVE_H