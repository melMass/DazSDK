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
	Defines list and iterator types.
**/

#ifndef DAZ_TYPES_H
#define DAZ_TYPES_H

/****************************
	Includes
****************************/

#include <QtCore/QList>
#include <QtCore/QPointer>

#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class DzBone;
class DzBoneBinding;
class DzBrickParam;
class DzCallBack;
class DzCamera;
class DzClassFactory;
class DzContentFile;
class DzController;
class DzElement;
class DzElementData;
class DzExpressionInput;
class DzFormula;
class DzImageBlend;
class DzLegacyJoint;
class DzLegacyJointParam;
class DzLight;
class DzMaterial;
class DzModifier;
class DzMorph;
class DzNode;
class DzNumericProperty;
class DzProperty;
class DzPropertyGroup;
class DzRigidityGroup;
class DzSceneData;
class DzShaderBrick;
class DzShape;
class DzSkeleton;
class DzTextureLayer;
class DzTimeRange;
class DzUVSet;
class DzVertexMap;
class DzViewTool;
class DzWSModifier;
class DzWeld;
class DzWidgetGroup;
class IDzSceneAsset;
class QWidget;

template <class DataType> class DzTSortedArray;
template <class DataType> class DzTArray;

/*****************************
	Type definitions
*****************************/

typedef QList<QWidget*>						DzWidgetList;
typedef QListIterator<QWidget*>				DzWidgetListIterator;
typedef QList<DzElement*>					DzElementList;
typedef QListIterator<DzElement*>			DzElementListIterator;
typedef QList<DzElementData*>				DzElementDataList;
typedef QListIterator<DzElementData*>		DzElementDataListIterator;
typedef QList<DzNode*>						DzNodeList;
typedef QListIterator<DzNode*>				DzNodeListIterator;
typedef QList<DzLight*>						DzLightList;
typedef QListIterator<DzLight*>				DzLightListIterator;
typedef QList<DzCamera*>					DzCameraList;
typedef QListIterator<DzCamera*>			DzCameraListIterator;
typedef QList<DzSkeleton*>					DzSkeletonList;
typedef QListIterator<DzSkeleton*>			DzSkeletonListIterator;
typedef QList<DzBone*>						DzBoneList;
typedef QListIterator<DzBone*>				DzBoneListIterator;
typedef QList< QPointer<DzBone> >			DzWeakBoneList;
typedef QListIterator< QPointer<DzBone> >	DzWeakBoneListIterator;
typedef QList<DzMaterial*>					DzMaterialList;
typedef QListIterator<DzMaterial*>			DzMaterialListIterator;
typedef QList<DzTimeRange>					DzTimeRangeList;
typedef QListIterator<DzTimeRange>			DzTimeRangeListIterator;
typedef QList<DzShape*>						DzShapeList;
typedef QListIterator<DzShape*>				DzShapeListIterator;
typedef QList<DzMorph*>						DzMorphList;
typedef QListIterator<DzMorph*>				DzMorphIterator;
typedef QList<DzModifier*>					DzModifierList;
typedef QListIterator<DzModifier*>			DzModifierIterator;
typedef QList<DzWSModifier*>				DzWSModifierList;
typedef QListIterator<DzWSModifier*>		DzWSModifierIterator;
typedef QList<DzProperty*>					DzPropertyList;
typedef QListIterator<DzProperty*>			DzPropertyListIterator;
typedef QList<DzNumericProperty*>			DzNumericPropertyList;
typedef QListIterator<DzNumericProperty*>	DzNumericPropertyListIterator;
typedef QList<DzPropertyGroup*>				DzPropertyGroupList;
typedef QListIterator<DzPropertyGroup*>		DzPropertyGroupListIterator;
typedef QList<DzFormula*>					DzFormulaList;
typedef QListIterator<DzFormula*>			DzFormulaListIterator;
typedef QList<DzContentFile*>				DzContentFileList;
typedef QListIterator<DzContentFile*>		DzContentFileListIterator;
typedef QList<DzLegacyJoint*>				DzLegacyJointList;
typedef QListIterator<DzLegacyJoint*>		DzLegacyJointListIterator;
typedef QList<DzLegacyJointParam*>			DzLegacyJointParamList;
typedef QListIterator<DzLegacyJointParam*>	DzLegacyJointParamListIterator;
typedef QList<DzWeld*>						DzWeldList;
typedef QListIterator<DzWeld*>				DzWeldListIterator;
typedef QList<DzImageBlend*>				DzImageBlendList;
typedef QListIterator<DzImageBlend*>		DzImageBlendListIterator;
typedef QList<DzWidgetGroup*>				DzWidgetGroupList;
typedef QListIterator<DzWidgetGroup*>		DzWidgetGroupListIterator;
typedef QList<DzVertexMap*>					DzVertexMapList;
typedef QListIterator<DzVertexMap*>			DzVertexMapListIterator;
typedef QList<DzUVSet*>						DzUVSetList;
typedef QListIterator<DzUVSet*>				DzUVSetListIterator;
typedef QList<DzCallBack*>					DzCallBackList;
typedef QListIterator<DzCallBack*>			DzCallBackIterator;
typedef QList<DzSceneData*>					DzSceneDataList;
typedef QListIterator<DzSceneData*>			DzSceneDataListIterator;
typedef QList<DzController*>				DzControllerList;
typedef QListIterator<DzController*>		DzControllerListIterator;
typedef QList<DzClassFactory*>				DzClassFactoryList;
typedef QListIterator<DzClassFactory*>		DzClassFactoryListIterator;
typedef QList<DzViewTool*>					DzViewToolList;
typedef QListIterator<DzViewTool*>			DzViewToolListIterator;
typedef QList<DzExpressionInput*>			DzExpressionInputList;
typedef QListIterator<DzExpressionInput*>	DzExpressionInputIterator;
typedef QList<DzBoneBinding*>				DzBoneBindingList;
typedef QListIterator<DzBoneBinding*>		DzBoneBindingListIterator;
typedef QList<IDzSceneAsset*>				DzSceneAssetList;
typedef QListIterator<IDzSceneAsset*>		DzSceneAssetListIterator;
typedef QList<DzRigidityGroup*>				DzRigidityGroupList;
typedef QListIterator<DzRigidityGroup*>		DzRigidityGroupListIterator;
typedef QList<DzTextureLayer*>				DzTextureLayerList;
typedef QListIterator<DzTextureLayer*>		DzTextureLayerListIterator;

