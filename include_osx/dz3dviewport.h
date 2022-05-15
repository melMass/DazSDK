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
	Defines the Dz3DViewport class.
**/

#ifndef DAZ_3DVIEWPORT_H
#define DAZ_3DVIEWPORT_H

/*****************************
	Include files
*****************************/

#include "dzopengl.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzBox3;
class DzCamera;
class DzCameraCube;
class DzContentMgr;
class DzDrawStyle;
class DzGeometryRegion;
class DzMaterial;
class DzMenu;
class DzNode;
class DzRenderHandler;
class DzViewport;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT Dz3DViewport : public QGLWidget {
	Q_OBJECT
	Q_ENUMS( FloorStyle )
	Q_ENUMS( ShadeStyle )
	Q_ENUMS( AnchorLocation )
	Q_ENUMS( ToolBarMode )
	Q_PROPERTY(	QColor background READ getBackground WRITE setBackground )
	Q_PROPERTY(	FloorStyle floorStyle READ getFloorStyle WRITE setFloorStyle )
	Q_PROPERTY(	ShadeStyle shadeStyle READ getShadeStyle WRITE setShadeStyle )
	Q_PROPERTY(	bool axesOn READ getAxesOn WRITE setAxesOn )
	Q_PROPERTY(	bool aspectOn READ getAspectOn WRITE setAspectOn )
	Q_PROPERTY(	bool showPoseTool READ getPoseToolOn WRITE setPoseToolOn )
	Q_PROPERTY( ToolBarMode toolBarMode READ getToolBarMode WRITE setToolBarMode )
	friend class Dz3DViewportNavBar;
	friend class Dz3DViewBackgroundUndoItem;
public:
	enum FloorStyle { NoFloor, WireFloor, SolidFloor,
		NO_FLOOR = NoFloor, WIRE_FLOOR = WireFloor, SOLID_FLOOR = SolidFloor };
	enum ShadeStyle { WireBox, SolidBox, Wireframe, LitWireframe, HiddenLine, 
		WireShaded, SmoothShaded, WireTextured, Textured,
		WIRE_BOX = WireBox, SOLID_BOX = SolidBox, WIREFRAME = Wireframe, LIT_WIREFRAME = LitWireframe,
		HIDDEN_LINE = HiddenLine, WIRE_SHADED = WireShaded, SMOOTH_SHADED = SmoothShaded, 
		WIRE_TEXTURED = WireTextured, TEXTURED = Textured };
	enum AnchorLocation { AnchorTopLeft, AnchorTopRight, AnchorBottomLeft, AnchorBottomRight };
	enum ToolBarMode { DockedToolBar, CameraCubeHUD };

	//
	// CREATORS
	//

	Dz3DViewport( const QGLFormat &format, DzViewport *parent, const QString &name = QString::null );
	virtual ~Dz3DViewport();

	//
	// MANIPULATORS
	//

	void	onShow();
	void	onHide();

	void	setDrawStyle( DzDrawStyle *style );
	void	setToolTipText( const QString &text = QString::null );

	void	setBackground( const QColor &color );
	void	setFloorStyle( FloorStyle style );
	void	setShadeStyle( ShadeStyle style );
	void	setAxesOn( bool onOff );
	void	setAspectOn( bool onOff );
	void	setPoseToolOn( bool onOff );
	void	setToolBarMode(ToolBarMode mode);

public slots:

	void		setCamera( DzCamera *cam );
	void		setCamera( const QString &cam );
	void		aimCamera();
	void		aimCameraAtPrimaryNode();
	void		aimCameraAtBox( const DzBox3 &box );
	void		frameCamera();
	void		frameCameraOnSelectedNodes();
	void		frameCameraOnBox( const DzBox3 &box );
	void		resetCamera();
	DzNode*		pickOnNode( const QPoint &pnt, bool useSelectionMaps = true, DzGeometryRegion **region = NULL );
	DzMaterial*	pickOnMaterial( const QPoint &pnt );
	int			pickOnFacet( const QPoint &pnt, DzNode **facetNode = NULL );
	int			pickOnGizmo( const QPoint &pnt );

	void		pickNodes( const QPolygonF &area, DzNodeList &nodes, bool useSelectionMaps = true );
	void		pickMaterials( const QPolygonF &area, DzMaterialList &mats );
	void		pickFacets( const QPolygonF &area, QList<int> &facets, DzNode **facetNode = NULL );
	void		pickGizmos( const QPolygonF &area, QList<int> &gizmos );
	void		appendHoverCursor( QCursor cursor );

	void		updateGLOptions();

	QImage		captureImage();

public:
	//
	// ACCESSORS
	//

	DzDrawStyle*	getDrawStyle();
	bool			isCurrent() const;

	QColor			getBackground() const;
	FloorStyle		getFloorStyle() const;
	ShadeStyle		getShadeStyle() const;
	bool			getAxesOn() const;
	bool			getAspectOn() const;
	bool			isToolBarDocked() const;
	bool			getPoseToolOn() const;
	ToolBarMode		getToolBarMode() const;
	DzCameraCube*	getCameraCube();


public slots:

