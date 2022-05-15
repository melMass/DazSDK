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
	Defines the DzPresentation class.
**/

#ifndef DAZ_PRESENTATION_H
#define DAZ_PRESENTATION_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPresentation : public DzBase, public DzRefCountedItem {
	Q_OBJECT
	Q_PROPERTY( QString type READ getType() WRITE setType() )
	Q_PROPERTY( QString label READ getLabel() WRITE setLabel() )
	Q_PROPERTY( QString description READ getDescription() WRITE setDescription() )
	Q_PROPERTY( QString iconLarge READ getIconLarge() WRITE setIconLarge() )
	Q_PROPERTY( QString iconSmall READ getIconSmall() WRITE setIconSmall() )
	Q_PROPERTY( QColor colorA READ getColorA() WRITE setColorA() )
	Q_PROPERTY( QColor colorB READ getColorB() WRITE setColorB() )
public:
	//
	// CREATORS
	//

	DzPresentation();
	virtual ~DzPresentation();

	QString	getType() const; 
	void	setType( const QString &str );

	QString	getLabel() const; 
	void	setLabel( const QString &str );

	QString	getDescription() const; 
	void	setDescription( const QString &str );

	QString	getIconLarge() const; 
	void	setIconLarge( const QString &str );

	QPixmap	getIconSmallPixmap( int width, int height ) const;
	QPixmap	getIconLargePixmap( int width, int height ) const;

	QString	getIconSmall() const; 
	void	setIconSmall( const QString &str );
	
	QColor	getColorA() const;
	void	setColorA( const QColor &color );

	QColor	getColorB() const;
	void	setColorB( const QColor &color );

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	save( DzOutFile *file ) const;

signals:
	void	iconReady();
	void	attributeChanged();

private slots:
	void	imageReady( QImage image, QSize size, QString relPath );

private:
	QPixmap	requestPixmap( const QString &imageStr, int width, int height ) const;

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzPresentation> DzPresentationPtr;
Q_DECLARE_METATYPE( DzPresentationPtr );

#endif // DAZ_PRESENTATION_H
