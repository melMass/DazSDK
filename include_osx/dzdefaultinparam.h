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
	Defines the default in brick param type.
**/

#ifndef DZ_DEFAULT_IN_PARAM_H
#define DZ_DEFAULT_IN_PARAM_H

/*****************************
	Include files
*****************************/

#include "dzbrickparam.h"

/*****************************
	Class definitions
*****************************/
/**
	Implemented in header file as simple example.
**/
class DZ_EXPORT DzDefaultInParam : public DzBrickParam {
	Q_OBJECT
public:
	
	DzDefaultInParam();
	virtual ~DzDefaultInParam();

	//DzBase
	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;

public slots:
	virtual int				getNumTokensNeeded() const;
	virtual int				getNumArgs() const;
	virtual void			setArgName( const QString &val );
	virtual QString			getArg( int i ) const;
	virtual bool			shouldWriteTokenInShader( int i ) const;
	virtual ParamDirection	getDirection() const;
	virtual ParamType		getType() const;
	virtual DzProperty*		getProperty( int i ) const;
	virtual int				getNumProperties() const;
	virtual int				getPropertyMapToken( int i ) const;
	virtual void			setType( int type );
	virtual void			setType( ParamType type );

	virtual ParamType 		getArgType( int i ) const;
	
	virtual	QString			getStringValue( int i ) const;

protected:
	virtual void		setTokenInBuffer();

private:
	struct	Data;
	Data	*m_data;
};


#endif // DZ_DEFAULT_IN_PARAM_H