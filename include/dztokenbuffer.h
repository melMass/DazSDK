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
/**
	@sdk
	@file
	Defines the DzTokenBuffer class.
**/

#ifndef DAZ_TOKEN_BUFFER
#define DAZ_TOKEN_BUFFER

/*****************************
	Include files
*****************************/

#include "dzrenderer.h"

/*****************************
	Forward declarations
*****************************/

class DzVec3;
class DzMatrix4;

/*****************************
	Include files
*****************************/

class DZ_EXPORT DzTokenBuffer {
public:
	static void		resetTokenList();
	static void		addIntegerToken( const QString &name, int val );
	static void		addFloatToken( const QString &name, float val );
	static void		addColorToken( const QString &name, const QColor &val );
	static void		addStringToken( const QString &name, const QString &val );
	static void		addPointToken( const QString &name, const DzVec3 &vec );
	static void		addVectorToken( const QString &name, const DzVec3 &vec );
	static void		addNormalToken( const QString &name, const DzVec3 &vec );
	static void		addMatrixToken( const QString &name, const DzMatrix4 &mtx );
	static void		addPointerToken( const QString &name, void *val );
	
	static void		addIntegerToken( const QString &name, const QList<QVariant> &vals );
	static void		addFloatToken( const QString &name, const QList<QVariant> &vals );
	static void		addColorToken( const QString &name, const QList<QVariant> &vals );
	static void		addStringToken( const QString &name, const QList<QVariant> &vals );
	static void		addPointToken( const QString &name, const QList<QVariant> &vals );
	static void		addVectorToken( const QString &name, const QList<QVariant> &vals );
	static void		addNormalToken( const QString &name, const QList<QVariant> &vals );
	static void		addMatrixToken( const QString &name, const QList<QVariant> &vals );
	static void		addPointerToken( const QString &name, const QList<QVariant> &vals );
	
	static int		getRendererArgs( DtToken **tokens, DtPointer **pointers );

	static void		loadTokenBuffer( QStringList &tokens, QList<QVariant> params );

private:
	static char*	createToken( const QString &type, const QString &name );
};

#endif // DAZ_TOKEN_BUFFER