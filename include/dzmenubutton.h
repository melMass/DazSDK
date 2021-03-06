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
	Defines the DzMenuButton class.
**/

#ifndef DAZ_MENU_BUTTON_H
#define DAZ_MENU_BUTTON_H

/*****************************
	Include files
*****************************/

#include "dzstyledbutton.h"

/****************************
	Forward declarations
****************************/

class QMenu;

/****************************
	Constants
****************************/

#define DZ_MENU_BUTTON_NO_SELECTION		-1

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMenuButton : public DzStyledButton {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzMenuButton( QWidget *parent, const QString &name, QString indeterminateText = QString::null );
	virtual ~DzMenuButton();

public slots:

	//
	// MANIPULATORS
	//

	int		insertItem( const QString &text, int id = -1, int index = -1 );
	int		insertSeparator( int index = -1 );
	void	removeItem( int menuID );
	void	removeItemAt( int index );
	void	selectItem( int menuID );
	void	selectItemAt( int index );
	void	setItemEnabled( int menuID, bool enable );
	void	setItemEnabledAt( int index, bool enable );
	void	setButtonText( const QString &text );
	void	setIndeterminateText( const QString &text, bool setIndeterminateNow = false );
	void	setIndeterminate();
	void	clear();

	//
	// ACCESSORS
	//

	QMenu*	getMenu() const;
	QString	getButtonText() const;
	QString	getIndeterminateText() const;
	int		getSelectionIndex() const;
	int		getSelectionID() const;
	int		count() const;

protected:

	//
	// MANIPULATORS
	//

	void			setButtonText( int menuID );

	virtual void	mousePressEvent( QMouseEvent *e );
	int				actionIndexOf(int menuID)const;

signals:

	void	menuIDSelected( int menuID );
	void	menuIndexSelected( int menuIndex );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MENU_BUTTON_H


