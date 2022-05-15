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
	Defines the DzBoolButton class.
**/

#ifndef DAZ_BOOL_BUTTON_H
#define DAZ_BOOL_BUTTON_H

/*****************************
	Include files
*****************************/

#include <QtGui/QPushButton>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBoolButton : public QPushButton
{
	Q_OBJECT
public:

	enum ButtonState { BStOff, BStOn, BStMult };

	//
	// CREATORS
	//

	DzBoolButton( QWidget *parent, const QString &trueText = QString::null, const QString &falseText = QString::null, const QString &name = QString::null );
	virtual ~DzBoolButton();

	//
	// MANIPULATORS
	//

	void			setState( ButtonState state );
	void			setStateText( const QString &trueText, const QString &falseText );

	//
	// ACCESSORS
	//

	ButtonState		getState() const;

public slots:

	virtual void	toggle();

signals:

	void			stateChanged( DzBoolButton::ButtonState state );

protected:
	void			paintEvent( QPaintEvent *event );
	virtual void	nextCheckState();

private:
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BOOL_BUTTON_H