typedef	DzTSortedArray<int>					DzSortedIntArray;
typedef	DzTArray<int>						DzIntArray;

typedef QList<DzShaderBrick*> DzShaderBrickList;
typedef QListIterator<DzShaderBrick*> DzShaderBrickIterator;
typedef QList<DzBrickParam*> DzBrickParamList;
typedef QListIterator<DzBrickParam*> DzBrickParamIterator;

class DzAbstractAssetContainer;
typedef DzTSharedPointer<DzAbstractAssetContainer> DzAbstractAssetContainerPtr;
typedef QList<DzAbstractAssetContainerPtr> DzAbstractAssetContainerList;
typedef QListIterator<DzAbstractAssetContainerPtr> DzAbstractAssetContainerIterator;

class DzAsset;
typedef DzTSharedPointer<DzAsset> DzAssetPtr;
typedef QList<DzAssetPtr> DzAssetList;
typedef QListIterator<DzAssetPtr> DzAssetIterator;

class DzGeometryRegion;
typedef	QList<DzGeometryRegion*> DzGeometryRegionList;
typedef QListIterator<DzGeometryRegion*> DzGeometryRegionIterator;

template <class DataType> class DzCMSSharedPointer;
class DzDBObjectBase;
typedef DzCMSSharedPointer<DzDBObjectBase> DzDBObjectBasePtr;
class DzDBProductTable;
typedef DzCMSSharedPointer<DzDBProductTable> DzDBProductTablePtr;
class DzDBCompatibilityBaseTable;
typedef DzCMSSharedPointer<DzDBCompatibilityBaseTable> DzDBCompatibilityBaseTablePtr;
class DzDBContentFoldersTable;
typedef DzCMSSharedPointer<DzDBContentFoldersTable> DzDBContentFoldersTablePtr;
class DzDBContentInstanceTable;
typedef DzCMSSharedPointer<DzDBContentInstanceTable> DzDBContentInstanceTablePtr;
class DzDBContentTable;
typedef DzCMSSharedPointer<DzDBContentTable> DzDBContentTablePtr;

typedef QList<DzDBProductTablePtr> DzDBProductTablePtrList;
typedef QList<DzDBObjectBasePtr> DzDBObjectBasePtrList;
typedef QListIterator<DzDBObjectBasePtr> DzDBObjectBasePtrIterator;

#endif // DAZ_TYPES_H