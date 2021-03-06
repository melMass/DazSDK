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
	Defines the DzViewport class.
**/

#ifndef DAZ_VIEWPORT_H
#define DAZ_VIEWPORT_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzViewportMgr;
class Dz3DViewport;
class DzOptionsMenu;
class QComboBox;
class DzViewAction;
class DzCamera;
class DzLight;
class DzView;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzViewport : public QFrame {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzViewport( DzViewportMgr *parent, const QString &name );
	virtual ~DzViewport();

	//
	// MANIPULATORS
	//

public slots:

	void	setView( DzView *view );

	//
	// ACCESSORS
	//

	Dz3DViewport*	get3DViewport() const;
	DzViewportMgr*	getManager() const;
	DzView*			getView() const;

protected:

	//
	// REIMPLEMENTATIONS
	//

	virtual void	styleChange( QStyle &oldStyle );
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	resizeEvent( QResizeEvent *e );

private slots:

	void	updateActiveView();
	void	changeView( int which );
	void	closeView();

signals:
	void	viewChanged( DzView *view );
	void	dimensionsChanged();

private:
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_VIEWPORT_H
