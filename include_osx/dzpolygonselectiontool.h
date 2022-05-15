/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This is UNPUBLISHED PROPRIETARY SOURCE CODE of DAZ 3D, Inc.
	the contents of this file may not be disclosed to third parties, 
	copied or duplicated in any form, in whole or in part, without the 
	prior written permission of DAZ 3D, Inc.
**********************************************************************/

#ifndef DAZ_FACET_SELECTION_TOOL_H
#define DAZ_FACET_SELECTION_TOOL_H

/*****************************
	Include files
*****************************/

#include "dzviewtool.h"
#include "dzaction.h"
#include "dztypes.h"

/*****************************
	Forward Declarations
*****************************/

class DzShape;
class DzNode;
class DzObject;
class DzFacetMesh;
class DzPolygonSelectionUndoItem;

/*****************************
	Class Definitions
*****************************/

class DZ_EXPORT DzPolygonSelectionTool : public DzViewTool {
	Q_OBJECT
	friend class DzPolygonSelectionUndoItem;
public:

	enum SelectionMode { RectangleSelection = 0, LassoSelection, DragSelection };

	DzPolygonSelectionTool( const QString &name, bool restrictToNode = false );
	virtual ~DzPolygonSelectionTool();
	
	virtual void	activate();
	virtual void	deactivate();
	virtual bool	mousePress( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void	mouseMove( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void	mouseRelease( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );

	void	doPolySelectionUndo();

	virtual void	contextMenu( Dz3DViewport *view, DzMenu *menu, const QPoint &pos );
	virtual void	buildOptionsMenu( DzActionMenu *menu ) const;
	virtual int		getOptionsMenuVersion() const;
	virtual void	draw( const DzDrawStyle &style, Dz3DViewport *view ) const;
	virtual void	aimCamera( Dz3DViewport *view  );
	virtual void	frameCamera( Dz3DViewport *view  );

public slots:

	void			setSelectionMode( SelectionMode mode );
	SelectionMode	getSelectionMode() const;

	void	selectFaceGroup( const QString &name );
	void	deselectFaceGroup( const QString &name );
	void	selectMaterialGroup( const QString &name );
	void	deselectMaterialGroup( const QString &name );		
	void	selectRegion( const QString &regionName );
	void	deselectRegion( const QString &regionName );
	void	selectRigidGroup( const QString& regionName, bool doRigid );
	void	deselectRigidGroup( const QString& regionName, bool doRigid );
	void	invertSelection();
	void	selectAll();
	void	clearSelection();
	void	growSelection();
	void	shrinkSelection();
	void	selectConnected();
	void	enableSymmetry( bool onOff );
	bool	symmetryEnabled();
	void	setSymmetryAxis( int axis );
	int		getSymmetryAxis();

	void	hideSelection();
	void	invertHidden();
	void	hideAll();
	void	showAll();

	void	lockSelection();
	void	invertLocked();
	void	lockAll();
	void	unlockAll();

	DzNode*		getCurrentNode() const;
	DzObject*	getCurrentObject() const;
	DzShape*	getCurrentShape() const;
	QStringList	getFaceGroupList() const;
	QStringList	getMaterialGroupList() const;
	QStringList	getRegionGroupList() const;
	QStringList getRigidGroupList() const;

	void	setFaceGroupVisiblity( const QString &grp, bool hide );
	void	setMaterialGroupVisiblity( const QString &grp, bool hide );
	void	setRegionVisiblity( const QString &grp, bool hide );
	void	setRigidityGroupVisiblity( const QString &grp, bool hide, bool doRigid );

signals:

	void	selectionModeChanged( DzPolygonSelectionTool::SelectionMode mode );
	void	currentNodeChanged( DzNode *node );
	void	currentShapeChanged( DzShape *shape );
	void	selectionChanged();
	void	visiblityChanged();

protected:

	virtual void	setNode( DzNode *node );

	void	beginFacetSelectionChange();
	void	endFacetSelectionChange();

private slots:

	void	updateCurrentShape();
	void	nodeRemoved();
	void	selMenuResult( int val );

private:

	enum	SelectionModifier { SelectNormal, SelectAdd, SelectSubtract };

	bool	pickOnFacet( Dz3DViewport *view, const QPoint &pos, SelectionModifier sel, bool isFirst );
	void	updateRectangle();
	void	applyLasso( Dz3DViewport *view, SelectionModifier sel );

	void	doPolySelectionUndo( DzFacetMesh *mesh );
	void	drawLasso( const DzDrawStyle &style, Dz3DViewport *view ) const;
	void	invalidate();
	void	setUpModifiers();
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FACET_SELECTION_TOOL_H