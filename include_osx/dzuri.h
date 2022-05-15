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
	Defines the DzUri class.
**/

#ifndef DAZ_URI_H
#define DAZ_URI_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"
#include "dzversion.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzUri {
public:

	enum SchemeType { NoScheme, ID, Name };
	enum PartFlag {
		NoPart =		0x00,
		Scheme =		0x01,
		NodePath =		0x02,
		ModifierPath =	0x04,
		PropertyPath =	0x08,
		IDPart =		0x10,
		FilePath =		0x20,
		AllParts =		0xff
	};
	Q_DECLARE_FLAGS( PartFlags, PartFlag )

	DzUri();
	explicit DzUri( const QString &uri );
	DzUri( const DzUri &uri );
	~DzUri();

	bool	operator==( const DzUri &uri ) const;
	bool	operator!=( const DzUri &uri ) const;
	DzUri&	operator=( const DzUri &uri );

	QStringList	getNodePath() const;
	QStringList	getModifierPath() const;
	QString		getFilePath() const;
	QStringList	getPropertyPath() const;
	QString		getId() const;
	SchemeType	getSchemeType()const;

	DzVersion	getFileVersion()const;
	void		setFileVersion(const DzVersion& version);
	
	bool	isEmpty() const;
	QString	toString() const;
	QString	toString( PartFlags flags ) const;
	QString	toLocalFilename() const;

	void	clear();
	void	detach();
	void	setUri( const QString &uri );

	void	setNodePath( const QStringList &nodePath );
	void	setModifierPath( const QStringList &modPath );
	void	setFilePath( const QString &filePath );
	void	setPropertyPath( const QStringList &propertyPath );
	void	setId( const QString &id );
	void	setSchemeType( SchemeType type );

	static DzUri		fromLocalFilename( const QString &filePath );
	static QString		escape( const QString &str, const QByteArray &exclude, const QByteArray &include );
	static QString		unescape( const QString &str );
	static QStringList	unescapePath( const QString& path );
	static QString		escapedPath(QStringList list, const QByteArray &exclude, const QByteArray &include );

	void*	internalData()const;
private:

	struct	Data;
	Data	*m_data;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(DzUri::PartFlags);

#endif // DAZ_URI_H
