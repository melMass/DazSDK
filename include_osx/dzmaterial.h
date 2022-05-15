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
	Defines the DzMaterial class.
**/

#ifndef DAZ_MATERIAL_H
#define DAZ_MATERIAL_H

/*****************************
	Include files
*****************************/

#include "dzbox3.h"
#include "dzelement.h"
#include "dzrendermgr.h"
#include "dztexture.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzBoolProperty;
class DzCoShaderInfo;
class DzDrawStyle;
class DzEnumProperty;
class DzFloatProperty;
class DzRenderSettings;
class DzGeometry;

/****************************
	Type Definitions
****************************/

typedef DzTSharedPointer<DzMaterial> DzMaterialPtr;
typedef DzTArray<DzMaterialPtr>	DzMaterialPtrList;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMaterial : public DzElement, public DzSceneAsset, public DzRefCountedItem {
	Q_OBJECT
	Q_PROPERTY( DzRenderMgr::RenderPriority renderPriority READ getRenderPriority WRITE setRenderPriority )
	Q_INTERFACES( IDzSceneAsset )
	friend class DzShape;
	friend class DzMaterialFactory;
public:
	//
	// CREATORS
	//

	DzMaterial();
	virtual ~DzMaterial();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			save( DzOutFile *file ) const;
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;

public slots:
	//
	// MANIPULATORS
	//

	virtual void	select( bool onOff );
	virtual void	setBakedMap( DzTexture *img );
	virtual void	setDiffuseColor( const QColor &color ) = 0;
	virtual void	setBaseOpacity( float val ) = 0;
	virtual void	setColorMap( const DzTexture *img ) = 0;
	virtual void	setOpacityMap( const DzTexture *img ) = 0;

	virtual void	setSmoothingOn( bool onOff );
	virtual void	setSmoothingAngle( float angle );

	virtual void	setRenderPriority( DzRenderMgr::RenderPriority priority );
	void			setRenderPriority( int priority );
	virtual void	enablePropagateRenderPriorityToNodes( bool propagate );
	DzBox3			getBoundingBox();

	//
	// ACCESSORS
	//

	virtual int			getNumUVMaps() const; 
	virtual int			getNumGLMaps() const; 
	virtual QColor		getDiffuseColor() const = 0;
	virtual double		getBaseOpacity() const = 0;
	virtual bool		isColorMappable() const = 0;
	virtual bool		isOpacityMappable() const = 0;
	virtual DzTexture*	getColorMap() const = 0;
	virtual DzTexture*	getOpacityMap() const = 0;
	virtual QString		getMaterialName() const = 0;
	virtual bool		needsTangentSpaceParams() const = 0;
	virtual bool		shouldAlwaysEmbed() const = 0;
	virtual bool		shadersMatch(const DzMaterial* otherMat)const;

	virtual bool		isOpaque() const { return true; }

	virtual bool		isSmoothingOn() const;
	virtual double		getSmoothingAngle() const;
	
	virtual DzRenderMgr::RenderPriority	getRenderPriority() const;
	virtual bool		isPropagateRenderPriorityToNodesEnabled() const;

	QObjectList			getAllMaps() const;
	bool				isSelected() const;
	DzTexture*			getBakedMap() const;
	void				startDrawHighlight();
	void				stopDrawHighlight();
	bool				isHighlighted() const;
	int					getIndex() const;
	
	DzEnumProperty*		getUVSetControl() const;
	DzBoolProperty*		getSmoothControl() const;
	DzFloatProperty*	getSmoothAngleControl() const;
	DzEnumProperty*		getRenderPriorityControl() const;
	DzBoolProperty*		getPropagatePriorityControl() const;
	DzFloatProperty*	getFollowBlendControl()const;

	QObjectList			getShapeList() const;
	virtual	bool		modifyAsset();
	virtual bool		modifyAsset( const DzUri &newUri );

	void				setFollowMaterial( DzMaterial* mat);
	DzMaterial*			getFollowMaterial()const;

	bool				isRenderingAsCoShader()const;

	virtual bool		shouldSortOnLoad() const;

public:

	DzShapeListIterator	shapeListIterator() const; 
	virtual void		getAllMaps( QList<DzTexturePtr> &images ) const { }
	void				setGL( const DzDrawStyle &style ) const;
	void				unsetGL( const DzDrawStyle &style ) const;
	void				setGLHighlight( const DzDrawStyle &style ) const;
	void				unsetGLHighlight( const DzDrawStyle &style ) const;
	virtual void		setRender( const DzRenderSettings &settings ) const;
	virtual void		unsetRender( const DzRenderSettings &settings ) const;

	DzUVSet*			getActiveUVSet( DzShape *shape ) const;
	DzUVSet*			getActiveUVSet( const DzGeometry* geom ) const;
	virtual bool		allowsAutoBake() const = 0;

public slots:
#ifndef Q_MOC_RUN
	static
#endif
	int					getNumMaterials();
#ifndef Q_MOC_RUN
	static
#endif
	DzMaterial*			getMaterial( int which );

signals:

	void	selectionStateChanged( DzMaterial *mat, bool onOff );
	void	bakedMapChanged();
	void	settingsChanged();
	void	uvsChanged();
	void	smoothingChanged();
	void	assetModified();
	void	assetWasSaved();
	void	followMaterialChanged();
	
protected:
	DzMaterial( const DzInFile *file );
	DzMaterial( const DzMaterial* material, bool copyDataItems = true);
	//
	// MANIPULATORS
	//

	virtual void	addedTo( DzShape *shape );
	virtual void	removedFrom( DzShape *shape );

	//
	// ACCESSORS
	//

	virtual void	setGLMat( const DzDrawStyle &style ) const = 0;
	virtual void	unsetGLMat( const DzDrawStyle &style ) const = 0;
	virtual void	setShader( const DzRenderSettings &settings ) const = 0;
	virtual void	setCoShader( const DzRenderSettings &settings, DzCoShaderInfo& info ) const = 0;
	virtual void	setGLBakeMat( const DzDrawStyle &style ) const;
	virtual void	unsetGLBakeMat( const DzDrawStyle &style ) const;

	bool			multiTexturingSupported() const;

private slots:

	void	updateUVList();
	void	connectForAutoBake();
	void	requestAutoBake();
	void	triggerAutoBake();
	void	resetBakedMap();
	void	propagateRenderPriorityToNodes();

private:
	void	init( bool doCreateProperties, const DzMaterial* copyFrom = NULL );
	void	createProperties(const DzMaterial* copyFrom);
	void	setTextureConvertShader( const DzRenderSettings &settings ) const;
	int		setTextureConvertTokens( const DzRenderSettings &settings ) const;
	
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzCoShaderInfo
{
public:
	DzCoShaderInfo();
	virtual ~DzCoShaderInfo();

	void setSurfaceCoShader( const QString& handle );
	void setDisplacementCoShader( const QString& handle, float displacementBound );

	QString getSurfaceCoShader()const;
	QString getDisplacementCoShader()const;
	float	getDisplacementCoShaderBound()const;

private:
	struct Data;
	Data* m_data;
};

#endif // DAZ_MATERIAL_H
