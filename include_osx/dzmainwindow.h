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
	Defines the DzMainWindow class.
**/

#ifndef DAZ_MAIN_WINDOW_H
#define DAZ_MAIN_WINDOW_H

/*****************************
	Include files
*****************************/

#include <QtGui/QMainWindow>

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzActionMgr;
class DzAutoHideTabBar;
class DzDockArea;
class DzDockDragWindow;
class DzFileFilter;
class DzPaneMgr;
class DzScript;
class DzShape;
class DzShutDownCheck;
class DzUIPopUpWgt;
class DzVideoClip;
class DzViewportMgr;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMainWindow : public QMainWindow {
	Q_OBJECT
	Q_PROPERTY( bool alwaysOnTop READ isAlwaysOnTop WRITE setAlwaysOnTop )
	Q_PROPERTY( bool toolTipsEnabled READ toolTipsEnabled WRITE setToolTipsEnabled )
	friend class DzApp;
	friend class DzMainWindowStatus;
private:
	//
	// CREATORS
	//

	DzMainWindow( QWidget *parent, bool askForSaveOnClose = true );
	~DzMainWindow();

public:
	DzError			startup();
	virtual bool	eventFilter( QObject *watched, QEvent *e );
	void			addShutDownCheck( DzShutDownCheck *check );
	
	bool			isAlwaysOnTop() const;
	void			setAlwaysOnTop( bool onOff );
	bool			toolTipsEnabled() const;
	void			setToolTipsEnabled( bool value );

	DzAutoHideTabBar*	getAutoHideTabBar( DzLocation loc ) const;
	DzDockDragWindow*	getDragWindow() const;

	static void		saveWindowGeometryState( QWidget *widget );
	static void		restoreWindowGeometryState( QWidget *widget );
	static void		ensureWindowOnScreen( QWidget *widget );

public slots:

	bool	doDirectoryDialog( const QString &caption, QString &dir,
				QWidget *parent = 0 );
	bool	doFileDialog( bool open, const QString &title, const QString &startWith,
				const DzFileFilter &fileFilter, QString &filename,
				int *selectedFilter = NULL, QWidget *parent = 0 );
	bool	doOpenFilesDialog( const QString &title, const QString &startWith,
				const DzFileFilter &fileFilter, QStringList &filenames,
				int *selectedFilter = NULL, QWidget *parent = 0 );
	bool	doFileDialog( bool open, const QString &title, const QString &startWith,
				const DzFileFilter *fileFilter, QString &filename,
				int *selectedFilter = NULL, QWidget *parent = 0 );
	bool	doOpenFilesDialog( const QString &title, const QString &startWith,
				const DzFileFilter *fileFilter, QStringList &filenames,
				int *selectedFilter = NULL, QWidget *parent = 0 );
	void	displayPrompt( const QString &msg, int millisec = -1 );
	void	removePrompt();
	void	repaintActive3DViewport();
	bool	doImageDialog( bool open, QString &filename, QWidget *parent = 0,
					const QString &startWith = QString::null );
	bool	doTextureFolderDialog( QString &filename, QWidget *parent = 0, 
					const QString &startWith = QString::null );
	bool	doVideoClipSaveDialog( QString &filename, QWidget *parent = 0, 
					const QString &startWith = QString::null );
	bool	doAudioClipOpenDialog( QString &filename, QWidget *parent = 0,
					const QString &startWith = QString::null );
	bool	doFileOpen( QWidget *parent = 0 );
	bool	doFileMerge( QWidget *parent = 0 );
	bool	doFileSave( QWidget *parent = 0 );
	bool	doFileSaveAs( QWidget *parent = 0, const QString &startWith = QString::null );
	bool	doFileSaveAs( QString &finalFileName, QWidget *parent = 0, const QString &startWith = QString::null );
	bool	doDAZSave( QWidget *parent = 0 );
	bool	doDAZSaveAs( QWidget *parent = 0, const QString &startWith = QString::null );
	bool	doDAZSaveAs( QString &finalFileName, QWidget *parent = 0, const QString &startWith = QString::null );
	bool	doFileImport( QWidget *parent = 0 );
	bool	doGeometryImport( DzShape **shape, QWidget *parent = 0 );
	bool	doFileExport( QWidget *parent = 0 );
	QImage	doImageOpen( QWidget *parent = 0 );
	bool	doImageSaveAs( const QImage &image, QWidget *parent = 0 );
	bool	doImageSaveAs( const QImage &image, QString &filename, QWidget *parent = 0 );
	bool	doVideoClipSaveAs( const DzVideoClip *clip, QWidget *parent = 0 );
	bool	doNewFile();
	bool	askSaveChanges();
	bool	askTurnOffLimits();
	bool	checkExistingFile( const QString &name );
	void	goFullScreen();
	void	exitFullScreen();


	bool	isUILocked() const;
	void	restoreUILockState();
	void	setUILocked( bool onOff, bool storeSetting = true );

	void			clearUIPopUp();
	DzUIPopUpWgt*	getUIPopUp();
	DzUIPopUpWgt*	showUIPopUpWgt( const QString &filename, QWidget *posWgt=NULL );
	DzUIPopUpWgt*	toggleUIPopUpWgt( const QString &filename, QWidget *posWgt=NULL );
	void			positionUIPopUp( QWidget *posWgt );

	//
	// ACCESSORS
	//

	DzDockArea*		getTopDockArea() const;
	DzDockArea*		getBottomDockArea() const;
	DzDockArea*		getLeftDockArea() const;
	DzDockArea*		getRightDockArea() const;
	DzDockArea*		dockArea( const QPoint &pos ) const;
	DzViewportMgr*	getViewportMgr() const;
	DzActionMgr*	getActionMgr() const;
	DzPaneMgr*		getPaneMgr() const;

signals:

	void	started();
	void	aboutToClose();
	void	alwaysOnTopChanged( bool onOff );
	void	uiLockedChanged();

protected:
	//
	// REIMPLEMENTATIONS
	//

	virtual void	dragEnterEvent( QDragEnterEvent *event );
	virtual void	dropEvent( QDropEvent *event );
	virtual void	closeEvent( QCloseEvent *e );
	virtual void	showEvent( QShowEvent *event );
	virtual void	resizeEvent( QResizeEvent *event );

private slots:

	void	updateCaption( const QString &filename );
	void	saveState( DzScript &script );

private:

	void			displayError( const QString &msg );
	DzUIPopUpWgt*	showUIPopUpWgtWithUiFile( const QString &filename, QWidget *posWgt );
	DzUIPopUpWgt*	showUIPopUpWgtWithScriptFile( const QString &filename, QWidget *posWgt );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MAIN_WINDOW_H
