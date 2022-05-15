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

#ifndef _DAZ_MAC_AUDIO_CLIP_H
#define _DAZ_MAC_AUDIO_CLIP_H

/*****************************
	Include files
*****************************/

#include "dzaudioclip.h"

/*****************************
	Class declarations
*****************************/

class QTMovie;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMacAudioClip : public DzAudioClip {
	Q_OBJECT
public:
	DzMacAudioClip();
	~DzMacAudioClip();

	/////////////////////////////////////
	// From DzBase
	
	virtual void	loadSection( DzInFile *file, short sectionID );

	virtual void	play();
	virtual void	pause();
	virtual void	reset();
	virtual void	setCurrentPosition( DzTime pos );
	virtual void	setRate( double rateMultiplier );
	
	DzError			importSound( const QString &filename );
	QTMovie*		getSoundMovie();

	virtual DzTime	getLength() const;
	virtual DzTime	getCurrentPosition() const;
	virtual double	getRate() const;
	
	virtual DzError	openFile( const QString &filename );

private:

	struct	Data;
	Data	*m_data;
};

#endif // _DAZ_MAC_AUDIO_CLIP_H