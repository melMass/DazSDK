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
	Defines the DzGeometryShellNode,DzGeometryShellShape,DzShellDummyFacetGeometry classes.
**/
#ifndef DAZ_GEOMETRY_SHELL_H
#define DAZ_GEOMETRY_SHELL_H

/*****************************
	Include files
*****************************/
#include "dznode.h"
#include "idzsceneasset.h"
#include "dzfacetshape.h"
#include "dzassetextraobjectio.h"
#include "dzfacetmesh.h"

/*****************************
	Forward declarations
*****************************/
class DzFloatProperty;
class DzFacetMesh;
class DzNodeProperty;
class DzFacetMesh;

/*****************************
	Forward declarations
*****************************/


class DzGeometryShellNode : public DzNode {
	Q_OBJECT
	friend class DzExtraGeometryShellNodeIO;
public:

	//
	// CREATORS/DESTRUCTORS
	//
	DzGeometryShellNode();
	DzGeometryShellNode(bool isSceneLoad);
	virtual ~DzGeometryShellNode();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	virtual void			postLoadFile( const DzInFile *file );
	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;

	void					setShellVisiblity( DzFacetMesh* newMesh );

public slots:
	virtual void			update( bool isRender = false );
	DzNodeProperty*			getShellNodeControl()const;


protected  slots:
	void					targetNodeChanged();
	void					tgtCacheInvalidated();
	
protected:
	DzGeometryShellNode( const DzInFile *file );	

private:
	void	createProperties();
	void	addFacetGroupVisiblity(const QString& name);
	void	removeFacetGroupVisiblity(const QString& name);
	void	addMaterialGroupVisiblity(const QString& name);
	void	removeMaterialGroupVisiblity(const QString& name);
	void	setUpFaceGroups( DzFacetMesh* mesh );
	void	setUpMaterials( DzFacetMesh* mesh );
	struct	Data;
	Data	*m_data;
};

class DzGeometryShellShape : public DzFacetShape {
	Q_OBJECT
public:
	DzGeometryShellShape();
	virtual ~DzGeometryShellShape();

	virtual DzVertexMesh*	getModifiableGeom( bool isRender, DzVertexMesh *currentCache = NULL ) const;
	virtual DzGeometry*		getGeometry() const;

	void	setGeometryShellNode( DzGeometryShellNode* node );

protected:
	virtual	void	finalize( DzNode &node, DzGeometry &wsGeom, bool isRender, bool allowResChange = true );

private:
	struct Data;
	Data *m_data;
};

class DzShellDummyFacetGeometry : public DzFacetMesh {
	Q_OBJECT
public:
	DzShellDummyFacetGeometry();
	virtual ~DzShellDummyFacetGeometry();
};

typedef DzTSharedPointer<DzShellDummyFacetGeometry> DzDummyFacetGeometryPtr;

class DzExtraGeometryShellNodeIO : public DzExtraNodeIO {
	Q_OBJECT
	friend class DzAssetGeometryShellNodeIO;
public:
	DzExtraGeometryShellNodeIO();
	virtual ~DzExtraGeometryShellNodeIO();

	virtual DzNode*	createNode()const;

	virtual DzError writeExtraDefinition( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	virtual DzError writeExtraInstance( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem *parentItem );
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem *parentItem );

	virtual DzError applyDefinitionToObject( QObject *object, const DzFileIOSettings *opts )const;
	virtual DzError applyInstanceToObject( QObject *object, const DzFileIOSettings *opts )const;

	virtual DzError resolveInstance( QObject *object, const DzFileIOSettings *opts ) const;
private:
	struct Data;
	Data* m_data;
};

class DzAssetGeometryShellNodeIO : public DzAssetJsonObject {
public:
	DzAssetGeometryShellNodeIO( DzAssetJsonItem *parent, DzExtraGeometryShellNodeIO *info );
	~DzAssetGeometryShellNodeIO();

	virtual DzAssetJsonItem*	startMemberArray( const QString &name );
private:
	DzExtraGeometryShellNodeIO	*m_info;
};

class DzExtraGeometryShellShapeIO : public DzExtraGeometryIO {
	Q_OBJECT
public:
	DzExtraGeometryShellShapeIO();
	virtual ~DzExtraGeometryShellShapeIO();

	virtual DzGeometry* createGeometry()const;
	virtual DzShape* createShape(DzGeometry* geom)const;

	virtual DzError writeExtraDefinition( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	virtual DzError writeExtraInstance( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem *parentItem );
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem *parentItem );

	virtual DzError applyDefinitionToObject( QObject *object, const DzFileIOSettings *opts )const;
	virtual DzError applyInstanceToObject( QObject *object, const DzFileIOSettings *opts )const;

private:
	struct Data;
	Data* m_data;
};
#endif // DAZ_GEOMETRY_SHELL_H