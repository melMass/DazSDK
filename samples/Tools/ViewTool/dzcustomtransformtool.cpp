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
#include "dzcustomtransformtool.h"

#include <QtGui/qevent.h>

#include "dz3dviewport.h"
#include "dzapp.h"
#include "dzcamera.h"
#include "dzdrawstyle.h"
#include "dzfloatproperty.h"
#include "dzlight.h"
#include "dzmainwindow.h"
#include "dzscene.h"
#include "dzskeleton.h"
#include "dzviewportmgr.h"
#include "dzviewtool.h"

#include "dzcustomtransformtoolpane.h"

///////////////////////////////////////////////////////////////////////
// DzCustomTransformTool
///////////////////////////////////////////////////////////////////////

struct DzCustomTransformTool::Data
{
	Data() :
		m_multiTransOn( false ),
		m_stdTool( NULL ),
		m_toolPane( NULL ),
		m_customBeginGenScale( 0.0f ),
		m_customEndGenScale( 0.0f )
	{
		initTransformTool();

		m_multiTransOn = true;
	}

	void initTransformTool()
	{
		DzMainWindow* mw = dzApp->getInterface();
		DzViewportMgr* toolMgr = mw ? mw->getViewportMgr() : NULL;
		if ( toolMgr )
		{
			m_stdTool = toolMgr->findTool( "DzUniversalTool" );
		}
	}

	int					m_multiTransOn;
	DzViewTool*			m_stdTool;

	DzCustomTransformToolPane*	m_toolPane;

	// multi-node transform tracking
	DzVec3			m_customBeginPos;
	DzQuat			m_customBeginRot;
	float			m_customBeginGenScale;
	DzVec3			m_customBeginScale;

	DzVec3			m_customEndPos;
	DzQuat			m_customEndRot;
	float			m_customEndGenScale;
	DzVec3			m_customEndScale;
};

/**
**/
DzCustomTransformTool::DzCustomTransformTool() :
	DzTransformTool( "Custom Transform" ), m_data( new Data )
{
	m_data->m_toolPane = new DzCustomTransformToolPane( dzApp->getInterface(), this );

	//restoreSettings( "DzCustomTransformTool" );
}

/**
**/
DzCustomTransformTool::~DzCustomTransformTool()
{
	//saveSettings( "DzCustomTransformTool" );

	delete m_data;
	m_data = 0;
}

/**
**/
void DzCustomTransformTool::activate()
{
	DzTransformTool::activate();
	DzConnect( dzScene, SIGNAL(primarySelectionChanged(DzNode*)),
		this, SLOT(handlePrimarySelectionChanged(DzNode*)) );

	m_node = dzScene->getPrimarySelection();

	if ( !m_data->m_stdTool )
	{
		m_data->initTransformTool();
		int breakHere = true;
	}
}

/**
**/
void DzCustomTransformTool::deactivate()
{
	dzScene->disconnect( this );
	DzTransformTool::deactivate();
}

/**
**/
void DzCustomTransformTool::handlePrimarySelectionChanged( DzNode* select )
{
	DzNode* node = dzScene->getPrimarySelection();
	m_node = node;
}

/**
**/
bool DzCustomTransformTool::mousePress( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier )
{
	unsigned int partID = view->pickOnGizmo( e->pos() );
	m_activePart = Part( partID );

	int handled = false;

	if ( m_data->m_stdTool )
	{
		handled = m_data->m_stdTool->mousePress( view, e, modifier );
	}
	else
	{
		handled = DzTransformTool::mousePress( view, e, modifier );
	}

	return handled;
}

/**
**/
void DzCustomTransformTool::mouseMove( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier )
{
	if ( m_data->m_multiTransOn )
	{
		customMoveBegin();
	}

	if ( m_data->m_stdTool )
	{
		m_data->m_stdTool->mouseMove( view, e, modifier );
	}
	else
	{
		DzTransformTool::mouseMove( view, e, modifier );
	}

	if ( m_data->m_multiTransOn )
	{
		customMoveEnd();
	}
}

/**
**/
void DzCustomTransformTool::mouseRelease( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier )
{
	if ( m_data->m_stdTool )
	{
		m_data->m_stdTool->mouseRelease( view, e, modifier );
	}
	else
	{
		DzTransformTool::mouseRelease( view, e, modifier );
	}
}

/**
**/
void DzCustomTransformTool::mouseOver( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier )
{
	if ( m_data->m_stdTool )
	{
		m_data->m_stdTool->mouseOver( view, e, modifier );
	}
	else
	{
		DzTransformTool::mouseOver( view, e, modifier );
	}
}

/**
**/
void DzCustomTransformTool::contextMenu( Dz3DViewport* view, DzMenu* menu, const QPoint &pos )
{
	if ( m_data->m_stdTool )
	{
		m_data->m_stdTool->contextMenu( view, menu, pos );
	}
	else
	{
		DzTransformTool::contextMenu( view, menu, pos );
	}

	// add any extra menu items we would like...
}

