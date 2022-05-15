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

#ifndef DAZ_BRICK_CAMERA_H
#define DAZ_BRICK_CAMERA_H

/*****************************
	Include files
*****************************/

#include "dzbasiccamera.h"
#include "dzdefaultbrickuser.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBrickCamera : public DzBasicCamera,
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
	DzBrickCamera();

	// Destructor
	~DzBrickCamera();

	//////////////////////////
	// from DzBase

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	startLoad( const DzInFile *file );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;

	// from DzCamera
	
	virtual void	setProjection( const DzRenderSettings &settings, float width, float height ) const;
	virtual void	setRenderGlobals( const DzRenderSettings &settings );

	/////////////////////////
	// from DzNode

	virtual QPixmap	getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon	getIcon() const;
	virtual void	draw( const DzDrawStyle &style ) const;

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
	virtual QString	getExtension() const;
	DzElement*		setAttributes( const DzSettings *settings );
	void			getAttributes( DzSettings *settings ) const;
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
	void			setCameraName( const QString &name );
	virtual QString	getCameraName() const;

private:

	void	init();
	void	connectToProperties();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BRICK_CAMERA_H
