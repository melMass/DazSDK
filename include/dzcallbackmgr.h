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
	Defines the DzCallBackMgr class.
**/

#ifndef DAZ_CALL_BACK_MGR_H
#define DAZ_CALL_BACK_MGR_H

/****************************
	Include files
****************************/

#include "dzscript.h"

class DzCallBackInternal;
/****************************
	Class definitions
****************************/
class DZ_EXPORT DzCallBack : public QObject {
	Q_OBJECT
	friend class DzCallBackMgr;
	friend struct DzCallBackMgrData;
	friend class  DzCallBackInternal;
public slots:

	const QObject*	getSender() const;
	QString			getScript() const;

	bool			isEvaluated();
	
	void			addToGroup( const QString &group );
	void			removeFromGroup( const QString &group );
	void			setScript( const QString &script, bool evaluate );

	void			setProcessAsEvent(bool onOff);
	bool			getProcessAsEvent()const;

	void			setBlockedDuringSceneLoad(bool onOff);
	bool			getBlockedDuringSceneLoad()const;
	
	int				getArgCount() const;
	QVariant		getArg( int i ) const;

	QStringList		getGroups() const;
	bool			setConnection( const QObject *sender, const QString &signal );
	bool			setConnection( const QObject *sender, const QString &signal, bool garbageCollect );
	int				setConnections( const QObject *sender, const QStringList &signalList, bool garbageCollect );
	void			clearConnection();

	bool			event( QEvent *e );
	
private slots:
	//no connections should be made to this slot directly, 
	//only the setConnection and clearConnection should
	//be used.
	void	executeCallBackScript();
	void	senderDestoryed();
	void	sceneLoadStart();
	void	sceneLoadFinish();

protected:
	DzCallBack( const QString &name );
	virtual ~DzCallBack();

	bool	isExecuting();
	void	deleteOnExecutionEnd();	
	bool	isSceneLoading();
	virtual void	executeScriptNoArgs()=0;

	QVariantList	createArgList();

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzCallBackMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
	friend class DzCallBack;
public slots:

	DzCallBack*	createCallBack( const QString &name );
	DzCallBack*	createCallBack( const QString &name, const QString &script, bool eval );

	void		clearAllCallBacks();
	void		deleteCallBack( int index );
	void		deleteCallBack( const QString &name );
	void		deleteCallBackGroup( const QString &name );
	void		deleteCallBack( DzCallBack *callBack );

	DzCallBack*	getCallBack( int index ) const;
	DzCallBack*	getCallBack( const QString &name ) const;
	int			getCallBackIndex( const QString &name ) const;
	int			getNumCallBacks() const;	
	QObjectList	getGroup( const QString &name ) const;
	QObjectList	getCallBackList() const;
	QStringList	getSignalSignature( const QObject *obj, const QString &signalName="" ) const;

private:
	//
	// CREATORS
	//
	DzCallBackMgr();
	~DzCallBackMgr();

private:
	//
	// DATA MEMBERS
	//
	struct	Data;
	Data	*m_data;
};

//this class is intentionally not exported
class DzCallBackScript : public DzScript { 
	Q_OBJECT
public:

	DzCallBackScript( const QObjectList &vars, const QStringList &varNames );
	~DzCallBackScript();

	static void		executeScript( const QString &script, const QStringList &varNames, const QObjectList &vars );	
	static void		evalScript( const QString &evalScript, const QStringList &varNames, const QObjectList &vars );

protected:

	virtual void	prepareGlobalObject( QScriptValue &globalObj );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_CALL_BACK_MGR_H
