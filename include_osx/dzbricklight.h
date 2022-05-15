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

#ifndef DAZ_BRICK_LIGHT_H
#define DAZ_BRICK_LIGHT_H

/*****************************
	Include files
*****************************/

#include "dzlight.h"
#include "dzdefaultbrickuser.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBrickLight : public DzLight,
					virtual public IDzBrickUser,
					protected DzDefaultBrickUser
{
	Q_OBJECT
	Q_INTERFACES( IDzBrickUser )
public:
	//
	// CREATORS	
	//

	// Constructors
	DzBrickLight();
	// Destructor
	virtual ~DzBrickLight();

	//////////////////////////
	// from DzBase

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	startLoad( const DzInFile *file );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;

	/////////////////////////
	// from DzNode

	virtual QPixmap	getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon	getIcon() const;
	virtual void	draw( const DzDrawStyle &style ) const;

	//////////////////////////////
	// from DzCamera

	virtual void	setFocalDistance( double dist );
	virtual double	getFocalDistance() const;
	virtual void	copyFrom( const DzElement *source );
	
	//DzDefaultBrick User
	virtual DzBrickMap			getBrickMap() const;
	virtual bool				allowBrick( DzShaderBrick *brick );
	virtual DzElement*			toElement();
	virtual const DzElement*	toElement() const;
	virtual void				release();
	virtual IDzBrickUser*		makeNew() const;
	QString						getDisplayName() const;
	void						addChildToElement( DzElement *element );

public slots:
		virtual QString		getExtension() const;
		//dzelement overrides
		virtual DzElement*	setAttributes( const DzSettings *settings );
		virtual void		getAttributes( DzSettings *settings ) const;

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

		virtual void					applyToScene();
		virtual QList<IDzBrickUser*>	fromScene();

protected slots:
	virtual void	removeSet( DzBrickSet *set );
	virtual void	brickIDChanged( int oldID );

private slots:
	void	resolvePropertyOwnership( DzShaderBrick *brick );

signals:
	void	brickRemoved( DzShaderBrick *brick );
	void	brickAdded( DzShaderBrick *brick );
	void	generateFilesStarted();
	void	generateFilesFinished();

public slots:
	
	virtual void	aimAt( const DzVec3 &pos );
	virtual void	frame( const DzBox3 &box, float aspect );

	void			setLightName( const QString &name );

	//////////////////////////
	// from DzLight

	virtual void	setGLShadow( int pass, int totalPasses, int *shadowMapSize = NULL );
	virtual void	unsetGLShadow();

	//
	// ACCESSORS
	//

	virtual QString			getLightName() const;
	DzBrickSet::LightType	getLightType() const;
	QString					getShadowMapPath() const;

	//////////////////////////
	// from DzLight

	virtual QColor	getDiffuseColor() const;
	virtual float	getIntensity() const;
	virtual bool	isDirectional() const;
	virtual bool	isOn() const;

	//////////////////////////
	// from DzCamera

	virtual void	setGL( int width, int height, const QRect &view, int pass = 0, int totalPasses = 1, bool depthOfField = false );
	virtual double	getNearClippingPlane() const;
	virtual double	getFarClippingPlane() const;

	//////////////////////////
	// from DzLight

	virtual void	create( const DzRenderSettings &settings, const QString &shadowMap ) const;
	virtual void	setShadowTransform( const DzRenderSettings &settings, const DzCamera *camera ) const;
	virtual bool	canViewThrough() const;

protected:

	//////////////////////////
	// from DzLight

	virtual void	setGLLighting( const DzDrawStyle &style, int pass = 0, int totalPasses = 1 );
	virtual void	unsetGLLighting( const DzDrawStyle &style );

private:

	void	init();
	void	connectToProperties();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BRICK_LIGHT_H
