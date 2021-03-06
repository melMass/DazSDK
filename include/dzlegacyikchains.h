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
	Defines the DzSourceFileData class.
**/

#ifndef DAZ_POSER_IK_CHAINS_DATA_H
#define DAZ_POSER_IK_CHAINS_DATA_H

/*****************************
	Include files
*****************************/

#include "dzcustomdata.h"

/*****************************
	Definitions
*****************************/
/** Identifying name for this DzElementData class **/
#define DZ_POSER_IK_CHAINS_DATA_NAME		"PoserIKChains"

/*****************************
	Forward declarations
*****************************/

class DzLegacyIKChain;
class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLegacyIKChains : public DzElementData {
	Q_OBJECT
public:
	DzLegacyIKChains();
	~DzLegacyIKChains();

	void	loadSection( DzInFile *file, short sectionID );
	void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	void	postLoadFile( const DzInFile *file );
	void	save( DzOutFile *file ) const;

public slots:

	int					getNumChains() const;
	DzLegacyIKChain*	getChain( int index ) const;
	void				addChain( DzLegacyIKChain *chain );

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzLegacyIKChain : public DzBase {
	Q_OBJECT
public:
	DzLegacyIKChain( const QString &name = QString::null );
	~DzLegacyIKChain();

	void loadSection( DzInFile *file, short sectionID );
	void setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	void postLoadFile( const DzInFile *file );
	void save( DzOutFile *file ) const;

public slots:

	bool	getActive() const;
	void	setActive( bool onOff );

	QString	getLabel() const;
	void	setLabel( const QString &label );

	int		getNumLinks() const;
	DzNode*	getLink( int index ) const;
	void	addLink( DzNode *node, float weight = 1.0f, int index = -1 );
	void	removeLink( int index );
	void	clearLinks();
	

	float	getLinkWeight( int index ) const;
	bool	setLinkWeight( int index, float weight );

	DzNode*	getGoal() const;
	void	setGoal( DzNode *node );

private slots:

	void	linkRemoved();
	void	goalRemoved();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_POSER_IK_CHAINS_DATA_H