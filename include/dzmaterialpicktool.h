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
	Defines the DzMaterialPickTool class.
**/

#ifndef DAZ_MATERIAL_PICK_TOOL_H
#define DAZ_MATERIAL_PICK_TOOL_H

/*****************************
	Include files
*****************************/

#include "dzpicktool.h"

/****************************
	Forward declarations
****************************/

class IDzBrickUser;
class DzSurfacesPane;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMaterialPickTool : public DzPickTool {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzMaterialPickTool();
	virtual ~DzMaterialPickTool();

	//
	// MANIPULATORS
	//

	///////////////////////////
	// from DzViewTool

	virtual void		activate();
	virtual void		deactivate();
	virtual bool		mousePress( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier accel);
	virtual void		mouseOver( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier accel );
	virtual void		mouseLeave( Dz3DViewport *view, QEvent *e );
	virtual QString		whatsThisText() const;
	virtual QWidget*	getPane( QWidget *parent ) const;
	virtual void		contextMenu( Dz3DViewport *view, DzMenu *menu, const QPoint &pos );
	virtual void		aimCamera( Dz3DViewport *view );
	virtual void		frameCamera( Dz3DViewport *view );

	void	getSelectionBoundingBox( DzBox3 &box );

public slots:
	virtual void	draw( const DzDrawStyle &style, Dz3DViewport *view ) const;
	void			setHighlightSelected( bool onOff );
	void			setHighlightWidth( int width );

protected:

	DzMaterialPickTool( const QString &name );

private slots:

	virtual void	clearHighlighting();
	void			menuSelection( int id );
	void			stylize();
	void			rebuildSelectedMats();

private:
	void	drawSelectedMaterials() const;
	void	drawMaterial( DzMaterial *mat ) const;
	void	updateNodeSelection();
	void	setHighlightMaterial( DzMaterial *mat, Dz3DViewport *view );
	void	selectAllMaterials( bool onOff, DzMaterial *match = NULL, bool useTextureMap = false, DzProperty* prop=NULL );
	void	selectAllMaterials( DzMaterial *match );
	DzProperty* getPropertyFromUser(bool imageOnly, DzMaterial* mat)const;
	DzSurfacesPane* getSurfacePane()const;

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzMaterialPickToolOptionsWgt : public QWidget
{
	Q_OBJECT
public:
	DzMaterialPickToolOptionsWgt( QWidget *parent, DzMaterialPickTool *tool );
	virtual ~DzMaterialPickToolOptionsWgt();

private slots:
	void	highlightSelectedChanged();
	void	outlineWidthChanged();

private:
	void	initOptions();
	void	buildSelectionGroup( QWidget *parent );
	
	struct Data;
	Data *m_data;
};

class DzMaterialPickToolFrame : public QFrame {
	Q_OBJECT
public:
	DzMaterialPickToolFrame( QWidget *parent, DzMaterialPickTool *tool );
	~DzMaterialPickToolFrame();

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MATERIAL_PICK_TOOL_H
