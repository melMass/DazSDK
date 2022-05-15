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
	Defines the DzBasicDialog class.
**/

#ifndef DAZ_BASIC_DIALOG_H
#define DAZ_BASIC_DIALOG_H

/*****************************
	Include files
*****************************/
#include <QtGui/QDialog>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QAbstractButton;

/*****************************
	Class Definitions
*****************************/

class DZ_EXPORT DzBasicDialog : public QDialog {
	Q_OBJECT
	friend class DzBasicDialogEventFilter;
public:

	//
	// CREATORS
	//

	DzBasicDialog( QWidget *parent, const QString &name );
	virtual ~DzBasicDialog();

	virtual void	addLayout( QLayout *layout, int stretch = 0 );
	virtual void	addWidget( QWidget *child, int stretch = 0, Qt::Alignment alignment = 0 );
	virtual void	addStretch( int stretch = 0 );
	virtual void	addSpacing( int spacing );

	virtual void	addButton( QAbstractButton *btn, int index = 1 );

	void			insertWidget( int index, QWidget *child, int stretch = 0, Qt::Alignment alignment = 0 );

	void	setAcceptButtonText( const QString &text );
	void	setApplyButtonText( const QString &text );
	void	setCancelButtonText( const QString &text );

	void	showApplyButton( bool onOff );
	void	showCancelButton( bool onOff );
	void	showHelpButton( bool onOff );
	void	showAcceptButton( bool onOff );

	void	setApplyButtonEnabled( bool onOff );
	void	setCancelButtonEnabled( bool onOff );
	void	setHelpButtonEnabled( bool onOff );
	void	setAcceptButtonEnabled( bool onOff );

signals:
	void	applyClicked();

protected:
	bool event( QEvent *e );

	virtual void	accept();
	virtual void	reject();

protected slots:

	virtual void	apply();
	virtual void	whatsThis();

	void	saveGeometryState();
	void	restoreGeometryState();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BASIC_DIALOG_H