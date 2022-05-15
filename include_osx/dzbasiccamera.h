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
	Defines the DzBasicCamera class.
**/

#ifndef DAZ_BASIC_CAMERA_H
#define DAZ_BASIC_CAMERA_H

/*****************************
	Include files
*****************************/

#include "dzcamera.h"

/****************************
	Forward declarations
****************************/

class DzBoolProperty;
class DzColorProperty;
class DzFloatProperty;

struct DblRect;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBasicCamera : public DzCamera {
	Q_OBJECT
	Q_PROPERTY( bool isPerspective READ isPerspective WRITE setPerspective )
	Q_PROPERTY( double currentViewWidth READ getCurrentViewWidth )
	Q_PROPERTY( double currentViewHeight READ getCurrentViewHeight )
	Q_PROPERTY( double fStop READ getFStop WRITE setFStop )
	Q_PROPERTY( bool depthOfField READ getDepthOfField WRITE setDepthOfField )
	friend class DzBasicCameraFactory;
public:
	//
	// CREATORS
	//

	DzBasicCamera( DzCamera::CameraType type = DzCamera::PERSPECTIVE_CAMERA, bool isViewCamera = false );
	virtual ~DzBasicCamera();

	//
	// MANIPULATORS
	//

	//////////////////////////////
	// from DzBase

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	postLoadFile( const DzInFile *file );

	//////////////////////////////
	// from DzCamera

	virtual void	setGL( int width, int height, const QRect &view, int pass = 0, int totalPasses = 1, bool depthOfField = false );
	virtual void	setFocalDistance( double dist );
	virtual void	setFocalLength( double dist );
	virtual void	setFStop( double stop );
	virtual void	setDepthOfField( bool useDOF );

	void			setPerspective( bool onOff );

	virtual void	reset();
	virtual void	aimAt( const DzVec3 &pos );
	virtual void	frame( const DzBox3 &box, float aspect );

public slots:

	void			setType( DzCamera::CameraType type );

public:

	//
	// ACCESSORS
	//

	////////////////////////////
	// from DzBase

	virtual void	save( DzOutFile *file ) const;

	////////////////////////////
	// from DzNode

	virtual void	draw( const DzDrawStyle &style ) const;

	////////////////////////////
	// from DzCamera

	virtual void	setProjection( const DzRenderSettings &settings, float width, float height ) const;

	virtual double	getFocalDistance() const;
	virtual double	getFocalLength() const;
	virtual double	getNearClippingPlane() const;
	virtual double	getFarClippingPlane() const;

	bool			isPerspective() const;
	virtual double	getCurrentViewWidth() const;
	virtual double	getCurrentViewHeight() const;
	virtual double	getFStop() const;
	virtual bool	getDepthOfField() const;
	virtual float	getOrthoZoom() const;
	virtual void	getViewportMatrix( int *pVec ) const;

public slots:

	DzFloatProperty*	getFocalDistChannel() const;
	DzFloatProperty*	getFocalLengthChannel() const;
	DzFloatProperty*	getFStopChannel() const;
	DzBoolProperty*		getDepthOfFieldChannel() const;
	DzBoolProperty*		getDisplayPersistenceChannel() const;
	DzFloatProperty*	getSightLineOpacityChannel() const;
	DzColorProperty*	getFovColorChannel() const;
	DzFloatProperty*	getFovLengthChannel() const;
	DzFloatProperty*	getFovOpacityChannel() const;
	DzFloatProperty*	getFocalPointScaleChannel() const;
	DzBoolProperty*		getDofVisibilityChannel() const;
	DzColorProperty*	getDofColorChannel() const;
	DzColorProperty*	getDofOverlayColorChannel() const;
	DzFloatProperty*	getDofOverlayOpacityChannel() const;
	DzBoolProperty*		getNearDofVisibilityChannel() const;
	DzBoolProperty*		getFarDofVisibilityChannel() const;
	virtual DzVec3		cursorToScene( int x, int y, float z ) const;
	virtual DzVec3		cursorToRay( int x, int y ) const;


	bool				isAtDefaultSceneCameraValues() const;
	bool				isDefaultSceneCamera() const;
	void				setIsDefaultSceneCamera(bool yesNo );

signals:

	void	fStopChanged( const DzTimeRange &range );
	void	depthOfFieldChanged();

protected:
	DzBasicCamera( const DzInFile *file );

private slots:

	void	updateProjection();

private:
	void	createProperties();

	void	drawPlane( DblRect &plane, double z, bool diagonal ) const;
	double	calculateDOF( double focalDistance, double focalLength, double fStop, bool nearPlane ) const;

	void	aimPerspective( const DzVec3 &pos );
	void	aimOrtho( const DzVec3 &pos );
	float	calculateFarPlane() const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BASIC_CAMERA_H
