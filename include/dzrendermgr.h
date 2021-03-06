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
	Defines the DzRenderMgr class.
**/

#ifndef DAZ_RENDER_MGR_H
#define DAZ_RENDER_MGR_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"

/****************************
	Forward declarations
****************************/

class DzRenderer;
class DzRenderOptions;

/****************************
	Type definitions
****************************/

typedef QListIterator<DzRenderer*> DzRendererIterator;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRenderMgr : public DzBase {
	Q_OBJECT
	Q_ENUMS( RenderPriority )
	friend class DzApp;
	friend class DzRendererFactoryList;
private:
	//
	// CREATORS
	//

	DzRenderMgr();
	~DzRenderMgr();

public slots:

	bool	doRender( DzRenderOptions *opt = NULL );
	void	setActiveRenderer( DzRenderer *r );
	void	showRenderDialog();

public:
	// Other classes (DzNode and DzMaterial) rely on the order and values of this enum.
	// It should not be changed.
	enum RenderPriority { 
		RENDER_PRIORITY_LOWEST = 0, 
		RENDER_PRIORITY_LOW, 
		RENDER_PRIORITY_BELOW_NORMAL, 
		RENDER_PRIORITY_NORMAL, 
		RENDER_PRIORITY_ABOVE_NORMAL, 
		RENDER_PRIORITY_HIGH, 
		RENDER_PRIORITY_HIGHEST 
	};

	DzRendererIterator	rendererIterator() const;

public slots:

	void		shutdown();
	int			getNumRenderers() const;
	DzRenderer*	getRenderer( int which ) const;
	QObjectList	getRendererList() const;
	DzRenderer*	findRenderer( const QString &className ) const;
	DzRenderer*	getActiveRenderer() const;
	
	bool		isRendering() const;

	bool		hasRender() const;
	QString		getLastSavedRenderPath() const;
	QString		saveLastRender() const;

	DzRenderOptions*	getRenderOptions() const;

	void		addRenderDirectory( const QString &directory, bool saveNow = true );
	bool		removeRenderDirectory( const QString &directory );
	void		removeAllRenderDirectories();
	int			getNumRenderDirectories() const;
	QString		getRenderDirectoryPath( int which ) const;
	QStringList	getBaseAndRelativePath( const QString &absPath );
	
	void		emitRenderFolderChanged();

#ifndef Q_MOC_RUN
	static
#endif
	QString		getRenderIconFileName( const QString &imageName, bool justFileName );
#ifndef Q_MOC_RUN
	static
#endif
	QString		getMetaXmlFileName( const QString &imageName, bool justFileName );
#ifndef Q_MOC_RUN
	static
#endif
	QString		getIconSuffix();

signals:

	void	rendererAdded( DzRenderer *renderer );
	void	activeRendererChanged( DzRenderer *renderer );
	void	renderStarting();
	void	renderFinished( bool succeeded );
	void	hasRenderChanged( bool state );
	void	renderDirectoryListChanged();
	void	renderFolderChanged();

protected:

	static void	addClass( DzClassFactory *type );

private:
	void	saveRenderDirectories();
	void	doHardRenderWarning();
	bool	doRenderOverwriteWarning( const QString &filename );
	bool	doRenderImageSeriesOverwriteWarning( const QString &filename );
	void	addRenderer( DzRenderer *r );
	void	setDefaultRenderDir();
	void	buildRenderDirs();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_RENDER_MGR_H