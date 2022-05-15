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
	Defines the DzGeometryRegion class.
**/

#ifndef DZ_GEOMETRYREGION_H
#define DZ_GEOMETRYREGION_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"
#include "dzvec3.h"

/*****************************
	Forward declarations
*****************************/

class DzFacetMesh;

/****************************
	Type definitions
****************************/

typedef QList< QPointer<DzProperty> > DzWeakPropertyList;
typedef QListIterator< QPointer<DzProperty> > DzWeakPropertyListIterator;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzGeometryRegion : public DzElement {
	Q_OBJECT
public:
	DzGeometryRegion( const QString &name = QString() );
	virtual	~DzGeometryRegion();

	DzGeometryRegion*			getGeometryRegionParent() const;
	DzGeometryRegion*			getGeometryRegionRoot() const;
	DzGeometryRegionIterator	geometryRegionChildItr() const;
	DzGeometryRegionList		geometryRegionChildList() const;
	int							getLeafRegionIndex() const;

	void		setLeafRegionIndex( int index );
	void		addChildRegion( DzGeometryRegion *childRegion );
	void		removeChildRegion( DzGeometryRegion *childRegion );
	int			getChildIndex( DzGeometryRegion *childRegion ) const;
	void		changeChildIndex( DzGeometryRegion *childRegion, int newIndex );

	int			getNumRegionFacetIndexes() const;
	const int*	getRegionFacetIndexes() const;	
	QSet<int>	getRegionFacetIndexesSet() const;
	void		setRegionFacetIndexes( const int *values, int count );
	void		preSizeRegionFacetIndexes( int count );

	void		addRegionFacetIndex( int index );

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;

	
	DzGeometryRegion*			findRegion( const QString &name ) const;
	DzGeometryRegion*			findRegionByLabel( const QString &label, bool recurse = true ) const;
	DzGeometryRegion*			findRegionByPath( const QString &path) const;
	DzWeakPropertyListIterator	propertyReferenceIterator() const;
	DzWeakPropertyList			propertyReferences() const;
	
	static DzGeometryRegion*	getCurrentRegionSelectionForNode( DzNode *node );
	static DzGeometryRegion*	getCurrentRegionLeafSelectionForNode( DzNode *node );
	static DzGeometryRegion*	getRegionRootForNode( DzNode *node );

	void						invalidateBox();

	static bool					propertyReferenceSortFunction( const DzProperty *prop1, const DzProperty *prop2 );
	static bool					propertyGroupSortFunction( const DzPropertyGroup *group1, const DzPropertyGroup *group2 );

public slots:
	virtual DzError setLabel( const QString &name );

	DzError		addPropertyReference( DzProperty *prop );
	DzError		insertPropertyReference( int index, DzProperty *prop );
	DzError		removePropertyReference( DzProperty *prop, bool nulRegion = true );
	DzError		removePropertyReference( const QString &name );
	void		removeAllPropertyReferences( bool preservePropertyPath = false, bool recurse = true );
	int			getNumReferenceProperties() const;
	DzProperty*	getPropertyReference( int index ) const;
	DzProperty*	findPropertyReference( const QString &name ) const;
	DzProperty*	findPropertyReferenceByLabel( const QString &label ) const;
	int			findPropertyReferenceIndex(  DzProperty *prop );
	QString		getPath() const;
	bool		hasPropertiesInGroup( DzPropertyGroup *group );
	bool		getDisplaysCards() const;
	void		setDisplayCards( bool onOff );
	DzVec3		getOrigin() const;
	QString		getNoSpaceLabel() const;
	
	DzError				moveRegionIndexes( DzFacetMesh *oldMesh, DzFacetMesh *newMesh );
	int					numGeometryRegionChildren() const;
	DzGeometryRegion*	getGeometryRegionChild( int which ) const;

protected:
	void	updatePaths( const QString &oldPath );
	void	updatePropertiesPaths( const QString &oldPath );
	
signals:
	void	leafRegionFacetListChanged();
	void	childRegionListChanged();
	void	heirarchyChanged();
	void	propertyReferenceAdded( DzProperty *newprop );
	void	propertyReferenceListChanged();
	void	heirarchyPropertyListChanged();

private:
	void	emitRegionFacetListChanged();
	void	emitHeirarchyChanged();
	DzError	insertPropertyReferenceInList( int &index, DzProperty *newprop );
	void	emitHeirarchyPropertyListChanged();
	void	buildBoundingBox() const;
	void	buildBoundingBox( DzFacetMesh *mesh ) const;
	void	updateRegionFacetIndexes( const QVector<int> &oldToNewMap );
	DzGeometryRegion* findRegionByPathRecurse(QStringList path) const;

	struct	Data;
	Data	*m_data;
};

#endif