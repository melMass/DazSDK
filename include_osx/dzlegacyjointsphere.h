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

#ifndef DZ_LEGACY_JOINT_SPHERE_H
#define DZ_LEGACY_JOINT_SPHERE_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"

/****************************
	Forward declarations
****************************/

class DzFloatProperty;
class DzMatrix4;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzLegacyJointSphere : public DzElement {
	Q_OBJECT
	friend class DzLegacyJointSphereFactory;
public:
	DzLegacyJointSphere();
	virtual ~DzLegacyJointSphere();
	
	virtual void	startLoad( const DzInFile *file );
	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;

	DzLegacyJointSphere* createCopy()const; 

public slots:
	virtual void	setPath( const QString &name );
	
	DzFloatProperty*	getXTransControl();
	DzFloatProperty*	getYTransControl();
	DzFloatProperty*	getZTransControl();

	DzFloatProperty*	getXRotControl();
	DzFloatProperty*	getYRotControl();
	DzFloatProperty*	getZRotControl();

	DzFloatProperty*	getScaleControl();
	DzFloatProperty*	getYScaleControl();
	DzFloatProperty*	getZScaleControl();
	DzFloatProperty*	getXScaleControl();
	
	DzMatrix4*		getMatrix();
	DzMatrix4*		getMatrixInverse();
	void			setByMatrix( const DzMatrix4 &mat, bool makeDefault = false );
	virtual void	getRiggingProperties( DzPropertyList &list );

signals:
	void	matrixChanged();
	void	changedProperty( QObject *prop );

protected:
	DzLegacyJointSphere( const DzInFile *file );

private slots:
	void	invalidateMatrix();

private:
	void	createProperties();
	
	struct	Data;
	Data	*m_data;
};

#endif //DZ_LEGACY_JOINT_SPHERE_H
