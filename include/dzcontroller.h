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
	Defines the DzController class.
**/

#ifndef DAZ_CONTROLLER_H
#define DAZ_CONTROLLER_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/*****************************
	Forward declarations
*****************************/

class DzProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzController : public DzBase {
	Q_OBJECT
	Q_PROPERTY( QString description READ description )
	Q_PROPERTY( int effect READ effectAsInt )
	friend class DzProperty;
public:

	enum ControllerEffect { None = 0, Additive, Replace };

	DzController( ControllerEffect effect );
	virtual ~DzController();

	virtual	QString		description() const = 0;
	virtual	QString		slaveDescription() const;
	ControllerEffect	effect() const;
	int					effectAsInt() const { return (int) effect(); }

public slots:
	DzProperty*	getOwner() const;

signals:

	void	currentValueChanged();
	void	attributeChanged();

protected:
	void	addSlaveControlToMaster( DzProperty *masterProperty );
	void	removeSlaveControlFromMaster( DzProperty *masterProperty );
	virtual void aboutToBeRemoved( DzProperty* prop );
	virtual void wasAdded( DzProperty* prop );

private:
	void	setOwner( DzProperty *prop );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_CONTROLLER_H
