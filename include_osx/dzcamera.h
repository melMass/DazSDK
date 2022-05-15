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
	Defines the DzCamera class.
**/

#ifndef DAZ_CAMERA_H
#define DAZ_CAMERA_H

/*****************************
	Include files
*****************************/

#include "dznode.h"

/****************************
	Forward declarations
****************************/

class DzHeadLight;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzCamera : public DzNode {
	Q_OBJECT
	Q_ENUMS( CameraType )
	Q_PROPERTY( double focalDistance READ getFocalDistance WRITE setFocalDistance )
	Q_PROPERTY( double focalLength READ getFocalLength WRITE setFocalLength )
	Q_PROPERTY( int type READ getTypeAsInt )
	Q_PROPERTY( double nearClippingPlane READ getNearClippingPlane )
	Q_PROPERTY( double farClippingPlane READ getFarClippingPlane )
	Q_PROPERTY( double aspectRatio READ getAspectRatio WRITE setAspectRatio )
public:

	enum CameraType { FRONT_CAMERA, BACK_CAMERA, LEFT_CAMERA, RIGHT_CAMERA, TOP_CAMERA,
						BOTTOM_CAMERA, PERSPECTIVE_CAMERA, ORTHO_CAMERA, GENERAL_CAMERA };

	//
	// CREATORS
	//

	DzCamera( CameraType type, bool isViewCam = false );
	virtual ~DzCamera();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		postLoadFile( const DzInFile *file );
	virtual void		save( DzOutFile *file ) const;
	virtual DzError		setLabel( const QString &name );
	virtual QPixmap		getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon		getIcon() const;
	virtual void		draw( const DzDrawStyle &style ) const;
	
		
	virtual QString		getAssetId() const;

	//
	// MANIPULATORS
	//

	virtual void	setGL( int width, int height, const QRect &view, int pass = 0, int totalPasses = 1,
							bool depthOfField = false ) = 0;

	virtual void	setFocalDistance( double dist ) = 0;
	virtual void	setFocalLength( double dist ) = 0;
	virtual void	setAspectRatio( double aspect );

public slots:

	virtual void	reset() = 0;
	virtual void	aimAt( const DzVec3 &pos ) = 0;
	virtual void	frame( const DzBox3 &box, float aspect ) = 0;

	virtual bool		shouldSortOnLoad() const;

public:
	//
	// ACCESSORS
	//

	virtual void	setProjection( const DzRenderSettings &settings, float width, float height ) const = 0;
	virtual void	setRenderGlobals( const DzRenderSettings &settings );
	virtual double	getFocalDistance() const = 0;
	virtual double	getFocalLength() const = 0;
	virtual double	getAspectRatio() const;
	CameraType		getType() const { return m_type; }
	int				getTypeAsInt() const { return (int) m_type; } // for DAZ Script
	virtual double	getNearClippingPlane() const = 0;
	virtual double	getFarClippingPlane() const = 0;

public slots:

	DzLight*	getHeadlight() const;
	DzVec3		getFocalPoint() const;
	double		getFieldOfView() const;
	bool		isViewCamera() const;

signals:

	void	projectionChanged();
	void	focalDistanceChanged( const DzTimeRange &range );
	void	focalLengthChanged( const DzTimeRange &range );
	void	aspectRatioChanged();

protected:

	CameraType	m_type;
	bool		m_isViewCamera;
	DzHeadLight	*m_headLight;

	virtual DzBox3		calcLocalBoundingBox() const;

	static const float	s_jitter[16][2];

	DzCamera( const DzInFile *file );

	//
	// ACCESSORS
	//

	void			accFrustum( float left, float right, float bottom,
						float top, float nearplane, float farplane, float focus,
						bool antiAlias, bool depthOfField, int pass,
						const QRect &tile ) const;

	void			accPerspective( float fovy, float aspect,
						float nearplane, float farplane, float focus,
						bool antiAlias, bool depthOfField, int pass,
						const QRect &view, const QRect &tile ) const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_CAMERA_H
