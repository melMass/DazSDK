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
	Defines the DzNode class.
**/

#ifndef DAZ_NODE_H
#define DAZ_NODE_H

/*****************************
	Include files
*****************************/

#include <QtGui/QStyle>

#include "dzbox3.h"
#include "dzelement.h"
#include "dzorientedbox3.h"
#include "dzquat.h"
#include "dzrendermgr.h"
#include "dzrotationorder.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzBoolProperty;
class DzDrawStyle;
class DzEnumProperty;
class DzFloatColor;
class DzFloatProperty;
class DzNumericNodeProperty;
class DzObject;
class DzPointAtController;
class DzPresentation;
class DzRenderSettings;
class DzSelectionMap;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNode : public DzElement, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	Q_PROPERTY( DzRenderMgr::RenderPriority renderPriority READ getRenderPriority WRITE setRenderPriority )
	friend class DzScene;
	friend class DzNodeChildUndoItem;
	friend class DzNodeChildListUndoItem;
	friend class DzNodeObjectUndoItem;
	friend class DzNodeBetaTransform;
	friend class DzWeld;
	friend class DzPointAtController;
	friend class DzNodeFactory;
public:
	//
	// CREATORS
	//

	DzNode();
	virtual ~DzNode();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	setStorablePaths( const QString &path );
	virtual void	copyFrom( const DzElement *source );
	virtual void	save( DzOutFile *file ) const;

	virtual DzElementClipboard*	copyToClipboard(const QStringList &contentTypes=QStringList()) const;
	virtual AssetType			getAssetType() const;
	virtual QString				getAssetId() const;
	virtual const QObject*		toQObject() const;
	virtual QObject*			toQObject();
	
	struct	Data;
public slots:

	//
	// MANIPULATORS
	//
	
	void			setManipOverColor( const QColor &color );
	void			clearManipOverColor();
	virtual void	update( bool isRender = false );
	virtual void	finalize( bool isRender = false, bool allowResChange = true );
	virtual void	select( bool onOff = true );
	void			setSelectable( bool onOff );
	void			setVisible( bool onOff );
	void			setRotationOrder( DzRotationOrder order );

	virtual void	setObject( DzObject *object );
	DzError			addNodeChild( DzNode *child, bool inPlace = false );
	DzError			removeNodeChild( DzNode *child, bool inPlace = false );
	void			removeAllNodeChildren();
	void			setWSTransform( const DzVec3 &pos, const DzQuat &rot,
						const DzMatrix3 &scale );
	void			setWSTransform( DzTime tm, const DzVec3 &pos, const DzQuat &rot,
						const DzMatrix3 &scale );
	void			setWSPos( const DzVec3 &pos );
	void			setWSPos( DzTime tm, const DzVec3 &pos );
	void			setWSRot( const DzQuat &rot );
	void			setWSRot( DzTime tm, const DzQuat &rot );
	void			setWSScale( const DzMatrix3 &scale );
	void			setWSScale( DzTime tm, const DzMatrix3 &scale );
	void			setLocalTransform( const DzVec3 &pos, const DzQuat &rot,
						const DzMatrix3 &scale );
	void			setLocalTransform( const DzVec3 &pos, const DzQuat &rot,
						const DzMatrix3 &scale, float generalScale );
	void			setLocalTransform( DzTime tm, const DzVec3 &pos, const DzQuat &rot,
						const DzMatrix3 &scale );
	void			setLocalTransform( DzTime tm, const DzVec3 &pos, const DzQuat &rot,
						const DzMatrix3 &scale, float generalScale );
	void			setLocalPos( const DzVec3 &pos );
	void			setLocalPos( DzTime tm, const DzVec3 &pos );
	void			setLocalRot( const DzQuat &rot );
	void			setLocalRot( DzTime tm, const DzQuat &rot );
	void			setLocalScale( const DzMatrix3 &scale, float generalScale );
	void			setLocalScale( const DzMatrix3 &scale);
	void			setLocalScale( DzTime tm, const DzMatrix3 &scale, float generalScale );
	void			setLocalScale( DzTime tm, const DzMatrix3 &scale );
	void			setOrientation( const DzQuat &orientation, bool makeDefault = false );
	void			setOrigin( const DzVec3 &origin, bool makeDefault = false );
	void			setEndPoint( const DzVec3 &endPnt, bool makeDefault = false );
	void			clearTransformData( const DzTimeRange &range );
	void			clearAllTransformData();
	virtual void	beginEdit();
	virtual void	finishEdit();
	virtual void	cancelEdit();
	virtual void	setInheritScale( bool onOff );
	void			setPointAtTarget( DzNode *target );
	void			setPointAtStrength( float strength );
	void			setHidden( bool onOff );
	virtual void	setRenderPriority( DzRenderMgr::RenderPriority priority );
	void			setRenderPriority( int priority );
	void			setVisibleInRender( bool onOff );
	void			setSelectionMap( DzSelectionMap *map );
	void			setPresentation( DzPresentation *pres );
	void			setPreviewBox( const DzOrientedBox3 &box );
	virtual	bool	modifyAsset();
	virtual bool	modifyAsset( const DzUri &newUri );
	virtual void	invalidateBoundingBoxes( bool checkSkeleton = true );

