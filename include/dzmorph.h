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
	Defines the DzMorph class.
**/

#ifndef DAZ_MORPH_H
#define DAZ_MORPH_H

/*****************************
	Include files
*****************************/

#include "dzmodifier.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzFloatProperty;
class DzMorphDeltas;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMorph : public DzModifier, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	friend class DzMorphFactory;
public:

	//
	// CREATORS/DESTRUCTORS
	//

	DzMorph();
	DzMorph( DzMorphDeltas *deltas );
	virtual ~DzMorph();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setStorablePaths( const QString &path );
	virtual void			setName( const QString &name );
	virtual DzError			apply( DzVertexMesh &geom, DzNode &node );
	virtual DzError			applyInverse( DzVertexMesh &geom, DzNode &node );
	virtual void			save( DzOutFile *file ) const;
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;
		
	virtual void			swapValueChannels(DzMorph* otherMorph);

	virtual DzError	apply( DzVertexMesh &geom, DzMorphDeltas &deltas, float value );

public slots:

	//
	// MANIPULATORS
	//

	void	setDeltas( DzMorphDeltas *deltas );

	//
	// ACCESSORS
	//

	DzMorphDeltas*		getDeltas() const;
	DzFloatProperty*	getValueChannel() const;
	virtual bool		modifyAsset();
	virtual bool		modifyAsset( const DzUri &newUri );

signals:
	void	deltasChanged();
	void	assetModified();
	void	assetWasSaved();

protected:
	DzMorph( const DzInFile *file );	

private:
	void	createProperties();

	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzLegacyPostJointMorph : public DzMorph {
	Q_OBJECT
	friend class DzLegacyPostJointMorphFactory;
public:

	//
	// CREATORS/DESTRUCTORS
	//

	DzLegacyPostJointMorph();
	DzLegacyPostJointMorph( DzMorphDeltas *deltas );
	virtual ~DzLegacyPostJointMorph();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;

	void					setBone(DzBone* bone);
	DzBone*					getBone()const;

protected:
	DzLegacyPostJointMorph( const DzInFile *file );
	
	virtual DzError	apply( DzVertexMesh &geom, DzMorphDeltas &deltas, float value );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MORPH_H
