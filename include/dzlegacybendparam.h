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
	Defines the DzLegacyBendParam class.
**/

#ifndef DAZ_LEGACY_BEND_PARAM_H
#define DAZ_LEGACY_BEND_PARAM_H

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

class DZ_EXPORT DzLegacyBendParam : public DzLegacyJointParam {
	Q_OBJECT
	Q_PROPERTY( bool applyAngles READ applyAngles WRITE setApplyAngles )
	Q_PROPERTY( double staticAngleA READ getStaticADouble WRITE setStaticADouble )
	Q_PROPERTY( double dynamicAngleB READ getDynamicBDouble WRITE setDynamicBDouble )
	Q_PROPERTY( double dynamicAngleC READ getDynamicCDouble WRITE setDynamicCDouble )
	Q_PROPERTY( double staticAngleD READ getStaticDDouble WRITE setStaticDDouble )
	Q_PROPERTY( bool applyBulges READ applyBulges WRITE setApplyBulges )
	Q_PROPERTY( double posLeftBulge READ getPosLeftBulgeDouble WRITE setPosLeftBulgeDouble )
	Q_PROPERTY( double posRightBulge READ getPosRightBulgeDouble WRITE setPosRightBulgeDouble )
	Q_PROPERTY( double negLeftBulge READ getNegLeftBulgeDouble WRITE setNegLeftBulgeDouble )
	Q_PROPERTY( double negRightBulge READ getNegRightBulgeDouble WRITE setNegRightBulgeDouble )
	friend class DzLegacyBendParamFactory;
public:

	DzLegacyBendParam();
	DzLegacyBendParam( DzBone *driver, DzLegacyJointParam::ParamAxis axis );
	virtual ~DzLegacyBendParam();

	//
	// MANIPULATORS
	//

	//////////////////////////////
	// from DzBase
	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		postLoadFile( const DzInFile *file );
	virtual void		save( DzOutFile *file ) const;
	virtual ParamType	type() const { return DzLegacyJointParam::Rotation; }
	virtual DzLegacyJointParam* deepCopy() const;
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();

	void	setApplyAngles( bool onOff );
	void	setStaticA( float angle, bool makeDefault = false );
	void	setDynamicB( float angle, bool makeDefault = false );
	void	setDynamicC( float angle, bool makeDefault = false );
	void	setStaticD( float angle, bool makeDefault = false );

	void	setApplyBulges( bool onOff );
	void	setPosLeftBulge( float bulge, bool makeDefault = false );
	void	setPosRightBulge( float bulge, bool makeDefault = false );
	void	setNegLeftBulge( float bulge, bool makeDefault = false );
	void	setNegRightBulge( float bulge, bool makeDefault = false );
	
	// Double versions needed for Q_PROPERTY properties to work in DAZScript
	void	setStaticADouble( double angle );
	void	setDynamicBDouble( double angle );
	void	setDynamicCDouble( double angle );
	void	setStaticDDouble( double angle );
	void	setPosLeftBulgeDouble( double bulge );
	void	setPosRightBulgeDouble( double bulge );
	void	setNegLeftBulgeDouble( double bulge );
	void	setNegRightBulgeDouble( double bulge );

	void	setLeftBulgeWeights( DzWeightMap *map );
	void	setRightBulgeWeights( DzWeightMap *map );

public slots:

	void	setAngles( float staticA, float dynamicB, float dynamicC, float staticD, bool makeDefault = false );
	void	setBulges( float posLeft, float posRight, float negLeft, float negRight, bool makeDefault = false );

	DzFloatProperty*	getPosLeftBulgeController() const;
	DzFloatProperty*	getPosRightBulgeController() const;
	DzFloatProperty*	getNegLeftBulgeController() const;
	DzFloatProperty*	getNegRightBulgeController() const;
	DzFloatProperty*	getStaticAngleAController() const;
	DzFloatProperty*	getDynamicAngleBController() const;
	DzFloatProperty*	getDynamicAngleCController() const;
	DzFloatProperty*	getStaticAngleDController() const;

public:
	//
	// ACCESSORS
	//
	bool	applyAngles() const;
	float	getStaticA() const;
	float	getDynamicB() const;
	float	getDynamicC() const;
	float	getStaticD() const;
	void	getAngles( float &staticA, float &dynamicB, float &dynamicC, float &staticD ) const;

	bool	applyBulges() const;
	float	getPosLeftBulge() const;
	float	getPosRightBulge() const;
	float	getNegLeftBulge() const;
	float	getNegRightBulge() const;
	void	getBulges( float &posLeft, float &posRight, float &negLeft, float &negRight ) const;

	// Double versions needed for Q_PROPERTY properties to work in DAZScript
	double	getStaticADouble() const;
	double	getDynamicBDouble() const;
	double	getDynamicCDouble() const;
	double	getStaticDDouble() const;
	double	getPosLeftBulgeDouble() const;
	double	getPosRightBulgeDouble() const;
	double	getNegLeftBulgeDouble() const;
	double	getNegRightBulgeDouble() const;

	const DzWeightMap*	getLeftBulgeWeights() const;
	const DzWeightMap*	getRightBulgeWeights() const;

public:
	DzLegacyBendParam( const DzInFile *file ); //internal use only

protected:
	virtual void	updateWeights( DzBone* bone, DzWeightMap &map, const DzNode &node, const DzGeometry &geom, const DzLegacyBoneVertex* vertMask, int maskCount );

private:
	void	createProperties();

	unsigned short	getVertexWeight( const DzVec3 &origin, const DzPnt3 pos, unsigned short &leftBulge, 
						unsigned short &rightBulge ) const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_LEGACY_BEND_PARAM_H
