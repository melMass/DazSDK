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

#include "dzcustomdata.h"
#include "dzassetextraobjectio.h"

/****************************
	Forward declarations
****************************/

struct MyReadContext;

/*****************************
	Class definitions
*****************************/

class MySceneModel : public DzSceneData {
	Q_OBJECT
public:

	MySceneModel();
	~MySceneModel();

	bool		isEmpty();

public slots:

	QString		coolText();
	void		setCoolText( const QString &value );

signals:

	void	coolTextChanged( const QString &value );

private:

	QString		m_coolText;
};


class MySceneModelIO : public DzExtraSceneDataIO {
	Q_OBJECT
public:

	MySceneModelIO();
	~MySceneModelIO();

	// From DzExtraSceneDataIO
	virtual DzSceneData*		createDataItem( const DzFileIOSettings* opts ) const;
	virtual bool				shouldWrite( QObject* object, const DzFileIOSettings* opts ) const;
	virtual DzError				writeExtraInstance( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem* parentItem );
	virtual DzError				applyInstanceToObject( QObject* object, const DzFileIOSettings* opts ) const;
	virtual DzError				resolveInstance( QObject* object, const DzFileIOSettings* opts ) const;

	// For reading
	MyReadContext*	m_context;
};


struct MyReadContext
{
	MyReadContext( DzAssetFile &file ) :
		m_file( file )
	{}

	DzAssetFile		&m_file;
	QString			m_coolText;
};


class ReadMySceneModel : public DzAssetJsonObject {
public:
	ReadMySceneModel( MyReadContext* context ):
		DzAssetJsonObject( context->m_file ), m_context( context )
	{}

	virtual bool	addMember( const QString &name, const QString &val );

	MyReadContext*	m_context;
};