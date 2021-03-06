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
	@file
	Defines the DzHttpHandler interface.
**/
#ifndef IDZ_HTTP_HANDLER_H
#define IDZ_HTTP_HANDLER_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

/**
	@sdk
	@interface IDzHttpHandler idzhttphandler.h
	@nosubgrouping
	@brief Interface providing methods relating to files...
**/
class DZ_EXPORT IDzHttpHandler
{
public:
	/**
		@sdk
		Destructor
	**/
	virtual ~IDzHttpHandler() {}

	/**
		@sdk
		Sets the host for this http handler
		@param host		The host used for this handler
	**/
	virtual void		setHost( const QString &host ) = 0;

	/**
		@sdk
		Sets the path for this handler
		@param path		The path used for this handler
	**/
	virtual void		setPath( const QString &path ) = 0;

	/**
		@sdk
		Sets the query for this handler
		@param query	The query used for this handler
	**/
	virtual void		setQueryString( const QString &query ) = 0;

	/**
		@sdk
		Sets the content type for this handler
		@param type		The content type used for this handler
	**/
	virtual void		setContentType( const QString &type ) = 0;
	
	/**
		@sdk
		Sets the request methd used for this handler
		@param method	The request method used for this handler
	**/
	virtual void		setRequestMethod( const QString &method ) = 0;

	/**
		@sdk
		Sets the connection mode used for this handler
		@param mode		The connection mode used for this handler
	**/
	virtual void		setConnectionMode( const QString &mode ) = 0;
	
	/**
		@sdk
		Creates a copy of this handler
		@return			a new handler with the same settings as this one
	**/
	virtual IDzHttpHandler *cloneHandler() = 0;

	/**
		@sdk
		Performs an asynchronous request
		@param content	The content of the request
	**/
	virtual void		doAsynchronousRequest( const QByteArray &content = NULL ) = 0;
	
	/**
		@sdk
		Performs a synchronous request
		@param content The content of the request
		@return a QByteArray of the content of the request
	**/
	virtual QByteArray	doSynchronousRequest( const QByteArray &content = NULL ) = 0;
	
	/**
		@sdk
		@return A string containing the last error message, if any
	**/
	virtual QString		getError()=0;
};

#endif	// IDZ_HTTP_HANDLER_H
