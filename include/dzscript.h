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
	Defines the DzScript class.
**/

#ifndef DAZ_SCRIPT_H
#define DAZ_SCRIPT_H

/****************************
	Include files
****************************/

#include <QtScript/QScriptEngine>

#include "dzauthor.h"
#include "dzbase.h"
#include "dzversion.h"

/****************************
	Forward declarations
****************************/

class DzFileFilter;
class DzScriptContext;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzScript : public DzBase {
	Q_OBJECT
	Q_ENUMS( ScriptFileMode )
	Q_ENUMS( ScriptLanguage )
	friend class DzScriptEngine;
public:

	//NOTE: This enum is duplicated in DzSaveFilterMgr for use in scripts!
	enum ScriptFileMode { UseExtension, TextScriptFile, DAZScriptFile, EncDAZScriptFile };

	enum ScriptLanguage { Unknown, DAZScript1, DAZScript2 };

	const static QString s_DAZScriptBinaryExtension;
	const static QString s_DAZScriptEncryptedBinaryExtension;
	const static QString s_DAZScript2TextExtension;
	const static QString s_DAZScript1TextExtension;
	//
	// CREATORS
	//

	DzScript( const QString &name = QString::null );
	DzScript( const DzScript &script );
	virtual ~DzScript();

	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	save( DzOutFile *file ) const;

	//
	// MANIPULATORS
	//

	DzScript		&operator=( const DzScript &script );
	
	static void		addVariableToGlobalObject( QScriptValue &globalObj, const QString &varName,
						QObject *var, QScriptEngine::ValueOwnership = QScriptEngine::QtOwnership );

public slots:

	bool	checkSyntax();
	bool	execute();
	bool	execute( const QVariantList &args );
	bool	call( const QString &function, const QVariantList &args );
	bool	loadFromFile( const QString &filename, bool convert = true );
	bool	getLastStatus();
	void	addCode( const QString &code );
	void	addLine( const QString &line, int indentLevel = 0 );
	void	setCode( const QString &code );
	void	makeEncrypted();
	void	clear();
	void	setContext( DzScriptContext *context );

	bool	convertToDAZScript2();

	//
	// ACCESSORS
	//

	QString			getFilename() const;
	DzError			saveToFile( const QString &filename, ScriptFileMode mode = UseExtension,
						const QString &filetype = "DAZ Script" ) const;
	QString			getCode() const;
	bool			isEmpty() const;
	bool			isEncrypted() const;
	bool			wasConverted( DzScript::ScriptLanguage language = DAZScript1 ) const;
	QVariant		result() const;
	QString			errorMessage() const;
	int				errorLine() const;
	QStringList		stackTrace() const;
	DzVersion		getScriptVersion() const;
	QString			getScriptType() const;
	ScriptLanguage	getScriptLanguage() const;
	DzAuthor		getAuthor() const;

	bool			getShouldReuseInterpreter() const;
	void			setReuseInterpreter( bool onoff );
	
	//
	// STATIC
	//
	
#ifndef Q_MOC_RUN
	static
#endif
	QVariant		evaluate( const QString &code, QObject *context = 0, bool compatibilityMode = false );
#ifndef Q_MOC_RUN
	static
#endif
	bool			isScriptFile( const QString &filename );
#ifndef Q_MOC_RUN
	static
#endif
	bool			isScriptBinaryFile( const QString &filename );
#ifndef Q_MOC_RUN
	static
#endif
	bool			isScriptTextFile( const QString &filename );
#ifndef Q_MOC_RUN
	static
#endif
	bool			isScriptExtension( const QString &ext );
#ifndef Q_MOC_RUN
	static
#endif
	bool			isScriptBinaryExtension( const QString &ext );
#ifndef Q_MOC_RUN
	static
#endif
	bool			isScriptTextExtension( const QString &ext );
#ifndef Q_MOC_RUN
	static
#endif
	QString			getScriptFile( const QString &filenameWithoutExtension );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptOpenExtensionsToFilter( DzFileFilter *filter );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptSaveExtensionsToFilter( DzFileFilter *filter );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptBinaryExtensionsToFilter( DzFileFilter *filter );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptTextExtensionsToFilter( DzFileFilter *filter, bool includeDeprecated = false );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptOpenExtensionsAsMultipleFilters( DzFileFilter *filter );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptSaveExtensionsAsMultipleFilters( DzFileFilter *filter );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptBinaryExtensionsAsMultipleFilters( DzFileFilter *filter );
#ifndef Q_MOC_RUN
	static
#endif
	void			addScriptTextExtensionsAsMultipleFilters( DzFileFilter *filter, bool includeDeprecated = false );
#ifndef Q_MOC_RUN
	static
#endif
	QStringList		getScriptExtensions();
#ifndef Q_MOC_RUN
	static
#endif
	QString			legalizeName( const QString &str );

signals:

	void executeScript( DzScript *script, const QStringList &args );

protected:

	virtual void	prepareGlobalObject( QScriptValue &globalObject ) { }

private:

	static void	doExecute( DzScript *script );
	static bool	doExecuteCompatible( DzScript *script );
	static bool	doExecuteQtScript( DzScript *script );

	bool	hasExecuted();	
	QString	preProcess( const QString &script );
	bool	readAsciiFile( const QString &filename );
	bool	readBinaryFile( const QString &filename );
	void	clearContext();
	void	prepareContext();

	void	scriptDisconnect();
	void	registerConnect( QObject *obj, const QString &val, 
				const QScriptValue &thisObj, const QScriptValue &func );
	void	addInclude( const QString &str );
	bool	hasInclude( const QString &str ) const;
	void	clearIncludes();

	struct	Data;
	Data	*m_data;
};

/**
	@sdk
	Safe cast for objects received from scripting that use DzTSharedPointerScriptWrapper
**/
template <class T>
inline T dz_script_metacast(QObject *object)
{
	const char *className = reinterpret_cast<T>(0)->staticMetaObject.className();
	return reinterpret_cast<T>((object ? object->qt_metacast(className) : 0));
}

/**
	@sdk
	Safe const cast for objects received from scripting that use DzTSharedPointerScriptWrapper
**/
template <class T>
inline T dz_script_metacast(const QObject *object)
{
	const char *className = reinterpret_cast<T>(0)->staticMetaObject.className();
	return reinterpret_cast<T>((object ? const_cast<QObject *>(object)->qt_metacast(className) : 0));
}

#endif // DAZ_SCRIPT_H
