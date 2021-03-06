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
	Defines the DzPickTool class.
**/

#ifndef DAZ_PICK_TOOL_H
#define DAZ_PICK_TOOL_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

#include "dzviewtool.h"

/****************************
	Forward declarations
****************************/

class DzNode;
class DzObject;
class DzSkeleton;
class DzFacetMesh;
class DzFaceGroup;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPickTool : public DzViewTool {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzPickTool();
	virtual ~DzPickTool();

	//
	// MANIPULATORS
	//

	virtual void		activate();
	virtual void		deactivate();
	virtual bool		mousePress( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual bool		mouseDoubleClick( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void		mouseOver( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void		mouseLeave( Dz3DViewport *view, QEvent *e );
	virtual void		draw( const DzDrawStyle &style, Dz3DViewport *view ) const;
	virtual QWidget*	getPane( QWidget *parent ) const;
	virtual void		contextMenu( Dz3DViewport *view, DzMenu *menu, const QPoint &pos );
	
	DzNode*				resolveSelectionNode( DzNode *rNode ) const;

public slots:
	virtual int		lineWidth() const { return 0; };
	virtual void	setLineWidth(int width ){ emit changedLineWidth(width); };
	virtual int		getNodeClickMode() const;

signals:

	void	changedLineWidth( int );

protected:

	DzPickTool( const QString &name );

	void			setHighlightNode( DzNode *node );
	virtual void	drawNodeHighlight( DzNode *highlightNode ) const;
	void			drawFaces( DzFacetMesh *mesh, DzPnt3 *verts ) const;
	void			drawFaceGroup(DzFaceGroup *faceGrp, DzFacetMesh *mesh) const;
	void			drawSelectionMapFaces( DzFacetMesh *mesh, DzPnt3 *verts, const QStringList &set ) const;
	void			drawObject( DzObject *obj, const QStringList &set ) const;
	void			drawSkel( DzSkeleton *skel ) const;
	void			setAlwaysUseDefaultPickMode( bool onOff );
	bool			getAlwaysUseDefaultPickMode() const;

private slots:

	void	clearMaterialSelection();
	void	menuSelection( int id );

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzBoundingBoxOptionsWidget : public QWidget {
	Q_OBJECT
public:
	DzBoundingBoxOptionsWidget( QWidget *parent, DzPickTool *tool );
	~DzBoundingBoxOptionsWidget();
private slots:
	void	drawStyleChanged(int index);
	void	oglDrawHighlightChanged(bool onOff);
private:
	void	buildBoundingBoxGroup( QWidget *parent );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzDrawStyleOptionsWidget : public QWidget {
	Q_OBJECT
public:
	DzDrawStyleOptionsWidget( QWidget *parent, DzPickTool *tool );
	~DzDrawStyleOptionsWidget();

private slots:
	void	setQuickDrawMode( int mode );
	void	setSubDManipulationMode( int mode );
	void	setManipulationBindingMode( int mode );

private:
	void	buildDrawStyleGroup( QWidget *parent );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzWireframeOptionsWidget : public QWidget {
	Q_OBJECT
public:
	DzWireframeOptionsWidget( QWidget *parent, DzPickTool *tool );
	~DzWireframeOptionsWidget();

private:
	void	buildWireframeGroup( QWidget *parent );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzNodePickModeOptionsWidget : public QWidget {
	Q_OBJECT
public:
	DzNodePickModeOptionsWidget( QWidget *parent, DzPickTool *tool );
	~DzNodePickModeOptionsWidget();

private:
	void		buildNodePickModeOptionsWidget( QWidget *parent );

	struct Data;
	Data *m_data;
};

class DzPickToolFrame : public QFrame {
	Q_OBJECT
public:
	DzPickToolFrame( QWidget *parent, DzPickTool *tool );
	~DzPickToolFrame();

private:

	struct	Data;
	Data	*m_data;
};

class DzPickToolMarshaller : public QObject {
	Q_OBJECT
public:
	DzPickToolMarshaller( QObject *parent );
	~DzPickToolMarshaller() {};

	void	setFactor( float v );

public slots:
	void	setValue( float v );
	void	setValue( int v );

	void	setIndex( bool v );
	void	setIndex( int v );

	void	setQDModeIndex( DzViewportMgr::QDMode v );
	void	setQDModeIndex( int v );

signals:
	void	valueChanged( float );
	void	valueChanged( int );
	void	indexChanged( bool );
	void	indexChanged( int );
	void	qDModeChanged( DzViewportMgr::QDMode );
	void	qDModeChanged( int );

private:
	float	m_factor;
};

#endif // DAZ_PICK_TOOL_H
