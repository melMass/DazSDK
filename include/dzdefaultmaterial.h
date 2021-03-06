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
	Defines the DzDefaultMaterial class.
**/

#ifndef DAZ_DEFAULT_MATERIAL_H
#define DAZ_DEFAULT_MATERIAL_H

/*****************************
	Include files
*****************************/

#include "dzmaterial.h"

/****************************
	Forward declarations
****************************/

class DzColorProperty;
class DzImageProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDefaultMaterial : public DzMaterial {
	Q_OBJECT
	friend class DzDefaultMaterialFactory;
public:
	//
	// CREATORS/DESTRUCTORS
	//

	DzDefaultMaterial();
	virtual ~DzDefaultMaterial();

	//
	// REIMPLEMENTATIONS
	//

	virtual void		postLoadFile( const DzInFile *file );
	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;
	virtual void		setDiffuseColor( const QColor &color );
	virtual void		setBaseOpacity( float val );
	virtual void		setColorMap( const DzTexture *img );
	virtual void		setOpacityMap( const DzTexture *img );
	virtual int			getNumGLMaps() const;
	virtual QColor		getDiffuseColor() const;
	virtual double		getBaseOpacity() const;
	virtual bool		isColorMappable() const { return true; }
	virtual bool		isOpacityMappable() const { return true; }
	virtual DzTexture*	getColorMap() const;
	virtual DzTexture*	getOpacityMap() const;
	virtual QString		getMaterialName() const { return "DAZ Studio Default"; }
	virtual bool		isOpaque() const;
	virtual void		getAllMaps( QList<DzTexturePtr> &maps ) const;
	virtual bool		allowsAutoBake() const { return false; /* We do not auto-bake default materials. */}

public slots:

	//
	// MANIPULATORS
	//

	void	setDiffuseStrength( float val );
	void	setDiffuseValueMap( const DzTexture *img );
	void	setAmbientStrength( float val );
	void	setAmbientValueMap( const DzTexture *img );
	void	setAmbientColor( const QColor &color );
	void	setAmbientColorMap( const DzTexture *img );
	void	setBumpMap( const DzTexture *img );
	void	setBumpStrength( float val );
	void	setBumpMin( float val );
	void	setBumpMax( float val );
	void	setDisplacementMap( const DzTexture *img );
	void	setDisplacementStrength( float val );
	void	setDisplacementMin( float val );
	void	setDisplacementMax( float val );
	void	setReflectionColor( const QColor &color );
	void	setReflectionMap( const DzTexture *img );
	void	setReflectionStrength( float val );
	void	setReflectionValueMap( const DzTexture *img );
	void	setRefractionColor( const QColor &color );
	void	setRefractionColorMap( const DzTexture *img ) const;
	void	setRefractionStrength( float val );
	void	setRefractionValueMap( const DzTexture *img );
	void	setIndexOfRefraction( float val );
	void	setSurfaceType( int val );
	void	setGlossinessStrength( float size );
	void	setGlossinessValueMap( const DzTexture *img );
	void	setMultThroughOpacity( bool onOff );
	void	setSpecularStrength( float size );
	void	setSpecularValueMap( const DzTexture *img );
	void	setSpecularColor( const QColor &color );
	void	setSpecularColorMap( const DzTexture *img );
	void	setNormalValueMap( const DzTexture *img );
	void	setHorizontalTiles( float tiles );
	void	setVerticalTiles( float tiles );
	void	setHorizontalOffset( float offset );
	void	setVerticalOffset( float offset );

	//
	// ACCESSORS
	//

