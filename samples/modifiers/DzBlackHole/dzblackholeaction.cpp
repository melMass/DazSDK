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
#include "dzblackholenode.h"

#include "dzscene.h"

#include "dzblackholeaction.h"
#include "dzblackholemod.h"

///////////////////////////////////////////////////////////////////////
// DzBlackHoleAction
///////////////////////////////////////////////////////////////////////

/**
	Creates a new action with the menu text "New BlackHole"
**/
DzBlackHoleAction::DzBlackHoleAction() : DzCreateItemAction( tr( "New BlackHole" ),
	tr( "Creates a new BlackHole node in the scene." ) )
{
	// Set the object name for the action to register it with the help and
	// interactive lesson systems

	setObjectName( DzBlackHoleAction::metaObject()->className() );
}

/**
	This gets called when the user clicks on our action item.
**/
void DzBlackHoleAction::executeAction()
{
	QString name = "BlackHole";
	DzNode* node = dzScene->findNode( name );
	if ( node )
	{
		int blackHoleCount = 2; 
		name = QString( "BlackHole %1" ).arg( blackHoleCount );
		while( dzScene->findNode( name ) )
		{
			blackHoleCount++;
			name = QString( "BlackHole %1" ).arg( blackHoleCount );
		}
	}

	DzBlackHoleNode* bhNode = new DzBlackHoleNode;
	bhNode->setRadius( 100.0f );

	DzBlackHoleMod* mod = new DzBlackHoleMod;

	bhNode->setName( name.toAscii() );
	//node->setLabel( "Black Hole" );

	mod->setNode( bhNode );

	dzScene->addNode( bhNode );
	dzScene->addWSModifier( mod, 0 );
}

#include "moc_dzblackholeaction.cpp"
