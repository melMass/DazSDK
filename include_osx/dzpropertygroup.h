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
	Defines the DzPropertyGroup class.
**/

#ifndef DAZ_PROPERTY_GROUP_H
#define DAZ_PROPERTY_GROUP_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dztypes.h"

/*****************************
	Forward declarations
*****************************/

class DzPropertyGroupTree;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPropertyGroup : public DzBase {
	Q_OBJECT
	friend class DzProperty;
	friend class DzPropertyGroupTree;
	friend class DzPropertyGroupFactory;
public:

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;

	//
	// ACCESSORS
	//

	void					collectAllPaths( QStringList &paths ) const;
	DzPropertyListIterator	getProperties() const;

public slots:

	QStringList				getAllPaths() const;
	int						getNumProperties() const;
	DzProperty*				getProperty( int i ) const;
	void					setUniquePropertyLabel( DzProperty *prop );
	bool					movePropertyToIndex( QString &propName, int newIndex );
	bool					movePropertyToIndex( DzProperty *prop, int newIndex );
	int						indexOfProperty( DzProperty *prop);
	QString					getPath() const;
	DzPropertyGroup*		getParent() const;
	DzPropertyGroup*		findSibling( const QString &name ) const;
	DzPropertyGroup*		getNextSibling() const;
	DzPropertyGroup*		getFirstChild() const;
	DzPropertyGroup*		findChild( const QString &name ) const;
	DzPropertyGroupTree*	getTree() const;
	bool					moveChildToIndex( QString &childName, int newIndex );

	DzGeometryRegion*		getRegion();
	bool					isRegion();

	void	setCollapsed( bool onOff );
	bool	getCollapsed();
	void	sort();

signals:

	void	parentChanged( DzPropertyGroup *newParent );
	void	addedChild( DzPropertyGroup *newChild );
	void	removedChild( DzPropertyGroup *child );
	void	childListChanged();
	void	treeChanged();

private:
	//
	// CREATORS
	//

	DzPropertyGroup( DzPropertyGroupTree *tree = NULL, const QString &name = tr( "<Unknown>" ) );
	~DzPropertyGroup();

	void	setTree( DzPropertyGroupTree *tree );
	void	setParent( DzPropertyGroup *parent );
	void	addSibling( DzPropertyGroup *sibling );
	void	addChild( DzPropertyGroup *child );
	void	removeChild( DzPropertyGroup *child );
	void	addProperty( DzProperty *prop );
	void	removeProperty( DzProperty *prop );
	bool	movePropertyToIndex( int curIndex, int newIndex );
	bool	hasProperty( const QString &label, DzProperty *exclude = NULL );

	DzPropertyGroup*	sortGroups( bool sortSibs );

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzPropertyGroupTree : public DzBase {
	Q_OBJECT
	friend class DzElement;
	friend class DzElementStatic;
	friend class DzProperty;
	friend class DzPropertyGroupTreeFactory;
public:

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;

	//
	// ACCESSORS
	//

	void	collectAllPaths( QStringList &paths ) const;

public slots:

	//
	// ACCESSORS
	//

	QStringList			getAllPaths() const;
	DzElement*			getOwner() const;
	DzPropertyGroup*	getFirstChild() const;
	DzPropertyGroup*	findChild( const QString &name ) const;
	bool				moveChildToIndex( QString &childName, int newIndex );
	bool				isPrivate();
	void				setIsPrivate( bool onoff );
	DzPropertyGroup*	getDefaultGroup() const;
	void				sortGroups();

signals:

	void	childListChanged();
	void	treeChanged();

private:
	//
	// CREATORS
	//

	DzPropertyGroupTree( DzElement *owner = NULL );
	~DzPropertyGroupTree();

	void	addChild( DzPropertyGroup *child );
	void	removeChild( DzPropertyGroup *child );
	void	setOwner( DzElement* owner );

	DzPropertyGroup*	getPropertyGroup( const QString &path );
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PROPERTY_GROUP_H
