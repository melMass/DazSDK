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

#ifndef DAZ_CREATENEWITEM_DIALOG_H
#define DAZ_CREATENEWITEM_DIALOG_H

/*****************************
	Include files
*****************************/

#include "dzoptionsdialog.h"

/*****************************
	Class Definitions
*****************************/

class DzCreateNewItemDlg : public DzOptionsDialog {
	Q_OBJECT
	Q_ENUMS( NewItemType )
public:

	enum NewItemType {
		BasicCamera = 0,
		DistantLight,
		SpotLight,
		PointLight,
		LinearPointLight,
		NullNode,
		NodeInstance,
		GeometryShell,
		GroupNode
	};

	DzCreateNewItemDlg( QWidget *parent, NewItemType itemType );
	~DzCreateNewItemDlg();

protected:

	void	apply();

protected:

	void	showEvent( QShowEvent *e );

private slots:

	void	readOptions();
	void	writeOptions();

private:

	void	createItem();
	QString	getUniqueName( const QString &base );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_CREATENEWITEM_DIALOG_H
