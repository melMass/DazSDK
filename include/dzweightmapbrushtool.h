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

#ifndef DAZ_WEIGHT_MAP_BRUSH_TOOL_H
#define DAZ_WEIGHT_MAP_BRUSH_TOOL_H

/*****************************
	Include files
*****************************/

#include "dz3dbrushtool.h"
#include "dzweightmap.h"

/*****************************
	Forward Declarations
*****************************/

class DzFacetShape;

/*****************************
	Class Definitions
*****************************/

class DZ_EXPORT DzWeightMapBrushTool : public Dz3DBrushTool {
	Q_OBJECT
public :

	enum DisplayMode { DisplayOff = 0, DisplayValue, DisplayBool };

	DzWeightMapBrushTool( const QString &name );
	virtual ~DzWeightMapBrushTool();
	
	virtual bool	mousePress( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void	mouseRelease( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void	mouseMove( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier );
	virtual void	contextMenu( Dz3DViewport *view, DzMenu *menu, const QPoint &pos );
	virtual void	buildOptionsMenu( DzActionMenu *menu ) const;
	virtual int		getOptionsMenuVersion() const;
	virtual void	draw( const DzDrawStyle &style, Dz3DViewport *view ) const;
	virtual void	applyDirectionalGradient();
	virtual void	applySphereGradient();


public slots:

	void			setWeightMap( DzWeightMap *map );
	DzWeightMap*	getWeightMap() const;

	void			setChildWeights( const QVector<DzWeightMapPtr> &weights );

	void			setSymmetryWeightMap( DzWeightMap *map );
	DzWeightMap*	getSymmetryWeightMap() const;

	void			addAdjunctWeightMap( DzWeightMap *map );
	void			clearAdjunctWeightMaps();
	int				getNumAdjunctWeightMaps() const;
	DzWeightMap*	getAdjunctWeightMap( int index ) const;

	void			setSensitivity( float val );
	float			getSensitivity() const;

	void			setSmoothFactor( float val );
	float			getSmoothFactor() const;

	void			setDisplayMode( DisplayMode mode );
	DisplayMode		getDisplayMode() const;

	void			enableSymmetry( bool onOff );
	bool			symmetryEnabled() const;

	void			setSymmetryAxis( int axis );
	int				getSymmetryAxis() const;

	void			setSymmetrySide( int side );
	int				getSymmetrySide() const;

	void			setLockCenterLine( bool onOff );
	bool			getLockCenterLine()const;

	virtual DzColorGradient*	getColorGradient() const;

	bool	copyWeights();
	bool	pasteWeights();
	bool	canCopyWeights();
	bool	canPasteWeights();
	bool	fillSelectedFaces( unsigned short weight );
	bool	smoothSelectedFaces( float smoothFactor, int iterations );
	bool	attenuateSelectedFaces( float percent );
	void	filterCurrentWeightMap( float value );

	QColor	getLockedMapColor()const;
	void	setLockedMapColor(const QColor color);
	void	setSelectedVerts( const QList<int> verts);
	QColor	getSelectedVertexColor()const;
	void	setSelectedVertexColor(const QColor color);

signals:

	void	weightMapChanged( DzWeightMap *map );
	void	symmetryWeightMapChanged( DzWeightMap *map );
	void	symmetryEnableChanged( bool onOff );
	void	symmetryAxisChanged( int axis );
	void	canCopyWeightsChanged( bool onOff );
	void	canPasteWeightsChanged( bool onOff );
	void	displayModeChanged( DzWeightMapBrushTool::DisplayMode mode );
	void	adjunctWeightListChanged();
	void	macroActionPerformed();
	void	paintedWeight();

protected:

	virtual void	setNode( DzNode *node );
	virtual void	invalidateMap(bool allowSymmetry );
	int				getSymmetricVertex( int index);
	void			restoreSettings(const QString &path = "WeightMapBrush");
	void			saveSettings( const QString &path = "WeightMapBrush" );
	virtual void	normalizeVertex( int vertIdx );
	virtual void	invalidateVertex( int vertIdx );

private:

	void	setObject( DzObject *object );

	void	smoothSelectedFaces( DzFacetMesh *mesh, float smoothFactor );
	void	apply( const DzTArray<int> &faces, float outerVal, float innerVal, const DzVec3 &hitPoint,
				bool additive, bool altBrush );
	void	applySmooth( int vertIndex, float factor, const DzPnt3 *verts, unsigned short *weights );
	float	calcSensitivity( float outerSqrd, float innerSqrd, const DzVec3 &hitPoint, const DzPnt3 &curPoint );
	void	clearVertexMap();
	void	clearSymmetryMap();
	void	buildSymmetryMap();
	void	clearSubDMap();
	bool	updateSubDMap( int level );
	void	drawFacetMesh( const DzDrawStyle &style, Dz3DViewport *view, DzFacetMesh *pmesh, DzFacetShape *shape ) const;
	void	drawSelectedVerts( const DzDrawStyle &style, Dz3DViewport *view, DzFacetMesh *pmesh)const;
	void	beginEdit();
	void	finishEdit();
	void	cancelEdit();
	void	setUpModifiers();
	DzVec3	getSphereIntersection( const DzVec3 &pnt1In, const DzVec3 &pnt2In ) const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_WEIGHT_MAP_BRUSH_TOOL_H