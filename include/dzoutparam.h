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
	Defines the DzOutParam class.
**/

#ifndef DZ_OUTPARAM_H
#define DZ_OUTPARAM_H

/*****************************
	Include files
*****************************/

#include "dzbrickparam.h"

/****************************
	Class definitions
*****************************/

class DZ_EXPORT DzOutParam : public DzBrickParam {
	Q_OBJECT
public:

	DzOutParam();
	virtual ~DzOutParam();

	//DzBase
	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	save( DzOutFile *file ) const;
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );

public slots:
	virtual int				getNumTokensNeeded() const;
	virtual int				getNumArgs() const;
	virtual QString			getArg( int i ) const;
	virtual bool			shouldWriteTokenInShader( int i );
	virtual ParamDirection	getDirection() const;
	virtual ParamType		getType() const;
	virtual DzProperty*		getProperty( int i ) const;
	virtual int				getNumProperties() const;
	virtual int				getPropertyMapToken( int i ) const;
	virtual void			setArgName( const QString &arg );
	virtual void			setIsAOV( bool onoff );
	virtual void			setType( ParamType type );
	virtual void			setType( int type );

	virtual ParamType 		getArgType( int i ) const;
	virtual	QString			getStringValue( int i ) const;

	virtual bool				isDirectPropDrivenOutput() const;
	virtual DzPropertyParam*	getDirectDrivingProperty() const;
	virtual void				setDirectDriveProperty( DzPropertyParam *param );

private slots:
	void	clearDriveProperty();

protected:
	virtual void	setTokenInBuffer();

private:
	struct	Data;
	Data	*m_data;
};


#endif //DZ_OUTPARAM_H