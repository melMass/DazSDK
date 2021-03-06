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

/*****************************
	Include files
*****************************/
#include "mysceneview.h"

#include <QtCore/QObject>
#include <QtGui/QLayout>

#include "dzscene.h"

#include "myscenemodel.h"

///////////////////////////////////////////////////////////////////////
// MySceneView
///////////////////////////////////////////////////////////////////////

/**
**/
MySceneView::MySceneView( QWidget* parent )	:
	QWidget( parent )
{
	QBoxLayout* layout = new QHBoxLayout();

	m_label = new QLabel();
	m_label->setText( tr( "Cool Text :" ) );
	m_label->setObjectName( "MySceneViewCoolTextLbl" );
	layout->addWidget( m_label );

	m_lineEdit = new QLineEdit();
	m_label->setObjectName( "MySceneViewCoolTextLEdit" );
	layout->addWidget( m_lineEdit );

	setLayout( layout );
}

/**
**/
MySceneView::~MySceneView()
{
}

/**
**/
void MySceneView::setModel( MySceneModel* model )
{
	if ( m_model )
	{
		disconnect( m_lineEdit, SIGNAL(changed(const QString&) ), model, SLOT(setCoolTest(const QString&) ) );
		disconnect( m_model, SIGNAL(coolTextChanged(const QString&) ), m_lineEdit, SLOT(setText(const QString&)) );
	}

	m_model = model;
	if ( m_model )
	{
		m_lineEdit->setText( m_model->coolText() );
		DzConnect( m_lineEdit, SIGNAL(textChanged(const QString&)), m_model, SLOT(setCoolText(const QString&)) );
		DzConnect( m_model, SIGNAL(coolTextChanged(const QString&)), m_lineEdit, SLOT(setText(const QString&)) );
	}
}

///////////////////////////////////////////////////////////////////////
// MyScenePane
///////////////////////////////////////////////////////////////////////

/**
**/
MyScenePane::MyScenePane() :
	DzPane( tr( "Scene Data (SDK Example)" ) ), m_view( 0 )
{
	QVBoxLayout* layout = new QVBoxLayout();

	m_view = new MySceneView( this );
	m_view->setObjectName( "SceneDataSceneView" );

	layout->addWidget( m_view );
	layout->addStretch();

	setLayout( layout );

	DzConnect( dzScene, SIGNAL(sceneCleared()), this, SLOT(createModel()) );

	createModel();
}

/**
**/
MyScenePane::~MyScenePane()
{
}

/**
**/
void MyScenePane::createModel()
{
	// make the model
	MySceneModel* model = new MySceneModel();
	dzScene->addDataItem( model );

	// connect to the view
	m_view->setModel( model );
}

#include "moc_mysceneview.cpp"
