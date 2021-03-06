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

#include <QtGui/QLineEdit>
#include <QtGui/QLabel>

#include "dzpane.h"
#include "dzaction.h"

#include "myscenemodel.h"

/*****************************
	Class definitions
*****************************/

class MySceneView : public QWidget {
	Q_OBJECT
public:

	MySceneView( QWidget* parent );
	~MySceneView();

	void		setModel( MySceneModel* model );

private:

	QPointer<MySceneModel>	m_model;
	QLabel*		m_label;
	QLineEdit*	m_lineEdit;
};


/**
	Our new action inherits from DzPaneAction so that it will automatically be
	added to the '&Window/&Panes (Tabs)' menu when the plugin is loaded the first
	time. It also inherits from DzPaneAction so that it will toggle on/off display
	of our pane in the interface.
**/
class MyScenePaneAction : public DzPaneAction {
	Q_OBJECT
public:

	MyScenePaneAction() :
		DzPaneAction( "MyScenePane" ) {}
};


/**
	This class is the interface pane
**/
class MyScenePane : public DzPane {
	Q_OBJECT
public:

	// Constructor
	MyScenePane();

	// Destructor
	~MyScenePane();

private slots:

	void		createModel();

private:

	MySceneView*		m_view;
};
