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
	Defines the DzNumericNodeProperty class.
**/

#ifndef DAZ_NUMERIC_NODE_PROPERTY_H
#define DAZ_NUMERIC_NODE_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzfloatproperty.h"

/****************************
	Forward declarations
****************************/

class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNumericNodeProperty : public DzFloatProperty {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzNumericNodeProperty();
	DzNumericNodeProperty( const QString &name, bool canAnimate, bool isUserProperty, float initVal = 0.0f );
	virtual ~DzNumericNodeProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;
	virtual QString		getWidgetClass(bool styled=true) const;
	virtual void		copyFrom( DzProperty *prop );
	virtual void		getAttributes( DzPropertySettings &settings ) const;
	virtual void		setAttributes( const DzPropertySettings &settings );
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

	virtual DzPropertyClipboard*	copyToClipboard() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual void	setMustHaveNode( bool onOff );
	virtual void	setNode( DzNode *node );

	//
	// ACCESSORS
	//

	virtual bool	isInvalidWithoutNode() const;
	virtual DzNode*	getNode() const;

signals:
#ifndef Q_MOC_RUN
private:
#endif
	void	nodeChanged( DzNode *node );
	void	invalidWithoutNodeChanged( bool onOff );

private slots:

	void	nodeRemoved();

protected:
	DzNumericNodeProperty( DzNumericNodeProperty const* nprop );
	struct	Data;

protected slots:
	void	emitNodeChanged( DzNode *node );
	void	emitInvalidWithoutNodeChanged( bool onOff );
};

class DZ_EXPORT DzNNPropertyClipboard : public DzFloatPropertyClipboard {
	Q_OBJECT
	friend class DzNumericNodeProperty;
public:
	virtual ~DzNNPropertyClipboard();

public slots:
	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzNNPropertyClipboard( const DzNumericNodeProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NUMERIC_NODE_PROPERTY_H
