/**********************************************************************
	Copyright (c) 2002-2020 Daz 3D, Inc. All Rights Reserved.

	This file is part of the Daz Studio SDK.

	This file may be used only in accordance with the Daz Studio SDK
	license provided with the Daz Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of Daz 3D, Inc, except as explicitly
	allowed in the Daz Studio SDK license.

	See http://www.daz3d.com to contact Daz 3D, Inc or for more
	information about the Daz Studio SDK.
**********************************************************************/
#pragma once

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

/****************************
	Forward declarations
****************************/

class DzCustomTransformTool;

/*****************************
	Class definitions
*****************************/

/**
	This class is used to provide the user with options displayed
	in the Tool Settings pane while our tool is active.
**/
class DzCustomTransformToolPane : public QFrame {
	Q_OBJECT
public:

	DzCustomTransformToolPane( QWidget* parent, const DzCustomTransformTool* tool );
	~DzCustomTransformToolPane();

public slots:

	// always nice to have
	virtual void	refresh();

protected slots:

	// slots for blocking/unblocking our refresh functions during content-changing operations such as a file load
	void	blockRefresh();
	void	unblockRefresh();
	bool	isBlocked();

	// interface widget interactions
	void	onAllowTransformsGrpChanged( bool onOff );
	void	onAllowTranslateChanged( int newState );
	void	onAllowRotateChanged( int newState );
	void	onAllowScaleChanged( int newState );

protected:

	void	initLayout();

private:

	struct Data;
	Data*	m_data;
};