public:

	//
	// ACCESSORS
	//

	virtual void		draw( const DzDrawStyle &style ) const;
	virtual void		drawGeometry( const DzDrawStyle &style ) const;
	virtual void		drawBoundingBox( bool shaded = true, bool picking = false ) const;
	void				drawLocalAxis() const;
	virtual void		prepareMotionSample(const DzRenderSettings &settings);
	virtual void		clearMotionSamples();
	virtual void		render( const DzRenderSettings &settings ) const;
	virtual QPixmap		getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon		getIcon() const;
	DzNodeListIterator	nodeChildrenIterator() const;
	void				getNodeChildren( DzNodeList &nodes, bool scanHierarchy = false ) const;

	void				getWSTransform( DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale ) const;
	void				getWSTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaults = false ) const;

	void				getLocalTransform( DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale ) const;
	void				getLocalTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaults = false ) const;
	
public slots:

	DzSkeleton*				getSkeleton() const;
	DzRotationOrder			getRotationOrder() const;
	bool					isSelected() const;
	bool					isSelectable() const;
	bool					isVisible() const;
	bool					isVisibileInRender() const;
	bool					castsShadow() const;
	DzObject*				getObject() const;
	int						getNumNodeChildren() const;
	DzNode*					getNodeChild( int i ) const;
	QObjectList				getNodeChildren( bool scanHierarchy = false ) const;
	bool					isNodeChild( const DzNode *node ) const;
	DzNode*					findNodeChild( const QString &name, bool scanHierarchy = false ) const;
	DzNode*					findNodeChildByAssetID( const QString &assetID, bool scanHierarchy = false, bool checkSource = true ) const;
	DzNode*					getNodeParent() const;
	bool					isRootNode() const;
	DzBox3					getLocalBoundingBox() const;
	DzOrientedBox3			getLocalOrientedBox() const;
	virtual DzBox3			getWSBoundingBox() const;
	virtual DzOrientedBox3	getWSOrientedBox() const;
	DzOrientedBox3			getPreviewBox() const;
	DzMatrix3				getWSTransform() const;
	DzMatrix3				getWSTransform( DzTime tm, bool defaultVal = false ) const;
	DzVec3					getWSPos() const;
	DzVec3					getWSPos( DzTime tm, bool defaultVal = false ) const;
	DzQuat					getWSRot() const;
	DzQuat					getWSRot( DzTime tm, bool defaultVal = false ) const;
	DzMatrix3				getWSScale() const;
	DzMatrix3				getWSScale( DzTime tm, bool defaultVal = false ) const;
	DzMatrix3				getLocalTransform() const;
	DzMatrix3				getLocalTransform( DzTime tm, bool defaultVal = false ) const;
	DzVec3					getLocalPos() const;
	DzVec3					getLocalPos( DzTime tm, bool defaultVal = false ) const;
	DzQuat					getLocalRot() const;
	DzQuat					getLocalRot( DzTime tm, bool defaultVal = false ) const;
	DzMatrix3				getLocalScale() const;
	DzMatrix3				getLocalScale( DzTime tm, bool defaultVal = false ) const;
	virtual DzQuat			getOrientation( bool defaultVal = false ) const;
	void					updateOrientation();
	virtual DzVec3			getOrigin( bool defaultVal = false ) const;
	virtual DzVec3			getEndPoint( bool defaultVal = false ) const;
	DzSelectionMap*			getSelectionMap() const;
	
	DzFloatProperty*		getXPosControl() const;
	DzFloatProperty*		getYPosControl() const;
	DzFloatProperty*		getZPosControl() const;
	DzFloatProperty*		getXRotControl() const;
	DzFloatProperty*		getYRotControl() const;
	DzFloatProperty*		getZRotControl() const;
	DzFloatProperty*		getScaleControl() const;
	DzFloatProperty*		getXScaleControl() const;
	DzFloatProperty*		getYScaleControl() const;
	DzFloatProperty*		getZScaleControl() const;
	DzBoolProperty*			getSelectabilityControl() const;
	DzBoolProperty*			getVisibilityControl() const;
	DzBoolProperty*			getRenderVisibilityControl() const;
	DzBoolProperty*			getShadowControl() const;
	DzEnumProperty*			getRenderPriorityControl() const;
	DzNumericNodeProperty*	getPointAtControl() const;
	
	DzFloatProperty*		getOriginXControl() const;
	DzFloatProperty*		getOriginYControl() const;
	DzFloatProperty*		getOriginZControl() const;
	DzFloatProperty*		getEndXControl() const;
	DzFloatProperty*		getEndYControl() const;
	DzFloatProperty*		getEndZControl() const;
	DzFloatProperty*		getOrientXControl() const;
	DzFloatProperty*		getOrientYControl() const;
	DzFloatProperty*		getOrientZControl() const;

	virtual bool			inheritsScale()const;
	bool					isHidden() const;
	virtual DzRenderMgr::RenderPriority	getRenderPriority() const;
	DzPresentation*			getPresentation() const;

	void					setInvisibleByGroup( bool yesNo );
	void					setUnselectableByGroup( bool yesNo );
	bool					invisibleByGroup();
	bool					unselectableByGroup();


