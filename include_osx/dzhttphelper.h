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

#ifndef	DAZ_HTTP_HELPER_H
#define DAZ_HTTP_HELPER_H

/*****************************
	Include files
*****************************/

#include "idzhttphandler.h"

/*****************************
	Forward declarations
*****************************/

class QSslError;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzHttpHelper : public QObject, public IDzHttpHandler {
	Q_OBJECT
public:
	DzHttpHelper();
	virtual ~DzHttpHelper();

public slots:

	virtual void	setHost( const QString &host );
	virtual void	setPath( const QString &path );
	virtual void	setQueryString( const QString &query );
	virtual void	setContentType( const QString &type );
	virtual void	setRequestMethod( const QString &method );
	virtual void	setConnectionMode( const QString &mode );
	virtual void	setHeaderValues( const QStringList &keys, const QStringList &values);

	virtual void		doAsynchronousRequest( const QByteArray &content = NULL );
	virtual QByteArray	doSynchronousRequest( const QByteArray &content = NULL );

	virtual void		abort();
	virtual QString		getError();
	

	virtual IDzHttpHandler *cloneHandler();

signals:

	void	received( QByteArray bytes );

private slots:

	void	done( bool error );
	void	sslErrors( const QList<QSslError> &errors );

private:

	void	doRequest( const QByteArray &content );
	
	struct	Data;
	Data	*m_data;
};

#endif
