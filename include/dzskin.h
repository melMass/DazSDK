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
	Defines the DzSkin class.
**/

#ifndef DAZ_SKIN_H
#define DAZ_SKIN_H

/****************************
	Include files
****************************/

#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class QDomElement;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzSkinFileLoader : public QObject
{
	Q_OBJECT
public:
	DzSkinFileLoader();
	virtual ~DzSkinFileLoader();

public slots:
	virtual void	setFile( const QString &filename );
	virtual QString	getFileText();
	
	QString	getFileDir() const;

	void	setResourceDirectory( const QString &resourceDir );
	QString	getResourceDirectory() const;

	void	setSkinDirectory( const QString &skinDir );
	QString	getSkinDirectory() const;

protected:
	virtual QString	getRawFileText();

private:
	struct	Data;
	Data	*m_data;
};

class DzSkin;
typedef DzTSharedPointer<DzSkin> DzSkinPtr;

class DZ_EXPORT DzSkin : public QObject, public DzRefCountedItem {
	Q_OBJECT
public:
	DzSkin( DzSkinFileLoader *loader = NULL );
	virtual ~DzSkin();

	bool	fromDOM( const QDomElement &root, const QString &styleName = QString() );

public slots:
	virtual QString	getTextFromFile();

	void	setSkinFile( const QString &skinFile );
	QString	getSkinFile() const;
	QString	getSkinDirectory() const;

	bool	fileProcessed() const;
	bool	processSkin();
	bool	processSkin( const QString &str );

	QString		getGeneralStyleSheet() const;
	QString		getStyleSpecificSheet( const QString &styleName ) const;
	QString		getFullStyleSheet( const QString &styleName ) const;
	QStringList	getStylesWithSpecificSheets() const;

	DzSkinPtr	getOverrideSkin( const QString &paneClassName ) const;
	QStringList	getOverridedPanes() const;

private:

	struct	Data;
	Data	*m_data;
};

Q_DECLARE_METATYPE(DzSkinPtr);

#endif // DAZ_SKIN_H
