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

#ifndef DAZ_RENDER_DLG_H
#define DAZ_RENDER_DLG_H

/*****************************
	Include files
*****************************/

#include "dzbasicdialog.h"

// #define TEST_ADV_OPTIONS

/*****************************
	Class definitions
*****************************/

class DzRenderDlg : public DzBasicDialog {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzRenderDlg( QWidget *parent );
	~DzRenderDlg();

	//
	// ACCESSORS
	//

	bool	renderNow() const;

public slots:

	void	render();

protected:

	void	apply();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_RENDER_DLG_H
