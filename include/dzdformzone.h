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
	Defines the DzDFormZone class.
**/

#ifndef DAZ_DFORM_ZONE_H
#define DAZ_DFORM_ZONE_H

/*****************************
	Include files
*****************************/

#include "dznode.h"

/*****************************
	Forward declarations
*****************************/

class DzDForm;
class DzNaturalSpline;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDFormZone : public DzNode {
	Q_OBJECT
	friend class DzDForm;
	friend class DzDFormZoneFactory;
public:

	DzDFormZone();
	virtual ~DzDFormZone();
	
	enum	DrawStyle { AxisOnly, Wireframe, Solid };

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			save( DzOutFile *file ) const;
	virtual void			drawGeometry( const DzDrawStyle &style ) const;
	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;

public slots:

	DzDForm*			getDForm() const;
	DzNaturalSpline*	getSpline() const;
	DzFloatProperty*	getOpacityControl() const;

	virtual bool		shouldSortOnLoad() const;

protected:
	DzDFormZone( const DzInFile *file );

	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;

private slots:

	void	removeDForm();

private:
	void	init( bool doCreateProperties );
	void	createProperties();
	void	setDForm( DzDForm *dform );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DFORM_ZONE_H
