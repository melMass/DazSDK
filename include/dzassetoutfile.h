/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This is UNPUBLISHED PROPRIETARY SOURCE CODE of DAZ 3D, Inc.
	the contents of this file may not be disclosed to third parties, 
	copied or duplicated in any form, in whole or in part, without the 
	prior written permission of DAZ 3D, Inc.
**********************************************************************/
#ifndef DAZ_ASSET_OUT_FILE_H
#define DAZ_ASSET_OUT_FILE_H


/**********************************************************************
	THIS IS NOT AN OFFICIAL PART OF THE SDK.
	ANY PART OF THIS FILE AND THE CLASSES IT CONTAINS MAY CHANGE AT ANY TIME.
	IT SHOULD NOT BE USED WHEN DEVELOPING PLUG-INS.
**********************************************************************/


/****************************
	Include files
****************************/

#include <QtCore/QStringList>

#include "dztsharedpointer.h"
#include "dztypes.h"
#include "dzuri.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class QIODevice;

class DzBase;
class DzAssetFile;
class DzAssetOutProperty;
class DzBulgeBinding;
class DzDFormModifier;
class DzERCLink;
class DzERCLink;
class DzFacetMesh;
class DzFigure;
class DzFileIOSettings;
class DzFloatProperty;
class DzGeometry;
class DzLegacyBinding;
class DzLegacyFigure;
class DzLegacyJointParam;
class DzLegacyJointSphere;
class DzLegacySourceInfo;
class DzMeshSmoothModifier;
class DzMorphDeltas;
class DzNumericProperty;
class DzObject;
class DzPresentation;
class DzProgress;
class DzSelectionMap;
class DzSkinBinding;
class DzTexture;
class DzTextureComponent;
class DzUri;
class DzVec3;
class DzWeightMap;
class IDzJsonIO;
class DzElementData;
class DzDForm;

typedef DzTSharedPointer<DzMaterial> DzMaterialPtr;
struct DzModifierDefinition;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzAssetOutFile {
public:
	DzAssetOutFile( const QString &path, const QString &fileType );
	DzAssetOutFile( const DzSceneAssetFileInfo &assetInfo, const QString &fileType, const QString &contentDir = QString::null );
	DzAssetOutFile( IDzSceneAsset *assetInfo, const QString &fileType, const QString &contentDir = QString::null );
	virtual ~DzAssetOutFile();

	void	setCompressOutput( bool onOff );
	bool	addAsset( IDzSceneAsset *asset );
	bool	addFormula( DzERCLink *formula, DzNumericProperty *output, IDzSceneAsset *owner );
	bool	addShapeMapping( DzGeometry *geom, DzShape *shape );

	bool	write();

	DzUri	getUri() const;
	DzSceneAssetFileInfo getSceneAssetFileInfo()const;
	bool	containsAsset( IDzSceneAsset *asset ) const;

	QString	getFileType() const;
	void	setFileType( const QString &type );

	DzFileIOSettings*	getSettings() const;

	QString	relativeUri( IDzSceneAsset *asset ) const;
	QString	relativeUri( const DzUri &uri ) const;
	QString	getInstanceId( DzBase *key, IDzSceneAsset *asset );
	QString	getUnqiueID( const QString& name );
	QString	getPropertyReference( bool includeValue, bool forSceneAnimationBlock, DzProperty *prop, DzNode *propertyNode = NULL, DzNode *savingNode = NULL );

	static void	getGeometryLegacySourceInfo( DzLegacySourceInfo &geomSourceInfo, DzGeometry *geom, DzShape *shape );

	bool	writeTextureMap( DzTexture *map, IDzJsonIO *io );
	void	cleanSourceInfo();

protected:

	virtual bool	writeScene( IDzJsonIO *io ) { return true; }
	virtual QString getParentUri( DzMorph *morph ) const;

