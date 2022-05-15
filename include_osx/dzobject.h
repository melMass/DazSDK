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
	Defines the DzObject class.
**/

#ifndef DAZ_OBJECT_H
#define DAZ_OBJECT_H

/*****************************
	Include files
*****************************/

#include "dzbox3.h"
#include "dzelement.h"
#include "dzorientedbox3.h"

/****************************
	Forward declarations
****************************/

class DzAbstractBuildGeometryFilter;
class DzDrawStyle;
class DzEnumProperty;
class DzRenderSettings;
class DzVertexMesh;

typedef DzTSharedPointer<DzVertexMesh> DzVertexMeshPtr;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzObject : public DzElement {
	Q_OBJECT
	friend class DzObjectShapeUndoItem;
	friend class ModifierListUndoItem;
	friend class DzObjectFactory;
	friend class DzObjectModifierLoadHelper;
public:

	DzObject();
	virtual ~DzObject();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	setStorablePaths( const QString &path );
	virtual void	copyFrom( const DzElement *source );
	virtual void	save( DzOutFile *file ) const;

	virtual DzElementClipboard*	copyToClipboard(const QStringList &contentTypes=QStringList()) const;

	//
	// MANIPULATORS
	//

	virtual void	update( DzNode &node, bool isRender );
	virtual void	finalize( DzNode &node, bool isRender, bool allowResChange = true );

	static void		invalidateAllCachedGeom();

public slots:

	virtual DzError	addShape( DzShape *shape, int index = -1 );
	virtual DzError	removeShape( int index );
	virtual DzError moveShape( DzShape* shape, int index = -1);
	virtual DzError	removeAllShapes();
	virtual DzError	addModifier( DzModifier *modifier, int index = -1 );
	virtual DzError	removeModifier( DzModifier *modifier );

	virtual DzError	moveModifier( DzModifier *modifier, int index = -1 );
	virtual DzError	removeAllModifiers(); 
	virtual void	invalidateCache();
	virtual void	forceCacheUpdate(DzNode *node, bool isRender = false );

	virtual void	beginEdit();
	virtual void	finishEdit();
	virtual void	cancelEdit();
	
	virtual void	buildFilteredGeometry( DzNode *node, DzAbstractBuildGeometryFilter *filter,bool finalizeGeom, DzVertexMeshPtr &finalGeom );

public:
	//
	// ACCESSORS
	//

	void	draw( const DzDrawStyle &style, const DzNode *node ) const;
	void	render( const DzRenderSettings &settings, const DzNode *node ) const;
	void	prepareMotionSample(const DzRenderSettings &settings, const DzNode *node);
	void	clearMotionSamples();

	DzModifierIterator	modifierIterator() const;
	void swapGeomChannels( DzObject* otherObject );
	void updateShapeControl();

public slots:

	virtual DzShape*		getCurrentShape() const;
	virtual int				getNumShapes() const;
	virtual DzShape*		getShape( int which ) const;
	virtual DzVertexMesh*	getCachedGeom() const;
	virtual int				getNumModifiers() const;
	virtual DzModifier*		getModifier( int which ) const;
	virtual DzModifier*		findModifier( const QString &name ) const;
	virtual int				findModifierIndex( DzModifier *mod ) const;
	virtual DzEnumProperty*	getGeometryControl() const;
	virtual DzBox3			getBoundingBox() const;
	virtual DzBox3			getLocalBoundingBox() const;
	virtual DzOrientedBox3	getLocalOrientedBox() const;

signals:

	void	modifierAdded( DzModifier *mod );
	void	modifierRemoved( DzModifier *mod );
	void	modifierStackChanged();
	void	shapeAdded( DzShape *shape );
	void	shapeRemoved( DzShape *shape );
	void	currentShapeSwitched();
	void	materialListChanged();
	void	materialSelectionChanged();
	void	drawnDataChanged();
	void	uvsChanged();
	void	cachedGeomInvalidated();
	void	cachedGeomUpdated();
	void	cachedGeomFinalized();
	void	shapeTopologyChanged();
	void	aboutToDelete();

protected:
	DzObject( const DzInFile *file );

	virtual DzVertexMesh*	buildWSGeometry( DzNode &node, bool isRender, DzVertexMesh *currentCache = NULL );

private slots:

	void	updateTime( DzTime tm );
	void	updateModifier();
	void	updateTransform();
	void	updateShape();
	void	updateMaterial();
	void	updateMaterialList();
	void	updateMaterialSelection();
	void	updateGeom();

private:
	//
	// MANIPULATORS
	//
	DzError removeModifierInternal( DzModifier * modifier, bool &deleteMod );
	void	createProperties();
	void	removeShapeInternal( int index );
	void	addModifierInternal( DzModifier *modifier, int index, bool addToChildren = true );
	void	addShapeInternal( DzShape *shape, int index, bool addToChildren = true );
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzObjectClipboard : public DzElementClipboard {
	Q_OBJECT
	friend class DzObject;
public:
	virtual ~DzObjectClipboard();

public slots:

	virtual DzError	paste( DzElement *elem, const QStringList &contentTypes = QStringList() ) const;

protected:
	DzObjectClipboard( const DzObject *elem, const QStringList &contentTypes );

private:
	struct	Data;
	Data	*m_data;
};



class DZ_EXPORT DzAbstractBuildGeometryFilter 
{
public:
	virtual	~DzAbstractBuildGeometryFilter();
	
	virtual	bool	acceptModifier( DzModifier *mod ) = 0;
	virtual bool	acceptWSModifier( DzWSModifier *wsMod ) = 0;
	virtual bool	applyWSTransform() = 0;
};

class DZ_EXPORT DzNoFilterBuildGeometryFilter : public DzAbstractBuildGeometryFilter
{
public:
	DzNoFilterBuildGeometryFilter() {  }
	virtual	~DzNoFilterBuildGeometryFilter() {  }

	virtual	bool	acceptModifier( DzModifier *mod ) { return true; }
	virtual bool	acceptWSModifier( DzWSModifier *wsMod ) { return true; }
	virtual bool	applyWSTransform() { return true; }
};

class DZ_EXPORT DzBuildMorphOnlyGeometryFilter : public DzAbstractBuildGeometryFilter
{
public:
	DzBuildMorphOnlyGeometryFilter();
	virtual	~DzBuildMorphOnlyGeometryFilter();
	virtual	bool	acceptModifier( DzModifier *mod );
	virtual bool	acceptWSModifier( DzWSModifier *wsMod ) { return false; }
	virtual bool	applyWSTransform() { return false; }
};

#endif // DAZ_OBJECT_H
