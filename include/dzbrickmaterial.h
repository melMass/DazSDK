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

#ifndef DZ_BRICK_MATERIAL_H
#define DZ_BRICK_MATERIAL_H

/*****************************
	Include files
*****************************/

#include "dzmaterial.h"
#include "dzdefaultbrickuser.h"

/****************************
	Forward declarations
****************************/

class DzDefaultMaterial;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBrickMaterial : public DzMaterial, 
										virtual public IDzBrickUser,
										protected DzDefaultBrickUser
{
	Q_OBJECT
	Q_INTERFACES( IDzBrickUser )
public:
	DzBrickMaterial();
	virtual ~DzBrickMaterial();

	virtual QString				getDisplayName() const;
	virtual DzElement*			toElement();
	virtual const DzElement*	toElement() const;
	virtual void				addChildToElement( DzElement *element );
	void						deepCopy( const DzElement *source );
	virtual void				copyFrom( const DzElement *source );
	virtual void				getAllMaps( QList<DzTexturePtr> &images ) const;

	//DzBase
	virtual void			startLoad( const DzInFile *file );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	
	virtual DzBrickMap		getBrickMap() const;
	virtual bool			allowBrick( DzShaderBrick *brick );
	
	QString					getOrginalNameForSet( const QString &name );
	virtual void			release();
	virtual IDzBrickUser*	makeNew() const;
	virtual bool			shadersMatch(const DzMaterial* otherMat)const;

public slots:
	virtual QString			getExtension() const;
	//dzelement overrides
	virtual DzElement*		setAttributes( const DzSettings *settings );
	virtual void			getAttributes( DzSettings *settings ) const;

	//IDzBrickUser inherits
	virtual QString			getBrickUserName() const;
	virtual void			setBrickUserName( const QString &name );
	virtual int				getNumBrickSets() const;
	virtual DzBrickSet*		getBrickSet( int i ) const;
	virtual unsigned int	addBrick( DzShaderBrick *brick );
	virtual DzShaderBrick*	getBrick( unsigned int id ) const;
	virtual QVariantList	getBrickIDs() const;
	virtual void			getBrickIDs( QList<unsigned int> &ids ) const;
	virtual void			deleteBrick( unsigned int id );
	virtual void			deleteBrick( DzShaderBrick *brick );
	virtual void			deleteAllBricks();
	virtual void			invalidateSets();	
	virtual void			moveBrick( unsigned int id, IDzBrickUser *newOwner );
	virtual QUuid			getIdentifier() const;
	virtual void			setIdentifier( const QUuid &ident );
	virtual void			updateIdentifierOnSetInvalidate( bool onOff );
	virtual bool			isInEditMode() const;
	virtual void			startEditMode();
	virtual void			endEditMode();

	virtual bool			usesLocalShaderSpace() const;

	virtual bool			shouldSortOnLoad() const;
	
	virtual void					applyToScene();
	virtual QList<IDzBrickUser*>	fromScene();

	virtual void		unsetRender( const DzRenderSettings &settings ) const;

protected slots:
	virtual void		removeSet( DzBrickSet *set );
	virtual void		brickIDChanged( int oldID );

public slots:
	//DzBrickMaterial
	
	virtual void		setDiffuseColor( const QColor &color );
	virtual void		setBaseOpacity( float val );
	virtual void		setColorMap( const DzTexture *img );
	virtual void		setOpacityMap( const DzTexture *img );
	virtual void		setMaterialName( const QString &name );

	virtual int			getNumUVMaps() const;
	virtual QColor		getDiffuseColor() const;
	virtual double		getBaseOpacity() const;
	virtual bool		isColorMappable() const;
	virtual bool		isOpacityMappable() const;
	virtual DzTexture*	getColorMap() const;
	virtual DzTexture*	getOpacityMap() const;
	virtual QString		getMaterialName() const;
	virtual bool		isOpaque() const;
	virtual void		setNeedsTangentSpaceParams( bool onoff );
	virtual bool		needsTangentSpaceParams() const;
	virtual bool		shouldAlwaysEmbed() const;
	virtual bool		allowsAutoBake() const;

#ifndef Q_MOC_RUN
	static
#endif
	DzBrickMaterial*	convertDefaultMaterial( DzDefaultMaterial *mat );

signals:
	void	brickRemoved( DzShaderBrick *brick );
	void	brickAdded( DzShaderBrick *brick );
	void	generateFilesStarted();
	void	generateFilesFinished();

protected:
	
	virtual void	setGLMat( const DzDrawStyle &style ) const;
	virtual void	unsetGLMat( const DzDrawStyle &style ) const;

	virtual void	setShader( const DzRenderSettings &settings ) const;
	virtual void	setCoShader( const DzRenderSettings &settings, DzCoShaderInfo& info ) const;

private slots:
	void		resolvePropertyOwnership( DzShaderBrick *brick );
	void		invalidateGLProperties();

private:	
	void			setupGLProperties()const;

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzBrickMaterial> DzBrickMaterialPtr;

#endif // DZ_BRICK_MATERIAL_H