	bool	write( QIODevice *dev );
	bool	writeFile( IDzJsonIO *io );
	bool	writeAssetInfo( IDzJsonIO *io );
	bool	writeContributor( const DzAuthor &contributor, IDzJsonIO *io );
	bool	writeLibraries( IDzJsonIO *io );
	bool	writeGeometryLibrary( IDzJsonIO *io, DzProgress &progress );
	bool	writeNodeLibrary( IDzJsonIO *io, DzProgress &progress );
	bool	writeUVSetLibrary( IDzJsonIO *io, DzProgress &progress );
	bool	writeModifierLibrary( IDzJsonIO *io, DzProgress &progress );
	bool	writeMaterialLibrary( IDzJsonIO *io, DzProgress &progress );
	bool	writeImageLibrary( IDzJsonIO *io, DzProgress &progress );
	bool	writeGeometryAsset( IDzSceneAsset *asset, IDzJsonIO *io );
	void	writeSource( IDzSceneAsset *asset, IDzJsonIO *io );
	bool	writeFigureGraft( DzFigure *fig, IDzJsonIO *io );
	bool	writeRigidity( DzShape *shape, IDzJsonIO *io );
	bool	writeRigidityGroup( DzShape *shape, DzRigidityGroup *group, IDzJsonIO *io );
	bool	writeNodeAsset( IDzSceneAsset *asset, IDzJsonIO *io );
	bool	writeNodeChannels( DzNode *node, IDzJsonIO *io, QSet<DzProperty*>& props, bool isInstance );
	bool	writeChannelsXYZ( const QString &channel, DzFloatProperty *x, DzFloatProperty *y, DzFloatProperty *z, IDzJsonIO *io, bool isInstance );
	bool	writeUVSetAsset( IDzSceneAsset *asset, IDzJsonIO *io );
	bool	writeModifierAsset( IDzSceneAsset *asset, IDzJsonIO *io);
	bool	writeMaterialAsset( IDzSceneAsset *asset, IDzJsonIO *io );
	bool	writeMaterial( DzMaterial *mat, IDzJsonIO *io, DzGeometry const *mesh, bool isDef, bool isEmbedded, bool isUVEmbedded, DzPropertyList *includeList = NULL );
	bool	writeMaterialChannel(const QString& name, DzProperty *prop, IDzJsonIO *io, bool isInstance, 
				DzPropertyList *includeList, QSet<DzProperty*>& writtenProps, bool onlyWriteIfMapped);
	bool	writeImageAsset( IDzSceneAsset *asset, IDzJsonIO *io );
	bool	writeImageLayer( DzTextureLayer *layer, IDzJsonIO *io );
	bool	writeImageComponent( DzTextureComponent *layer, IDzJsonIO *io );
	bool	writeMorphAsset( DzMorph *morph, IDzJsonIO *io );
	bool	writeMorphDeltas( DzMorph *morph, DzMorphDeltas *deltas, IDzJsonIO *io );
	bool	writeDeltaList( const QString& tag, IDzJsonIO *io, const QVector<int> &normalDeltaV, DzMorphDeltas *deltas );
	bool	writeDFormAsset( DzDFormModifier *morph, IDzJsonIO *io );
	bool	writeSkinAsset( DzSkinBinding *morph, IDzJsonIO *io );
	bool	writeLegacyBindingAsset( DzLegacyBinding *binding, IDzJsonIO *io );
	bool	writeBoneBinding( DzBoneBinding *bind, IDzJsonIO *io );
	bool	writeBulgeBinding( const QString &name, DzBulgeBinding *bind, IDzJsonIO *io );
	bool	writeWeightMap( const QString &name, DzWeightMap *map, IDzJsonIO *io );
	bool	writeSelectionMap( DzSelectionMap *map, IDzJsonIO *io );
	bool	writeModifierChannel( DzProperty *prop, IDzJsonIO *io, bool isInstance, bool legInstance = false );
	bool	writeLegacyJoint( DzLegacyJoint *joint, IDzJsonIO *io );
	bool	writeLegacyJointParam( DzLegacyJointParam *param, IDzJsonIO *io );
	bool	writeJointSphere( DzLegacyJointSphere *sphere, IDzJsonIO *io );
	bool	writeSmoothAsset( DzMeshSmoothModifier *smooth, IDzJsonIO *io );
	bool	writeCustomModifier( DzModifier *modifier, IDzJsonIO *io );
	bool	writeLegacyFigureAsset( DzLegacyFigure *figure, IDzJsonIO *io );
	bool	writeGeomVertices( DzGeometry *geom, IDzJsonIO *io );
	bool	writeGeomFaceGroups( DzFacetMesh *geom, IDzJsonIO *io );
	bool	writeGeomMatGroups( DzFacetMesh *geom, IDzJsonIO *io );
	bool	writeGeomPolygons( DzFacetMesh *geom, IDzJsonIO *io );
	bool	writeVec3Member( const QString &name, const DzVec3 &val, IDzJsonIO *io );
	bool	writeVec4Member( const QString &name, const DzVec3 &val, float w, IDzJsonIO *io );
	bool	writePresentation( DzPresentation *presentation, IDzJsonIO *io );
	virtual bool writeGeometryInstances( DzObject *obj, bool isEmbedded, IDzJsonIO *io );
	virtual bool writeShapeInstance( DzShape *shape, bool isEmbedded, IDzJsonIO *io );
	void	writeInstanceUrl( IDzJsonIO * io, IDzSceneAsset * asset );
	bool	writeGeometryLegacySourceInfo( DzShape *shape, bool isDef, IDzJsonIO *io );
	bool	writeRegionRecurse( DzGeometryRegion *region, IDzJsonIO *io );
	bool	writeFormulas( IDzSceneAsset *asset, IDzJsonIO *io );

