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
	Defines the DzSelectionMap class.
**/

#ifndef DAZ_SELECTION_MAP_H
#define DAZ_SELECTION_MAP_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/****************************
	Forward declarations
****************************/

class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSelectionMap : public DzBase {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzSelectionMap();
	virtual ~DzSelectionMap();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;

public slots:

	//
	// MANIPULATORS
	//

	DzError	addPair( const QString &faceGroupName, DzNode *node, bool replaceIfExists = false );
	DzError	removePair( int index );
	void	clearAll();
	void	nodeDeleted( DzNode *node );

	//
	// ACCESSORS
	//

	int		getNumPairs() const;
	DzNode*	getPairNode( int index ) const;
	QString	getPairGroup( int index ) const;
	QString	findGroupForNode( const DzNode *node )const;
	DzNode*	findNodeForGroup( const QString &groupName )const;
	int		findPair( const DzNode *node ) const;
	int		findPair( const QString &groupName ) const;

signals:
	void	visibilityChanged();
	void	mapModified();

private:
	
	void	removePairInternal( int index );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SELECTION_MAP_H