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
	Defines the DzBackdrop class.
**/

#ifndef DAZ_BACKDROP_H
#define DAZ_BACKDROP_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"

/****************************
	Forward declarations
****************************/

class DzBoolProperty;
class DzDrawStyle;
class DzEnumProperty;
class DzRenderSettings;
class DzTexture;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBackdrop : public DzElement {
	Q_OBJECT
	Q_ENUMS( Rotation )
	Q_PROPERTY( bool flipHorizontal READ getFlipHorizontal WRITE setFlipHorizontal )
	Q_PROPERTY( bool flipVertical READ getFlipVertical WRITE setFlipVertical )
	Q_PROPERTY( Rotation rotation READ getRotation WRITE setRotation )
	friend class DzBackdropOptionsDlg;
	friend class DzBackdropFactory;
public:

	enum Rotation { NO_ROTATION = 0, ROTATE_LEFT_90, ROTATE_RIGHT_90, ROTATE_180 };

	//
	// CREATORS
	//

	DzBackdrop();
	virtual ~DzBackdrop();

	//
	// MANIPULATORS
	//

	//////////////////////////////
	// from DzBase

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );

	virtual void	setFlipHorizontal( bool val );
	virtual void	setFlipVertical( bool val );
	virtual void	setRotation( Rotation rot );

public slots:

	virtual void	setTexture( const DzTexture *map );
	virtual void	showOptions( QWidget *parent = NULL );
	virtual void	clear();

public:
	//
	// ACCESSORS
	//

	////////////////////////////
	// from DzBase

	virtual void		save( DzOutFile *file ) const;
	virtual void		draw( const DzDrawStyle &style, int width, int height, const QRect &view ) const;
	virtual void		render( const DzRenderSettings &settings, int width, int height ) const;

	virtual bool		getFlipHorizontal() const;
	virtual bool		getFlipVertical() const;
	virtual Rotation	getRotation() const;

public slots:

	virtual DzMaterial*	getMaterial() const;
	virtual DzTexture*	getTexture() const;
	DzEnumProperty*		getRotationControl() const;
	DzBoolProperty*		getVerticalFlipControl() const;
	DzBoolProperty*		getHorizontalFlipControl() const;

signals:

	void				drawnDataChanged();

protected:
	DzBackdrop( const DzInFile *file );

private:
	void createMaterial();
	void createProperties();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BACKDROP_H
