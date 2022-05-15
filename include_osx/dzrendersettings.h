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
	Defines the DzRenderSettings class.
**/

#ifndef DAZ_RENDER_SETTINGS_H
#define DAZ_RENDER_SETTINGS_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"
#include "dzmatrix3.h"

/****************************
	Forward declarations
****************************/

class QColor;
class DzRenderer;
class DzRenderOptions;
class DzMaterial;
class DzVertexMesh;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRenderMotionBlurSample {
public:

	//
	// CREATORS
	//

	DzRenderMotionBlurSample();
	DzRenderMotionBlurSample(const DzRenderMotionBlurSample& other);
	DzRenderMotionBlurSample(quint64 baseMeshID, DzVertexMesh* mesh, DzTime time, const DzMatrix3& wsMat);
	
	~DzRenderMotionBlurSample();

	DzRenderMotionBlurSample&	operator=( const DzRenderMotionBlurSample& other );

	DzVertexMesh* getMesh()const;
	void		  setMesh(DzVertexMesh* mesh);

	DzTime		  getTime()const;
	void		  setTime(DzTime time);

	quint64		  getBaseMeshID()const;
	void		  setBaseMeshID(quint64 meshID);

	DzMatrix3	  getWSTransform()const;
	void		  setWSTransform(const DzMatrix3& wsTrans);

	
private:

	struct	Data;
	Data	*m_data;
};

typedef QList<DzRenderMotionBlurSample> DzRenderMotionBlurSampleList;
typedef QListIterator<DzRenderMotionBlurSample> DzRenderMotionBlurSampleIterator;

class DZ_EXPORT DzRenderSettings {
public:

	//
	// CREATORS
	//

	DzRenderSettings( DzRenderer *r, const DzRenderOptions *options );
	~DzRenderSettings();

	void	setShadowPass( bool onOff );
	void	setBackgroundColor( QColor color );

	DzRenderer*				renderEngine() const;
	const DzRenderOptions*	renderOptions() const;
	bool					isShadowPass() const;
	QColor					backgroundColor() const;
	DzMaterial*				currentMaterial() const;
	void					setCurrentMaterial( DzMaterial *mat ) const;
	DzRenderMotionBlurSampleList currentMotionSamples() const;
	void					setCurrentMotionSamples( const DzRenderMotionBlurSampleList& samples ) const;
	void					clearCurrentMotionSamples() const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_RENDER_SETTINGS_H
