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
	Source file for the DzTextInputFile class.
**/

#ifndef DAZ_TEXT_INPUT_FILE_H
#define DAZ_TEXT_INPUT_FILE_H

/*****************************
	Include files
*****************************/

#include <QtCore/QFile>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTextInputFile {
public:
	//
	// CREATORS
	//

	DzTextInputFile( const QString &filename, bool isCompressed = false, bool stripQuotes = true );
	~DzTextInputFile();

	//
	// MANIPULATORS
	//

	bool	open();
	void	close();
	void	setStripQuotes( bool strip );
	void	setShowProgress( bool onOff );

	bool	getLine( char **tokens, int &nTokens );

	//
	// ACCESSORS
	//

	bool	atEnd() const;
	bool	stripQuotes();
	int		size() const;
	QString	name() const;

private:

	//
	// FUNCTIONS
	//

	int		parse( char *str, char **v ) const;

	int		getch();
	void	ungetch( int c );

	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT IDzTextInputFile
{
public:
	virtual ~IDzTextInputFile() { }

	virtual bool	open() = 0;
	virtual void	close() = 0;
	virtual void	setStripQuotes(bool strip) = 0;
	virtual bool	getLine( char **tokens, int &nTokens ) = 0;

	//
	// ACCESSORS
	//

	virtual bool	atEnd() const = 0;
	virtual bool	stripQuotes() = 0;
	virtual int		size() const = 0;
	virtual QString	name() const = 0;
};

// Adapts the concrete class to the interface through delegation.
// Owns the DzTextInputFile passed into its c'tor.
// Do not give it pointers to objects on the stack.
class DZ_EXPORT DzTextInputFileAdapter : public IDzTextInputFile
{
public:
	DzTextInputFileAdapter(DzTextInputFile *inputFile)
		: m_inputFile(inputFile)
	{
	}

	virtual ~DzTextInputFileAdapter()
	{
		delete m_inputFile;
		m_inputFile = 0;
	}

	virtual bool	open() { return m_inputFile->open(); }
	virtual void	close() { m_inputFile->close(); }
	virtual void	setStripQuotes(bool strip) { m_inputFile->setStripQuotes(strip); }
	virtual bool	getLine(char **tokens, int &nTokens) { return m_inputFile->getLine(tokens, nTokens); }
	virtual bool	atEnd() const { return m_inputFile->atEnd(); }
	virtual bool	stripQuotes() { return m_inputFile->stripQuotes(); }
	virtual int		size() const { return m_inputFile->size(); }
	virtual QString	name() const { return m_inputFile->name(); }

private:
	DzTextInputFile*	m_inputFile;
};

#endif DAZ_TEXT_INPUT_FILE_H