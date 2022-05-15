/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This is UNPUBLISHED PROPRIETARY SOURCE CODE of DAZ 3D, Inc;
	the contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of DAZ 3D, Inc.
**********************************************************************/

#ifndef DAZ_PROPERTY_HELPER_H
#define DAZ_PROPERTY_HELPER_H

/*****************************
	Include files
*****************************/

#include "dztypes.h"

/*****************************
	Forward declarations
*****************************/

class DzERCLink;

/*****************************
	Class Definition
*****************************/
class DZ_EXPORT DzPropertyHelper
{
public:
	//Getters
	static DzProperty*	isMorphProperty( DzProperty *prop );
	static DzProperty*	isNodeProperty( DzProperty *prop );
	static DzProperty*	isModifierProperty( DzProperty *prop );
	static DzProperty*	isTransformProperty( DzProperty *prop );
	static DzProperty*	isDFormModProperty( DzProperty *prop );
	static DzProperty*	isLegacyJointProperty( DzProperty *prop );
	static bool			isLegacyProperty( DzProperty *prop );
	static bool			isAtDefaultValue( DzProperty *prop );
	static QString		getLabel( DzProperty *prop );
	static QString		getInternalName( DzProperty *prop );
	static QString		getNodeName( DzProperty *prop );
	static QString		getNodeType( DzProperty *prop );
	static DzNode*		getNode( DzProperty *prop );
	static DzERCLink*	getErcController( DzProperty *controlledProp, DzProperty *controllingProp );
	static bool			getMin( DzProperty *prop, float &min );
	static bool			getMax( DzProperty *prop, float &max );
	static void			getPropertiesOnElement( DzElement *elem, DzPropertyList &propList );
	static void			getPropertiesOnNode( DzProperty *prop, DzPropertyList &propList, bool includeModifiers = true );
	static void			getPropertiesOnNode( const DzNode* node, DzPropertyList &propList, bool includeModifiers = true );
	static void			getPrivatePropertiesOnNode( DzProperty *prop, DzPropertyList &propList );
	static void			getPrivatePropertiesOnNode( const DzNode* node, DzPropertyList &propList );
	static void			getRegionPropertiesOnNode( DzNode * curNode, DzPropertyList& propList );
	static void			getRegionPropertiesRecurse( DzGeometryRegion* region, DzPropertyList& propList );
	static DzProperty*	findPropertyOnNode( QString& propName,DzNode* node );
	static DzProperty*	findPropertyOnNodeByLabel( QString& label,DzNode* node );
	static DzProperty*	findPropertyOnNodeByInternalName( QString& internalName,DzNode* node );

	//Setters
	static void	setMin( DzProperty *prop, float min );
	static void	setMax( DzProperty *prop, float max );
	static void	setMinMax( DzProperty *prop, float min, float max );
	static bool	setInternalName( DzProperty *prop, QString &name );
	static void	setPropertyPath( DzProperty* prop, const QString& inPath );
};

#endif //DAZ_PROPERTY_HELPER_H