	double		getDiffuseStrength() const;
	DzTexture*	getDiffuseValueMap() const;
	double		getAmbientStrength() const;
	DzTexture*	getAmbientValueMap() const;
	QColor		getAmbientColor() const;
	DzTexture*	getAmbientColorMap() const;
	double		getBumpStrength() const;
	DzTexture*	getBumpMap() const;
	double		getBumpMin() const;
	double		getBumpMax() const;
	double		getDisplacementStrength() const;
	double		getDisplacementMin() const;
	double		getDisplacementMax() const;
	DzTexture*	getDisplacementMap() const;
	QColor		getReflectionColor() const;
	DzTexture*	getReflectionMap() const;
	double		getReflectionStrength() const;
	DzTexture*	getReflectionValueMap() const;
	QColor		getRefractionColor() const;
	DzTexture*	getRefractionColorMap() const;
	double		getRefractionStrength() const;
	DzTexture*	getRefractionValueMap() const;
	double		getIndexOfRefraction() const;
	int			getSurfaceType() const;
	bool		isMultThroughOpacity() const;
	QColor		getSpecularColor() const;
	DzTexture*	getSpecularColorMap() const;
	double		getSpecularStrength() const;
	DzTexture*	getSpecularValueMap() const;
	double		getGlossinessStrength() const;
	DzTexture*	getGlossinessValueMap() const;
	DzTexture*	getNormalValueMap() const;
	double		getHorizontalOffset() const;
	double		getHorizontalTiles() const;
	double		getVerticalOffset() const;
	double		getVerticalTiles() const;

	virtual bool	needsTangentSpaceParams() const;
	virtual bool	shouldAlwaysEmbed() const;

	DzColorProperty*	getDiffuseColorControl() const;
	DzFloatProperty*	getDiffuseStrengthControl() const;
	DzColorProperty*	getAmbientColorControl() const;
	DzFloatProperty*	getAmbientStrengthControl() const;
	DzColorProperty*	getSpecularColorControl() const;
	DzFloatProperty*	getSpecularStrengthControl() const;
	DzFloatProperty*	getGlossinessControl() const;
	DzFloatProperty*	getOpacityControl() const;
	DzFloatProperty*	getBumpControl() const;
	DzFloatProperty*	getBumpMinControl() const;
	DzFloatProperty*	getBumpMaxControl() const;
	DzFloatProperty*	getDisplacementControl() const;
	DzFloatProperty*	getDisplacementMinControl() const;
	DzFloatProperty*	getDisplacementMaxControl() const;
	DzColorProperty*	getReflectionColorControl() const;
	DzFloatProperty*	getReflectionStrengthControl() const;
	DzColorProperty*	getRefractionColorControl() const;
	DzFloatProperty*	getRefractionStrengthControl() const;
	DzFloatProperty*	getIndexOfRefractionControl() const;
	DzEnumProperty*		getSurfaceTypeControl() const;
	DzBoolProperty*		getMultThroughOpacityControl() const;
	DzImageProperty*	getNormalValueMapControl() const;
	DzFloatProperty*	getHorizontalTilesControl() const;
	DzFloatProperty*	getHorizontalOffsetControl() const;
	DzFloatProperty*	getVerticalTilesControl() const;
	DzFloatProperty*	getVerticalOffsetControl() const;

protected:
	DzDefaultMaterial( const DzInFile *file );

	/////////////////////////
	// from DzMaterial

	virtual void	setGLMat( const DzDrawStyle &style ) const;
	virtual void	unsetGLMat( const DzDrawStyle &style ) const;
	virtual void	setShader( const DzRenderSettings &settings ) const;
	virtual void	setCoShader( const DzRenderSettings &settings, DzCoShaderInfo& info ) const;

	void setShaderAttributes( const DzRenderSettings &settings, float& bound ) const;
	bool setDisplacementShaderTokens() const;
	int	setRenderTokens( const DzRenderSettings &settings ) const;
	QString getSurfaceShaderName( const DzRenderSettings &settings ) const;

private:
	void	createProperties();

	void	do_0x040000fc_fix( const DzInFile *file );
	void	do_0x01060008_fix( const DzInFile *file );
	void	do_0x01000e00_fix( const DzInFile *file );
	void	do_0x00091800_fix( const DzInFile *file );
	void	do_0x00091308_fix( const DzInFile *file );
	void	do_0x00091204_fix( const DzInFile *file );
	void	do_0x00091200_fix( const DzInFile *file );

	void	setShaderInternal( const DzRenderSettings &settings, DzCoShaderInfo* info ) const;

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DEFAULT_MATERIAL_H
