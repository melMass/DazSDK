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
	Defines the DzThreadMgr class.
**/

#ifndef DAZ_THREAD_MGR_H
#define DAZ_THREAD_MGR_H

/****************************
	Include files
****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzThreadOp;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzThreadMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
private:

	//
	// CONSTRUCTORS
	//

	DzThreadMgr();
	~DzThreadMgr();

public slots:

	//
	// MANIPULATORS
	//

	void	enableMultiThreading( bool onOff );

	//
	// ACCESSORS
	//

	bool	isMultiThreadingEnabled() const;
	int		getNumThreads() const;

public:

	void	addThreadOp( DzThreadOp *op );
	void	wait();

signals:

	void	multiThreadingEnabled( bool onOff );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_THREAD_MGR_H