signals:

	void	parentChanged( DzNode *node, DzNode *oldParent, DzNode *newParent );
	void	transformChanged();
	void	selected( DzNode *node, bool onOff );
	void	rotationOrderChanged();
	void	childAdded( DzNode *child );
	void	childRemoved( DzNode *child );
	void	childListChanged();
	void	objectChanged( DzNode *node, DzObject *oldObject, DzObject *newObject );
	void	drawnDataChanged();
	void	visibilityChanged();
	void	selectabilityChanged();
	void	aboutToBeRemoved();
	void	removed();
	void	added();
	void	hiddenChanged( bool hidden );
	void	riggingChanged();
	void	materialListChanged();
	void	materialSelectionChanged();
	void	uvsChanged();
	void	assetModified();
	void	assetWasSaved();
	void	boundBoxInvalidated();
	void	aboutToDelete( DzNode *node );
	void	inheritScaleChanged();

protected slots:

	void	invalidateCache();
	void	selectionMapModified();
	void	updateTransform();
	void	updateVis();
	void	updateRenderable();
	
	
protected:
	DzNode( const DzInFile *file );

	virtual void	calcWSTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaultVals = false ) const;
	virtual void	calcLocalTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaultVals = false ) const;
	virtual void	setNodeParent( DzNode *parent );
	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;
	void			bcCastShadowsProperty( DzBoolProperty *prop );
	void			drawNull( const DzDrawStyle &style ) const;
	bool			boundingBoxesValid();

private slots:

	void	updatePointAtTarget( DzNode *node );
	void	updateAfterSceneLoad();
	void	sceneLoaded();

private:
	void	createProperties();
	void	setTransformPresentation( DzProperty *prop );
	void	setUserPropertyPresentation( DzProperty *prop );
	void	createRiggingProperties();

	DzPointAtController*	getPointAtController();

	void			setObjectInternal( DzObject *obj, bool addToChildren = true );
	void			cacheTransform();
	void			insertNodeChild( DzNode *child, int index = -1 );
	bool			getMajorColor( DzFloatColor &color ) const;
	void			setRotationPropertyFlags();

	friend struct Data;
	Data	*m_data;
};

class DZ_EXPORT DzNodeClipboard : public DzElementClipboard {
	Q_OBJECT
	friend class DzNode;
public:
	virtual ~DzNodeClipboard();

public slots:

	virtual DzError	paste( DzElement *elem, const QStringList &contentTypes = QStringList() ) const;

protected:

	DzNodeClipboard( const DzNode *node, const QStringList &contentTypes );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NODE_H
