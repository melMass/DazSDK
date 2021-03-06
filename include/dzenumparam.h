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
	Defines the DzEnumParam class.
**/

#ifndef DZ_ENUMPARAM_H
#define DZ_ENUMPARAM_H

/*****************************
	Include files
*****************************/

#include "dzbrickparam.h"

/****************************
	Forward declarations
****************************/

class DzEnumProperty;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzEnumParam : public DzBrickParam {
	Q_OBJECT
public:
	DzEnumParam();
	virtual ~DzEnumParam();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;

public slots:
	virtual void			setList( const QStringList &strings, const QList<QVariant> &values );
	virtual void			addItemToList( const QString strings, const QVariant &val );
	virtual void			setItem( int index, const QString string, const QVariant &val );
	virtual void			removeItem( int i );
	virtual int				getNumItems();
	virtual QVariant		getItemValue( int i );
	virtual QString			getItemLabel( int i );
	virtual void			clearItems();

	virtual int				getNumTokensNeeded() const;
	virtual int				getNumArgs() const;
	virtual QString			getArg( int i ) const;
	virtual ParamType		getArgType( int i ) const;
	
	virtual DzProperty*		getProperty( int i ) const;
	virtual ParamType		getTypeForToken( int i ) const;
	virtual ParamType		getType() const;
	virtual bool			shouldWriteTokenInShader( int i ) const;
	virtual int				getNumProperties() const;
	virtual ParamDirection	getDirection() const;
	virtual void			setDirection( int i );
	virtual QString			writeShaderPrep() const;
	virtual bool			needsPrepForCall( int i ) { return true; }
	virtual QString			writeCallPrep( const QString &newToken, int i ) const;
	virtual void			setType( int i );
	virtual	QString			getStringValue( int i ) const;
	virtual int				getPropertyMapToken( int i ) const;
	virtual void			setShouldWriteTokenInShader( bool onoff );
	virtual void			setArgName( const QString &name );
	virtual DzEnumProperty*	getEnumProperty() const;
	
protected:
	virtual void	setTokenInBuffer();

private slots:
	void			propertyDestoyed();

private:
	QString	valsToString() const;
	QString	valsToScript() const;
	QString	stringToScript() const;
	void	deleteProperty( DzProperty *temp );

	struct	Data;
	Data	*m_data;
};

#endif //DZ_ENUMPARAM_H