/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This file is part of the DAZ Studio SDK.

	This file may be used only in accordance with the DAZ Studio SDK 
	license provided with the DAZ Studio SDK.

	The contents of this file may not be disclosed to third parties, 
	copied or duplicated in any form, in whole or in part, without the 
	prior written permission of DAZ 3D, Inc, except as explicitly
	allowed in the DAZ Studio SDK license.

	See http://www.daz3d.com to contact DAZ 3D or for more 
	information about the DAZ Studio SDK.
**********************************************************************/
#ifndef DZ_SHADERMIXERUTILITY_UTILITY
#define DZ_SHADERMIXERUTILITY_UTILITY

/*****************************
	Include files
*****************************/

#include "dzbrickparam.h"
#include "idzbrickuser.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzShaderMixerUtility
{
public:
	DzShaderMixerUtility();
	~DzShaderMixerUtility();

	static QString	resolveType( DzBrickParam::ParamType src, DzBrickParam::ParamType tgt, const QString &var );
	static QString	resolveToFloat( DzBrickParam::ParamType src, const QString &var );
	static QString	resolveToColor( DzBrickParam::ParamType src, const QString &var );
	static QString	resolveToPoint( DzBrickParam::ParamType src, const QString &var );
	static QString	resolveToVector( DzBrickParam::ParamType src, const QString &var );
	static QString	resolveToNormal( DzBrickParam::ParamType src, const QString &var );
	static QString	resolveToMatrix( DzBrickParam::ParamType src, const QString &var );
	static QString	resolveToString( DzBrickParam::ParamType src, const QString &var );
	
	static void		resetTokens();
	static QString	getNewToken();
	static QString	getVecString( int type, const DzVec3 &vec );
	static QString	getColorString( const QColor &color, const QString &space="rgb" );
	static QString	getFloatString( float val );
	static QString	getMatrixString( const DzMatrix4 &matrix );
	static QString	getEscapedString( const QString &string );
	static void		createDirs( const QString &destDir );
	static QString	getCustomBrickPath();
	static void		getBrickUserList( DzBrickUserList &list );

	static IDzBrickUser*	toBrickUser( DzElement *elem );
};

#endif //DZ_SHADERMIXERUTILITY_UTILITY
