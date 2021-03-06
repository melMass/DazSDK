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
	Defines the DzERCLink class.
**/

#ifndef DAZ_ERC_LINK_H
#define DAZ_ERC_LINK_H

/*****************************
	Include files
*****************************/

#include "dznumericcontroller.h"
#include "dztstack.h"

/****************************
	Forward declarations
****************************/

class DzBone;
class DzNode;
class DzNumericProperty;
class DzSkeleton;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzERCLink : public DzNumericController {
	Q_OBJECT
	Q_ENUMS( ERCType ERCKeyInterpolation );
	Q_PROPERTY( bool active READ isActive WRITE setActive )
	Q_PROPERTY( bool autoOverride READ autoOverride WRITE setAutoOverride )
	Q_PROPERTY( bool isUserLink READ isUserLink WRITE setUserLink )
	Q_PROPERTY( double scalar READ getScalar WRITE setScalar )
	Q_PROPERTY( double addend READ getAddend WRITE setAddend )
	Q_PROPERTY( ERCType type READ getType WRITE setType )
	Q_PROPERTY( ERCKeyInterpolation keyInterpolation READ getKeyInterpolation WRITE setKeyInterpolation )
public:

	enum ERCType { ERCDeltaAdd = 0, ERCDivideInto, ERCDivideBy, ERCMultiply, ERCSubtract, ERCAdd, ERCKeyed };
	enum ERCKeyInterpolation { LINEAR_INTERP, CONSTANT_INTERP, TCB_INTERP  };

	DzERCLink();
	DzERCLink( DzNumericProperty *property, double scalar = 1.0, double addend = 0.0 );
	DzERCLink( ERCType type, DzNumericProperty *property, double scalar = 1.0, double addend = 0.0 );
	virtual ~DzERCLink();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;
	virtual	QString	description() const;
	virtual QString slaveDescription() const;
	virtual double	apply( double val, DzTime tm, bool local ) const;
	virtual double	applyInverse( double val, DzTime tm, bool local ) const;

	//
	// MANIPULATORS
	//

	void	setActive( bool onOff );
	void	setScalar( double val );
	void	setAddend( double val );
	void	setAutoOverride( bool onOff );
	void	setType( ERCType type );
	void	setKeyInterpolation( ERCKeyInterpolation interp );
	void	setUserLink( bool yesNo );
	void	setSaveWithOutput( bool yesNo );

	//
	// ACCESSORS
	//

	double	evaluate( DzTime time, bool local = false ) const;
	bool	isActive() const;
	double	getScalar() const;
	double	getAddend() const;
	bool	autoOverride() const;
	ERCType	getType() const;
	ERCKeyInterpolation	getKeyInterpolation() const;
	bool	isUserLink() const;
	bool	getSaveWithOutput() const;

	//
	// STATIC METHODS
	//

	static bool			testCircularLink( DzNumericProperty *control, DzNumericProperty *slave );
	static DzERCLink*	createErcLink( DzNumericProperty *control, DzNumericProperty *slave,
									int index = -1 );
	static bool			shouldERCSaveWithOutput( DzNumericProperty *control, DzNumericProperty * output );
	static QString		getERCText( ERCType type );
	static QString		getPropertyDescriptionText( DzProperty* prop);

	bool				getKeyValue(int which, double& key, double& value, double& t, double& c, double& b)const;
	bool				getKeyValue( int which, double& key, double& value ) const;
	bool				isKey( double t, int &index ) const;

public slots:

	DzNumericProperty*	getCurrentProperty() const;
	DzNumericProperty*	getProperty() const;
	void				setProperty( DzNumericProperty *prop );

	int					getNumKeyValues()const;
	
	int					findKeyIndex(double key);
	int					addKeyValue(double key, double value);
	int					addKeyValue( double key, double value, double t, double c, double b );
	bool				removeKeyValue(int which);
	
	double				getKey(int which)const;
	double				getKeyValue(int which)const;
	double				getKeyParamT(int which)const;
	double				getKeyParamC(int which)const;
	double				getKeyParamB(int which)const;

	double				getKeyOpValue( double val ) const;

signals:

	void	propertyDeleted( DzProperty *prop );
	void	ercSourcePropertyRemoved( DzProperty *prop);

private slots:

	void	changeFollowBone( DzBone *bone );
	void	changeFollowTarget( DzSkeleton *skel );
	void	blockSignals();
	void	unblockSignals();
	void	removeSource();
	void	removeProp();
	void	sourcePropRemoved();

protected:
	virtual void aboutToBeRemoved( DzProperty* prop );
	virtual void wasAdded( DzProperty* prop );

	void modifyERCAssetOwner( DzProperty* prop );
private:

	void	connectToSource();
	void	changeFollowNode( DzNode *node );
	void	setProp( DzNumericProperty *prop );
	void	connectSignalBlocking();

	static bool	testERC( DzNumericProperty *ctrl, DzNumericProperty *slave,
					DzTStack<DzNumericProperty*> &testStack );
	double	interpolate( double ratio, int firstKey ) const;
	struct Data;
	Data	*m_data;
};

#endif // DAZ_ERC_LINK_H
