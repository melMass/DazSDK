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

#ifndef DAZ_PROGRESS_H
#define DAZ_PROGRESS_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

///////////////////////////////////////////////////////////////////////
// IDzProgress
///////////////////////////////////////////////////////////////////////

class DZ_EXPORT IDzProgress {
public:
	virtual ~IDzProgress();

	virtual void	step( int numSteps = 1 ) = 0;
	virtual void	update( int position ) = 0;
	virtual void	cancel() = 0;
	virtual void	finish() = 0;

	virtual void	setInfo( const QString &info ) = 0;

	virtual bool	isCancelled() const = 0;
};

///////////////////////////////////////////////////////////////////////
// DzProgress
///////////////////////////////////////////////////////////////////////

class DZ_EXPORT DzProgress : public IDzProgress {
public:
	DzProgress( const QString &info, int totalSteps = 0, bool isCancellable = false, 
		bool showTimeElapsed = false );
	virtual ~DzProgress();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	step( int numSteps = 1 );
	virtual void	update( int position );
	virtual void	cancel();
	virtual void	finish();

	virtual void	setInfo( const QString &info );

	virtual bool	isCancelled() const;

	//
	// MANIPULATORS
	//

	void	setAdditionalInfoWidget( QWidget *wid );
	void	setUseCloseCheckbox( bool showClose );
	void	setCloseOnFinish( bool closeOnFinish );
	void	setShowTimeElapsed( bool showElapsed );
	void	setShowTimeEstimate( bool showEstimate );

	//
	// ACCESSORS
	//

	QWidget*	getAdditionalInfoWidget() const;
	bool		isShowingCloseCheckbox() const;
	bool		isCloseOnFinish() const;
	bool		isShowingTimeElapsed() const;
	bool		isShowingTimeEstimate() const;

	//
	// STATIC
	//

	static void	enable( bool onOff = true );
	static bool	isEnabled();
	static void	pause();
	static void	resume();
	static bool	isActive();
	static void	setCurrentInfo( const QString &info );

private:
	struct	Data;
	Data	*m_data;
};

///////////////////////////////////////////////////////////////////////
// DzBackgroundProgress
///////////////////////////////////////////////////////////////////////

class DZ_EXPORT DzBackgroundProgress : public IDzProgress
{
public:
	DzBackgroundProgress( const QString &info, int totalSteps, bool isCancellable = false );
	virtual ~DzBackgroundProgress();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	step( int numSteps = 1 );
	virtual void	update( int position );
	virtual void	cancel();
	virtual void	finish();

	virtual void	setInfo( const QString &info );

	virtual bool	isCancelled() const;

	//
	// STATIC
	//

	static bool		isActive();

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PROGRESS_H