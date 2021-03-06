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
	Defines the DzCustomData class.
**/

#ifndef DAZ_CUSTOM_DATA_H
#define DAZ_CUSTOM_DATA_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/*****************************
	Forward declarations
*****************************/

class DzElement;
class DzSettings;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzCustomData : public DzBase {
	Q_OBJECT
public:

	DzCustomData( const QString &name, bool persistent = false );
	virtual ~DzCustomData();

public slots:

	bool	isPersistent() const { return m_isPersistent; }

private:

	bool	m_isPersistent;
};

class DZ_EXPORT DzElementData : public DzCustomData {
	Q_OBJECT
	friend class DzElement;
public:

	DzElementData( const QString &name, bool persistent = false );

public slots:

	DzElement*	getOwner() const { return m_owner; }
	virtual DzElementData* duplicate(DzElement* owner)const;

private:

	DzElement	*m_owner;
};

class DZ_EXPORT DzSimpleElementData : public DzElementData {
	Q_OBJECT
	friend class DzElement;
public:

	DzSimpleElementData( const QString &name, bool persistent = false );
	virtual ~DzSimpleElementData();

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;

	const DzSettings*	getSettings() const { return m_settings; }
	virtual DzElementData* duplicate( DzElement* owner ) const;

public slots:

	DzSettings*	getSettings() { return m_settings; }

private:

	DzSettings*	m_settings;
};

class DZ_EXPORT DzSceneData : public DzCustomData {
	Q_OBJECT
public:

	DzSceneData( const QString &name, bool persistent = false );
};

class DZ_EXPORT DzSimpleSceneData : public DzSceneData {
	Q_OBJECT
public:

	DzSimpleSceneData( const QString &name, bool persistent = false );
	virtual ~DzSimpleSceneData();

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;

	const DzSettings*	getSettings() const { return m_settings; }

public slots:

	DzSettings*	getSettings() { return m_settings; }

private:

	DzSettings*	m_settings;
};

#endif // DAZ_CUSTOM_DATA_H
