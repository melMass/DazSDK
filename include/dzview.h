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
	Defines the DzView class.
**/

#ifndef DAZ_VIEW_H
#define DAZ_VIEW_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class Dz3DViewport;
class DzView;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzViewToolBar : public QWidget {
	Q_OBJECT
	friend class DzView;

public:
	enum LayoutSide { Left = 0, Right };

private:
	DzViewToolBar( DzView *parent );
	~DzViewToolBar();

public:

	void	addWidget( QWidget *widget, LayoutSide side = Right );
	void	addLayout( QLayout *layout, LayoutSide side = Right);
	void	addSpacing( int spacing, LayoutSide side = Right );
	void	addStretch( int stretch, LayoutSide side = Right );

protected:
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &oldStyle );

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzView : public QWidget {
	Q_OBJECT
	friend class DzViewport;
public:
	//
	// CREATORS
	//

	DzView( const QString &name = QString::null );
	virtual ~DzView();

public slots:

	virtual QString	getDescription() const = 0;
	virtual QPixmap	getIcon() const = 0;

public:

	void	setViewport( Dz3DViewport *viewport );

protected:

	DzViewToolBar*	getToolBar() const;
	virtual void	styleChange( QStyle &oldStyle );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_VIEW_H
