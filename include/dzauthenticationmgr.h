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
	Defines the DzAuthenticationMgr class.
**/

#ifndef DZ_AUTHENTICATION_MGR_H
#define DZ_AUTHENTICATION_MGR_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzAuthenticationMgrImpl;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAuthenticationMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
private:
	DzAuthenticationMgr();
	~DzAuthenticationMgr();

public slots:
	bool	authenticateUser();
	bool	isAuthenticated();
	QString	getUserToken();
	void	logout();

signals:
	void	loggedIn();
	void	loggedOut();

private:
	DzAuthenticationMgrImpl *m_impl;
};

#endif // DZ_AUTHENTICATION_MGR_H
