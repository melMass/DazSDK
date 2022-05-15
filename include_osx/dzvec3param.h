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
	Defines the DzVec3Param class.
**/

#ifndef DZ_VEC3PARAM_H
#define DZ_VEC3PARAM_H
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

class DZ_EXPORT DzVec3Param : public DzBrickParam {
	Q_OBJECT
public:
	DzVec3Param();
	virtual ~DzVec3Param();

	//DzBase
	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;

public slots:
	virtual void			setArgName( const QString &arg ) const;
	virtual int				getNumTokensNeeded() const;
	virtual int				getNumArgs() const;
	virtual QString 		getArg(int i) const;
	virtual ParamType 		getArgType(int i) const;

	virtual DzProperty*		getProperty(int i) const;

	virtual DzFloatProperty*		getXProperty() const;
	virtual DzFloatProperty*		getYProperty() const;
	virtual DzFloatProperty*		getZProperty() const;

	virtual ParamType		getTypeForToken( int i ) const;
	virtual ParamType		getType() const;
	virtual bool			shouldWriteTokenInShader( int i ) const;
	virtual int				getNumProperties() const;
	virtual ParamDirection	getDirection() const;
	virtual void			setDirection( int i );
	virtual void			setType( int i );
	virtual bool			needsPrepForCall( int i ) { return true; }
	virtual QString			writeCallPrep( const QString &newToken, int i ) const;
	virtual void			setShouldWriteTokenInShader( bool onoff );
	virtual	QString			getStringValue( int i ) const;
	virtual int				getPropertyMapToken( int i ) const { return -1; }
	
protected:
	virtual void		setTokenInBuffer();
private slots:
	void				propertyDestoyed();
private:
	void deleteProperty( DzProperty *temp );
	
	struct	Data;
	Data	*m_data;
};

#endif //DZ_VEC3PARAM_H