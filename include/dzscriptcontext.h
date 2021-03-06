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
	Defines the DzScriptContext class.
**/

#ifndef DAZ_SCRIPT_CONTEXT_H
#define DAZ_SCRIPT_CONTEXT_H

/****************************
	Include files
****************************/

#include <QtCore/QVariant>

#include "dzauthor.h"

/****************************
	Forward declarations
****************************/

class DzScript;
class QDesktopWidget;
class QScriptEngine;
class QScriptValue;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzScriptContext : public QObject {
	Q_OBJECT
	friend class DzScript;
	friend struct DzScriptData;
public:
	DzScriptContext();
	virtual ~DzScriptContext();

	virtual void	buildContext( QScriptEngine *engine, QScriptValue &globalObject ) const;

public slots:

	void			beginUndo();
	void			cancelUndo();
	void			acceptUndo( const QString &caption );
	void			clearUndoStack();

	void			setBusyCursor();
	void			clearBusyCursor();

	void			startProgress( const QString &info, int totalSteps = 0, bool isCancellable = false,
						bool showTimeElapsed = false );
	void			stepProgress( int numSteps = 1 );
	void			updateProgress( int position );
	void			finishProgress();
	bool			progressIsCancelled() const;
	bool			progressIsActive() const;

	void			startBackgroundProgress( const QString &info, int totalSteps = 0, bool isCancellable = false );
	void			stepBackgroundProgress( int numSteps = 1 );
	void			updateBackgroundProgress( int position );
	void			finishBackgroundProgress();
	bool			backgroundProgressIsCancelled() const;
	bool			backgroundProgressIsActive() const;

	QString			getScriptFileName() const;
	DzAuthor		getScriptAuthor() const;
	QString			getScriptVersionString() const;
	QString			getScriptType() const;

	QObject*		getObjectParent( QObject *obj ) const;
	bool			pointersAreEqual( const QObject *ptr1, const QObject *ptr2 ) const { return (ptr1 == ptr2); }

	bool			shiftPressed() const;
	bool			ctrlPressed() const;

	QDesktopWidget*	getDesktop() const;
	QString			getErrorMessage( int errCode );
	void			processEvents();
	void			makePersistent( QObject *obj );
	QVariantList	getArguments() const;

private:
	DzScriptContext( DzScript *script );

	void	setScript( DzScript *script );
	void	setArgs( const QVariantList &args );
	void	clearExecution();
	void	prepareExecution();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SCRIPT_CONTEXT_H