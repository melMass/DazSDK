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
	Defines the DzMenu class.
**/

#ifndef DAZ_MENU_H
#define DAZ_MENU_H

/*****************************
	Include files
*****************************/

#include <QtCore/QObject>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzAction;
class QAction;
class QPoint;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMenu : public QObject {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzMenu();
	virtual ~DzMenu();

public slots:

	//
	// MANIPULATORS
	//

	int		addSubMenu( const QString &label, int menu = 0 );
	int		findSubMenu( const QString &label, int menu = 0 );
	int		addAction( DzAction	*action, int menu = 0 );
	int		addAction( const QString &className, int menu = 0 );
	int		addItem( const QString &item, int menu = 0 );
	int		addItem( const QString &item, const QObject *receiver, const QString &member, int menu = 0 );
	void	addSeparator( int menu = 0 );
	int		exec();
	int		exec( const QPoint &pos );

	//
	// ACCESSORS
	//

	bool	isEmpty() const;

signals:

	void	activated( int id );

private slots:

	void	selectItem( QAction *action );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MENU_H