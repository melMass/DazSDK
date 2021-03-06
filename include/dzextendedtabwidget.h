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

#ifndef DZ_EXTENDED_TAB_WIDGET_H
#define DZ_EXTENDED_TAB_WIDGET_H

/*****************************
	Include files
*****************************/

#include <QtGui/QTabWidget>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzExtendedTabWidget : public QTabWidget {
	Q_OBJECT
public:
	DzExtendedTabWidget( QWidget *parent = NULL,bool backgroundStyled = false );
	virtual ~DzExtendedTabWidget();

	void		setIsBackgroundStyled( bool onOff );
	bool		backgroundStyled() const;
	QTabBar*	tabBar();

protected:
	virtual void	paintEvent( QPaintEvent *e );

signals:
	void	tabClicked( int tabIndex );

private:
	struct	Data;
	Data	*m_data;
};

#endif