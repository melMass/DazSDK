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
	Defines the DzInstanceNode, DzNodeShapeInstance, DzInstanceGroupItem, 
	DzInstanceGroupNode, and DzGroupNodeShapeInstance classes.
**/
#ifndef DZ_INSTANCE_NODE_H
#define DZ_INSTANCE_NODE_H

/*****************************
   Include files
*****************************/
#include "dzshape.h"
#include "dzaction.h"
#include "dzmatrix3.h"
#include "dznode.h"
#include "dzabstractshapeinstance.h"
/****************************
   Forward declarations
****************************/
class DzNodeProperty;
class DzEnumProperty;
class DzBoolProperty;
class DzInstanceGroupNode;
/*****************************
   Class definitions
*****************************/

class DZ_EXPORT DzInstanceNode : public DzNode
{
	Q_OBJECT
public:
	DzInstanceNode();
	virtual ~DzInstanceNode();

	//reimplementations
	virtual void	setObject( DzObject *object );
	virtual void	draw( const DzDrawStyle &style ) const;

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;

public slots:
	virtual DzNodeProperty* getTargetControl()const;
	virtual DzEnumProperty* getCopyModeControl()const;
	virtual DzBoolProperty* getPreviewControl()const;

	DzNode*					getTarget()const;

protected:
	virtual DzBox3			calcLocalBoundingBox() const;

signals:
	void				targetChanged();

protected slots:
	virtual void		updateTarget();

private:
	void				createProperties();

protected:
	virtual void		addInstancesToShape( DzNode* target, DzNode* node, DzShape* shape );
	void				clearInstances();

	struct Data;
	Data* m_data;
};

class DZ_EXPORT DzNodeShapeInstance : public DzAbstractShapeInstance {
	Q_OBJECT
public:
	DzNodeShapeInstance(DzInstanceNode* node, DzNode* target, DzNode* geomNode);
	virtual ~DzNodeShapeInstance();

	virtual void		addedToShape(DzShape* shape);
	bool				removeFromShape();

public slots:
	virtual DzNode*		getPickNode()const;
	virtual DzMatrix3	getWSTransform() const;
	virtual DzMatrix3	getWSTransform(DzTime tm) const;
	virtual bool		shouldRender( const DzRenderSettings &settings )const;
	virtual bool		shouldDraw( const DzDrawStyle &style )const;

protected:
	struct Data;
	Data* m_data;
};


class DZ_EXPORT DzInstanceGroupItem : public DzBase
{
	Q_OBJECT
	friend class DzInstanceGroupNode;
public:
	virtual				~DzInstanceGroupItem();

	void				getWSTransform( DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale ) const;
	void				getWSTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaults = false ) const;
	void				getLocalTransform( DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale ) const;

public slots:
	void				setScale( float x, float y, float z, float genScale);
	void				setRotation(float x, float y, float z);
	void				setPosition(float x, float y, float z);
	void				setOrigin(float x, float y, float z);
	void				setEndPoint(float x, float y, float z);
	void				setOrientation(float x, float y, float z);
	void				setRotationOrder( DzRotationOrder order);
	void				setInheritScale( bool onOff );

	DzVec3				getXYZScaleValues()const;
	float				getGeneralScaleValue()const;
	DzVec3				getRotationValues()const;
	DzVec3				getPositionValues()const;
	DzVec3				getOriginValues()const;
	DzVec3				getEndPointValues()const;
	DzVec3				getOrientationValues()const;
	DzRotationOrder		getRotationOrder()const;
	bool				inheritsScale();

	void				copyTransformFromNode(const DzNode* node);
	void				copyTransformToNode(DzNode* node)const;

	QString				getLabel()const;
	void				setLabel(const QString& label);

	DzMatrix3	getLocalScale() const;
	DzQuat		getLocalRot() const;
	DzMatrix3	getLocalTransform() const;
	DzVec3		getLocalPos() const;
	
	DzMatrix3	getWSTransform() const;
	DzMatrix3	getWSTransform( DzTime tm, bool defaultVal = false ) const;
	DzVec3		getWSPos() const;
	DzVec3		getWSPos( DzTime tm, bool defaultVal = false ) const;
	DzQuat		getWSRot() const;
	DzQuat		getWSRot( DzTime tm, bool defaultVal = false ) const;
	DzMatrix3	getWSScale() const;
	DzMatrix3	getWSScale( DzTime tm, bool defaultVal = false ) const;
	DzQuat		getOrientation() const;

protected slots:
	void	updateTransform();
	void	updateOrientation();

signals:
	void	transformChanged();
	void	localTransformChanged();

protected:
	DzInstanceGroupItem(DzInstanceGroupNode* node);
	
	virtual void	calcWSTransform( DzTime tm, DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale, bool defaultVals = false ) const;
	virtual void	calcLocalTransform( DzVec3 &pos, DzQuat &rot, DzMatrix3 &scale ) const;
	void			cacheTransform();
private:
	struct Data;
	Data* m_data;
};

class DZ_EXPORT DzInstanceGroupNode : public DzInstanceNode
{
	Q_OBJECT
	friend class DzInstanceGroupItem;
public:
	DzInstanceGroupNode();
	virtual ~DzInstanceGroupNode();

	//reimplementations
	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;

public slots:
	void					beginItemEdit();
	void					finishItemEdit();
	bool					isEditingItems()const;
	DzInstanceGroupItem*	createItem(int* index=0);
	int						getNumberOfGroupItems()const;
	DzInstanceGroupItem*	getGroupItem(int index)const;
	int						findIndexForItem(DzInstanceGroupItem* item)const;
	void					removeItem(int index);
	void					clearItems();
	
protected:
	virtual void			addInstancesToShape( DzNode* target, DzNode* node, DzShape* shape );protected:
	virtual DzBox3			calcLocalBoundingBox() const;

private:
	struct GData;
	GData* m_gdata;
};

class DZ_EXPORT DzGroupNodeShapeInstance : public DzNodeShapeInstance {
	Q_OBJECT
public:
	DzGroupNodeShapeInstance( DzInstanceGroupItem* item, DzInstanceGroupNode* node, DzNode* target, DzNode* geomNode);
	virtual ~DzGroupNodeShapeInstance();

public slots:
	virtual DzMatrix3 getWSTransform() const;
	virtual DzMatrix3 getWSTransform(DzTime tm) const;
	DzInstanceGroupItem* getItem()const;

private:
	struct GData;
	GData* m_gdata;
};

#endif // DZ_INSTANCE_NODE_H
