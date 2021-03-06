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
	Defines the DzDForm class.
**/

#ifndef DAZ_DFORM_H
#define DAZ_DFORM_H

/*****************************
	Include files
*****************************/

#include "dznode.h"

/*****************************
	Forward declarations
*****************************/

class DzDFormBase;
class DzDFormModifier;
class DzDFormZone;
class DzFacetMesh;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDForm : public DzNode {
	Q_OBJECT
	friend class DzDFormModifier;
	friend class DzDFormFactory;
public:
	//
	// CREATORS
	//

	DzDForm();
	virtual ~DzDForm();

	//
	// REIMPLEMENTATINOS
	//

	virtual	QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;
	virtual	void			drawGeometry( const DzDrawStyle &style ) const;
	
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			save( DzOutFile *file ) const;
	
	void	setLegacyAliasPropertyForBone( DzDFormModifier *mod, DzBone *bone );

public slots:

	void	setBase( DzDFormBase *base );
	void	setZone( DzDFormZone *zone );
	void	setGradientMax( QColor color );
	void	setGradientMin( QColor color );
	void	setOpacity( float val );
	void	setAvatarScale( float val );
	void	applyToNode( DzNode *node );

	DzDFormBase*		getBase() const;
	DzDFormZone*		getZone() const;
	int					getNumModifiers() const;
	DzDFormModifier*	getModifier( int i ) const;
	DzDFormModifier*	getModifierForNode( DzNode *node ) const;
	QColor				getGradientMax() const;
	QColor				getGradientMin() const;
	double				getOpacity() const;
	double				getAvatarScale() const;

	DzFloatProperty*	getOpacityControl() const;
	DzFloatProperty*	getAvatarScaleControl() const;

	virtual bool		shouldSortOnLoad() const;

protected:

	DzDForm( const DzInFile *file );

	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;

private slots:

	void	removeDForm();

private:
	void			init( bool doCreateProperties );
	void			createProperties();
	void			addModifier( DzDFormModifier *mod );
	void			removeModifier( DzDFormModifier *mod );
	void			addModifierToNode( DzNode *node );
	void			drawGeometry( DzFacetMesh *geom ) const;
	void			drawVertexWeights( DzDFormModifier *mod ) const;
	DzFacetMesh*	initMesh( const char *name );

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DFORM_H
