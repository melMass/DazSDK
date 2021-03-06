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
	Defines the DzNumericNodePropertyWgt class.
**/

#ifndef DAZ_NUMERIC_NODE_PROPERTY_WGT_H
#define DAZ_NUMERIC_NODE_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzbasicpropertywgt.h"

/****************************
	Forward declarations
****************************/

class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNumericNodePropertyWgt : public DzBasicPropertyWgt {
	Q_OBJECT
public:

	enum NodeDisplay { PropertyDependent, AlwaysDisplayNode, NeverDisplayNode };

	//
	// CREATORS
	//

	DzNumericNodePropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzNumericNodePropertyWgt();

public slots:

	virtual DzError addProperty( DzProperty *prop );
	virtual void	removeAllProperties();
	virtual bool	doOptionsDialog();

	void			setNodeDisplay( NodeDisplay mode );
	NodeDisplay		getNodeDisplay() const;

protected slots:

	virtual void	updateValue();
	virtual void	updateFromList();

protected:

	virtual void	showEvent( QShowEvent *e );

private slots:

	void	changeNode( DzNode *node );
	void	setValue( float val );
	void	propertyChangeNotify();
	void	propStateChangeNotify();
	void	startEdit();
	void	finishEdit();

private:

	void	setLayout( int layout );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NUMERIC_NODE_PROPERTY_WGT_H

