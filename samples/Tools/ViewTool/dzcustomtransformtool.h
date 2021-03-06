/**********************************************************************
	Copyright (c) 2002-2020 Daz 3D, Inc. All Rights Reserved.

	This file is part of the Daz Studio SDK.

	This file may be used only in accordance with the Daz Studio SDK
	license provided with the Daz Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of Daz 3D, Inc, except as explicitly
	allowed in the Daz Studio SDK license.

	See http://www.daz3d.com to contact Daz 3D, Inc or for more
	information about the Daz Studio SDK.
**********************************************************************/
#pragma once

/*****************************
	Include files
*****************************/

#include "dztransformtool.h"

/*****************************
	Class definitions
*****************************/

/**
**/
class DzCustomTransformTool : public DzTransformTool {
	Q_OBJECT
public:

	DzCustomTransformTool();
	~DzCustomTransformTool();

public slots:

	// From DzViewTool
	virtual void		activate();
	virtual void		deactivate();

	// override/extend user interface
	bool				mousePress( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void		mouseMove( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void		mouseRelease( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void		mouseOver( Dz3DViewport* view, QMouseEvent* e, DzViewportMgr::ViewMouseModifier modifier );

	virtual void		contextMenu( Dz3DViewport* view, DzMenu* menu, const QPoint &pos );
	virtual void		draw( const DzDrawStyle &style, Dz3DViewport* view ) const;

	virtual QWidget*	getPane( QWidget* parent ) const;

protected slots:

	void				handlePrimarySelectionChanged( DzNode* select );

protected:

	virtual void	customMoveBegin();
	virtual void	customMoveEnd();

private:

	struct Data;
	Data	*m_data;
};
