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
	Defines the DzScene class.
**/

#ifndef DAZ_SCENE_H
#define DAZ_SCENE_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzbox3.h"
#include "dztexture.h"
#include "dztimerange.h"
#include "dztypes.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzAudioClip;
class DzBackdrop;
class DzDrawStyle;
class DzOpenGLRenderSettings;
class DzRenderer;
class DzScript;
class IDzSceneNodeFilter;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzScene : public DzBase, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	Q_ENUMS( DzOpenMethod )
	Q_FLAGS( IncludeFlags )
	friend class DzApp;
	friend class DzSceneTimeChangeUndoItem;
	friend class DzSceneTimeStepChangeUndoItem;
	friend class DzScenePlayRangeChangeUndoItem;
	friend class DzSceneAnimRangeChangeUndoItem;
	friend class DzScenePrimSelectUndoItem;
	friend class DzSceneAudioUndoItem;
	friend class DzSceneBackdropUndoItem;
	friend class DzSceneLoader;
public:

	// This enum should actually be named simply "OpenMethod" (sans-Dz),
	// but because the current public build of Bryce 5.5(c) included the
	// wrapper header which then used the Dz name, and we've since
	// changed it for consistency with the rest of the SDK, we do this - REW
	enum	DzOpenMethod { DefaultMethod = 0, OpenNew, MergeFile };
	typedef	DzOpenMethod OpenMethod;

	enum	IncludeFlags { DzObjectsOnly = 0x00000000, DzIncludeLightsFlag = 0x00000001,
				DzIncludeCamerasFlag = 0x00000002, DzIncludeNonShadowersFlag = 0x00000004,
				DzIncludeNonVisibleFlag = 0x00000008, DzIncludeAllFlag = 0x000000ff };
private:

	//
	// CREATORS
	//

	DzScene();
	~DzScene();

public:

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;

	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;
	virtual void			assetSaved();
	virtual bool			modifyAsset();
	virtual bool			modifyAsset( const DzUri &newUri );
	virtual bool			assetNeedSave() const;
	//
	// MANIPULATORS
	//

	void	init();
	void	draw( DzDrawStyle &style );
	void	renderGL( DzDrawStyle &style, const DzOpenGLRenderSettings &settings );

	void				setNodeFilter( IDzSceneNodeFilter *filter );
	IDzSceneNodeFilter*	getNodeFilter();

public slots:

	void	clear();
	bool	isClearing();
	bool	isLoading();
	bool	isDAZLoading();
	void	setBackdrop( DzBackdrop *backdrop );
	void	setAudio( DzAudioClip *audio, int startFrame = 0 );
	bool	addNode( DzNode *node );
	bool	removeNode( DzNode *node );
	void	removeSelected();
	void	removeAllLights();
	void	removeAllCameras();
	DzError	addWSModifier( DzWSModifier *modifier, int index = -1 );
	DzError	removeWSModifier( DzWSModifier *modifier );
	DzError	addDataItem( DzSceneData *item );
	DzError	removeDataItem( DzSceneData *item );
	void	update();
	void	markChanged();
	DzError	saveScene( const QString &filename = "" );
	DzError	loadScene( const QString &filename, DzOpenMethod method );
	void	saveThumbnail( const QString &filename );
	void	selectAllNodes( bool onOff );
	void	selectAllSkeletons( bool onOff );
	bool	setPrimarySelection( DzNode *node );
	void	setHighlightNode( DzNode *node );
	void	beginTimeEdit();
	void	finishTimeEdit();
	void	setTime( DzTime time );
	void	setFrame( int frame );
	void	stepTime( int nFrames = 1, bool forward = true );
	void	setTimeStep( DzTime time );
	void	setPlayRange( DzTimeRange range );
	void	setAnimRange( DzTimeRange range );
	void	play( bool realtime = true );
	void	pause();
	void	loopPlayback( bool onOff );
	void	selectAllTime( bool onOff );
	void	invalidate();
	int		getNumStorablesInScene();	
	void	setAssetLoadPath(const QString& absolutePath);
	QString	getAssetLoadPath(bool* saveToCur=NULL)const;
	void	setPreviewLights( bool onoff );
	bool	getPreviewLights() const;

public:

	//
	// ACCESSORS
	//

	void					getActiveImages( QList<DzTexturePtr> &images ) const;
	DzNodeListIterator		nodeListIterator() const;
	DzSkeletonListIterator	skeletonListIterator() const;
	DzLightListIterator		lightListIterator() const;
	DzCameraListIterator	cameraListIterator() const;
	DzNodeListIterator		selectedNodeListIterator() const;
	DzSkeletonListIterator	selectedSkeletonListIterator() const;
	DzLightListIterator		selectedLightListIterator() const;
	DzCameraListIterator	selectedCameraListIterator() const;
	DzWSModifierIterator	wsModifierListIterator() const;
	DzTimeRangeListIterator	selectedTimeRangeListIterator() const;

