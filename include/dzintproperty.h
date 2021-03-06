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
	Defines the DzIntProperty class.
**/

#ifndef DAZ_INT_PROPERTY_H
#define DAZ_INT_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dznumericproperty.h"
#include "dztsimplearray.h"

/****************************
	Forward declarations
****************************/

class DzIntKeysList;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzIntKey {
public:
	int				m_data;
	DzTime			m_time;
	unsigned short	m_selected:1;

	bool			operator==( const DzIntKey &key ) const
						{ return (m_data == key.m_data && m_time == key.m_time); }
};

class DZ_EXPORT DzIntKeyArray : public DzTSimpleArray<DzIntKey> { };

class DZ_EXPORT DzIntProperty : public DzNumericProperty {
	Q_OBJECT
	friend class IntPropertyMaxMinUndoItem;
	friend class IntPropertyValueUndoItem;
	friend class IntPropertyKeyChangeUndoItem;
public:
	//
	// CREATORS
	//

	DzIntProperty();
	DzIntProperty( const QString &name, bool canAnimate, bool isUserProperty, int initVal = 0 );
	virtual ~DzIntProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;
	virtual void		selectKey( int i, bool onOff = true );
	virtual int			selectKeys( const DzTimeRange &range, bool onOff );
	virtual int			selectAllKeys( bool onOff = true );
	virtual int			deleteKeys( int start, int end );
	virtual int			deleteSelectedKeys();
	virtual void		deleteAllKeys();
	virtual void		copyFrom( DzProperty *prop );
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();
	virtual QString		getWidgetClass(bool styled/*=true*/) const;
	virtual int			getNumKeys() const;
	virtual DzTimeRange getKeyRange() const;
	virtual DzTimeRange getSelectedKeyRange() const;
	virtual int			getNumSelectedKeys() const;
	virtual DzTime		getKeyTime( int i ) const;
	virtual int			getKeyIndexRange( const DzTimeRange &iv, int &start ) const;
	virtual bool		isKey( DzTime t, int &index ) const;
	virtual bool		isKeySelected( int i ) const;
	virtual void		getAttributes( DzPropertySettings &settings ) const;
	virtual void		setAttributes( const DzPropertySettings &settings );
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

	virtual DzPropertyClipboard*	copyToClipboard() const;

	virtual void	setRawValue( DzTime tm, int val );
	virtual void	setRawValue( int val );

public slots:

	//
	// MANIPULATORS
	//
	virtual void	setDoubleValue( DzTime tm, double val );
	virtual void	setDoubleDefaultValue(double val);
	virtual int		adjustValue( int val );
	virtual int		adjustValue( DzTime tm, int val );
	virtual void	setValue( int val );
	virtual void	setValue( DzTime tm, int val );
	virtual void	setDefaultValue( int val );
	virtual void	setKeyValue( int keyIndex, int val );
	virtual void	setMin( int min );
	virtual void	setMax( int max );
	virtual void	setMinMax( int min, int max );
	virtual void	setSensitivity( int sens );

public:
	//
	// ACCESSORS
	//

	virtual bool	getMinMax( int &min, int &max ) const;

public slots:

	
	virtual double	getDoubleValue(DzTime tm) const;
	virtual double	getDoubleDefaultValue() const;
	virtual int		getRawValue() const;
	virtual int		getRawValue( DzTime tm ) const;
	virtual int		getValue( DzTime tm ) const;
	virtual int		getValue() const;
	virtual int		getLocalValue() const;
	virtual int		getLocalValue( DzTime tm ) const;
	virtual int		getDefaultValue() const;
	virtual int		getKeyValue( int i ) const;
	virtual int		getMin() const;
	virtual int		getMax() const;
	virtual int		getSensitivity() const;
	virtual bool	currentValueIsDefaultValue() const;
	virtual void	setCurrentAttributesAsDefinition();	
	virtual bool	doCurrentAttributesMatchDefinition()const;

protected:

	struct	Data;

	DzIntProperty( DzIntProperty::Data *data );
	DzIntProperty( const QString &name, bool canAnimate, bool isUserProperty, int initVal, DzIntProperty::Data *data );
	DzIntProperty( DzIntProperty const* iprop );
	DzIntKeyArray&			getKeys();
	const DzIntKeyArray&	getKeys() const;
};

class DZ_EXPORT DzIntPropertyClipboard : public DzPropertyClipboard {
	Q_OBJECT
	friend class DzIntProperty;
public:
	virtual ~DzIntPropertyClipboard();

public slots:
	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzIntPropertyClipboard( const DzIntProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_INT_PROPERTY_H