	DzNode* getAssetNode( IDzSceneAsset * asset )const;
	bool	writeFormula( DzFormula *formula, const QString &stage, const QString &outputRef, IDzJsonIO *io );
	bool	writeFormula( DzERCLink *ercLink, const QString &outputRef, IDzJsonIO *io, DzNode* srcNode );
	bool	writeExtraElementData( DzElement *elem, IDzJsonIO *io, bool &extraStarted );
	bool	writeExtraSceneData( IDzJsonIO *io, bool writeCurrentSceneInfo );
	bool	writePreviewBox( DzNode *node, IDzJsonIO *io );
	bool	writeAltGeometryInstances( DzLegacyFigure *fig, IDzJsonIO *io );
	bool	writeNodeAdditionalChannels( DzNode *node, IDzJsonIO *io, const QSet<DzProperty*>& writtenProps, 
				bool isInstance, bool isEmbbed, DzPropertyList additionalProps, bool& extraStarted );
	bool	writeAdditionalChannels( DzElement *elem, const QSet<DzProperty*> &writtenProps, 
				bool isInstance, bool isEmbbed, bool filterModProperties, bool filterAlais, bool& additionalStarted, bool& extraStarted, IDzJsonIO *io, const QString& typeTag, 
				DzPropertyList additionalProps=DzPropertyList() );

	bool	writeAdditionalChannels( DzPropertyListIterator &propIt, bool filterUser, bool filterAlais, const QSet<DzProperty*> &writtenProps, bool isInstance, bool isEmbbed, bool &additionalStarted, bool &extraStarted, IDzJsonIO * io, const QString &typeTag );
	virtual bool writeProperty( const QString& tagName, DzProperty *prop, DzAssetOutProperty &outProp, IDzJsonIO *io, bool isInstance );
	bool	writeCamera( DzCamera *camera, IDzJsonIO *io );
	bool	writeLight( DzLight *light, IDzJsonIO *io );

	QString	getPropertyGroup( DzProperty *prop ) const;
	QString	getPresetPropertyReference( DzProperty *prop, DzNode *rootNode, DzNode *node = NULL );
	
	DzNode*	getNode( DzProperty *prop ) const;
	DzNode*	getNode( DzElement *elem ) const;
	bool	makeAssetIDUnique( IDzSceneAsset *asset );
	bool	writeMorphLegacySourceInfo( DzMorph *morph, IDzJsonIO *io );
	bool	writeRenderSettings( IDzJsonIO * io );
	bool	writeSceneSettings( IDzJsonIO * io );
	bool	writeShapeMatGroups( DzShape *shape, IDzJsonIO *io );
	void	setNodePropertyPath( DzProperty * prop, DzNode * node, DzUri &uri );
	void	setMaterialPropertyPath( DzMaterial* mat, DzProperty * prop, DzUri &uri );
	