/**
**/
void DzCustomTransformTool::draw( const DzDrawStyle &style, Dz3DViewport* view ) const
{
	if ( m_data->m_stdTool )
	{
		m_data->m_stdTool->draw( style, view );
	}
	else
	{
		DzTransformTool::draw( style, view );
	}

	// add any extra drawing we would like...
}

/**
**/
QWidget* DzCustomTransformTool::getPane( QWidget* parent ) const
{
	return m_data->m_toolPane;
}

/**
**/
void DzCustomTransformTool::customMoveBegin()
{
	if ( !m_node )
	{
		return;
	}

	DzMatrix3 tMat;

	m_node->getWSTransform( m_data->m_customBeginPos, m_data->m_customBeginRot, tMat );

	m_data->m_customBeginGenScale = m_node->getScaleControl()->getValue();
	m_data->m_customBeginScale[0] = m_node->getXScaleControl()->getValue();
	m_data->m_customBeginScale[1] = m_node->getYScaleControl()->getValue();
	m_data->m_customBeginScale[2] = m_node->getZScaleControl()->getValue();
}

/**
**/
void DzCustomTransformTool::customMoveEnd()
{
	if ( !m_node )
	{
		return;
	}

	int transformType = 0;
	DzVec3 tVec;

	const int keyCtrl = dzApp->modifierKeyState();
	switch ( keyCtrl )
	{
	case Qt::ControlModifier:
		// we are going to activate on [CTRL]
		// fall through, and have everything else exit
		break;
	case Qt::ShiftModifier:
	case Qt::AltModifier:
	default:
		return;
	}

	DzMatrix3 tMat;
	m_node->getWSTransform( m_data->m_customEndPos, m_data->m_customEndRot, tMat );

	m_data->m_customEndGenScale = m_node->getScaleControl()->getValue();
	m_data->m_customEndScale[0] = m_node->getXScaleControl()->getValue();
	m_data->m_customEndScale[1] = m_node->getYScaleControl()->getValue();
	m_data->m_customEndScale[2] = m_node->getZScaleControl()->getValue();

	const DzVec3 deltaPos = m_data->m_customEndPos - m_data->m_customBeginPos;

	DzQuat deltaRot = m_data->m_customBeginRot.inverse();
	deltaRot *= m_data->m_customEndRot;

	const float deltaGenScale = m_data->m_customEndGenScale - m_data->m_customBeginGenScale;
	const DzVec3 deltaScale = m_data->m_customEndScale - m_data->m_customBeginScale;

	switch ( m_activePart )
	{
	case X_TRANS:
	case Y_TRANS:
	case Z_TRANS:
	case XY_TRANS:
	case YZ_TRANS:
	case ZX_TRANS:
	case VIEW_TRANS:
		transformType = 1;
		break;
	case X_ROT:
	case Y_ROT:
	case Z_ROT:
	case VIEW_ROT:
	case FREE_ROT:
		transformType = 2;
		break;
	case X_SCALE:
	case Y_SCALE:
	case Z_SCALE:
	case XY_SCALE:
	case YZ_SCALE:
	case ZX_SCALE:
	case GEN_SCALE:
		transformType = 3;
		break;
	}

	switch ( transformType )
	{
	case 1:
	case 2:
	case 3:
		break;
	case 0:
	default:
		return;
	}

	DzNodeListIterator nodeIt = dzScene->selectedNodeListIterator();
	DzNode* curNode = NULL;

	nodeIt.toFront();

	while ( nodeIt.hasNext() )
	{
		curNode = nodeIt.next();
		if ( curNode == m_node )
		{
			continue;    // this is the primary node and has already been transformed
		}

		// ignore types that we don't want to transform
		if ( !( qobject_cast<DzLight*>( curNode ) ||
			qobject_cast<DzCamera*>( curNode ) ||
			qobject_cast<DzSkeleton*>( curNode ) ||
			curNode->className() == "DzNode" ) )
		{
			continue;
		}

		switch ( transformType )
		{
		case 1: // translate
			tVec = curNode->getWSPos();
			tVec += deltaPos;
			curNode->setWSPos( tVec );
			break;
		case 2: // rotate
			{
				DzQuat tRot = curNode->getWSRot();
				tRot *= deltaRot;
				curNode->setWSRot( tRot );
			}
			break;
		case 3: // scale
			{
				float tFlt = deltaScale.dot( deltaScale );
				if ( tFlt != 0.0 )
				{
					tVec[0] = curNode->getXScaleControl()->getValue();
					tVec[1] = curNode->getYScaleControl()->getValue();
					tVec[2] = curNode->getZScaleControl()->getValue();

					tVec += deltaScale;

					curNode->getXScaleControl()->setValue( tVec[0] );
					curNode->getYScaleControl()->setValue( tVec[1] );
					curNode->getZScaleControl()->setValue( tVec[2] );
				}

				if ( deltaGenScale != 0 )
				{
					tFlt = curNode->getScaleControl()->getValue();
					tFlt += deltaGenScale;

					curNode->getScaleControl()->setValue( tFlt );
				}
			}
			break;
		case 0: // unknown (could add some additional custom handling)
		default:
			break;
		}
	}
}

#include "moc_dzcustomtransformtool.cpp"
