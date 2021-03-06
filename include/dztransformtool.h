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
	Defines the DzTransformTool class.
**/

#ifndef DAZ_TRANSFORM_TOOL_H
#define DAZ_TRANSFORM_TOOL_H

/*****************************
	Include files
*****************************/

#include "dzvec3.h"
#include "dzquat.h"
#include "dzpicktool.h"

/****************************
	Forward declarations
****************************/

class DzLine3;
class DzNode;
class DzUndoStackHold;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTransformTool : public DzPickTool {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzTransformTool( const QString &name );
	virtual ~DzTransformTool();

	//
	// MANIPULATORS
	//

	///////////////////////////
	// from DzViewTool

	virtual bool	mousePress( Dz3DViewport *view, QMouseEvent *e ,DzViewportMgr::ViewMouseModifier modifier);
	virtual void	mouseMove( Dz3DViewport *view, QMouseEvent *e ,DzViewportMgr::ViewMouseModifier modifier);
	virtual void	mouseRelease( Dz3DViewport *view, QMouseEvent *e ,DzViewportMgr::ViewMouseModifier modifier);
	virtual void	mouseOver( Dz3DViewport *view, QMouseEvent *e ,DzViewportMgr::ViewMouseModifier modifier);

protected:
	enum Part { NONE = 0, X_ROT, Y_ROT, Z_ROT, VIEW_ROT, FREE_ROT,
		X_TRANS, Y_TRANS, Z_TRANS, XY_TRANS, YZ_TRANS, ZX_TRANS, VIEW_TRANS,
		X_SCALE, Y_SCALE, Z_SCALE, XY_SCALE, YZ_SCALE, ZX_SCALE, GEN_SCALE };

	//
	// DATA MEMBERS
	//

	Part			m_activePart;
	DzNode			*m_node;
	double			m_projMtx[16];
	DzVec3			m_startPnt;
	DzVec3			m_center, m_xNormal, m_yNormal, m_zNormal, m_viewNormal;
	DzVec3			m_xAxis, m_yAxis, m_zAxis;
	DzVec3			m_startPos, m_startScale, m_startRot;
	float			m_startGenScale;
	DzQuat			m_camWSRot,	m_startRotQ;
	float			m_sweepAngle;
	DzUndoStackHold	*m_undoHold;
	Dz3DViewport	*m_curView;
	int				m_viewport[4];
	int				m_mouseStartX, m_mouseStartY;
	DzVec3			m_lastPnt;
	float			m_startS, m_startS2;

	//
	// ACCESSORS
	//

	virtual DzVec3	getHitPoint( int x, int y, float &s, float &s2 ) const;

private:

	struct	Data;
	Data	*m_data;
};

extern DZ_EXPORT unsigned char s_polyStipple[];

#endif // DAZ_TRANSFORM_TOOL_H
