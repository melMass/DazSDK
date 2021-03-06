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
	Defines the DzFormula class.
**/

#ifndef DAZ_FORMULA_H
#define DAZ_FORMULA_H

/*****************************
	Include files
*****************************/

#include "dznumericcontroller.h"
#include "dztypes.h"

/*****************************
	Forward declarations
*****************************/

class DzFormulaController;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFormula : public DzBase {
	Q_OBJECT
	Q_ENUMS( Operation )
	friend class DzFormulaController;
public:
	enum	Operation { OpNone = -1, OpAdd, OpSubtract, OpMultiply, OpDivide, OpModulo, 
				OpInverse, OpNegate, OpMax, OpMin, OpPower, OpRoot, OpSqrt, OpAbs, OpFloor, OpCeiling, 
				OpSin, OpSinh, OpArcSin, OpCos, OpCosh, OpArcCos, OpTan, OpTanh, OpArcTan,
				OpExp, OpLog, OpLog10, OpMean, OpPushInput, OpPushConstant };

	DzFormula();
	~DzFormula();

	DzNumericPropertyListIterator	propertyListIterator() const;

public slots:

	double	evaluate( DzTime tm ) const;

	void	clear();

	bool	addOp( DzFormula::Operation op );
	bool	addOpPush( DzNumericProperty *prop );
	bool	addOpPush( float constant );

	int					getNumOperations() const;
	Operation			getOperation( int which ) const;
	DzNumericProperty*	getOperationInput( int which ) const;
	float				getOperationConstant( int which ) const;

	bool					hasInputProperty(DzNumericProperty* prop)const;
	DzFormulaController*	getOwner()const;

	void		getAllProperties( DzNumericPropertyList &propList, bool checkForDuplicates = true );
	static int	getNumArguments( DzFormula::Operation op );

signals:

	void	currentValueChanged();

private:

	float	getInputValue( int which, DzTime tm ) const;
	void	setOwner( DzFormulaController *cntrl );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzFormulaController : public DzNumericController {
	Q_OBJECT
	Q_ENUMS( Stage )
	friend class DzFormula;
public:

	enum	Stage { StageSum, StageProduct };

	DzFormulaController();
	virtual ~DzFormulaController();

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

	DzFormulaListIterator	formulaIterator( DzFormulaController::Stage sec = StageSum ) const;

public slots:

	void		addFormula( DzFormula *formula, DzFormulaController::Stage sec = StageSum );

	int			getNumFormulas( DzFormulaController::Stage sec = StageSum ) const;
	DzFormula*	getFormula( int which, DzFormulaController::Stage sec = StageSum ) const;

	void		getAllProperties( DzNumericPropertyList &propList, bool checkForDuplicates = true );

	static DzFormulaController*	findFormulaController( DzProperty *prop );

private:
	void formulaPropertyAdded(DzNumericProperty* prop);
	void formulaPropertyRemoved(DzNumericProperty* prop);

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_EXPRESSION_H
