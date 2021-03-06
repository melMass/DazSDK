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
	Defines the DzFloatProperty class.
**/

#ifndef DAZ_FLOAT_PROPERTY_H
#define DAZ_FLOAT_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dznumericproperty.h"

/****************************
	Forward declarations
****************************/

class DzFloatKey;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFloatProperty : public DzNumericProperty {
	Q_OBJECT
	Q_ENUMS( InterpolationType TransformType )
	friend class FloatPropertyMaxMinUndoItem;
	friend class FloatPropertyDefValChangeUndoItem;
	friend class FloatPropertyValChangeUndoItem;
	friend class FloatPropertyKeyChangeUndoItem;
public:
	enum InterpolationType { LINEAR_INTERP, CONSTANT_INTERP, TCB_INTERP, HERMITE_INTERP };
	enum TransformType { NON_TRANSFORM = 0, SCALE, TRANSLATE, ROT_FIRST_AXIS, ROT_SECOND_AXIS, ROT_THIRD_AXIS };

	//
	// CREATORS
	//

	DzFloatProperty();
	DzFloatProperty( const QString &name, bool canAnimate, bool isUserProperty, float initVal = 0.0f );
	virtual ~DzFloatProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			save( DzOutFile *file ) const;
	virtual void			selectKey( int i, bool onOff = true );
	virtual int				selectKeys( const DzTimeRange &range, bool onOff );
	virtual int				selectAllKeys( bool onOff = true );
	virtual int				deleteKeys( int start, int end );
	virtual int				deleteSelectedKeys();
	virtual void			deleteAllKeys();
	virtual void			copyFrom( DzProperty *prop );
	virtual void			beginEdit();
	virtual void			finishEdit();
	virtual void			cancelEdit();
	virtual QString			getWidgetClass(bool styled=true) const;
	virtual int				getNumKeys() const;
	virtual DzTimeRange		getKeyRange() const;
	virtual DzTimeRange		getSelectedKeyRange() const;
	virtual int				getNumSelectedKeys() const;
	virtual DzTime			getKeyTime( int i ) const;
	virtual int				getKeyIndexRange( const DzTimeRange &iv, int &start ) const;
	virtual bool			isKey( DzTime t, int &index ) const;
	virtual bool			isKeySelected( int i ) const;
	virtual void			getAttributes( DzPropertySettings &settings ) const;
	virtual void			setAttributes( const DzPropertySettings &settings );
	virtual DzProperty*		createAlias();
	virtual DzProperty*		duplicate()const;
	virtual void			setIsClamped( bool val );

	virtual DzPropertyClipboard*	copyToClipboard() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual double	adjustValue( float val );
	virtual double	adjustValue( DzTime tm, float val );
	virtual void	setDoubleValue(DzTime tm, double val);
	virtual void	setDoubleDefaultValue(double val);
	virtual void	setValue( float val );
	virtual void	setValue( DzTime tm, float val );
	virtual void	setValue( DzTime tm, float val, InterpolationType interp );
	virtual void	setValue( DzTime tm, float val, InterpolationType interp,
						float param0, float param1, float param2 );

	virtual void	setDefaultValue( float val );
	virtual void	setKeyValue( int i, float val );
	virtual void	setKeyInterpolation( int i, InterpolationType interp );
	virtual void	setKeyInterpolation( int i, InterpolationType interp,
						float param0, float param1, float param2 );
	virtual void	setMin( float min );
	virtual void	setMax( float max );
	virtual void	setMinMax( float min, float max );
	virtual void	setSensitivity( float sens );
	virtual void	setDisplayAsPercent( bool onOff );
	virtual void	multiply( float val, bool applyToDefault = true );
	virtual void	divide( float val, bool applyToDefault = true );
	virtual void	add( float val, bool applyToDefault = true );
	virtual void	subtract( float val, bool applyToDefault = true );
	virtual void	setTransformType( DzFloatProperty::TransformType type);

public:
	//
	// ACCESSORS
	//

	virtual bool	getMinMax( float &min, float &max ) const;

public slots:

	virtual double	getDoubleValue( DzTime tm ) const;	
	virtual double	getDoubleDefaultValue() const;
	virtual double	getRawValue() const;
	virtual double	getRawValue( DzTime tm ) const;
	virtual double	getValue() const;
	virtual double	getValue( DzTime tm ) const;
	virtual double	getLocalValue() const;
	virtual double	getLocalValue( DzTime tm ) const;
	virtual double	getDefaultValue() const;
	virtual double	getKeyValue( int i ) const;

	virtual InterpolationType	getKeyInterpolationType( int i, float *param0 = NULL,
									float *param1 = NULL, float *param2 = NULL ) const;

	virtual double	getMin() const;
	virtual double	getMax() const;
	virtual bool	getDisplayAsPercent() const;
	virtual double	getSensitivity() const;
	virtual bool	currentValueIsDefaultValue() const;
	virtual void	setCurrentAttributesAsDefinition();
	virtual bool	doCurrentAttributesMatchDefinition()const;

	virtual DzFloatProperty::TransformType	getTransformType() const;

signals:
#ifndef Q_MOC_RUN
private:
#endif
	void	displayAsPercentChanged();

protected  slots:
	void	emitDisplayAsPercentChanged();

protected:
	struct	Data;

	DzFloatProperty( DzFloatProperty::Data *data );
	DzFloatProperty( DzFloatProperty const* fprop );
	DzFloatProperty( const QString &name, bool canAnimate, bool isUserProperty, float initVal, DzFloatProperty::Data *data );

private slots:

	void	updateParent();
	void	updateClamped( bool onOff );

private:

	float	interpolate( float ratio, int firstKey ) const;
	float	startingTangent( int key, const DzFloatKey *keys ) const;
	float	endingTangent( int key, const DzFloatKey *keys ) const;
};

class DZ_EXPORT DzFloatPropertyClipboard : public DzPropertyClipboard {
	Q_OBJECT
	friend class DzFloatProperty;
public:
	virtual ~DzFloatPropertyClipboard();

public slots:
	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzFloatPropertyClipboard( const DzFloatProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FLOAT_PROPERTY_H