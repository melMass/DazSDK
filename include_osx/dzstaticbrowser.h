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
	Defines the DzStaticBrowser class.
**/

#ifndef DAZ_STATIC_BROWSER_H
#define DAZ_STATIC_BROWSER_H

/*****************************
	Include files
*****************************/

#include <QtGui/QTextBrowser>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStaticBrowser : public QTextBrowser {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStaticBrowser( QWidget *parent, const QString &name = QString::null, bool autoFollowLinks = true );
	virtual ~DzStaticBrowser();

public slots:
	//
	// MANIPULATORS
	//

	virtual void		setSource( const QString &name );
	virtual void		setText( const QString &txt, const QString &context );
	virtual QVariant	loadResource( int type, const QUrl &name );

	void	setAutoFollowLinks( bool onOff );

	bool	getAutoFollowLinks() const;

private slots:

	void	followLink( const QUrl &link );
	void	finished( int id, bool error );
	void	loadingFinished();
	void	loadItem( const QString &name );
	void	loadedItem( const QString &item );

signals:

	void	requestFailed();

private:
	//
	// DATA MEMBERS
	//
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STATIC_BROWSER_H
