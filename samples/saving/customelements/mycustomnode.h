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

#include "dzassetextraobjectio.h"
#include "dznode.h"

/****************************
	Forward declarations
****************************/

class DzFloatProperty;

/*****************************
	Class definitions
*****************************/

class MyCustomNode : public DzNode {
	friend class MyCustomNodeIO;
	Q_OBJECT
public:

	MyCustomNode();
	~MyCustomNode();

private:

	DzFloatProperty*	m_property;
	int					m_myInt;
};


class MyCustomNodeIO : public DzExtraNodeIO {
	Q_OBJECT
public:

	MyCustomNodeIO();
	~MyCustomNodeIO();

	// From DzExtraNodeIO
	virtual DzNode*				createNode() const;
	virtual DzError				writeExtraDefinition( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzError				writeExtraInstance( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem* parentItem );
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem* parentItem );
	virtual DzError				applyDefinitionToObject( QObject* object, const DzFileIOSettings* opts ) const;
	virtual DzError				applyInstanceToObject( QObject* object, const DzFileIOSettings* opts ) const;

	virtual void				getOwnedAssets( QObject* object, QList< IDzSceneAsset* > &assets );

	// For reading
	struct		Context;
	Context*	m_context;
};


struct MyCustomNodeIO::Context
{
	Context( DzAssetFile &file ) :
		m_file( file ),
		m_myInt( -1 )
	{}

	DzAssetFile &m_file;
	int          m_myInt;
};


class ReadMyCustomNode : public DzAssetJsonObject {
public:
	ReadMyCustomNode( MyCustomNodeIO::Context* context ) :
		DzAssetJsonObject( context->m_file ), m_context( context )
	{}

	virtual bool			addMember( const QString &name, double val );

	MyCustomNodeIO::Context*	m_context;
};
