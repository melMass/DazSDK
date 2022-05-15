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
	Defines the DzControllerHelper class.
**/

#ifndef DAZ_CONTROLLER_INFO_H
#define DAZ_CONTROLLER_INFO_H

/*****************************
	Include files
*****************************/
#include "dztypes.h"

/*****************************
	Forward Declarations
*****************************/

class DzERCLink;
class DzFormulaController;

/*****************************
	Class Definition
*****************************/
class DZ_EXPORT DzControllerHelper : public QObject
{
	Q_OBJECT
	Q_ENUMS( ControllerType )
public:
	enum ControllerDirection
	{
		CD_TopDown = 0,
		CD_BottomUp
	};

	DzControllerHelper( bool initData = true );
	virtual ~DzControllerHelper();

	static DzERCLink*			getERCLink( DzProperty *master, DzProperty *slave );
	static DzFormulaController*	getFormulaController( DzProperty *master, DzProperty *slave );

public slots:
	void						setData( bool initData = true );
	void						setData( DzSkeleton* skel, bool initData = true );
	void						setData( DzNodeList &nodes, bool initData = true );
	void						setData( DzPropertyList &props, bool initData = true );
	void						refreshData();

	void						getLinks( DzProperty *prop, DzPropertyList &linkProps, ControllerDirection dir );
	bool						hasLink( DzProperty *prop, DzProperty *linkProp, ControllerDirection dir );

private:
	void						clearData();
	void						clearDataSet();
	void						generateKeys( DzPropertyList &propList );
	void						generateSceneKeys( DzPropertyList &propList );
	void						generateNodeKeys( DzPropertyList &propList );
	void						generatePropertyKeys( DzPropertyList &propList );
	void						generateLinkInfo( DzPropertyList &propList );
	void						addLinkInfo( DzPropertyList &keyList, DzProperty *key, DzNumericPropertyList &ctrlProps );
	
	//Internal Data Structure
	struct Data;
	Data	*m_data;
};

#endif //DAZ_CONTROLLER_INFO_H