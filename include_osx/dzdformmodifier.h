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
	Defines the DzDFormModifier class.
**/

#ifndef DAZ_DFORM_MODIFIER_H
#define DAZ_DFORM_MODIFIER_H

/*****************************
	Include files
*****************************/

#include "dzmodifier.h"
#include "idzsceneasset.h"

/****************************
	Forward declarations
****************************/

class DzDForm;
class DzFloatProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDFormWeightDelta {
public:
	DzDFormWeightDelta();
	DzDFormWeightDelta( int vertIdx, unsigned short weight );
	DzDFormWeightDelta( const DzDFormWeightDelta &delta );

	DzDFormWeightDelta&	operator=( const DzDFormWeightDelta &delta );

	int				m_vertIdx;	/**< Vertex index for the delta */
	unsigned short	m_weight;	/**< Delta weight */
};

class DZ_EXPORT DzDFormModifier : public DzModifier, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	friend class DzDForm;
	friend class DzDFormModifierFactory;
public:

	DzDFormModifier();
	virtual ~DzDFormModifier();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;
	
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;

	virtual DzError	apply( DzVertexMesh &geom, DzNode &node );
	virtual DzError	applyInverse( DzVertexMesh &geom, DzNode &node );

public slots:

	void				setDForm( DzDForm *dform );
	void				setMaskBone( DzBone * bone );

	DzBone*				getMaskBone()const;

	DzDForm*			getDForm() const;
	DzFloatProperty*	getValueChannel() const;
	DzMorph*			spawnMorph( DzNode *node, QString name ) const;
	DzDFormModifier*	createAltGeomDFormer(bool atFront=true);
	void				clearAltDFormer();

	void				setApplyAsLegacy(bool onOff);
	bool				isAppliedAsLegacy()const;

	virtual bool		modifyAsset();
	virtual bool		modifyAsset( const DzUri &newUri );

signals:

	void	dformChanged( DzDForm *newDForm );
	void	assetModified();
	void	assetWasSaved();

protected:
	DzDFormModifier( const DzInFile *file );

private slots:

	void	clearDForm();
	void	dFormDestroyed();
	void	connectNodeSignals();
	void	disconnectNodeSignals();
	void	nodeRemovalCleanup();

private:
	
	void			init( bool doCreateProperties );
	void			createProperties();
	int				getNumWeights();
	const DzDFormWeightDelta*	getWeights() const;
	DzMorph	*		findMorph( DzNode *node, QString name ) const;
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DFORM_MODIFIER_H
