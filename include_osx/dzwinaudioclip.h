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
	Defines the DzWinAudioClip class.
**/

#ifndef DAZ_WIN_AUDIO_CLIP_H
#define DAZ_WIN_AUDIO_CLIP_H

/*****************************
	Include files
*****************************/

#include "dzaudioclip.h"

/****************************
	Forward declarations
****************************/

class CSound;
class CSoundManager;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzWinAudioClip : public DzAudioClip {
	Q_OBJECT
public:
	DzWinAudioClip();
	virtual ~DzWinAudioClip();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	play();
	virtual void	pause();
	virtual void	reset();
	virtual void	setCurrentPosition( DzTime pos );
	virtual void	setRate( double rateMultiplier );
	virtual DzTime	getLength() const;
	virtual DzTime	getCurrentPosition() const;
	virtual double	getRate() const;
	virtual DzError	openFile( const QString &filename );

	//
	// MANIPULATORS
	//

	void	setSound( CSound *sound, const QString &filename );

	//
	// ACCESSORS
	//

	CSoundManager*	getManager() const;
	CSound*			getSound() const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_WIN_AUDIO_CLIP_H
