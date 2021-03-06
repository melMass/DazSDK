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
#include "dzcustomtransformtoolaction.h"

#include <QtCore/QFileInfo>
#include <QtCore/QStringBuilder>

#include "dpcimages.h"
#include "dzapp.h"
#include "dzstyle.h"

///////////////////////////////////////////////////////////////////////
// DzCustomTransformTool
///////////////////////////////////////////////////////////////////////

/**
	Creates a new action for our tool
**/
DzCustomTransformToolAction::DzCustomTransformToolAction() :
	DzViewToolAction( "DzCustomTransformTool" )
{
	// Set the object name for the action to register it with the help and
	// interactive lesson systems

	setObjectName( DzCustomTransformToolAction::metaObject()->className() );

	// Initialize our icon
	initIcons();

	// Make the connection that will update our icon when interface colors are changed
	DzConnect( dzApp, SIGNAL(styleChanged(DzStyle*)),
		this, SLOT(handleInterfaceColorsChanged()) );

	// Make the connection that will update our icon when interface style has changed
	DzStyle* curStyle = dzApp->getStyle();
	DzConnect( curStyle, SIGNAL(interfaceColorsChanged()),
		this, SLOT(handleInterfaceColorsChanged()) );
}

/**
**/
QKeySequence DzCustomTransformToolAction::getDefaultAccel() const
{
	return QKeySequence();
}

/**
**/
void DzCustomTransformToolAction::initIcons()
{
	QString iconName = "tool_icon_base";
	QPixmap pixBase;
	getRawIconPixmap( iconName, pixBase );

	QIcon icon;
	makeIconVariants( icon, pixBase );
	QAction::setIcon( icon );
}

/**
**/
void DzCustomTransformToolAction::getRawIconPixmap( QString &iconBaseName, QPixmap &basePixmap ) const
{
	const QString iconPath = DzStyle::getIconsPath() % QLatin1Literal( "/SdkSamples" );
	const QString iconFile = QString( "%1/%2.png" ).arg( iconPath ).arg( iconBaseName );

	QFileInfo fileInfo;
	fileInfo.setFile( iconFile );

	if ( fileInfo.exists() ) // use a local "WIP" icon if found
	{
		basePixmap.load( iconFile );
	}
	else // use the embedded icon
	{
		basePixmap = QPixmap::fromImage( getEmbeddedImage( iconBaseName.toLatin1() ) );
	}
}

/**
**/
void DzCustomTransformToolAction::makeIconVariants( QIcon &icon, QPixmap &basePixmap )
{
	DzStyle* style = dzApp->getStyle();
	QPalette pal = style->getColors();

	const QString styleDef = style->getStyleDefinition();

	QColor activeOnClr;
	QColor normalOnClr;
	QColor activeOffClr;
	const QColor normalOffClr = pal.text().color();

	if ( styleDef.compare( "Highway" ) == 0
		|| styleDef.compare( "Main Street" ) == 0 )
	{
		activeOnClr = pal.highlightedText().color();
		normalOnClr = activeOnClr;
		activeOffClr = pal.light().color();
	}
	else //Darkside, etc.
	{
		activeOnClr = normalOffClr;
		normalOnClr =pal.highlight().color();
		activeOffClr = pal.highlightedText().color();
	}

	QPixmap pixActiveOn( basePixmap );
	DzStyle::adjustHSV( pixActiveOn, activeOnClr );
	icon.addPixmap( pixActiveOn, QIcon::Active, QIcon::On );

	QPixmap pixNormalOn( basePixmap );
	DzStyle::adjustHSV( pixNormalOn, normalOnClr );
	icon.addPixmap( pixNormalOn, QIcon::Normal, QIcon::On );

	QPixmap pixActiveOff( basePixmap );
	DzStyle::adjustHSV( pixActiveOff, activeOffClr );
	icon.addPixmap( pixActiveOff, QIcon::Active, QIcon::Off );

	QPixmap pixNormalOff( basePixmap );
	DzStyle::adjustHSV( pixNormalOff, normalOffClr );
	icon.addPixmap( pixNormalOff, QIcon::Normal, QIcon::Off );
}

/**
**/
void DzCustomTransformToolAction::handleInterfaceColorsChanged()
{
	initIcons();
}

#include "moc_dzcustomtransformtoolaction.cpp"
