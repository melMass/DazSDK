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
#include "mycustommaterial.h"

#include "dzfloatproperty.h"
#include "dzopengl.h"
#include "idzjsonio.h"

///////////////////////////////////////////////////////////////////////
// MyCustomMaterial
///////////////////////////////////////////////////////////////////////

/**
**/
MyCustomMaterial::MyCustomMaterial()
{
	// This custom bool value is shown only for completeness. You will
	// most likely want to use properties as shown below.
	m_bool = ( rand() & 0x1 ) == 1;

	// Create a property and add it to the scene,
	// no further IO work is needed as DzMaterial handles any properties we add
	m_property = new DzFloatProperty( "MyCustomFloat", false, false, 0 );
	m_property->setLabel( "Custom Float" );
	m_property->setPath( "General/Custom" );
	m_property->setIsMappable( false );
	m_property->setMinMax( 0, 1 );
	m_property->setIsClamped( true );

	addProperty( m_property );
}

/**
**/
MyCustomMaterial::~MyCustomMaterial()
{
}

/**
**/
bool MyCustomMaterial::toggle() const
{
	return m_bool;
}

/**
**/
void MyCustomMaterial::setToggle( bool v )
{
	m_bool = v;
}

/**
**/
void MyCustomMaterial::setDiffuseColor( const QColor &color )
{
}

/**
**/
void MyCustomMaterial::setBaseOpacity( float val )
{
}

/**
**/
void MyCustomMaterial::setColorMap( const DzTexture* img )
{
}

/**
**/
void MyCustomMaterial::setOpacityMap( const DzTexture* img )
{
}

/**
**/
QColor MyCustomMaterial::getDiffuseColor() const
{
	return QColor( 0, 0, 255, 255 );
}

/**
**/
double MyCustomMaterial::getBaseOpacity() const
{
	return 1;
}

/**
**/
bool MyCustomMaterial::isColorMappable() const
{
	return false;
}

/**
**/
bool MyCustomMaterial::isOpacityMappable() const
{
	return false;
}

/**
**/
DzTexture* MyCustomMaterial::getColorMap() const
{
	return 0;
}

/**
**/
DzTexture* MyCustomMaterial::getOpacityMap() const
{
	return 0;
}

/**
**/
QString MyCustomMaterial::getMaterialName() const
{
	return "MyMaterialName";
}

/**
**/
bool MyCustomMaterial::needsTangentSpaceParams() const
{
	return false;
}

/**
**/
bool MyCustomMaterial::shouldAlwaysEmbed() const
{
	return false;
}

/**
**/
bool MyCustomMaterial::allowsAutoBake() const
{
	return false;
}

/**
**/
void MyCustomMaterial::setGLMat( const DzDrawStyle &style ) const
{
	const float v = m_property->getValue();

	// purple to blue in this case, black to yellow in the else
	if ( m_bool )
	{
		glColor4f( 1.0f - v, 0, v, 1 );
	}
	else
	{
		glColor4f( 0, v, 0, 1 );
	}
}

/**
**/
void MyCustomMaterial::unsetGLMat( const DzDrawStyle &style ) const
{
	// if we had turned on anything like glEnable(GL_TEXTURE), we would want to clean that up.
}

/**
**/
void MyCustomMaterial::setShader( const DzRenderSettings &settings ) const
{
}

/**
**/
void MyCustomMaterial::setCoShader( const DzRenderSettings &settings, DzCoShaderInfo &info ) const
{
}

///////////////////////////////////////////////////////////////////////
// MyCustomMaterialIO
///////////////////////////////////////////////////////////////////////

/**
**/
MyCustomMaterialIO::MyCustomMaterialIO() :
	m_context( 0 )
{
}

/**
**/
MyCustomMaterialIO::~MyCustomMaterialIO()
{
	delete m_context;
}

/**
**/
void MyCustomMaterialIO::setIncludeProperties( DzPropertyList* includeProps )
{
}

/**
**/
DzMaterial*	MyCustomMaterialIO::createMaterial() const
{
	return new MyCustomMaterial();
}

/**
**/
bool MyCustomMaterialIO::needToReplaceMaterial( const DzMaterial* currentMaterial )
{
	return DzExtraMaterialIO::needToReplaceMaterial( currentMaterial );
}

/**
**/
DzError MyCustomMaterialIO::writeExtraDefinition( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts ) const
{
	return DZ_NO_ERROR;
}

/**
**/
DzError MyCustomMaterialIO::writeExtraInstance( QObject* object, IDzJsonIO* io, const DzFileIOSettings* opts )const
{
	MyCustomMaterial* material = qobject_cast<MyCustomMaterial*>( object );

	io->addMember( "my_toggle", material->toggle() );

	return DZ_NO_ERROR;
}

/**
**/
DzAssetJsonObject* MyCustomMaterialIO::startDefinitionRead( DzAssetJsonItem* parentItem )
{
	return 0;
}

/**
**/
DzAssetJsonObject* MyCustomMaterialIO::startInstanceRead( DzAssetJsonItem* parentItem )
{
	m_context = new Context( parentItem->getFile() );
	return new ReadMyCustomMaterial( m_context );
}

/**
**/
DzError MyCustomMaterialIO::applyDefinitionToObject( QObject* object, const DzFileIOSettings* opts ) const
{
	return DZ_NO_ERROR;
}

/**
**/
DzError MyCustomMaterialIO::applyInstanceToObject( QObject* object, const DzFileIOSettings* opts )const
{
	MyCustomMaterial* material = qobject_cast<MyCustomMaterial*>( object );

	material->setToggle( m_context->m_bool );

	return DZ_NO_ERROR;
}

///////////////////////////////////////////////////////////////////////
// ReadMyCustomMaterial
///////////////////////////////////////////////////////////////////////

/**
**/
bool ReadMyCustomMaterial::addMember( const QString &name, bool val )
{
	if ( name == "my_toggle" )
	{
		m_context->m_bool = val;
	}
	else
	{
		return DzAssetJsonObject::addMember( name, val );
	}

	return true;
}

#include "moc_mycustommaterial.cpp"
