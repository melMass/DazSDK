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
	Defines the DzIconPushBtn class.
**/

#ifndef DZ_ICON_PUSH_BTN_H
#define DZ_ICON_PUSH_BTN_H

/****************************
	Include files
****************************/

#include <QtGui/QStyle>
#include <QtGui/QPushButton>

#include "dzgeneraldefs.h"

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzIconPushBtn : public QPushButton
{
	Q_OBJECT
public:
	DzIconPushBtn( QWidget *parent, const QString &name, QStyle::StandardPixmap pixmap );
	virtual ~DzIconPushBtn();

protected:
	virtual void	paintEvent( QPaintEvent *ev );
	virtual void	styleChange( QStyle &style );
	virtual QSize	sizeHint() const;

private:
	struct	Data;
	Data	*m_data;
};

#endif