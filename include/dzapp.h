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
	Defines the DzApp class.
**/

#ifndef DAZ_APP_H
#define DAZ_APP_H

/*****************************
	Include files
*****************************/

#include <QtCore/QEvent>
#include <QtGui/QApplication>

#include "dzauthor.h"
#include "dztypes.h"
#include "dzversion.h"

/****************************
	Forward declarations
****************************/

class DzAppSettingsMgr;
class DzAssetIOMgr;
class DzAssetMgr;
class DzAuthenticationMgr;
class DzBase;
class DzCallBackMgr;
class DzContentMgr;
class DzDeviceMgr;
class DzExportMgr;
class DzFileIOPresetMgr;
class DzGuid;
class DzHelpMgr;
class DzImageMgr;
class DzImportMgr;
class DzMainWindow;
class DzMultiMediaMgr;
class DzPluginMgr;
class DzRenderMgr;
class DzSaveFilterMgr;
class DzScript;
class DzSkin;
class DzStyle;
class DzTextureBakerMgr;
class DzTextureConvertorMgr;
class QDir;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzApp : public QApplication {
	Q_OBJECT
	Q_ENUMS( Platform OperatingSystem ReleaseEdition GraphicsMode )
	Q_PROPERTY( QString appName READ getAppNameProp )
	Q_PROPERTY( int version READ getVersionProp )
	Q_PROPERTY( quint64 version64 READ getVersion64Prop )
	Q_PROPERTY( QString versionString READ getVersionStringProp )
	Q_PROPERTY( QString longVersionString READ getLongVersionStringProp )

	friend class DzRegistrationWizardFrame;

public:

	enum	Platform { Windows, MacOSX };
	enum	OperatingSystem {
				WindowsUnknown, Windows95, Windows98, WindowsMe,
				Windows2000, WindowsXP, Windows2003, WindowsVista,
				Windows7,
				MacUnknown, Mac10_0, Mac10_1, Mac10_2, Mac10_3,
				Mac10_4, Mac10_5, Mac10_6, Mac10_7
			};
	enum	ReleaseEdition { Free, Standard, Advanced, Pro, Alpha, Beta };
	enum	GraphicsMode { NoInterface, NoInterfaceWithOpenGL, FullInterface };

	//
	// CREATORS
	//

	DzApp( int& argc, char **argv, bool makeInterfaceAvailable = true, bool runAsSlave = false );
	virtual ~DzApp();

	//
	// MANIPULATORS
	//

	//////////////////////////////////
	// from DzObject

	virtual bool	event( QEvent *e );

	//////////////////////////////////
	// from QApplication

	virtual bool	notify( QObject *receiver, QEvent *e );

	// Initialize the application - this gets called by run().
	// This is supposed to be a private function, but someone made it public for the
	// Bryce integration - don't call this method!
	bool		init( GraphicsMode mode, const QString &startupScriptPath = QString::null );

	bool		run( DzApp::GraphicsMode mode = DzApp::FullInterface );
	void		setOpenFileName( const QString &filename );
	void		restoreDefaults();

	void		getDiskSpace( const QString &path, qint64 *totalBytes, qint64 *freeBytes ) const;
	Qt::HANDLE	getGUIThreadID() const;
	bool		doRegistrationWizard();
	bool		doAuthorshipWizard();
	bool		applicationDataValid() const;

public slots:

	QString	getTempFilename();
	QString	getTempRenderFilename();
	void	showURL( const QString &url );
	void	setLoadSavePath( const QString &dir );
	void	statusLine( const QString &msg, bool writeToLog = true );
	void	log( const QString &buffer );
	void	debug( const QString &msg );
	void	warning( const QString &msg );
	bool	flushLogBuffer();

	bool	setStyleDefinition( const QString &name );

	bool	setTempPath( const QString &tempPath );
	void	restoreDefaultTempPath();

	void	enableMultiThreading( bool onOff );

	//
	// ACCESSORS
	//

	Platform				platform() const;
	OperatingSystem			operatingSystem() const;
	QString					operatingSystemString() const;
	bool					isStarting() const;
	bool					isRunning() const;
	bool					isClosing() const;
	bool					isSlave() const;
	bool					writeConfigScript( QString configScriptFilename = QString::null ) const;
	DzMainWindow*			getInterface() const;
	QString					getHomePath() const;
	QString					getDAZDataPath() const;
	QString					getProgramDataPath() const;
	QString					getAppDataPath() const;
	QString					getDocumentsPath() const;
	QString					getShadersPath() const;
	QString					getGeneratedShadersPath() const;
	QString					getUtilitiesPath() const;
	QString					getPluginsPath() const;
	QString					getTempPath() const;
	QString					getScriptsPath() const;
	QString					getGeneratedScriptsPath() const;
	QString					getAbsoluteScriptPath( const QString &scriptName ) const;
	QString					getResourcesPath() const;
	QString					getDocumentationPath() const;
	DzAuthor				getCurrentAuthor() const;
	QString					getLoadSavePath() const;
	DzImportMgr*			getImportMgr() const;
	DzExportMgr*			getExportMgr() const;
	DzFileIOPresetMgr*		getFileIOPresetMgr() const;
	DzSaveFilterMgr*		getSaveFilterMgr() const;
	DzAssetIOMgr*			getAssetIOMgr() const;
	DzContentMgr*			getContentMgr() const;
	DzAssetMgr*				getAssetMgr() const;
	DzAppSettingsMgr*		getAppSettingsMgr() const;
	DzImageMgr*				getImageMgr() const;
	DzHelpMgr*				getHelpMgr() const;
	DzRenderMgr*			getRenderMgr() const;
	DzTextureConvertorMgr*	getTextureConvertorMgr() const;
	DzTextureBakerMgr*		getTextureBakerMgr() const;
	DzMultiMediaMgr*		getMultiMediaMgr() const;
	DzDeviceMgr*			getDeviceMgr() const;
	DzCallBackMgr*			getCallBackMgr() const;
	DzPluginMgr*			getPluginMgr() const;
	DzAuthenticationMgr*	getAuthenticationMgr() const;
	int						modifierKeyState() const;
	DzStyle*				getStyle() const;
	QString					getStyleDefinition() const;
	QStringList				getStyleDefinitionList() const;
	bool					isMultiThreadingEnabled() const;

