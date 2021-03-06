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

#include <QtGui/QPixmap>

#include "dznode.h"
#include "dzassetextraobjectio.h"

/****************************
	Forward declarations
****************************/

class DzBlackHoleMod;
class DzFloatProperty;

/*****************************
	Class definitions
*****************************/
/**

**/
class DzBlackHoleNode : public DzNode {
	Q_OBJECT
public:
	//
	// CREATORS/DESTROYERS
	//

	// Default Constructor
	DzBlackHoleNode();

	// Destructor
	~DzBlackHoleNode();

	//////////////////////////////
	// Keep these only for backwards compatibility
	virtual void	loadSection( DzInFile* file, short sectionID );
	virtual void	setPointer( const DzInFile* file, short sectionID, short pointerID, DzBase* ptr );


	////////////////////////////
	// from DzNode
	virtual void	draw( const DzDrawStyle &style ) const;
	virtual void	render( const DzRenderSettings &settings ) const;

public slots: // public slots can be accessed via script

	DzFloatProperty*	getRadiusControl() const;

	void			setRadius( float radius );
	float			getRadius() const;

signals: // signals can be accessed via script

	void			radiusChanged();

private:

	DzFloatProperty*	m_radius;
};


// all we really need is the createNode, radius is saved by the system
class DzBlackHoleNodeIO : public DzExtraNodeIO {
	Q_OBJECT
public:
	DzBlackHoleNodeIO();
	~DzBlackHoleNodeIO();

	// DzExtraNodeIO
	virtual DzNode*				createNode() const;
	virtual DzError				writeExtraDefinition( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzError				writeExtraInstance( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem* parentItem );
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem* parentItem );
	virtual DzError				applyDefinitionToObject( QObject* object, const DzFileIOSettings* opts ) const;
	virtual DzError				applyInstanceToObject( QObject* object, const DzFileIOSettings* opts ) const;

	virtual void				getOwnedAssets( QObject* object, QList< IDzSceneAsset* > &assets );
};
