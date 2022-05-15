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
	Defines the DzUndoStack class.
**/

#ifndef DAZ_UNDO_STACK_H
#define DAZ_UNDO_STACK_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QString;
class DzUndoList;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzUndoStackHold {
public:
	DzUndoStackHold();
	~DzUndoStackHold();

	void	accept( const QString &caption );
	void	drop();
	void	cancel();

private:

	bool	m_needRelease;
};

class DZ_EXPORT DzUndoStackLock {
public:
	DzUndoStackLock();
	virtual ~DzUndoStackLock();

	void	lock();
	void	unlock();
	bool	isLocked()const;

private:
	bool	m_isLocked;
};


class DZ_EXPORT DzUndoItem {
public:
	//
	// CREATORS
	//

	virtual ~DzUndoItem() { }

	//
	// MANIPULATORS
	//

	virtual void	undo() = 0;
	virtual void	redo() { undo(); }
	virtual int		size() const { return 1; }
};


class DZ_EXPORT DzUndoStack : public QObject {
	Q_OBJECT
	friend class DzApp;
private:
	//
	// CREATORS
	//

	DzUndoStack( int maxStackDepth = 20 );
	~DzUndoStack();

public slots:
	bool	push( DzUndoItem *item );
	void	beginHold();

	void	accept( const QString &caption );
	void	drop();
	void	cancel();
	bool	undo();
	bool	redo();
	void	clearAll();
	void	lock();
	void	unlock();

	//
	// ACCESSORS
	//

	bool	hasItems() const;
	int		getNumItems() const;
	int		getNumUndoItems() const;
	int		getNumRedoItems() const;
	QString	getUndoCaption() const;
	QString	getRedoCaption() const;
	bool	canPushItems() const;
	bool	canUndo() const;
	bool	canRedo() const;
	bool	isInUndoRedo() const;

signals:
	void	undoAvailable( bool yesNo );
	void	redoAvailable( bool yesNo );
	void	undoCaptionChanged( const QString &caption );
	void	redoCaptionChanged( const QString &caption );

private:
	struct	Data;
	Data	*m_data;
};

extern DZ_EXPORT DzUndoStack *dzUndoStack;

#endif // DAZ_UNDO_STACK_H
