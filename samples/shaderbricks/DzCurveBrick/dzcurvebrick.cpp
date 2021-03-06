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
#include "dzcurvebrick.h"

#include "dpcscript.h"
#include "dzdefaultinparam.h"
#include "dzinfile.h"
#include "dzoutfile.h"
#include "dzoutparam.h"
#include "dzpropertyparam.h"
#include "dzundostack.h"
#include "dzfloatcolor.h"

//////////////////////////////////////////////////////////////////////////
// DzCurveBrick
//////////////////////////////////////////////////////////////////////////
struct DzCurveBrick::Data
{
};

/**
**/
DzCurveBrick::DzCurveBrick():
	m_data( new Data )
{
	DzUndoStackLock lock;

	addOutParameter( DzBrickParam::Color, "curveResult", "Curve" );

	addColorParameter( "", "basecolor", "Base Color", "Base Color", DzFloatColor( 0.109f, 0.037f, 0.007f ).rgba() );
	addColorParameter( "", "tipcolor", "Tip Color", "Tip Color", DzFloatColor( 0.519f, 0.325f, 0.125f ).rgba() );
	addFloatParameter( "", "DiffuseStrength", "Diffuse Strength", "Diffuse Strength", 0.6f, 0.6f, 0.0f, 1.0f, true ); // Diffuse Strength (Kd); Range (0, 1)

	addColorParameter( "", "SpecularColor", "Specular Color", "Specular Color", DzFloatColor( 0.759f, 0.662f, 0.562f ).rgba() );
	addFloatParameter( "", "Ks", "Specular Strength", "Specular Strength", 0.35f, 0.35f, 0, 1, true );
	addFloatParameter( "", "roughness", "Roughness", "Roughness", 0.15f, 0.15f, 1.0e-5f, 1, true );
}

/**
**/
DzCurveBrick::~DzCurveBrick()
{
	delete m_data;
	m_data = 0;
}

/**
**/
DzShaderString* DzCurveBrick::getBrickClassShaderCode() const
{
	return new DzShaderString( getEmbeddedSource( "curvehair" ) );
}

/**
**/
DzShaderString*	DzCurveBrick::getShaderCodeCall( const QStringList &varCallNames, const QStringList &varArgNames ) const
{
	const QString curveResult = getVarName( "curveResult", varCallNames, varArgNames );
	const QString Ks = getVarName( "Ks", varCallNames, varArgNames );
	const QString roughness = getVarName( "roughness", varCallNames, varArgNames );
	const QString basecolor = getVarName( "basecolor", varCallNames, varArgNames );
	const QString tipcolor = getVarName( "tipcolor", varCallNames, varArgNames );
	const QString specularcolor = getVarName( "SpecularColor", varCallNames, varArgNames );
	const QString Kd = getVarName( "DiffuseStrength", varCallNames, varArgNames );

	const QString code = QString( "%1 = dz_curve_hair(-normalize(I),%2,%3,%4,%5,%6,%7);" )
			.arg( curveResult )
			.arg( Ks )
			.arg( roughness )
			.arg( Kd )
			.arg( basecolor )
			.arg( tipcolor )
			.arg( specularcolor );

	return new DzShaderString( QString( code ) );
}

#include "moc_dzcurvebrick.cpp"