	bool			usingInterface() const;
	QString			getDataFolderName() const;
	QString			getDataFolderPathBase() const;
	QString			getDataFolderPath() const;
	bool			isRegistered() const;
	ReleaseEdition	releaseEdition() const;
	QString			releaseEditionString() const;
	int				bitArchitecture() const;
	QString			bitArchitectureString() const;
	QWidget*		getDialogParent() const;
	bool			breadCrumbTrackingIsActive() const;
	void			setBreadCrumbTrackingActive( bool onOff );
	void			sendSourceBreadCrumb( int id, const QString &shortmsg = QString(), const QString &numeric = QString(), const QString &longMsg = QString() );
	void			setUpBreadCrumbTrackingSignalWatch( QObject *obj, const char *signal, int id = -1 );
	void			clearDelayedDeleteStack( bool doProgress );
	void			addSessionFileLoad( const QString &name );

	void			refreshStyleSheet( bool rereadFromFile = false );
	DzSkin*			getSkin() const;
	bool			setSkin( const QString &fileName );
	void			clearSkin();
	QString			createUuid() const;
	QString			createDigest( QStringList tokens ) const;
	QString			createDigest( const QByteArray &data ) const;
	GraphicsMode	getGraphicsMode() const;

public:

	// Aliases for static functions to provide properties to DAZ Script
	QString	getAppNameProp() const { return getAppName(); }
	int		getVersionProp() const { return getVersion().getVersionNumber32(); }
	quint64	getVersion64Prop() const { return getVersion().getVersionNumber(); }
	QString	getVersionStringProp() const { return getVersionString(); }
	QString	getLongVersionStringProp() const { return getLongVersionString(); }

	//
	// STATIC
	//

	static QString						getAppName();
	static DzVersion					getVersion();
	static QString						getVersionString();
	static QString						getLongVersionString();
	static void							setBusyCursor();
	static void							clearBusyCursor();
	static DzClassFactoryListIterator	classFactoryIterator();
	static const DzClassFactory*		findClassFactory( const QString &className );
	static const DzClassFactory*		findClassFactory( const DzGuid &id );
	static int							getNumClassFactories();
	static const DzClassFactory*		getClassFactory( int idx );
	static void							delayedDelete( DzBase *obj );
	static void							pauseDelayedDelete();
	static void							resumeDelayedDelete();
	static void							deleteAtShutdown( QObject *obj );

	QStringList&						getCommandArguments() const;

signals:

	void	saveStateScript( DzScript &script );
	void	starting();
	void	closing();
	void	styleChanged( DzStyle *newStyle );

	void	debugMsg( const QString &msg );
	void	warningMsg( const QString &msg );
	void	skinChanged();
	void	styleAboutToChange();

	void	multiThreadingChanged( bool onOff );
	void	eventLoopStarted();

private slots:

	void	styleNeedsUpdate();
	void	deleteNext();
	void	appClosing();
	void	doBreadCrumbTrackingSetup();
	
private:

	//
	// MANIPULATORS
	//

	void	storeCommandArguments( int argc, char **argv );
	void	doStartupWizard();
	bool	doStartup( GraphicsMode mode );
	bool	doExec();
	bool	doShutdown();
	void	setHomePath();
	void	setAppDataPath();
	void	setProgramDataPath();
	void	setDocumentsPath();
	bool	parseArguments();
	bool	finishStartup( GraphicsMode mode );
	bool	doUpdateCheck();
	void	createInterface();
	bool	doAppRegistration();

	bool	createManagers();
	void	assignClassFactories();
	void	doStartupScript();
	void	doRunOnceScripts();
	void	doRunOnceDirRecurse(const QString &dir);
	void	checkLogFileSize();
	void	appendToCommandLog( const QString &buffer );
	void	restoreDefaultsInternal( bool copyScript );
	void	loadTranslator();
	void	logStartup();
	void	logCPUID();
	void	logFatal( const QString &msg );
	void	rebuildStyle();
	void	setStyle( DzStyle *style );
	void	clearTempFiles();
	void	clearDir( QDir dir, bool recursive = false );
	void	setPrefixes( const QString &prefixes );
	void	copySettings();
	void	loadApplicationData();
	void	saveApplicationData();
	QString	findUserBreadCrumbTrackingGuid();
	void	doStartupScene();

	DzStyle*	createStyle( const QString &name ) const;
	QStringList	getPrefixes();
	void		findCreatorScenes();
	
	//
	// DATA MEMBERS
	//

	struct	Data; 
	Data	*m_data;
};

class DZ_EXPORT DzLogEvent : public QEvent {
public:
	DzLogEvent( QString statusStr, bool writeToStatus = true );

	QString	getString() const { return m_statusStr; }
	bool	writeToStatus() const { return m_writeToStatus; }

private:

	QString	m_statusStr;
	bool	m_writeToStatus;
};

extern DZ_EXPORT DzApp *dzApp;

#endif // DAZ_APP_H
