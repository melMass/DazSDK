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
	Defines the DzAction class.
**/

#ifndef DAZ_ACTION_H
#define DAZ_ACTION_H

/****************************
	Include files
****************************/

#include <QtGui/QAction>
#include <QtGui/QStyle>

#include "dzgeneraldefs.h"

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzAction : public QAction {
	Q_OBJECT
	Q_PROPERTY( QString description READ getDescription WRITE setDescription )
	Q_PROPERTY( QString iconFile READ getIconFile WRITE setIcon )
	Q_PROPERTY( QString actionGroup READ getActionGroup )
	Q_PROPERTY( QString defaultMenu READ getDefaultMenuPath )
	Q_PROPERTY( QString defaultToolBar READ getDefaultToolBar )
	Q_PROPERTY( QString defaultShortcut READ getDefaultShortcut )
	friend class DzActionMgr;
protected:
	//
	// CREATORS
	//

	DzAction( const QString &text = QString::null, const QString &desc = QString::null );
	virtual ~DzAction();

public slots:

	//
	// MANIPULATORS
	//

	void	setOff( bool onOff );

public:

	void	setDescription( const QString &description );
	void	setIcon( QStyle::StandardPixmap pix );
	void	setIcon( const QString &file );

	//
	// ACCESSORS
	//

	QString					getDescription() const;
	QStyle::StandardPixmap	getIcon() const;
	QString					getIconFile() const;
	virtual QString			getActionGroup() const;
	virtual QString			getDefaultMenuPath() const;
	virtual QString			getDefaultToolBar() const;
	virtual QKeySequence	getDefaultAccel() const;
	QString					getDefaultShortcut() const;

	void	setShowTextWithIcon(bool onOff);
	bool	getShowTextWithIcon() const;

signals:

	void	enabled( bool onOff );

protected:

	virtual void	init();
	virtual void	styleChange();
	QString			toolTipAcceleratorText() const;
	void			setToolTipWithAcceleratorText(QString tipText);

	virtual void	updateInlineHelp();

protected slots:

	virtual void	executeAction();
	virtual void	toggleAction( bool onOff );

private:

	void	updateIcon();

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzViewToolAction : public DzAction {
	Q_OBJECT
protected:

	DzViewToolAction( const char *toolClassName );
	virtual ~DzViewToolAction();

	virtual void	toggleAction( bool onOff );

public:

	virtual QString	getActionGroup() const;
	virtual QString	getDefaultMenuPath() const;
	virtual QString	getDefaultToolBar() const;

public slots:

	QString			getToolClassName() const;

private slots:

	void	toolActivated();
	void	toolDeactivated();

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzSaveFilterAction : public DzAction {
	Q_OBJECT
protected:

	DzSaveFilterAction( const char *filterClassName );
	virtual ~DzSaveFilterAction();

	void	executeAction();

public:

	virtual QString	getActionGroup() const;
	virtual QString	getDefaultMenuPath() const;

	QString			getFilterClassName() const;

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzAssetIOFilterAction : public DzAction {
	Q_OBJECT
protected:

	DzAssetIOFilterAction( const char *filterClassName );
	virtual ~DzAssetIOFilterAction();

	void	executeAction();

public:

	virtual QString	getActionGroup() const;
	virtual QString	getDefaultMenuPath() const;

	QString			getFilterClassName() const;

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPaneAction : public DzAction {
	Q_OBJECT
protected:

	DzPaneAction( const char *paneClassName );
	virtual ~DzPaneAction();

	virtual void	toggleAction( bool onOff );
	virtual void	init();

public:

	virtual QString	getActionGroup() const;
	virtual QString	getDefaultMenuPath() const;

public slots:

	QString	getPaneClassName() const;
	void	labelChanged( const QString &newLabel );

private slots:

	void	updateVisibility( bool onOff );

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzCreateItemAction : public DzAction {
	Q_OBJECT
protected:

	DzCreateItemAction( const QString &text = QString::null, const QString &desc = QString::null );
	virtual ~DzCreateItemAction();

public:

	virtual QString	getActionGroup() const;
	virtual QString	getDefaultMenuPath() const;
};

class DZ_EXPORT DzEditAction : public DzAction {
	Q_OBJECT
protected:

	DzEditAction( const QString &text = QString::null, const QString &desc = QString::null );
	virtual ~DzEditAction();

public:

	virtual QString	getActionGroup() const;
	virtual QString	getDefaultMenuPath() const;
};

class DZ_EXPORT DzSaveAsSupportAction : public DzAction {
	Q_OBJECT
protected:
	DzSaveAsSupportAction(const QString &text = QString::null, const QString &desc = QString::null);
	virtual ~DzSaveAsSupportAction();

public:

	virtual QString	getActionGroup() const;
	virtual QString	getDefaultMenuPath() const;
};
#endif // DAZ_ACTION_H
