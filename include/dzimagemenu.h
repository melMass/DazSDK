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
	Defines the DzImageMenu class.
**/

#ifndef DAZ_IMAGE_MENU_H
#define DAZ_IMAGE_MENU_H

/*****************************
	Include files
*****************************/

#include <QtGui/QPushButton>

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class DzTexture;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzImageMenu : public QPushButton {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzImageMenu( QWidget *parent = NULL, const QString &name = QString::null );
	virtual ~DzImageMenu();

	///////////////////////////////////
	// from QWidget
	virtual QSize	sizeHint() const;

	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);

public slots:
	//
	// MANIPULATORS
	//

	void	setIndeterminate();
	void	setMinimized( bool onOff );
	void	selectImage( const DzTexture *img );
	void	setDisplayImage(bool onOff);
	void	setDrawStyled(bool onOff);
	bool	isDrawStyled() const;

	//
	// ACCESSORS
	//

	DzTexture*	currentImage() const;
	bool		isMinimized() const;
	bool		getIndeterminate() const;
	
signals:

	void	selectionChanged( const DzTexture *newImage );

protected slots:

	void	showMenu();
	void	selectItem( QAction *which );
	void	updateMenu();


protected:
	////////////////////////
	// from QAbstractButton
	virtual void	paintEvent( QPaintEvent *evt );
	virtual void	drawButtonLabel();
	virtual void	showEvent( QShowEvent *e );
private:

	void	updateSelection();
	void	updateSizeHint();
	void	drawStyled( QPaintEvent *evt );
	
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_IMAGE_MENU_H


