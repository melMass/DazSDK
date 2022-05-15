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
	Defines the DzHelpMgr class.
**/

#ifndef DAZ_HELP_MGR_H
#define DAZ_HELP_MGR_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzAction;
class QDomElement;
class QDomDocument;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzHelpContentsItem {
	friend class DzHelpMgr;
private:
	DzHelpContentsItem();
	DzHelpContentsItem( DzHelpContentsItem *parent, const QString &name, const QUrl &url );
	~DzHelpContentsItem();

public:

	QString				getName() const;
	QUrl				getUrl() const;
	int					getNumChildren() const;
	DzHelpContentsItem*	getChild( int which ) const;
	int					findChild( DzHelpContentsItem *child ) const;
	DzHelpContentsItem*	getParent() const;

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzHelpMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
	friend class DzStyle;
	friend class DzActionMgr;
	friend class DzHelpItemIterator;
private:
	//
	// CONSTRUCTORS
	//

	DzHelpMgr();
	~DzHelpMgr();

public:

	bool			getHelpItem( const QString &label, QString *group = NULL, QString *description = NULL,
						QString *toolTip = NULL, QString *statusTip = NULL, QString *helpString = NULL ) const;

public slots:

	void			browseToPage( const QString &page );
	void			browseToUrl( const QUrl &url );
	void			browseToUrl( const QString &urlString );	// provided for script access
	void			browseToKeyword( const QString &keyword );
	void			browseToIdentifier( const QString &identifier );

	int				getNumKeywords() const;
	QString			getKeyword( int which ) const;
	QUrl			getKeywordUrl( int which ) const;
	QUrl			findKeywordUrl( const QString &keyword ) const;

	int				getNumIdentifiers() const;
	QString			getIdentifier( int which ) const;
	QUrl			getIdentifierUrl( int which ) const;
	QUrl			findIdentifierUrl( const QString &id ) const;

	DzHelpContentsItem*	getHelpContents() const;

	int				getNumFilters() const;
	QString			getFilterName( int which ) const;
	QStringList		getFilterAttributes( int which ) const;
	QStringList		findFilterAttributes( const QString &name ) const;

	QStringList		getHelpItemLabels() const;
	bool			hasHelpItem( const QString &label ) const;
	bool			isHelpItemUsed( const QString &label ) const;
	QString			getGroup( const QString &label ) const;
	QString			getDescription( const QString &label ) const;
	QString			getToolTip( const QString &label ) const;
	QString			getStatusTip( const QString &label ) const;
	QString			getHelpString( const QString &label ) const;

	void			setHelpItem( const QString &label, const QString &group, const QString &description,
						const QString &toolTip, const QString &statusTip, const QString &helpString );
	void			setGroup( const QString &label, const QString &group );
	void			setDescription( const QString &label, const QString &description );
	void			setToolTip( const QString &label, const QString &toolTip );
	void			setStatusTip( const QString &label, const QString &statusTip );
	void			setHelpString( const QString &label, const QString &helpString );

	bool			renameHelpItem( const QString &oldLabel, const QString &newLabel );
	bool			removeHelpItem( const QString &label );

	DzError			saveInlineHelp( const QString &filename );

	void			updateHelp( QWidget *w );
	void			updateHelp( DzAction *a );

private:

	void	registerWidget( QWidget *w );
	void	registerAction( DzAction *a );

	void	readHelpIndex();
	void	helpIndexFromDOM( const QDomElement &root, DzHelpContentsItem *parent );
	void	readHelpFile( const QString &filePath, DzHelpContentsItem *parent );
	void	helpFileFromDOM( const QDomElement &root, DzHelpContentsItem *parent, const QString &localPath );
	void	helpFilterDefFromDOM( const QDomElement &root );
	void	helpFilterFromDOM( const QDomElement &root, DzHelpContentsItem *parent, const QString &localPath );
	void	helpTocFromDOM( const QDomElement &root, DzHelpContentsItem *parent, const QString &localPath );
	void	helpKeywordsFromDOM( const QDomElement &root, const QString &localPath );
	void	inlineHelpFromDOM( const QDomElement &helpElem );
	void	helpTextFromDOM( const QDomElement &helpElem );
	void	loadHelpDirectory( const QString &dirName, DzHelpContentsItem *parent );
	bool	openDomDocument( const QString &filepath, QDomDocument &doc );
	QUrl	refToURL( const QString &href, const QString &localPath );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_HELP_MGR_H