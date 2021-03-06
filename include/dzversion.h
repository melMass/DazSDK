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
	Defines the Current Application and SDK version numbers.
**/

#ifndef DAZ_STUDIO_VERSION_H
#define DAZ_STUDIO_VERSION_H

/*****************************
	Include files
*****************************/

#if !defined(RC_INVOKED) && !defined(INFO_PLIST_INVOKED)
#include "dzgeneraldefs.h"
#endif

/*****************************
	DAZ Studio version
*****************************/

/**
	Major and Minor version numbers.
**/
#define DZ_VERSION_MAJOR	4
#define DZ_VERSION_MINOR	5
#define DZ_VERSION_REV		0
#define DZ_VERSION_BUILD	114

/**
	Defines the DAZ Studio version number
**/
#define DZ_VERSION	DzVersion( DZ_VERSION_MAJOR, DZ_VERSION_MINOR, DZ_VERSION_REV, DZ_VERSION_BUILD )

/**
	The current shipping version of the SDK any time this changes, plug-ins for
	DAZ Studio must be recompiled. This is what the application uses to determine
	if it can load a plug-in, if the version reported does not match, the plug-in is
	not loaded.
**/
#define DZ_SDK_VERSION_MAJOR	4
#define DZ_SDK_VERSION_MINOR	5
#define DZ_SDK_VERSION_REV		0
#define DZ_SDK_VERSION_BUILD	100

/**
	Defines the DAZ Studio SDK version number
**/
#define DZ_SDK_VERSION	DzVersion( DZ_SDK_VERSION_MAJOR, DZ_SDK_VERSION_MINOR, DZ_SDK_VERSION_REV, DZ_SDK_VERSION_BUILD )

/**
	This is the minimum SDK version that is compatible with the current build of
	DAZ Studio. Plug-ins will only be loaded if they have been compiled against
	a version of the SDK between this version and the current SDK version above.
**/
#define DZ_MIN_SDK_VERSION_MAJOR	4
#define DZ_MIN_SDK_VERSION_MINOR	5
#define DZ_MIN_SDK_VERSION_REV		0
#define DZ_MIN_SDK_VERSION_BUILD	100

/**
	Defines the minimum SDK version for plug-in compatibility with this version of DAZ Studio
**/
#define DZ_MIN_SDK_VERSION	DzVersion( DZ_MIN_SDK_VERSION_MAJOR, DZ_MIN_SDK_VERSION_MINOR, DZ_MIN_SDK_VERSION_REV, DZ_MIN_SDK_VERSION_BUILD )

#if !defined(INFO_PLIST_INVOKED) 
/*****************************
	Class Definitions
*****************************/

class DZ_EXPORT DzVersion {
public:
	DzVersion();
	DzVersion( const DzVersion &version );
	DzVersion( unsigned int version );
	DzVersion( quint64 version );
	DzVersion( unsigned short major, unsigned short minor, unsigned short revision, unsigned short build );
	~DzVersion();

	void			setVersionNumber( unsigned int version );
	void			setVersionNumber( quint64 version );
	void			setVersionNumber( unsigned short major, unsigned short minor, unsigned short revision, unsigned short build );

	quint64			getVersionNumber() const;
	unsigned int	getVersionNumber32() const;

	unsigned short	getMajorVersion() const;
	unsigned short	getMinorVersion() const;
	unsigned short	getRevisionNumber() const;
	unsigned short	getBuildNumber() const;

	QString			getVersionString() const;
	QString			getLongVersionString() const;

	bool			isValid() const;

	bool		operator<( const DzVersion &version ) const;
	bool		operator>( const DzVersion &version ) const;
	bool		operator<=( const DzVersion &version ) const;
	bool		operator>=( const DzVersion &version ) const;
	bool		operator==( const DzVersion &version ) const;
	bool		operator!=( const DzVersion &version ) const;

	DzVersion&	operator=( const DzVersion &version );

	static DzVersion	fromString( const QString &versionStr, bool *ok = NULL );

private:

	quint64	m_version;
};
#endif // !defined(INFO_PLIST_INVOKED) 

#endif // DAZ_STUDIO_VERSION_H
