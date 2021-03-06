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
	Defines the DzPropertyParam class.
**/

#ifndef DZ_PROPERTYPARAM_H
#define DZ_PROPERTYPARAM_H

/*****************************
	Include files
*****************************/

#include "dzbrickparam.h"

/****************************
	Forward declarations
****************************/

class DzShaderBrick;
class DzProperty;
class DzTokenBuffer;
class DzFloatProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPropertyParam : public DzBrickParam {
	Q_OBJECT
public:
	DzPropertyParam();
	virtual ~DzPropertyParam();

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;

public slots:
	virtual void			setProperty( DzProperty *prop, const QString &arg, const QString &mapArg );
	virtual int				getNumTokensNeeded() const;
	virtual int				getNumArgs() const;
	virtual QString 		getArg( int i ) const;
	virtual ParamType 		getArgType( int i ) const;
	virtual DzProperty*		getProperty( int i ) const;
	virtual ParamType		getTypeForToken( int i ) const;
	virtual ParamType		getType() const;
	virtual bool			shouldWriteTokenInShader( int i ) const;
	virtual int				getNumProperties() const;
	virtual ParamDirection	getDirection() const;
	virtual void			setDirection( int i );
	virtual void			setShouldWriteTokenInShader( bool onoff );
	virtual	QString			getStringValue( int i ) const;
	virtual int				getPropertyMapToken( int i ) const;

protected:
	virtual void		setTokenInBuffer();

private slots:
	void				propertyDestoyed();
	void				deleteProperty( DzProperty *temp );

private:
	struct	Data;
	Data	*m_data;
};

#endif// DZ_PROPERTYPARAM_H