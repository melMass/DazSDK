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
	Defines the DzDrawStyle class.
**/

#ifndef DAZ_DRAW_STYLE_H
#define DAZ_DRAW_STYLE_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class DzLight;
class DzPolySorter;
class DzSceneShader;
class QPixmap;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDrawStyle : public DzBase, public DzRefCountedItem {
	Q_OBJECT
	Q_PROPERTY( bool drawObjectsOnly READ drawObjectsOnly WRITE setDrawObjectsOnly )
	Q_PROPERTY( bool drawShadowCastersOnly READ drawShadowCastersOnly WRITE setDrawShadowCastersOnly )
	Q_PROPERTY( bool renderQuality READ renderQuality WRITE setRenderQuality )
	Q_PROPERTY( bool drawCuesDefault READ getDrawCuesDefault WRITE setDrawCuesDefault )
	Q_PROPERTY( bool isUserStyle READ isUserStyle )
	Q_ENUMS( ShadeStyle TransparencyMode PickingMode )
public:

	enum ShadeStyle { WireBox, SolidBox, Wireframe, LitWireframe, HiddenLine, WireShaded, SmoothShaded,
		WireTextured, Textured, GLSLShader, Unshaded, Picking,
		WIRE_BOX = WireBox, SOLID_BOX = SolidBox, WIREFRAME = Wireframe, LIT_WIREFRAME = LitWireframe,
		HIDDEN_LINE = HiddenLine, WIRE_SHADED = WireShaded, SMOOTH_SHADED = SmoothShaded, 
		WIRE_TEXTURED = WireTextured, TEXTURED = Textured, GLSL_SHADER = GLSLShader, UNSHADED = Unshaded,
		PICKING = Picking };
	enum TransparencyMode { DrawOpaqueOnly, DrawTransparentOnly, DrawBoth,
		DRAW_OPAQUE_ONLY = DrawOpaqueOnly, DRAW_TRANSPARENT_ONLY = DrawTransparentOnly, 
		DRAW_BOTH = DrawBoth };
	enum PickingMode { PickNone, PickFaces, PickPoints, PickNodes, PickMaterials,
		PICK_NONE = PickNone, PICK_FACES = PickFaces, PICK_POINTS = PickPoints, PICK_NODES = PickNodes,
		PICK_MATERIALS = PickMaterials };

	virtual ~DzDrawStyle();

	//
	// MANIPULATORS
	//

	void	setTransMode( TransparencyMode mode );
	void	setPass( int pass );
	void	setDrawObjectsOnly( bool onOff );
	void	setDrawShadowCastersOnly( bool onOff );
	void	setRenderQuality( bool onOff );
	void	setNonOpaqueSorter( DzPolySorter *sorter );
	void	setDrawCuesDefault( bool onOff );

	//
	// ACCESSORS
	//

	PickingMode			pickMode() const;
	TransparencyMode	transMode() const;
	DzPolySorter*		nonOpaqueSorter() const;
	bool				drawObjectsOnly() const;
	bool				drawShadowCastersOnly() const;
	
	bool	renderQuality() const;
	bool	getDrawCuesDefault() const;

public slots:
	bool	selectionMapsEnabled() const;
	int		pass() const;
	bool	drawCues() const;

	void	forceUseLighting();

	ShadeStyle				shadeStyle() const;
	virtual DzSceneShader*	shader() const { return NULL; }

public:

	virtual bool	isUserStyle() const { return false; }

protected:

	DzDrawStyle( ShadeStyle style );

	void	setPickMode( PickingMode mode );
	void	enableSelectionMaps( bool onOff );

private:
	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzDrawStyle>	DzDrawStylePtr;

class DZ_EXPORT DzPickStyle : public DzDrawStyle {
	Q_OBJECT
public:
	DzPickStyle();
	virtual ~DzPickStyle();

	void	setPickingMode( DzDrawStyle::PickingMode mode );
	void	setSelectionMapsEnabled( bool onOff );

private:

	PickingMode	m_pickMode;
};


class DZ_EXPORT DzUnshadedStyle : public DzDrawStyle {
	Q_OBJECT
public:
	DzUnshadedStyle();
	virtual ~DzUnshadedStyle();
};


class DZ_EXPORT DzDefaultStyle : public DzDrawStyle {
	Q_OBJECT
public:
	DzDefaultStyle();
	virtual ~DzDefaultStyle();

	virtual DzSceneShader*	shader() const;

public slots:	
	void	setLight( DzLight *light );
	bool	shadersValid();

private:

	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzUserDrawStyle : public DzDrawStyle {
	Q_OBJECT
	Q_PROPERTY( bool isEnabled READ isEnabled )
public:
	DzUserDrawStyle( ShadeStyle style );
	virtual ~DzUserDrawStyle();

	virtual bool	isUserStyle() const { return true; }

public slots:

	virtual QPixmap	getPixmap() const = 0;
	virtual QString	getDescription() const = 0;

public:

	virtual QWidget*	getPane( QWidget *parent ) const { return NULL; }
	virtual bool		isEnabled() const { return true; }
};


class DZ_EXPORT DzWireBoxStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzWireBoxStyle();
	virtual ~DzWireBoxStyle();

public slots:
	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};


class DZ_EXPORT DzSolidBoxStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzSolidBoxStyle();
	virtual ~DzSolidBoxStyle();

public slots:
	virtual QPixmap	getPixmap() const;
	virtual QString getDescription() const;
};


class DZ_EXPORT DzWireFrameStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzWireFrameStyle();
	virtual ~DzWireFrameStyle();

public slots:
	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};


class DZ_EXPORT DzLitWireFrameStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzLitWireFrameStyle();
	virtual ~DzLitWireFrameStyle();

public slots:
	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};


class DZ_EXPORT DzHiddenLineStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzHiddenLineStyle();
	virtual ~DzHiddenLineStyle();

	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};


class DZ_EXPORT DzWireShadedStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzWireShadedStyle();
	virtual ~DzWireShadedStyle();

	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};


class DZ_EXPORT DzSmoothShadedStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzSmoothShadedStyle();
	virtual ~DzSmoothShadedStyle();

	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};



class DZ_EXPORT DzWireTexturedStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzWireTexturedStyle();
	virtual ~DzWireTexturedStyle();

	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};


class DZ_EXPORT DzTexturedStyle : public DzUserDrawStyle {
	Q_OBJECT
public:
	DzTexturedStyle();
	virtual ~DzTexturedStyle();

	virtual QPixmap	getPixmap() const;
	virtual QString	getDescription() const;
};

#endif // DAZ_DRAW_STYLE_H
