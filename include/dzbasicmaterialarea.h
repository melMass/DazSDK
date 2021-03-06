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
	Defines the DzBasicMaterialArea class.
**/
#ifndef DAZ_BASIC_MATERIAL_AREA_H
#define DAZ_BASIC_MATERIAL_AREA_H

/*****************************
	Include files
*****************************/

#include <QtGui/QGridLayout>
#include <QtGui/QScrollArea>

#include "dzgeneraldefs.h"

/*****************************
	Forward Declarations
*****************************/

class DzProperty;
class DzSimpleWidgetGroup;

/*****************************
	Class Definitions
*****************************/

class DZ_EXPORT DzBasicMaterialArea : public QScrollArea {
	Q_OBJECT
public:
	DzBasicMaterialArea( QWidget *parent, const QString &name = QString::null );

	void	clear();
	void	showWidget( bool show );
	void	addProperty( DzProperty *prop );

protected:
	virtual void	resizeEvent( QResizeEvent *e );

private:
	void initCommonGroup( DzSimpleWidgetGroup *group );
	void initSmoothingGroup( DzSimpleWidgetGroup *group );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzSimpleWidgetGroup : public QGridLayout {
	Q_OBJECT
public:

	DzSimpleWidgetGroup( QWidget *parent, const QString &text, int border = 0, int spacing = -1, 
		const QString &name = QString::null );
	~DzSimpleWidgetGroup();
	
	void				registerWidget( QWidget *widget );
	void				showWidgetBar( bool show );
	void				appendWidget( QWidget *widget );

signals:

	void				collapsedChanged( bool onOff );

private slots:

	void				setVis( bool onOff );
	void				changedStateInverted( bool onOff );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BASIC_MATERIAL_AREA_H