public slots:

	bool			needsSave() const;
	DzBackdrop*		getBackdrop() const;
	DzBox3			getBoundingBox( int flags = DzIncludeAllFlag ) const;
	DzAudioClip*	getAudio() const;
	int				getAudioStartFrame() const;
	QString			getFilename( bool *savedTo = NULL ) const;
	int				getNumNodes() const;
	int				getNumSkeletons() const;
	int				getNumLights() const;
	int				getNumCameras() const;
	int				getNumWSModifiers() const;
	DzNode*			getNode( int which ) const;
	QObjectList		getNodeList() const;
	DzSkeleton*		getSkeleton( int which ) const;
	QObjectList		getSkeletonList() const;
	DzLight*		getLight( int which ) const;
	QObjectList		getLightList() const;
	DzCamera*		getCamera( int which ) const;
	QObjectList		getCameraList() const;
	DzWSModifier*	getWSModifier( int which ) const;
	QObjectList		getWSModifierList() const;
	DzNode*			findNode( const QString &name ) const;
	DzNode*			findNodeByLabel( const QString &label ) const;
	DzSkeleton*		findSkeleton( const QString &name ) const;
	DzSkeleton*		findSkeletonByLabel( const QString &label ) const;
	DzCamera*		findCamera( const QString &name ) const;
	DzCamera*		findCameraByLabel( const QString &label ) const;
	DzLight*		findLight( const QString &name ) const;
	DzLight*		findLightByLabel( const QString &label ) const;
	int				findNodeIndex( const DzNode *node ) const;
	int				findSkeletonIndex( const DzSkeleton *skelton ) const;
	DzSceneData*	findDataItem( const QString &name ) const;
	DzNode*			getPrimarySelection() const;
	int				getNumSelectedNodes() const;
	DzNode*			getSelectedNode( int index ) const;
	QObjectList		getSelectedNodeList() const;
	int				getNumSelectedSkeletons() const;
	DzSkeleton*		getSelectedSkeleton( int index ) const;
	QObjectList		getSelectedSkeletonList() const;
	int				getNumSelectedLights() const;
	DzLight*		getSelectedLight( int index ) const;
	QObjectList		getSelectedLightList() const;
	int				getNumSelectedCameras() const;
	DzCamera*		getSelectedCamera( int index ) const;
	QObjectList		getSelectedCameraList() const;
	DzNode*			getHighlightNode() const;
	DzTime			getTime() const;
	int				getFrame() const;
	DzTime			getTimeStep() const;
	bool			isPlaying() const;
	bool			isLoopingEnabled() const;
	DzTimeRange		getPlayRange() const;
	DzTimeRange		getAnimRange() const;
	int				getNumSelectedTimeRanges() const;
	int				getNumDataItems();
	DzSceneData*	getDataItem(int i);

	QString			getUniqueTopLevelLabel( const QString &label, DzNode* node=0 )const;
	
#ifndef Q_MOC_RUN
	static
#endif		
	QString			stripLabelNumber( const QString &label);

signals:
	void	drawnDataChanged();
	void	nodeSelectionListChanged();
	void	skeletonSelectionListChanged();
	void	lightSelectionListChanged();
	void	cameraSelectionListChanged();
	void	primarySelectionChanged( DzNode *node );
	void	highlightNodeChanged( DzNode *node );
	void	sceneClearStarting();
	void	sceneCleared();
	void	sceneLoadStarting();
	void	sceneLoaded();
	void	sceneFilenameChanged( const QString &newName );
	void	timeChanging( DzTime newTime );
	void	timeChanged( DzTime time );
	void	timeStepChanged( DzTime time );
	void	playRangeChanged( const DzTimeRange &range );
	void	animRangeChanged( const DzTimeRange &range );
	void	timeSelectionChanged();
	void	nodeAdded( DzNode *node );
	void	aboutToRemoveNode( DzNode *node );
	void	nodeRemoved( DzNode *node );
	void	nodeListChanged();
	void	skeletonAdded( DzSkeleton *node );
	void	skeletonRemoved( DzSkeleton *node );
	void	skeletonListChanged();
	void	lightAdded( DzLight *node );
	void	lightRemoved( DzLight *node );
	void	lightListChanged();
	void	cameraAdded( DzCamera *node );
	void	cameraRemoved( DzCamera *node );
	void	cameraListChanged();
	void	wsModifierAdded( DzWSModifier *modifier );
	void	wsModifierRemoved( DzWSModifier *modifier );
	void	wsModifierStackChanged();
	void	playbackStarted();
	void	playbackFinished();
	void	loopPlaybackChanged( bool onOff );
	void	aboutToRender( DzRenderer *r );
	void	renderFinished( DzRenderer *r );
	void	materialListChanged();
	void	materialSelectionChanged();
	void	sceneSaveStarting( const QString &filename );
	void	sceneSaved( const QString &filename );
	void	assetModified();
	void	assetWasSaved();

private slots:

	void	updateSelection( DzNode *node, bool onOff );
	void	saveState( DzScript &script );
	void	addRenderer( DzRenderer *r );
	void	startSceneLoad();
	void	finishSceneLoad();

private:

	DzError	readSceneFile( const QString &filename, DzInFile &inFile, bool isMerge );
	void	createDefaultCamera();
	void	cacheBumpMapData();
	void	freeBumpMapCache();
	int		createGLShadowmap( DzLight *light, int pass, int totalPasses );
	void	doRealTimePlay();
	void	doPlay();
	void	setAudioInternal( DzAudioClip *audio, int startFrame );
	void	setBackdropInternal( DzBackdrop *backdrop );
	void	clearInternal();

	struct	Data;
	Data	*m_data;
};

extern DZ_EXPORT DzScene *dzScene;

#endif // DAZ_SCENE_H
