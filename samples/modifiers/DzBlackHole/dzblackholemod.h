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

#include "dzwsmodifier.h"

/****************************
	Forward declarations
****************************/

class DzBlackHoleNode;

/*****************************
	Class definitions
*****************************/
class DzBlackHoleMod : public DzWSModifier {
	Q_OBJECT
public:

	DzBlackHoleMod();
	DzBlackHoleMod( DzNode* node );
	~DzBlackHoleMod();

	//
	// MANIPULATORS
	//

	//////////////////////////////
	// Keep these only for backwards compatibility
	virtual void	loadSection( DzInFile* file, short sectionID );
	virtual void 	setPointer( const DzInFile* file, short sectionID, short pointerID, DzBase* ptr );


	virtual DzError	apply( DzVertexMesh &geom, DzNode &node );
	virtual DzError	applyInverse( DzVertexMesh &geom, DzNode &node );

	void			setNode( DzBlackHoleNode* node );

private slots:

	void			updateTransform();
	void			updateRadius();

private:

	float				m_radius;
	DzBlackHoleNode*	m_node;
};
