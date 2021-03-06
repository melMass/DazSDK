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
	Defines the DzOptionsDialog class.
**/

#ifndef DAZ_OPTIONS_DIALOG_H
#define DAZ_OPTIONS_DIALOG_H

/*****************************
	Include files
*****************************/

#include "dzbasicdialog.h"

/****************************
	Forward declarations
****************************/

class QLayoutItem;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzOptionsDialog : public DzBasicDialog {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzOptionsDialog( QWidget *parent, const QString &name );
	virtual ~DzOptionsDialog();

	virtual void	addLayout( QLayout *layout, int stretch = 0 );
	virtual void	addWidget( QWidget *child, int stretch = 0 );

	virtual void	addOptionsLayout( QLayout *layout, int stretch = 0 );
	virtual void	addOptionsWidget( QWidget *child, int stretch = 0 );

	void	setMainMargin( int margin );
	void	setOptionsMargin( int margin );

protected slots:

	virtual void	toggleOptions();
	virtual void	showOptions();
	virtual void	hideOptions();

protected:

	virtual bool	optionsShown();

private:

	void	updateVisRecurse( QLayoutItem *item );
	void	updateVis( QWidget *widget );
	void	updateOptionsButton();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_OPTIONS_DIALOG_H