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
	Defines the DzVideoClip class.
**/

#ifndef DAZ_VIDEO_CLIP_H
#define DAZ_VIDEO_CLIP_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QImage;
class DzAudioClip;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzVideoClip : public QObject {
	Q_OBJECT
public:
	DzVideoClip();
	DzVideoClip( int width, int height, int rate );
	virtual ~DzVideoClip();

public slots:

	//
	// MANIPULATORS
	//

	void	appendFrame( const QImage &img );
	void	appendFrameFile( const QString &imgFilename );
	void	setFrameRate( int rate );
	void	setAudio( DzAudioClip *audio, DzTime audioStartTime );

	//
	// ACCESSORS
	//

	int				getFrameRate() const;
	int				getWidth() const;
	int				getHeight() const;
	int				getNumFrames() const;
	QImage			getFrame( int i ) const;
	DzAudioClip*	getAudio() const;
	DzTime			getAudioStartTime() const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_VIDEO_CLIP_H