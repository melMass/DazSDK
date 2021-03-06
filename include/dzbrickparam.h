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
	Defines the DzBrickParam and DzParamConnections classes.
**/

#ifndef DZ_BRICKPARAM_H
#define DZ_BRICKPARAM_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzmimedata.h"

/****************************
	Forward declarations
****************************/

class DzMatrix4;
class DzPropertyParam;
class DzVec3;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzParamConnection : public QObject
{
	Q_OBJECT
	friend class DzBrickParam;
public:
	DzParamConnection();
	DzParamConnection( DzParamConnection &con );
	virtual ~DzParamConnection();

	DzParamConnection&	operator=( const DzParamConnection &con );
	bool	operator==( const DzParamConnection &con ) const;
	bool	operator!=( const DzParamConnection &con ) const;

public slots:
	DzBrickParam*	getParam() const;
	int				getIndex() const;
	int				getParentIndex() const;

private:
	void	setParam( DzBrickParam *param );
	void	setIndex( int index );
	void	setParentIndex( int index );

	DzParamConnection( DzBrickParam *param, int index );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzBrickParam : public DzBase
{
	Q_OBJECT
	Q_ENUMS(ParamDirection)
	Q_ENUMS(ParamType)
	friend class DzShaderBrick;
	friend class DzBrickSet;
	friend class DzBrickGroup;

public:
	DzBrickParam();
	virtual ~DzBrickParam();

	enum ParamDirection { None = 0, In, Out, AOV };
	enum ParamType { Unknown = 0, Float, Color, Point, Vector, Normal, Matrix, String };

	//DzBase
	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;
	static QString		typeToString(int i);
	static ParamType	stringToType( const QString &typeString );
	
	QString				getStringOfTokens() const;
	void				setTokensWithString( const QString &str );
	void				clearTokens();

public slots:
	
	QString			getLabel() const;
	void			setLabel( const QString &label );

	void			setIsAdvanced(bool onOff);
	bool			getIsAdvanced() const;
	
	//pure virtual slots
	virtual int				getNumTokensNeeded() const = 0;
	virtual int				getNumArgs() const = 0;
	virtual QString 		getArg( int i ) const = 0;
	virtual ParamType 		getArgType( int i ) const = 0;
	virtual DzProperty*		getProperty( int i ) const = 0;
	//index in token array of map token or -1 if no map token
	//i = index of the property
	virtual int				getPropertyMapToken( int i ) const = 0;
	//Property count must be >= token count
	//if properties are mapped, map tokens should appear
	//in order after tokens for standard properties
	virtual int				getNumProperties() const = 0;
	virtual ParamDirection	getDirection() const = 0;
	
	//over all param type
	virtual ParamType		getType() const = 0;

	//used for the shader default values on the tokens
	virtual	QString			getStringValue( int i ) const = 0;

	virtual QString			getPropertyPath( int i ) const;
	virtual void			setPropertyPath( int i, const QString &path );

	virtual QString 		getToken( int i ) const;
	//type for individual tokens
	virtual ParamType		getTypeForToken( int i ) const { return getType(); }
	
	
	virtual QString			writeShaderPrep() const { return QString(); }

	//if a param need to be set up before a the "function" call is made
	//this should return true. 
	//this call is not relevant for Out or AOV direction params
	virtual bool			needsPrepForCall( int i ) { return false; }

	//Return the shader code;
	//The params preped val will need to be in the new token at the end of the code snid bit
	//The token will be the same type as getType() of class uniform
	//Thus only uniform vars (other tokens) should be used to compose it
	virtual QString			writeCallPrep( const QString &newToken , int i ) const { return QString(); }
	
	//token needs to be in the list of parameters for the final shader
	virtual bool	shouldWriteTokenInShader( int i ) const { return false; }

	virtual bool	isArray() const;
	virtual void	setIsArray( bool onoff );
	virtual int		getOutputArraySize() const;
	virtual void	setOutputArraySize( int i );
	virtual bool	giveArrayAsList() const;
	virtual void	setGiveArrayAsList( bool onoff );
			
	//if a global default val is not empty and the param is not connected
	//the params tokens will not be written and instead the final token
	//will be set to the global var val
	//this is only used for params with an "In" direction
	virtual QString	getDefaultGlobalValue() const;
	virtual void	setDefaultGlobalValue( const QString &val );

	virtual DzShaderBrick*	getTopBrickOwner() const;
	virtual int				getScopePosition() const;
	virtual void			setScopePosition( int position );

	//simple wraps of static functions for scripting
	virtual QString	getTypeString( int i ) const;
	virtual QString	getVecString( int type, const DzVec3 &vec ) const;
	virtual QString	getColorString( const QColor &color, const QString &space = "rgb" ) const;
	virtual QString	getFloatString( float val ) const;
	virtual QString	getMatrixString( const DzMatrix4 &matrix ) const;
	virtual QString	getEscapedString( const QString &string ) const;
	virtual QString	getNewToken() const;

	//connection functions
	virtual bool			canConnect( DzBrickParam *param ) const;
	
	int						getNumConnections() const;
	DzParamConnection*		getConnection( int i ) const;
	void					addConnection( DzBrickParam *param );
	void					removeConnection( int i );
	void					removeConnection( DzBrickParam *param );
	void					removeAllConnections();
	void					moveConnectionsToParam( DzBrickParam *param );
	virtual QString			simpleText() const;

	virtual bool				isDirectPropDrivenOutput() const { return false; }
	virtual DzPropertyParam*	getDirectDrivingProperty() const { return NULL; }

signals:
	void	propertyChanged( DzProperty *prop );
	void	propertyListChanged();
	void	removed();
	void	connectionsChanged();
	void	invalidateFiles();
	void	typeChanged();
	void	labelChanged();

protected:
	virtual void		setTokenInBuffer() = 0;
	virtual void		setOwner( DzShaderBrick *brick );

	//data
	struct	Data;
	Data	*m_data;

private:
	void	removeConnectionLink( int i );
	void	addConnectionLink( DzParamConnection &con, DzBrickParam *param );
	
};

class DZ_EXPORT DzBrickParamMime : public DzMimeData
{
public:
	DzBrickParamMime( DzBrickParam *param );

	static QByteArray		encode( const DzBrickParam *param );
	static DzBrickParam*	decode( const QMimeData *src );

	static const QString	s_mimeType;
};

#endif //DZ_BRICKPARAM_H