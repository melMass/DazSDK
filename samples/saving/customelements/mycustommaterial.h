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

#include <QtGui/QColor>

#include "dzassetextraobjectio.h"
#include "dzmaterial.h"

/****************************
	Test Script
****************************/

/* Test by creating a primitive, selecting it, and then executing the following in the Script IDE

var oNode = Scene.getPrimarySelection();
var oObject = oNode ? oNode.getObject() : null;
var oShape = oObject ? oObject.getCurrentShape() : null;
var oMaterial = oShape ? oShape.getMaterial( 0 ) : null;
if( oMaterial ){
	oShape.replaceMaterial( oMaterial, new MyCustomMaterial() );
}

*/

/****************************
	Forward declarations
****************************/

class DzFloatProperty;

/*****************************
	Class definitions
*****************************/

class MyCustomMaterial : public DzMaterial {
	friend class MyCustomNodeIO;
	Q_OBJECT
	Q_PROPERTY( bool toggled READ toggle WRITE setToggle )
public:

	MyCustomMaterial();
	~MyCustomMaterial();

	bool				toggle() const;
	void				setToggle( bool v );

public slots:

	// From DzMaterial
	virtual void		setDiffuseColor( const QColor &color );
	virtual void		setBaseOpacity( float val );
	virtual void		setColorMap( const DzTexture* img );
	virtual void		setOpacityMap( const DzTexture* img );

	virtual QColor		getDiffuseColor() const;
	virtual double		getBaseOpacity() const;
	virtual bool		isColorMappable() const;
	virtual bool		isOpacityMappable() const;
	virtual DzTexture*	getColorMap() const;
	virtual DzTexture*	getOpacityMap() const;
	virtual QString		getMaterialName() const;
	virtual bool		needsTangentSpaceParams() const;
	virtual bool		shouldAlwaysEmbed() const;
	virtual bool		allowsAutoBake() const;

protected:

	virtual void		setGLMat( const DzDrawStyle &style ) const;
	virtual void		unsetGLMat( const DzDrawStyle &style ) const;
	virtual void		setShader( const DzRenderSettings &settings ) const;
	virtual void		setCoShader( const DzRenderSettings &settings, DzCoShaderInfo &info ) const;

private:

	DzFloatProperty*	m_property;
	bool				m_bool;
};


class MyCustomMaterialIO : public DzExtraMaterialIO {
	Q_OBJECT
public:

	MyCustomMaterialIO();
	~MyCustomMaterialIO();

	// From DzExtraNodeIO
	virtual void				setIncludeProperties( DzPropertyList* includeProps );
	virtual DzMaterial*			createMaterial() const;
	virtual bool				needToReplaceMaterial( const DzMaterial* currentMaterial );
	virtual DzError				writeExtraDefinition( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzError				writeExtraInstance( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const;
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem* parentItem );
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem* parentItem );
	virtual DzError				applyDefinitionToObject( QObject* object, const DzFileIOSettings* opts ) const;
	virtual DzError				applyInstanceToObject( QObject* object, const DzFileIOSettings* opts ) const;

	// For reading
	struct		Context;
	Context*	m_context;
};


struct MyCustomMaterialIO::Context
{
	Context( DzAssetFile &file ) :
		m_file( file ),
		m_bool( false )
	{}

	DzAssetFile		&m_file;
	bool			m_bool;
};


class ReadMyCustomMaterial : public DzAssetJsonObject {
public:
	ReadMyCustomMaterial( MyCustomMaterialIO::Context* context ) :
		DzAssetJsonObject( context->m_file ), m_context( context )
	{}

	virtual bool	addMember( const QString &name, bool val );

	MyCustomMaterialIO::Context*		m_context;
};