	DzViewport*		getViewport() const;
	DzCamera*		getCamera() const;
	QRect			getAspectFrameRect() const;
	virtual bool	isHardwareRenderable() const;
	virtual bool	hardwareRender( DzRenderHandler *handler ) const;
	virtual bool	renderThumbnail( DzRenderHandler *handler ) const;

public:

	static Dz3DViewport*	sharedWidget();

signals:

	void	activeCameraChanged( DzCamera *cam );
	void	dimensionsChanged();
	void	viewChanged();
	void	drawStyleChanged( DzDrawStyle *style );
	void	contextMenuAboutToShow( DzMenu *menu, QPoint pos );
	void	backgroundColorChanged( const QColor &color );
	void	floorStyleChanged( FloorStyle style );
	void	axesOnChanged( bool onOff );
	void	aspectOnChanged( bool onOff );
	void	toolBarDocked( bool onOff );
	void	toolModeChanged( Dz3DViewport::ToolBarMode mode );

protected slots:

	void	updateView();
	void	removeCamera( DzNode *cam );

protected:
	//
	// REIMPLEMENTATIONS
	//

	virtual void	resizeEvent( QResizeEvent *e );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseDoubleClickEvent( QMouseEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual void	leaveEvent( QEvent *e );
	virtual void	keyPressEvent( QKeyEvent *e );
	virtual void	keyReleaseEvent( QKeyEvent *e );
	virtual void	wheelEvent( QWheelEvent *e );
	virtual void	dragEnterEvent( QDragEnterEvent *e );
	virtual void	dragMoveEvent( QDragMoveEvent *e );
	virtual void	dragLeaveEvent( QDragLeaveEvent *e );
	virtual void	dropEvent( QDropEvent *e );
	virtual void	tabletEvent( QTabletEvent *e );
	virtual void	contextMenuEvent( QContextMenuEvent *e );

	virtual void	paintGL();
	virtual void	initializeGL();
	virtual void	resizeGL( int w, int h );

	virtual bool	startPan( Qt::MouseButton btn );
	virtual bool	startRotate( Qt::MouseButton btn );
	virtual bool	startZoom( Qt::MouseButton btn );
	virtual bool	startBank( Qt::MouseButton btn );
	virtual void	drag( const QPoint &delta );
	virtual void	endDrag();

private slots:

	void	endOperation();
	void	sceneLoaded();
	void	updateAspect();
	void	showContextMenu( const QPoint &pos );
	void	showDropContextMenu();
	void	lockRedraws( bool onOff );

private:
	//
	// DATA MEMBERS
	//

	struct	Data; 
	Data	*m_data;

	//
	// MANIPULATORS
	//

	void	startOrbit();
	void	startRotate();
	void	startPan();
	void	startDolly();
	void	startBank();
	void	startDZoom();
	void	startFZoom();
	void	updatePickImage( bool useSelectionMaps );
	void	updateMaterialPickImage();
	void	updateFacetPickImage();
	bool	setContentManagerDropOptions( DzContentMgr *contentMgr );

	//
	// ACCESSORS
	//

	bool	render( DzRenderHandler *handler, bool isThumbnail );
	void	doPolySort() const;
	void	drawFloor() const;
	void	drawCenterAxes() const;
	void	drawDropTarget() const;
	void	drawAspectFrame();
	void	setGLOptions();
	QImage	getCurrentImage( const QRect &rect );

	void	handleContentDragMove( const QPoint &dragPoint, bool allowDropAt = true, bool allowContextMenu = true );
	void	enableAntialiasing() const;
	void	disableAntialiasing() const;


	void	dockToolBar( bool onOff );
};

class DzOpenGLRenderProgress : public QObject {
	Q_OBJECT
public:
	DzOpenGLRenderProgress();
	~DzOpenGLRenderProgress();

	///////////////////////////
	// from QObject

	virtual bool	eventFilter( QObject *watched, QEvent *e );

	//
	// MANIPULATORS
	//

	void	startRender();
	void	stopRender();
	void	statusLine( const QString &status, bool log = false );

	//
	// ACCESSORS
	//

	bool	isCancelled() const;

public slots:

	void	cancel();

private:

	struct	Data; 
	Data	*m_data;
};

class DzOpenGLRenderSettings {
public:
	DzOpenGLRenderSettings();
	~DzOpenGLRenderSettings();

	//
	// MANIPULATORS
	//

	void	setCamera( DzCamera *cam );
	void	setViewWidth( int width );
	void	setViewHeight( int height );
	void	setDrawRect( const QRect &rect );
	void	setCurrentPass( int curPass );
	void	setTotalPasses( int passes );
	void	setDrawBackDrop( bool onOff );

	//
	// ACCESSORS
	//

	DzOpenGLRenderProgress*	getProgress() const;
	DzCamera*				getCamera() const;

	int		viewWidth() const;
	int		viewHeight() const;
	QRect	drawRect() const;
	int		getCurrentPass() const;
	int		getTotalPasses() const;
	bool	drawBackDrop() const;

private:

	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_3DVIEWPORT_H
