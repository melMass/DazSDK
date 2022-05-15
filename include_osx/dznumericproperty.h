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
	Defines the DzNumericProperty class.
**/

#ifndef DAZ_NUMERIC_PROPERTY_H
#define DAZ_NUMERIC_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzproperty.h"

/****************************
	Forward declarations
****************************/

class DzTexture;
class DzNumericController;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNumericProperty : public DzProperty {
	Q_OBJECT
	Q_ENUMS( XYZInterest )
public:
	enum XYZInterest { NO_INTEREST, X_INTEREST, Y_INTEREST, Z_INTEREST, ALL_INTEREST };

	//
	// CREATORS
	//

	DzNumericProperty();
	DzNumericProperty( const QString &name, bool canAnimate, bool isUserProperty );
	virtual ~DzNumericProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;
	virtual bool	isNumeric() const { return true; }
	virtual void	getAttributes( DzPropertySettings &settings ) const;
	virtual void	setAttributes( const DzPropertySettings &settings );
	virtual void	setCanAutoFollow( bool onOff );
	virtual DzPropertyClipboard*	copyToClipboard() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual void	setXYZInterest( XYZInterest interest );
	virtual void	setIsModulo( bool val );
	virtual void	setIsClamped( bool val );
	virtual void	setIsMappable( bool val );
	virtual void	setMap( const DzTexture *img );
	virtual void	setMap( const QString &imgFile );
	virtual void	setMustHaveMap( bool val );
	virtual void	clearMap();
	virtual void	insertController( DzNumericController *controller, int idx = -1 );
	virtual void	linkTo( DzNumericProperty *master );
	virtual void	unlink();

	//
	// ACCESSORS
	//

	virtual bool				isInvalidWithoutMap() const;
	virtual bool				isMappable() const;
	virtual bool				isMapped() const;
	virtual DzTexture*			getMapValue( DzTime time ) const;
	virtual DzTexture*			getMapValue() const;
	virtual XYZInterest			getXYZInterest() const;
	virtual bool				isModulo() const;
	virtual bool				isClamped() const;
	virtual bool				isLinked() const;
	virtual bool				isMaster() const;
	virtual DzNumericProperty*	getLinkProperty() const;
	virtual DzNumericProperty*	getFollowProperty() const;

	virtual void	setDoubleValue( double val );
	virtual void	setDoubleValue( DzTime tm, double val ) = 0;
	
	virtual double	getDoubleValue() const;
	virtual double	getDoubleValue( DzTime tm ) const = 0;

	virtual void	setDoubleDefaultValue( double val ) = 0;
	virtual double	getDoubleDefaultValue() const = 0;
	
	virtual double	getFollowValue() const;
	virtual double	getFollowValue( DzTime tm ) const;

	DzProperty*		findMatchingProperty( DzNode *node, bool useStrictMatching = true );

	void	setFollowListeners();

signals:
#ifndef Q_MOC_RUN
private:
#endif
	void	minMaxChanged();
	void	clampedChanged( bool onOff );
	void	mapChanged();
	void	linked();
	void	unlinked();

protected slots:

	void	emitMinMaxChanged();
	void	emitClampedChanged( bool onOff );
	void	emitMapChanged();
	void	emitLinked();
	void	emitUnlinked();

protected:
	struct	Data;

	DzNumericProperty( DzNumericProperty::Data *data );
	DzNumericProperty( const QString &name, bool canAnimate, bool isUserProperty, DzNumericProperty::Data *data );

	double			applyControllers( DzTime tm, double raw = 0.0, bool local = false ) const;
	double			applyControllersInverse( DzTime tm, double raw, bool local = false ) const;
	virtual void	setOwner( DzElement *owner );

private slots:

	void	linkNotify();
	void	changeFollowBone( DzBone *bone );
	void	changeFollowTarget( DzSkeleton *skel );
	void	removeFollowProperty();
	void	removeFollowNode();
	

private:

	void	setLink( DzNumericProperty *link, bool isMaster );
	void	clearLink();
	void	changeFollowNode( DzNode *node );
	void	setFollowProperty( DzNumericProperty *prop );
};

#endif // DAZ_NUMERIC_PROPERTY_H
