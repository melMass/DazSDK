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
	Defines the DzPushModifier class.
**/
#ifndef DAZ_PUSH_MODIFIER_H
#define DAZ_PUSH_MODIFIER_H

/*****************************
	Include files
*****************************/
#include "dzmodifier.h"
#include "idzsceneasset.h"
#include "dzassetextraobjectio.h"

/*****************************
	Forward declarations
*****************************/
class DzFloatProperty;
class DzFacetMesh;

/*****************************
	Forward declarations
*****************************/


class DzPushModifier : public DzModifier, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
public:

	//
	// CREATORS/DESTRUCTORS
	//

	DzPushModifier();
	virtual ~DzPushModifier();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setName( const QString &name );
	virtual void			save( DzOutFile *file ) const;
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;

	
	virtual DzError			apply( DzVertexMesh &geom, DzNode &node );
	virtual DzError			applyInverse( DzVertexMesh &geom, DzNode &node );

	virtual DzError			apply( DzFacetMesh &geom, float val );

public slots:

	//
	// ACCESSORS
	//
	DzFloatProperty*	getValueChannel() const;
	virtual bool		modifyAsset();
	virtual bool		modifyAsset( const DzUri &newUri );

signals:
	void	assetModified();
	void	assetWasSaved();

protected:
	DzPushModifier( const DzInFile *file );	

private:
	void	createProperties();

	struct	Data;
	Data	*m_data;
};

class DzExtraPushModifierIO: public DzExtraModifierIO {
	Q_OBJECT
public:
	DzExtraPushModifierIO();
	virtual ~DzExtraPushModifierIO();
	virtual DzModifier*	createModifier(const QString& name, DzObject *tgtObject)const;

	virtual DzError writeExtraDefinition( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	virtual DzError writeExtraInstance( QObject *object, IDzJsonIO *io, const DzFileIOSettings *opts )const;
	
	virtual DzAssetJsonObject*	startDefinitionRead( DzAssetJsonItem *parentItem );
	virtual DzAssetJsonObject*	startInstanceRead( DzAssetJsonItem *parentItem );

	virtual DzError applyDefinitionToObject( QObject *object, const DzFileIOSettings *opts )const;
	virtual DzError applyInstanceToObject( QObject *object, const DzFileIOSettings *opts )const;

private:
	struct Data;
	Data* m_data;
};

#endif // DAZ_PUSH_MODIFIER_H