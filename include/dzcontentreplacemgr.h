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

#ifndef DZ_CONTENT_REPLACE_MGR
#define DZ_CONTENT_REPLACE_MGR

/*****************************
	Include files
*****************************/

#include "dztypes.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzContentReplaceMgr : public QObject {
	Q_OBJECT
	Q_ENUMS( ContentReplaceMode )
	friend class DzContentMgr;
private:
	DzContentReplaceMgr( QObject *parent = NULL );
	~DzContentReplaceMgr();

public:

	enum ContentReplaceMode { ALWAYS_REPLACE, NEVER_REPLACE, ASK_WHEN_MATCHING,  ASK_TO_REPLACE };
	bool getCancelLoad();

public slots:

	ContentReplaceMode getReplaceMode();
	void	setReplaceMode( ContentReplaceMode mode );

	QString getNewContentPath();
	void	setNewContentPath( const QString &contentPath );

	QString getNewContentType();
	void	setNewContentType( const QString &contentType );

	void	getReplaceNodes( DzNodeList &replaceNodes );
	void	setReplaceNodes( const DzNodeList &replaceNodes );
	
	void	getPotentialReplaceNodes( DzNodeList &potentialReplaceNodes, DzNode *baseNode );
	void	getDefaultReplaceNodes( DzNodeList &defaultReplaceNodes, DzNode *baseNode );

	void	updateReplaceNodes( DzNode *baseNode );
	void	removeReplaceNodes();
	void	clearReplaceData();

	void	initReplaceForContentLoad( const QString &path, DzNode *baseNode );
	void	doReplace();

signals:

	void contentReplaceModeChanged( DzContentReplaceMgr::ContentReplaceMode mode );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DZ_CONTENT_REPLACE_MGR
