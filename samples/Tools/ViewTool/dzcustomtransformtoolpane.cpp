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
#include "dzcustomtransformtoolpane.h"

#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>

#include "dzscene.h"
#include "dzstyle.h"

#include "dzcustomtransformtool.h"

///////////////////////////////////////////////////////////////////////
// DzCustomTransformToolPane
///////////////////////////////////////////////////////////////////////

/**
**/
struct DzCustomTransformToolPane::Data
{
	Data( DzCustomTransformTool* tool ) :
		m_tool( tool ),
		m_refreshBlocked( false ),
		m_allowTransformsGrp( NULL ),
		m_allowTranslate( NULL ),
		m_allowRotate( NULL ),
		m_allowScale( NULL )
	{}

	DzCustomTransformTool	*m_tool;
	bool	m_refreshBlocked;

	// widgets
	QGroupBox		*m_allowTransformsGrp;
	QCheckBox		*m_allowTranslate;
	QCheckBox		*m_allowRotate;
	QCheckBox		*m_allowScale;
};

/**
**/
DzCustomTransformToolPane::DzCustomTransformToolPane( QWidget* parent, const DzCustomTransformTool* tool ) :
	QFrame( parent ), m_data( new Data( ( DzCustomTransformTool* ) tool ) )
{
	blockRefresh();

	initLayout();

	unblockRefresh();

	// disable the interface during scene operations (see the SceneInfo sample for additional comments.)
	DzConnect( dzScene, SIGNAL(sceneLoadStarting()), this, SLOT(blockRefresh()) );
	DzConnect( dzScene, SIGNAL(sceneClearStarting()), this, SLOT(blockRefresh()) );
	DzConnect( dzScene, SIGNAL(sceneLoaded()), this, SLOT(unblockRefresh()) );
	DzConnect( dzScene, SIGNAL(sceneCleared()), this, SLOT(unblockRefresh()) );
}

/**
**/
DzCustomTransformToolPane::~DzCustomTransformToolPane()
{
	delete m_data;
	m_data = 0;
}

/**
**/
void DzCustomTransformToolPane::refresh()
{
	if( isBlocked() )
	{
		return;
	}

	if( !m_data->m_tool )
	{
		return;
	}

	// update our UI elements
}

/**
**/
void DzCustomTransformToolPane::blockRefresh()
{
	// A scene file is being loaded - block the refresh functions
	m_data->m_refreshBlocked = true;
}

/**
**/
void DzCustomTransformToolPane::unblockRefresh()
{
	// A scene file just finished loading - unblock the refresh functions,
	// and force an update of our data.
	m_data->m_refreshBlocked = false;
	refresh();
}

/**
**/
bool DzCustomTransformToolPane::isBlocked()
{
	return m_data->m_refreshBlocked;
}

/**
**/
void DzCustomTransformToolPane::onAllowTransformsGrpChanged( bool onOff )
{
//	if( m_data->m_tool )
//		m_data->m_tool->setAllowTransforms( onOff );
}

/**
**/
void DzCustomTransformToolPane::onAllowTranslateChanged( int newState )
{
//	if( m_data->m_tool )
//		m_data->m_tool->setAllowTranslate( newState );
}

/**
**/
void DzCustomTransformToolPane::onAllowRotateChanged( int newState )
{
//	if( m_data->m_tool )
//		m_data->m_tool->setAllowRotate( newState );
}

/**
**/
void DzCustomTransformToolPane::onAllowScaleChanged( int newState )
{
//	if( m_data->m_tool )
//		m_data->m_tool->setAllowScale( newState );
}

/**
**/
void DzCustomTransformToolPane::initLayout()
{
	// use Style-based elements
	int margin = style()->pixelMetric( DZ_PM_GeneralMargin );

	// Define the layout for the pane
	QVBoxLayout* mainLyt = new QVBoxLayout();
	mainLyt->setMargin( margin );
	mainLyt->setSpacing( margin );
	setLayout( mainLyt );

	// set up a scroll area in case the pane is resized small
	QScrollArea* scrollView = new QScrollArea();
	scrollView->setObjectName( "MultiNodeTransPaneScrollArea" );
	scrollView->setWidgetResizable( true );
	scrollView->setFrameStyle( NoFrame );
	scrollView->setLineWidth( 0 );
	mainLyt->addWidget( scrollView, 1 );

	QWidget* scrollContents = new QWidget();
	scrollContents->setObjectName( "MultiNodeTransPaneScrollContentsWgt" );
	scrollView->setWidget( scrollContents );

	QVBoxLayout* scrollContentsLyt = new QVBoxLayout( scrollContents );
	scrollContentsLyt->setMargin( 0 );
	scrollContentsLyt->setSpacing( margin );

	// primary on/off checkable group for our basic options
	m_data->m_allowTransformsGrp = new QGroupBox( tr( "Allow Transforms : " ) );
	m_data->m_allowTransformsGrp->setObjectName( "MultiNodeTransAllowGrp" );
	m_data->m_allowTransformsGrp->setCheckable( true );
	m_data->m_allowTransformsGrp->setChecked( true );
	DzConnect( m_data->m_allowTransformsGrp, SIGNAL(toggled(bool)), this, SLOT(onAllowTransformsGrpChanged(bool)) );

	QHBoxLayout* wgtGroupLayout = new QHBoxLayout( m_data->m_allowTransformsGrp );
	wgtGroupLayout->setMargin( 0 );
	wgtGroupLayout->setSpacing( margin );

	scrollContentsLyt->addWidget( m_data->m_allowTransformsGrp );

	// individual transform on/off options
	m_data->m_allowTranslate = new QCheckBox( tr( "Translate" ) );
	m_data->m_allowTranslate->setObjectName( "MultiNodeTransAllowTranslate" );
	m_data->m_allowTranslate->setChecked( true );
	DzConnect( m_data->m_allowTranslate, SIGNAL(stateChanged(int)), this, SLOT(onAllowTranslateChanged(int)) );
	wgtGroupLayout->addWidget( m_data->m_allowTranslate );

	m_data->m_allowRotate = new QCheckBox( tr( "Rotate" ) );
	m_data->m_allowRotate->setObjectName( "MultiNodeTransAllowRotate" );
	m_data->m_allowRotate->setChecked( true );
	DzConnect( m_data->m_allowRotate, SIGNAL(stateChanged(int)), this, SLOT(onAllowRotateChanged(int)) );
	wgtGroupLayout->addWidget( m_data->m_allowRotate );

	m_data->m_allowScale = new QCheckBox( tr( "Scale" ) );
	m_data->m_allowScale->setObjectName( "MultiNodeTransAllowScale" );
	m_data->m_allowScale->setChecked( true );
	DzConnect( m_data->m_allowScale, SIGNAL(stateChanged(int)), this, SLOT(onAllowScaleChanged(int)) );
	wgtGroupLayout->addWidget( m_data->m_allowScale );

	// Qt will attempt to stretch and space out the widgets to use all available space.
	// by adding this stretch factor at the end, "it" will be stretched to fill all
	// the unused space, and our above widgets will then use only the space they require.
	// (you can comment out the next line and rebuild, to see the difference.)
	scrollContentsLyt->addStretch( 1 );

	// handle any post-layout requirements
	setMinimumSize( minimumSizeHint() );
}

#include "moc_dzcustomtransformtoolpane.cpp"
