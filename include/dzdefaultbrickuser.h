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
	Defines the a helper interface for DzShaderBrick users.
**/

#ifndef DZ_DEFAULT_BRICK_USER_H
#define DZ_DEFAULT_BRICK_USER_H

//reserved section ids to save/restore DzBrickSets and name
#define DZ_SETS_SECTION		0x00D0
#define DZ_NAME_SECTION		0x00D1
#define DZ_IDENT_SECTION	0x00D2

/*****************************
	Include files
*****************************/

#include "idzbrickuser.h"

/****************************
	Forward declarations
****************************/

class DzPropertySettings;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDefaultBrickUser : virtual public IDzBrickUser
{
	friend class DzBrickSet;
public:
	DzDefaultBrickUser();
	virtual ~DzDefaultBrickUser();

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;
	virtual	void		postLoadFile( const DzInFile *file );

	virtual bool		allowBrick( DzShaderBrick *brick );
	DzBrickMap			getBrickMap() const;
	QString				getOrginalNameForSet( const QString &name );
	static const DzClassFactory*	getBrickClassFactory( const QString &name );
	QString				getBaseShaderFileName();
	
	virtual void	applyNodeToScene();
	static void		setAttributesHelper( IDzBrickUser *user, const DzSettings *settings, bool brickInfoOnly = false );
	static void		setAttributesHelper( IDzBrickUser *user, const DzSettings *settings, QHash<QString,DzShaderBrick*> &madeBricks, bool brickInfoOnly );

	static DzShaderBrick*	setBrickWithSettings( DzSettings *curBrickSetting, DzShaderBrick *curBrick );
	static int		getIndexForParam( DzSettings *curConSet, const QString &keyName, DzShaderBrick *srcBrick );
	static void		getAttributesHelper( const IDzBrickUser *user, QList<uint> &brickIds, DzSettings *settings, bool brickInfoOnly = false );

	static void		getPropertyValue( DzProperty *prop, DzPropertySettings &settings );
	static void		setPropertyValue( DzProperty *prop, DzPropertySettings &settings );
	static void		writeBrickToSettings( DzShaderBrick *brick, DzSettings *brickSettings, bool writeTokens );

public:

	//DzDefaultBrickUser
	virtual QString			getBrickUserName() const;
	virtual void			setBrickUserName( const QString &name );
	virtual int				getNumBrickSets() const;
	virtual DzBrickSet*		getBrickSet( int i ) const;
	virtual unsigned int	addBrick( DzShaderBrick *brick );

	virtual DzShaderBrick*	getBrick( unsigned int id ) const;
	virtual QVariantList	getBrickIDs() const;
	virtual void			getBrickIDs( QList<unsigned int> &ids ) const;
	virtual void			deleteBrick( unsigned int id );
	void					deleteBrick( unsigned int id, bool disconnect );
	virtual void			deleteBrick( DzShaderBrick *brick );
	virtual void			deleteAllBricks();
	virtual void			invalidateSets();
	
	virtual void			removeSet( DzBrickSet *set );
	virtual void			moveBrick( unsigned int id, IDzBrickUser *newOwner );
	virtual QUuid			getIdentifier() const;
	virtual void			setIdentifier( const QUuid &ident );
	virtual void			updateIdentifierOnSetInvalidate( bool onOff );
	virtual bool			isInEditMode() const;
	virtual void			startEditMode();
	virtual void			endEditMode();

	virtual bool			usesLocalShaderSpace() const;
	
protected:	
	virtual void			resolvePropertyOwnership( DzShaderBrick *brick );
	virtual void			brickIDChanged( int oldID );
	void						setAssetIDFromBrickUserName();
private:
	uint					getNewKey();

	void					fixSetNames();
	int						addBrickInternal( DzShaderBrick *brick );
	static DzTexture*		getImage( const QString &sMapFile );

	struct	Data;
	Data	*m_data;
};

#endif // DZ_DEFAULT_BRICK_USER_H