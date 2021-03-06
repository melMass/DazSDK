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
	Defines the DzSpotLight class.
**/

#ifndef DAZ_SPOT_LIGHT_H
#define DAZ_SPOT_LIGHT_H

/*****************************
	Include files
*****************************/

#include "dzdistantlight.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSpotLight : public DzDistantLight {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzSpotLight();
	virtual ~DzSpotLight();
	
	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	setGL( int width, int height, const QRect &view, int pass = 0,
						int totalPasses = 1, bool depthOfField = false );
	virtual void	setFocalDistance( float dist );
	virtual void	aimAt( const DzVec3 &pos );
	virtual void	frame( const DzBox3 &box, float aspect );
	virtual void	save( DzOutFile *file ) const;
	virtual QPixmap	getPixmap(QStyle::State state = QStyle::State_None) const;
	virtual QIcon	getIcon() const;
	virtual void	draw( const DzDrawStyle &style ) const;
	virtual void	create( const DzRenderSettings &settings, const QString &shadowMap ) const;
	virtual void	setShadowTransform( const DzRenderSettings &settings, const DzCamera *camera ) const;
	virtual bool	isDirectional() const { return false; }
	virtual double	getFocalDistance() const;
	
public slots:

	//
	// ACCESSORS
	//

	bool				getLightVisibility() const;
	DzFloatProperty*	getSpreadAngleControl() const;
	float				getRayOpacity() const;
	float				getLineOpacity() const;
	float				getBaseOpacity() const;
	float				getEdgeOpacity() const;

private slots:

	void	onVisibilityChanged();

protected:

	virtual void	setGLLighting( const DzDrawStyle &style, int pass = 0, int totalPasses = 1 );
	virtual void	unsetGLLighting( const DzDrawStyle &style );
	void			drawPointerRepresentation() const;
	void			makeConnections();
	virtual DzBox3	calcLocalBoundingBox() const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SPOT_LIGHT_H
