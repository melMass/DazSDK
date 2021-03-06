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
	Defines the DzViewportMgr class.
**/

#ifndef DAZ_VIEWPORT_MGR_H
#define DAZ_VIEWPORT_MGR_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzcamera.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzViewport;
class DzBox3;
class DzViewTool;
class DzScript;
class DzView;
class DzUserDrawStyle;
class DzMenu;
class Dz3DViewport;
class DzClassFactory;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzViewportMgr : public QWidget {
	Q_OBJECT
	Q_ENUMS( Layout QDMode ViewOperation ViewMouseBtnAccelerator ViewMouseModifier NodeClickMode RegionClickMode )
	friend class DzMainWindow;
	friend class DzViewport;
public:
	enum Layout { NO_PANES = 0, SINGLE_PANE, LEFT_RIGHT, TOP_BOTTOM, LEFT2_RIGHT,
					LEFT3_RIGHT, LEFT_RIGHT2, LEFT_RIGHT3, TOP2_BOTTOM, TOP3_BOTTOM,
					TOP_BOTTOM2, TOP_BOTTOM3, FOUR_PANE, NUM_LAYOUTS };
	enum QDMode { QDOff = 0, QDWire, QDSmooth };
	enum ViewOperation { NoOperation = 0, OrbitCamera, RotateCamera, PanCamera, DollyCamera,
		BankCamera, ZoomDCamera, ZoomFCamera };

	enum NodeClickMode { Node = 0, SkeletonThenNode, Skeleton };
	enum RegionClickMode { Nested = 0, Flat };
	
	enum ViewMouseBtnAccelerator { NoAccel = 0, LeftClick, RightClick, MidClick, AltLeftClick, AltRightClick,
		AltMidClick, CtrlLeftClick, CtrlRightClick, CtrlMidClick, ShiftLeftClick, ShiftRightClick,
		ShiftMidClick, CtrlAltLeftClick, CtrlAltRightClick, CtrlAltMidClick, CtrlShiftLeftClick,
		CtrlShiftRightClick, CtrlShiftMidClick, AltShiftLeftClick, AltShiftRightClick,
		AltShiftMidClick, CtrlAltShiftLeftClick, CtrlAltShiftRightClick, CtrlAltShiftMidClick };

	enum ViewMouseModifier { NoModifier = 0, Alt, Shift, Ctrl, CtrlAlt, CtrlShift, CtrlAltShift, ShiftAlt };

private:
	//
	// CREATORS
	//

	DzViewportMgr( QWidget *parent );
	virtual ~DzViewportMgr();

public slots:

	void	setLayout( Layout val );
	void	resetViewCameras();
	void	setActiveViewport( DzViewport *activeView );
	void	setPropagateBackgroundColor( bool onOff );
	void	repaintActive3DViewport();
	void	setActiveTool( DzViewTool *tool );
	void	setActiveTool( int which );
	void	activateNextTool();
	void	activatePrevTool();
	void	setViewRatios( float hSingle, float h1, float h2, float vSingle, float v1, float v2 );
	void	setMouseBtnAccelerator( DzViewportMgr::ViewOperation operation, DzViewportMgr::ViewMouseBtnAccelerator accel );
	bool	validateMouseBtnAccelerator( DzViewportMgr::ViewMouseBtnAccelerator accel );
	bool	validateMouseWheelAccelerator( DzViewportMgr::ViewMouseModifier accel);
	void	setInvertMouseWheel( bool onOff );
	
	void	setNodeClickMode(int mode);
	int		getNodeClickMode() const;

	void	setRegionClickMode(int mode);
	int		getRegionClickMode() const;

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		getNumViews();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzView*	getView( int which );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		getNumUserDrawStyles();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzUserDrawStyle*	getUserDrawStyle( int which );

public:

	void	lockRedraws();
	void	unlockRedraws();
	void	setQuickDrawMode( QDMode mode );
	void	setSubDManipulationOn( bool onOff );
	void	setManipulationBindingOn( bool onOff );
	void	startManipulation();
	void	endManipulation();

	//
	// STATIC
	//

	static void	addClass( DzClassFactory *type );

	//
	// ACCESSORS
	//

	//////////////////////////
	// from QWidget

	virtual QSize		sizeHint() const;
	virtual QSize		minimumSizeHint() const;
	virtual QSizePolicy sizePolicy() const;

public slots:

	DzViewport*		getActiveViewport() const;
	int				getNumViewports() const { return 4; }
	DzViewport*		getViewport( int which ) const;
	int				getNumVisibleViewports() const;
	Layout			getLayout() const;
	bool			getPropagateBackgroundColor() const;
	int				getNumTools() const;
	DzViewTool*		getTool( int i ) const;
	DzViewTool*		getActiveTool() const;
	DzViewTool*		findTool( const QString &className ) const;
	int				getNumViewCameras() const;
	DzCamera*		getViewCamera( int which ) const;
	DzCamera*		getViewCamera( DzCamera::CameraType type ) const;
	QString			getMouseBtnAcceleratorString( DzViewportMgr::ViewMouseBtnAccelerator accel ) const;
	QString			getMouseBtnAcceleratorString( DzViewportMgr::ViewOperation operation ) const;

	ViewMouseBtnAccelerator	getMouseBtnAccelerator( DzViewportMgr::ViewOperation operation ) const;
	ViewMouseBtnAccelerator	getMouseBtnAccelerator( const QString &str ) const;
	ViewMouseBtnAccelerator	getMouseBtnAccelerator( Qt::MouseButton button, Qt::KeyboardModifiers modifiers ) const;
	ViewMouseBtnAccelerator	getMouseBtnAccelerator( int mouseBtn, bool ctrl, bool alt, bool shift ) const;

	ViewOperation	getOperation( DzViewportMgr::ViewMouseBtnAccelerator accel ) const;
	bool			getInvertMouseWheel() const;
	
	QString				getMouseModifierString( DzViewportMgr::ViewMouseModifier accel ) const;
	ViewMouseModifier	getMouseModifier( const QString &str ) const;
	ViewMouseModifier	getMouseModifier( Qt::KeyboardModifiers modifiers ) const;
	ViewMouseModifier	getMouseModifier( bool ctrl, bool alt, bool shift ) const;
	


public:

	bool			isRedrawLocked() const;
	bool			isManipulation() const;
	bool			isQuickDraw() const;
	DzDrawStyle*	getQuickDrawStyle() const;
	QDMode			getQuickDrawMode() const;
	bool			isSubDManipulationOn() const;
	bool			isManipuationBindingOn() const;
	void			getViewRatios( float &hSingle, float &h1, float &h2, float &vSingle, 
						float &v1, float &v2 ) const;

	int						getNumViewportCameras() const;
	DzCamera*				getViewportCamera( int which ) const;
	DzCameraListIterator	getViewportCameras() const;

	bool			allowGraftDrawing() const;
	void			setAllowGraftDrawing(bool onOff);

signals:

	void	toolListChanged();
	void	activeToolSwitched();
	void	activeViewSwitched();
	void	activeViewResized();
	void	propagateBackgroundColorChanged( bool onOff );
	void	viewLayoutChanged();
	void	contextMenuAboutToShow( DzMenu *menu, Dz3DViewport *view, QPoint pos );
	void	viewportCameraListChanged();
	void	redrawsLocked( bool onOff );
	void	manipStarted();
	void	manipFinished();
	void	quickDrawModeChanged( DzViewportMgr::QDMode mode );
	void	subDManipulationChanged( bool );
	void	accelChanged( DzViewportMgr::ViewOperation operation, DzViewportMgr::ViewMouseBtnAccelerator accel );
	void	acceleratorsChanged();
	void	invertMouseWheelChanged( bool onOff );
	void	nodeClickModeChanged( int );
	void	regionClickModeChanged( int );
	void	graftDrawingChanged();
	void	manipulationBindingChanged( bool );

protected:
	//
	// MANIPULATORS
	//

	//////////////////////////
	// from QWidget

	virtual void	resizeEvent( QResizeEvent *e );

private slots:

	void	setActiveCamera( DzCamera *cam );
	void	hBar1Moved( int amount );
	void	hBar2Moved( int amount );
	void	vBar1Moved( int amount );
	void	vBar2Moved( int amount );
	void	viewportContextMenu( DzMenu *menu, QPoint pos );
	void	updateViewportCameras();
	void	cameraAdded( DzCamera *cam );

private:

	void	setViewGeometries();
	void	addTool( DzViewTool *tool );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_VIEWPORT_MGR_H
