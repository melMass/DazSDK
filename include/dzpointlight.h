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
	Defines the DzPointLight class.
**/

#ifndef DAZ_POINT_LIGHT_H
#define DAZ_POINT_LIGHT_H

/*****************************
	Include files
*****************************/

#include "dzdistantlight.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPointLight : public DzDistantLight {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzPointLight();
	virtual ~DzPointLight();
	
	//
	// Enumerations
	//

	enum drawType	{ DRAW_RINGS, DRAW_RAYS, DRAW_BOTH };

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file,short sectionID );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	save( DzOutFile *file ) const;
	virtual void	setGLShadow( int pass, int totalPasses, int *shadowMapSize = NULL ) { }
	virtual void	unsetGLShadow() { }
	virtual QPixmap	getPixmap (QStyle::State state = QStyle::State_None ) const;
	virtual QIcon	getIcon() const;
	virtual void	draw( const DzDrawStyle &style ) const;
	virtual void	create( const DzRenderSettings &settings, const QString &shadowMap ) const;
	virtual bool	isDirectional() const { return false; }
	virtual bool	canViewThrough() const { return false; }
	

public slots:

	DzBoolProperty*	getDisplayPersistanceControl() const;

protected:

	virtual void	setGLLighting( const DzDrawStyle &style, int pass = 0, int totalPasses = 1 );
	virtual void	unsetGLLighting( const DzDrawStyle &style );

	void	drawPointerRepresentation() const;
	void	drawHorizRings( double y, double sliceRadius, bool bOuter, bool bNegLight, float opacity ) const;
	void	drawVertRings( double radius, bool bOuter, bool bNegLight, float opacity ) const;
	bool	shouldDrawPointer() const;
	float	getDisplaySphereOpacity() const;
	virtual DzBox3	calcLocalBoundingBox() const;
		
private slots:

	void	onStdFallOffChanged();
	void	makeConnections();
	void	onVisibilityChanged();

private:

	double	getFalloffDistance( double lightPercent );
	bool	getLightVisibility();
	void	drawLightGeometry() const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_POINT_LIGHT_H
