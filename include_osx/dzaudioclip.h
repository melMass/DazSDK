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
	Defines the DzAudioClip class.
**/

#ifndef DAZ_AUDIO_CLIP_H
#define DAZ_AUDIO_CLIP_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class DzAudioClip;

/****************************
	Type Definitions
****************************/

typedef DzTSharedPointer<DzAudioClip> DzAudioClipPtr;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAudioClip : public DzBase, public DzRefCountedItem {
	Q_OBJECT
	Q_PROPERTY( DzTime currentPosition READ getCurrentPosition WRITE setCurrentPosition )
	Q_PROPERTY( double rate READ getRate WRITE setRate )
	Q_PROPERTY( DzTime length READ getLength )
	Q_PROPERTY( QString filename READ getFilename )
public:
	DzAudioClip();
	virtual ~DzAudioClip();

	//////////////////////////////
	// from DzBase

	virtual void	loadSection( DzInFile *file, short sectionID ) = 0;
	virtual void	save( DzOutFile *file ) const;

	virtual void	setCurrentPosition( DzTime pos ) = 0;
	virtual void	setRate( double rateMultiplier ) = 0;
	virtual DzTime	getLength() const = 0;
	virtual DzTime	getCurrentPosition() const = 0;
	virtual double	getRate() const = 0;

	QString			getFilename() const;

public slots:

	virtual void	play() = 0;
	virtual void	pause() = 0;
	virtual void	reset() = 0;

	virtual DzError	openFile( const QString &filename ) = 0;

protected:

	void			setFilename( const QString &filename );

private:

	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_AUDIO_CLIP_H