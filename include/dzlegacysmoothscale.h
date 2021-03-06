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
	Defines the DzLegacySmoothScale class.
**/

#ifndef DAZ_LEGACY_SMOOTH_SCALE_H
#define DAZ_LEGACY_SMOOTH_SCALE_H

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

class DZ_EXPORT DzLegacySmoothScale : public DzLegacyJointParam {
	Q_OBJECT
	Q_PROPERTY( bool applyZones READ applyZones WRITE setApplyZones )
	Q_PROPERTY( double loEnd READ getLoEndDouble WRITE setLoEndDouble )
	Q_PROPERTY( double loStart READ getLoStartDouble WRITE setLoStartDouble )
	Q_PROPERTY( double hiStart READ getHiStartDouble WRITE setHiStartDouble )
	Q_PROPERTY( double hiEnd READ getHiEndDouble WRITE setHiEndDouble )
	friend class DzLegacySmoothScaleFactory;
public:
	DzLegacySmoothScale();
	DzLegacySmoothScale( DzBone *driver, DzLegacyJointParam::ParamAxis axis );
	DzLegacySmoothScale( DzBone *driver, DzLegacyJointParam::ParamAxis axis,
		float loEnd, float loStart, float hiStart, float hiEnd );
	virtual ~DzLegacySmoothScale();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		postLoadFile( const DzInFile *file );

	virtual ParamType	type() const { return DzLegacyJointParam::Scale; }
	virtual DzLegacyJointParam* deepCopy() const;
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();
	virtual void		save( DzOutFile *file ) const;

	//
	// MANIPULATORS
	//

	void	setLoEnd( float val, bool makeDefault = false );
	void	setLoStart( float val, bool makeDefault = false );
	void	setHiStart( float val, bool makeDefault = false );
	void	setHiEnd( float val, bool makeDefault = false );
	// Double versions needed for Q_PROPERTY properties to work in DAZScript
	void	setLoEndDouble( double val );
	void	setLoStartDouble( double val );
	void	setHiStartDouble( double val );
	void	setHiEndDouble( double val );

	void	setApplyZones( bool onOff );

public slots:

	void				setSmoothZones( float loEnd, float loStart, float hiStart, float hiEnd, bool makeDefault = false );
	DzFloatProperty*	getLoStartController() const;
	DzFloatProperty*	getLoEndController() const;
	DzFloatProperty*	getHiStartController() const;
	DzFloatProperty*	getHiEndController() const;

public:
	//
	// ACCESSORS
	//

	bool	applyZones() const;
	float	getLoEnd() const;
	float	getLoStart() const;
	float	getHiStart() const;
	float	getHiEnd() const;
	// Double versions needed for Q_PROPERTY properties to work in DAZScript
	double	getLoEndDouble() const;
	double	getLoStartDouble() const;
	double	getHiStartDouble() const;
	double	getHiEndDouble() const;

	void	getSmoothZones( float &loEnd, float &loStart, float &hiStart, float &hiEnd ) const;
	bool	loValid() const;
	bool	hiValid() const;

public:
	DzLegacySmoothScale( const DzInFile *file ); //internal use only
	
protected:
	virtual void	updateWeights( DzBone* bone, DzWeightMap &map, const DzNode &node, const DzGeometry &geom, const DzLegacyBoneVertex* vertMask, int maskCount );
	void			updateValues();

private:
	void	createProperties();
	float	getVertexWeight( const DzPnt3 pos, bool high ) const;
	
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LEGACY_SMOOTH_SCALE_H