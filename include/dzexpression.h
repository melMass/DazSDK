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
	Defines the DzExpression class.
**/

#ifndef DAZ_EXPRESSION_H
#define DAZ_EXPRESSION_H

/*****************************
	Include files
*****************************/

#include "dznumericcontroller.h"
#include "dztypes.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzExpressionInput : public DzBase {
	Q_OBJECT
	Q_PROPERTY( bool autoOverride READ autoOverride WRITE setAutoOverride )
public:

	DzExpressionInput();
	DzExpressionInput( DzNumericProperty *prop, const QString &label );
	virtual ~DzExpressionInput();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;

	void	setAutoOverride( bool onOff );
	bool	autoOverride() const;

public slots:

	//
	// MANIPULATORS
	//

	void	setProperty( DzNumericProperty *prop );
	void	setLabel( const QString &label );

	//
	// ACCESSORS
	//

	DzNumericProperty*	getCurrentProperty() const;
	DzNumericProperty*	getProperty() const;
	QString				getLabel() const;
	QVariant			getValue( DzTime tm ) const;

signals:

	void	currentValueChanged();
	void	propertyDeleted( DzProperty *prop );
	void	sourcePropertyRemoved( DzProperty *prop);
	void	labelChanged( const QString &label );

private slots:

	void	changeFollowBone( DzBone *bone );
	void	changeFollowTarget( DzSkeleton *skel );
	void	removeSource();
	void	removeProp();
	void	sourcePropRemoved();
	void	blockSignals();
	void	unblockSignals();

private:

	void	connectToSource();
	void	changeFollowNode( DzNode *node );
	void	setProp( DzNumericProperty *prop );
	void	connectSignalBlocking();

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzExpression : public DzNumericController {
	Q_OBJECT
	Q_PROPERTY( bool active READ isActive WRITE setActive )
public:

	DzExpression();
	virtual ~DzExpression();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		postLoadFile( const DzInFile *file );
	virtual void		save( DzOutFile *file ) const;
	virtual	QString		description() const;
	virtual double		apply( double val, DzTime tm, bool local ) const;
	virtual double		applyInverse( double val, DzTime tm, bool local ) const;

	//
	// MANIPULATORS
	//

	void	setActive( bool onOff );

public slots:

	void	setExpression( const QString &script, const QString &inverseScript = QString::null );
	DzError	addInput( DzExpressionInput *input );
	DzError	removeInput( int which );
	DzError	removeInput( DzExpressionInput *input );
	void	removeAllInputs();

public:

	//
	// ACCESSORS
	//

	bool						isActive() const;
	DzExpressionInputIterator	inputIterator() const;

public slots:

	QString				getExpression() const;
	QString				getInverseExpression() const;
	int					getNumInputs() const;
	DzExpressionInput*	getInput( int which ) const;
	DzExpressionInput*	findInput( DzNumericProperty *prop ) const;
	DzExpressionInput*	findInput( const QString &label ) const;

private:

	void	clearInputs();
	void	invalidateContext();
	void	updateContext( double val, DzTime tm );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_EXPRESSION_H
