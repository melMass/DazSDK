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
	Defines the DzOptionsFrame class.
**/

#ifndef DAZ_OPTIONS_FRAME_H
#define DAZ_OPTIONS_FRAME_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class DzRenderOptions;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzOptionsFrame : public QFrame {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzOptionsFrame( const QString &label, QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzOptionsFrame();

	QString	getLabel() const { return m_label; }
	bool	isUpdated() { return m_updated; }
	void	updated( bool status ) { m_updated = status; }

public slots:

	virtual void	applyChanges() = 0;
	virtual void	resetOptions() = 0;
	virtual bool	applyValid() const { return true; }
	virtual void	restoreOptions( DzRenderOptions *options ) { }

signals:

	void	optionsChanged();

private:

	QString	m_label;
	bool	m_updated;
};

#endif // DAZ_OPTIONS_FRAME_H


