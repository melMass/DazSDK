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
	@file
	Defines the DzPopUpWidget class.
**/
#ifndef DZ_POP_UP_WIDGET_H
#define DZ_POP_UP_WIDGET_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

#include "dztypes.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPopUpWidget : public QFrame
{
	Q_OBJECT
public:
	DzPopUpWidget( const QString &name, QWidget *parent );
	virtual ~DzPopUpWidget();

	bool			isMouseOver() const;
	static int		getScreenIndex( const QPoint &pos, QWidget *wgt );
	static QWidget*	getScreen( const QPoint &pos, QWidget *wgt );

	void	positionPopUp( QPoint &point );

signals:

	void	mouseLeave();

protected:

	virtual void	leaveEvent( QEvent *eve );
	virtual void	resizeEvent( QResizeEvent *eve );
	virtual void	createMask( const QSize &size );
	virtual void	paintEvent( QPaintEvent *ev );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DZ_POP_UP_WIDGET_H
