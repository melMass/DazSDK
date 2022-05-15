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
	Defines the DzNodeProperty class.
**/

#ifndef DAZ_NODE_PROPERTY_H
#define DAZ_NODE_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzproperty.h"

/****************************
	Forward declarations
****************************/

class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNodeProperty : public DzProperty {
	Q_OBJECT
	friend class DzNodePropertyValChangeUndoItem;
	friend class DzNodePropertyKeyChangeUndoItem;
public:
	//
	// CREATORS
	//

	DzNodeProperty();
	DzNodeProperty( const QString &name, bool canAnimate, bool isUserProperty );
	virtual ~DzNodeProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;
	virtual int			deleteKeys( int start, int end );
	virtual int			deleteSelectedKeys();
	virtual void		deleteAllKeys();
	virtual void		copyFrom( DzProperty *prop );
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();
	virtual bool		isNumeric() const { return false; }
	virtual int			getNumKeys() const;
	virtual DzTimeRange getKeyRange() const;
	virtual DzTimeRange getSelectedKeyRange() const;
	virtual int			getNumSelectedKeys() const;
	virtual DzTime		getKeyTime( int i ) const;
	virtual int			getKeyIndexRange( const DzTimeRange &iv, int &start ) const;
	virtual bool		isKey( DzTime t, int &index ) const;
	virtual bool		isKeySelected( int i ) const;
	virtual QString		getWidgetClass(bool styled=true) const;
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

	virtual DzPropertyClipboard*	copyToClipboard() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual void	setDefaultValue( DzNode *val );
	virtual void	setValue( DzNode *val );
	virtual void	setValue( DzTime tm, DzNode *val );
	virtual void	setKeyValue( int which, DzNode *val );
	virtual void	exclude( const DzNode *node );

	//
	// ACCESSORS
	//

	virtual DzNode*	getDefaultValue() const;
	virtual DzNode*	getValue() const;
	virtual DzNode*	getValue( DzTime tm ) const;
	virtual DzNode*	getKeyValue( int i ) const;
	virtual bool	isExcluded( const DzNode *node ) const;
	virtual bool	currentValueIsDefaultValue() const;

signals:

	void	aboutToChange();

protected:

	struct	Data;

	DzNodeProperty( const DzNodeProperty* nprop);
	DzNodeProperty( DzNodeProperty::Data *data );
	DzNodeProperty( const QString &name, bool canAnimate, bool isUserProperty, DzNodeProperty::Data *data );
};

class DZ_EXPORT DzNodePropertyClipboard : public DzPropertyClipboard {
	Q_OBJECT
	friend class DzNodeProperty;
public:
	virtual ~DzNodePropertyClipboard();

public slots:
	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzNodePropertyClipboard( const DzNodeProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NODE_PROPERTY_H
