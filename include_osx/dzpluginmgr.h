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
	Defines the DzPluginMgr class.
**/

#ifndef DAZ_PLUGIN_MGR_H
#define DAZ_PLUGIN_MGR_H

/****************************
	Include files
****************************/

#include "dzversion.h"
#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzGuid;
class QByteArray;
class DzPlugin;
class DzPluginsWizardFrame;

/****************************
	Type definitions
****************************/

typedef QListIterator<DzPlugin*> DzPluginListIterator;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPluginMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
	friend class DzPluginsWizardFrame;
private:

	//
	// CONSTRUCTORS
	//

	DzPluginMgr( const QByteArray &pluginData );
	~DzPluginMgr();

public:

	//
	// MANIPULATORS
	//

	DzError		startup();
	DzError		shutdown();

	//
	// ACCESSORS
	//

	DzPluginListIterator	pluginListIterator() const;
	QByteArray				getActivationData(const DzGuid &guid);
	void					setActivationData(const DzGuid &guid, const QString &data);
	bool					registerPlugins( QMap<DzPlugin*, QString> plugins );

public slots:
	void					doAboutPluginsDlg();

	int			getNumPlugins() const;
	DzPlugin*	findPlugin( const QString pluginName ) const;
	DzPlugin*	getPlugin( int which ) const;

private:
	void	addPlugin( DzPlugin *plugin );
	void	loadPlugins( const QString &path );
	bool	loadPlugin( const QString &filename, bool ignored );
	void	registerTrialPlugins();
	void	doRegisterPluginsDialog( QList<DzPlugin*> plugins );
	void	buildPluginsFrame( QList<DzPlugin*> plugins, DzPluginsWizardFrame *frm );
	QStringList				loadConfiguration();

	QByteArray				getPluginData();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PLUGIN_MGR_H