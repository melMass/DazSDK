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
	Defines the DzBulgeBinding class.
**/

#ifndef DAZ_BULGE_BINDING_H
#define DAZ_BULGE_BINDING_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"

/****************************
	Forward declarations
****************************/

class DzWeightMap;
class DzFloatProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBulgeBinding : public DzElement {
	Q_OBJECT
	friend class DzBulgeBindingFactory;
public:

	//
	// CREATORS
	//

	DzBulgeBinding();
	virtual ~DzBulgeBinding();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;
	virtual void		setStorablePaths( const QString &path );
	virtual void		postLoadFile( const DzInFile *file );

	//
	// MANIPULATORS
	//
	void				setAxis( int axis );
	void				setBulgeValues( float posLeft, float posRight, float negLeft, float negRight, bool setAsDefault=false );
	DzError				setLeftWeights( DzWeightMap *map );
	DzError				setRightWeights( DzWeightMap *map );

public slots:
	void				setPosLeftBulge( float val, bool setAsDefault=false );
	void				setPosRightBulge( float val, bool setAsDefault=false );
	void				setNegLeftBulge( float val, bool setAsDefault=false );
	void				setNegRightBulge( float val, bool setAsDefault=false );
	//
	// ACCESSORS
	//
public:
	int					getAxis() const;
	void				getBulgeValues( float &posLeft, float &posRight, float &negLeft, float &negRight, bool defaultVal = false ) const;
	float				getPosLeftBulge(bool defaultVal = false) const;
	float				getPosRightBulge(bool defaultVal = false) const;
	float				getNegLeftBulge(bool defaultVal = false) const;
	float				getNegRightBulge(bool defaultVal = false) const;
	DzFloatProperty*	getPosLeftBulgeController() const;
	DzFloatProperty*	getPosRightBulgeController() const;
	DzFloatProperty*	getNegLeftBulgeController() const;
	DzFloatProperty*	getNegRightBulgeController() const;
	DzWeightMap*		getLeftWeights() const;
	DzWeightMap*		getRightWeights() const;
	void				updatePropertyNames();

signals:

	void				weightsChanged();
	void				weightListChanged();
	void				currentValueChanged();
	void				attributesChanged();

protected:
	DzBulgeBinding( const DzInFile *file );

private:

	void				updateLeftMapName();
	void				updateRightMapName();
	void				createProperties();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BULGE_BINDING_H