	virtual bool	shouldEmbed( IDzSceneAsset *asset ) const;
	virtual bool	currentValueInAnimation()const;
	virtual DzPropertyList* getMaterialIncludeProperties() const;


	void	cleanInfoFromNode( DzNode *node );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzSceneOutFile : public DzAssetOutFile {
public:
	DzSceneOutFile( const QString &path );
	DzSceneOutFile( const QString &path, const DzNodeList &nodes, bool writeParentRefs = false, bool filterModifiers = false,
					bool assignTheAssets = true );
	virtual ~DzSceneOutFile();

	QStringList	getUnsavedAssets() const;
	void	setCurrentFrameOnly( bool onOff );
	void	setStartFrame( DzTime time );
	void	setEndFrame( DzTime time );
	const DzNodeList&	getExportNodes() const;
	void	setExportNodes( const DzNodeList &nodes );
	void	validateAnimationRanges();
	DzTime	getStartFrame() const;
	DzTime	getEndFrame() const;
	bool	getCurrentFrameOnly() const;
	

protected:

	virtual bool	writeScene( IDzJsonIO *io );
	virtual bool	writeModifierInstances( DzNode *node, IDzJsonIO *io, bool &foundModifier );
	virtual bool	writeAnimations( DzNode *node, IDzJsonIO *io, bool &foundAnimation );
	virtual bool	writeMaterialInstances( DzNode *node, IDzJsonIO *io, bool sceneInstances, bool &foundMaterial );
	virtual bool	writeNodeInstance( DzNode *node, IDzJsonIO *io );
	virtual void	wirteNodeInstanceFollow( DzSkeleton * figure, IDzJsonIO * io );
	virtual void	writeNodeInstanceParent( DzNode * node, IDzJsonIO * io );
	virtual bool	writeUVInstances( DzNode *node, DzShape* shape, IDzJsonIO * io, bool &foundModifier );

	bool	writeNodeInstances( IDzJsonIO *io );
	bool	writeNodeInstanceRecurse( DzNode *node, IDzJsonIO *io );
	bool	writeUVInstances(IDzJsonIO *io);
	bool	writeUVInstancesRecurse( DzNode *node, IDzJsonIO *io, bool &foundUVs );
	bool	writeUVInstances( DzNode *node, IDzJsonIO *io, bool &foundUVs );
	bool	writeModifierInstances( IDzJsonIO *io );
	bool	writeModifierInstancesRecurse( DzNode *node, IDzJsonIO *io, bool &foundModifier );
	bool	writeModifierInstances( DzObject *obj, QString nodeUriStr, bool &foundModifier, IDzJsonIO *io );
	bool	writePropertyModifierInstance( DzProperty* prop, bool &foundModifier, IDzJsonIO * io, QString nodeUriStr );
	bool	writeModifierInstance( DzModifier *mod, DzObject *obj, QString nodeUriStr, bool &foundModifier, IDzJsonIO *io );
	QString	getModifierParentID( DzModifier *mod, DzObject *obj, const QString& nodeUriString );
	bool	writeMaterialInstances( IDzJsonIO *io );
	bool	writeMaterialInstancesRecurse( DzNode *node, IDzJsonIO *io, bool sceneInstances, bool &foundMaterial );
	bool	writeShapeMaterialInstances( DzNode *node, DzShape *shape, IDzJsonIO *io, bool sceneInstances, bool &foundMaterial );
	bool	writeAnimations( IDzJsonIO *io );
	bool	writeAnimations( DzProperty *prop, IDzJsonIO *io, bool writeOnlyIfMultiKey, bool &foundAnimation );
	bool	canWriteNode( DzNode *node );
	bool	canWriteModifier( DzModifier *mod );
	bool	shouldFilterOutModifier( DzModifier *mod );
	bool	isAutoLoadedModifier( DzModifier *mod, IDzSceneAsset *asset ) const;
	bool	isAutoLoadedModifier( DzProperty *prop ) const;
	bool	isAutoLoadedUVSet( DzNode *node, DzUVSet *uvSet ) const;
	bool	canWriteAsset( IDzSceneAsset *asset );
	virtual void	assignAssets();
	bool	assignNodesRecurse( DzNode *node );
	bool	assignNode( DzNode *node );

	bool	assignShape( DzShape *shape );
	bool	embedAsset( IDzSceneAsset *asset );	
	bool	isEmbedAsset( IDzSceneAsset *asset );

	bool	isGeneratedMorph( DzMorph *morph ) const;

private:
	void	assignEmbeddedAssetsERC();
	void	assignEmbeddedAssetERC( IDzSceneAsset *asset );
	void	assignEmbeddedERC( DzNode *node );
	void	assignEmbeddedERC( DzSkinBinding *skin );
	void	assignEmbeddedERC( DzLegacyBinding *legBind );
	void	assignEmbeddedERC( DzNumericProperty *prop, IDzSceneAsset *owner );
	void	assignEmbeddedERC( DzERCLink *ercLink, IDzSceneAsset *owner, DzNumericProperty *prop );
	IDzSceneAsset * getPropertyAssetOwner( DzNumericProperty* tgtProp);
	void	assignLegacyMorphERC( DzObject *obj, DzLegacyFigure *legFig );
	void	addEmbeddedFormula( DzERCLink *link, DzNumericProperty *prop, IDzSceneAsset *asset );
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzGeometryOutFile : public DzAssetOutFile {
public:
	DzGeometryOutFile( DzShape *shape, IDzSceneAsset *geomAsset, const QString &contentDir = QString::null );
	virtual ~DzGeometryOutFile();

protected:
	bool	assignAssets( DzShape *shape );
};

class DZ_EXPORT DzMaterialAssetOutFile : public DzAssetOutFile {
public:
	DzMaterialAssetOutFile( DzMaterial* mat, const QString &contentDir = QString::null );
	virtual ~DzMaterialAssetOutFile();

	
	virtual bool	writeProperty( const QString& tagName, DzProperty *prop, DzAssetOutProperty &outProp, IDzJsonIO *io, bool isInstance );
};

class DZ_EXPORT DzNodeOutFile : public DzAssetOutFile {
public:
	DzNodeOutFile( DzNode *node, bool writeGeom, const QString &contentDir = QString::null );
	virtual ~DzNodeOutFile();

	DzNode*	getNode() const;
	bool	assignAssets( DzNode *node );

protected:

	DzNode	*m_node;
	bool	m_writeGeom;
};

class DZ_EXPORT DzFigureOutFile : public DzNodeOutFile {
public:
	DzFigureOutFile( DzFigure *figure, bool writeGeom, const QString &contentDir = QString::null );
	virtual ~DzFigureOutFile();

private:

	bool	assignBoneAssets( DzFigure *figure );
};

class DZ_EXPORT DzModifierOutFile : public DzAssetOutFile {
public:
	DzModifierOutFile( DzMorph *morph, const QString &contentDir = QString::null );
	DzModifierOutFile( DzProperty *prop, const QString &contentDir = QString::null );
	virtual ~DzModifierOutFile();

	DzMorph*	getMorph() const;
	DzProperty*	getProperty() const;
	void		setOverrideParentPath(const QString& parentPath);

protected:

	virtual bool	writeScene( IDzJsonIO *io );
	virtual QString getParentUri( DzMorph *morph ) const;

private:

	bool	writeModifierInstances( IDzJsonIO *io );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzUVSetOutFile : public DzAssetOutFile {
public:
	DzUVSetOutFile( DzUVSet *uvSet, DzNode *owner, const QString &contentDir = QString::null );
	virtual ~DzUVSetOutFile();

	DzUVSet*	getUVSet() const;

protected:

	virtual bool	writeScene( IDzJsonIO *io );

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPropertiesOutFile : public DzAssetOutFile {
public:
	DzPropertiesOutFile( DzNode *root, const DzPropertyList &poseShapeProps, const DzPropertyList &matProps, const DzMaterialList &mats, bool writeInstances, const QString &contentDir = QString::null );
	virtual ~DzPropertiesOutFile();

	void setCurrentFrameOnly( bool onOff );
	void setStartFrame( DzTime time );
	void setEndFrame( DzTime time );

protected:

	virtual bool	writeScene( IDzJsonIO *io );
	bool			writeAnimations( DzProperty *prop, IDzJsonIO *io );
	bool			writeMatAnimations( DzProperty *prop, IDzJsonIO *io );
	virtual bool	writeMaterialInstances( IDzJsonIO *io );
	bool			writeUVSetAnimation( DzMaterial* mat, IDzJsonIO * io, const QString& propRef );
	virtual bool	writeProperty( const QString& tagName, DzProperty *prop, DzAssetOutProperty &outProp, IDzJsonIO *io, bool isInstance );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPoseOutFile : public DzAssetOutFile {
public:
	DzPoseOutFile( DzNode *root, const DzPropertyList &props, const QString &contentDir = QString::null );
	virtual ~DzPoseOutFile();

	void setCurrentFrameOnly( bool onOff );
	void setStartFrame( DzTime time );
	void setEndFrame( DzTime time );

protected:

	virtual bool	writeScene( IDzJsonIO *io );
	bool			writeAnimations( DzProperty *prop, IDzJsonIO *io );

private:
	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzShapingOutFile : public DzAssetOutFile {
public:
	DzShapingOutFile( DzNode *root, const DzPropertyList &props, const QString &contentDir = QString::null );
	virtual ~DzShapingOutFile();

	void setCurrentFrameOnly( bool onOff );
	void setStartFrame( DzTime time );
	void setEndFrame( DzTime time );

protected:

	virtual bool	writeScene( IDzJsonIO *io );
	bool			writeAnimations( DzProperty *prop, IDzJsonIO *io );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzCharacterOutFile : public DzSceneOutFile {
public:
	DzCharacterOutFile( const QString &path, const DzNodeList &nodes, bool writeParentRefs = false );
	virtual ~DzCharacterOutFile();

	void setWriteMorphs( bool onOff );
	void setWriteMaterials( bool onOff );

protected:

	virtual bool	writeModifierInstances( DzNode *node, IDzJsonIO *io, bool &foundModifier );

	
	virtual bool	writeMaterialInstances( DzNode *node, IDzJsonIO *io, bool sceneInstances, bool &foundMaterial );
	virtual bool	writeAnimations( DzNode *node, IDzJsonIO *io, bool &foundAnimation );
	DzAssetFile*	getFile( const DzUri &uri );
	QString			resolve( const DzUri &uri );

private:
	DzModifierDefinition const*	findModifierDefinition( DzAssetFile *file, const DzUri &uri );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzHierarchicalMaterialOutFile : public DzSceneOutFile {
public:
	DzHierarchicalMaterialOutFile( const QString &path, const DzNodeList &nodes );
	virtual ~DzHierarchicalMaterialOutFile();

	
	virtual void	assignAssets();
protected:

	virtual bool	writeModifierInstances( DzNode *node, IDzJsonIO *io, bool &foundModifier );

	
	virtual bool	writeAnimations( DzNode *node, IDzJsonIO *io, bool &foundAnimation );
	virtual bool	writeAnimations( DzProperty *prop, IDzJsonIO *io, bool &foundAnimation );
	virtual bool	writeAnimations( DzObject* obj, IDzJsonIO *io, bool &foundAnimation );
	virtual bool	writeNodeInstance( DzNode *node, IDzJsonIO *io );
	virtual bool	writeShapeInstance( DzShape *shape, bool isEmbedded, IDzJsonIO *io );	
	virtual bool	writeUVInstances( DzNode *node, DzShape* shape, IDzJsonIO * io, bool &foundModifier );
	virtual bool	currentValueInAnimation() const;
	virtual bool	writeUVSetAnimation( DzMaterial* mat, IDzJsonIO * io, const QString& propRef );
	virtual bool	shouldEmbed( IDzSceneAsset *asset ) const;
	virtual bool	writeProperty( const QString& tagName, DzProperty *prop, DzAssetOutProperty &outProp, IDzJsonIO *io, bool isInstance );
private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzWearableOutFile : public DzSceneOutFile {
public:
	DzWearableOutFile( DzSkeleton* baseSkel, bool writeBasePose, bool reparentBase, const QString &path, const DzNodeList &nodes, bool writeParentRefs = false );
	virtual ~DzWearableOutFile();

protected:
	virtual bool	writeNodeInstance( DzNode *node, IDzJsonIO *io );
	virtual void	writeNodeInstanceParent( DzNode * node, IDzJsonIO * io );
	virtual void	wirteNodeInstanceFollow( DzSkeleton * figure, IDzJsonIO * io );
	virtual bool	writeAnimations( DzNode *node, IDzJsonIO *io, bool &foundAnimation );
	bool			writeAnimations( DzProperty *prop, IDzJsonIO *io );
private:
	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzMaterialOutFile : public DzAssetOutFile {
public:
	DzMaterialOutFile( DzShape *shape, const DzMaterialPtr &mat, const DzPropertyList &propList, bool writeInstances, const QString &contentDir = QString::null );
	DzMaterialOutFile( DzShape *shape, const DzMaterialList &mats, const DzPropertyList &propList, bool writeInstances, const QString &contentDir /*= QString::null */ );
	virtual ~DzMaterialOutFile();

	void	setWriteInstances( bool onOff );
	void	setWriteAnimation( bool onOff );
		
protected:

	virtual bool	writeScene( IDzJsonIO *io );
	virtual bool	writeMaterialInstances( IDzJsonIO *io );	
	bool			writeAnimations( IDzJsonIO *io );
	bool			writeAnimations( DzProperty *prop, IDzJsonIO *io, bool &foundAnimation );

	bool			writeUVSetAnimation( DzMaterial* mat, IDzJsonIO * io, const QString& propRef );
	virtual bool	writeProperty( const QString& tagName, DzProperty *prop, DzAssetOutProperty &outProp, IDzJsonIO *io, bool isInstance );

	virtual DzPropertyList* getMaterialIncludeProperties() const;
	virtual	bool	currentValueInAnimation()const;
	
private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzElementDataOutFile : public DzAssetOutFile {
public:
	DzElementDataOutFile( const QString &path, const QString &type, DzElementData *data );
	DzElementDataOutFile( const QString &path, const QString &type, const DzElementDataList &dataItems );
	virtual ~DzElementDataOutFile();

protected:
	virtual bool	writeScene( IDzJsonIO *io );

private:
	bool	writeDataItem( DzElementData *dataItem, IDzJsonIO *io );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzRenderSettingsOutFile : public DzAssetOutFile {
public:
	DzRenderSettingsOutFile( const QString &path );
	virtual ~DzRenderSettingsOutFile();

protected:
	virtual bool	writeScene( IDzJsonIO *io );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzDFormOutFile : public DzSceneOutFile {
public:
	DzDFormOutFile( const QString &path, const DzNodeList &exportNodes, const DzNodeList &dformList, const DzNodeList & targetList, const DzNodeList & figureList );
	~DzDFormOutFile();
	
protected:
	virtual bool	writeScene( IDzJsonIO *io );
	
	bool	writeDFormNodeInstances( IDzJsonIO *io );
	bool	writeDFormNodeInstance( DzNode *node, IDzJsonIO *io );
	bool	writeDFormModifierInstances( IDzJsonIO *io );
	bool	writeDFormModifierInstance( DzDFormModifier *mod, IDzJsonIO *io );
	bool	writeDFormAnimations( IDzJsonIO *io );
	bool	writeDFormModifierAnimation( DzDFormModifier *mod, IDzJsonIO *io, bool &foundAnimation );
	
private:

	void	assignDFormModifierAssets();
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_ASSET_OUT_FILE_H
