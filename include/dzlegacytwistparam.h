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
	Defines the DzLegacyTwistParam class.
**/

#ifndef DAZ_LEGACY_TWIST_PARAM_H
#define DAZ_LEGACY_TWIST_PARAM_H

/*****************************
	Include files
*****************************/

#include "dzlegacyjointparam.h"

/*****************************
	Forward declarations
*****************************/

class DzFloatProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLegacyTwistParam : public DzLegacyJointParam {
	Q_OBJECT
	Q_PROPERTY( bool applyBlend READ applyBlend WRITE setApplyBlend )
	Q_PROPERTY( double start READ getStartDouble WRITE setStartDouble )
	Q_PROPERTY( double end READ getEndDouble WRITE setEndDouble )
	friend class DzLegacyTwistParamFactory;
public:

	DzLegacyTwistParam();
	DzLegacyTwistParam( DzBone *driver, DzLegacyJointParam::ParamAxis axis );
	DzLegacyTwistParam( DzBone *driver, DzLegacyJointParam::ParamAxis axis, float start, float end );
	virtual ~DzLegacyTwistParam();

	//
	// MANIPULATORS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		postLoadFile( const DzInFile *file );

	virtual ParamType	type() const { return DzLegacyJointParam::Rotation; }
	virtual DzLegacyJointParam* deepCopy() const;
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();

	void	setApplyBlend( bool onOff );
	void	setStart( float start, bool makeDefault = false );
	void	setEnd( float end, bool makeDefault = false );
	// Double versions needed for Q_PROPERTY properties to work in DAZScript
	void	setStartDouble( double start );
	void	setEndDouble( double end );

public slots:

	void				setBlendZone( float start, float end, bool makeDefault = false );
	DzFloatProperty*	getBlendStartPostionController() const;
	DzFloatProperty*	getBlendEndPostionController() const;

public:

	//
	// ACCESSORS
	//

	virtual void	save( DzOutFile *file ) const;

	bool	applyBlend() const;
	void	getBlendZone( float &start, float &end ) const;
	float	getStart() const;
	float	getEnd() const;
	// Double versions needed for Q_PROPERTY properties to work in DAZScript
	double	getStartDouble() const;
	double	getEndDouble() const;

public:
	DzLegacyTwistParam( const DzInFile *file ); //internal use only

protected:
	virtual void	updateWeights( DzBone* bone, DzWeightMap &map, const DzNode &node, const DzGeometry &geom, const DzLegacyBoneVertex* vertMask, int maskCount );

private:
	void	createProperties();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LEGACY_TWIST_PARAM_H