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
	Defines the DzFileProperty class.
**/

#ifndef DAZ_FILE_PROPERTY_H
#define DAZ_FILE_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzstringproperty.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFileProperty : public DzStringProperty {
	Q_OBJECT
	Q_ENUMS( FileType )
public:
	//
	// CREATORS
	//

	DzFileProperty();
	DzFileProperty( const QString &name, bool isUserProperty );
	virtual ~DzFileProperty();
	enum FileType { FileSave = 0, FileOpen = 1, Dir = 2 };
	//
	// REIMPLEMENTATIONS
	//

	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		save( DzOutFile *file ) const;
	virtual void		postLoadFile( const DzInFile *file );
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();
	virtual void		copyFrom( DzProperty *prop );
	virtual QString		getWidgetClass(bool styled=true) const;
	virtual DzProperty*	createAlias();
	virtual DzProperty*	duplicate()const;

	virtual DzPropertyClipboard*	copyToClipboard() const;

public slots:

	virtual void		setFilter( const QString &filter );
	virtual QString		getFilter() const;
	virtual FileType	getType() const;
	virtual void		setType( int type );
	virtual QString		getAbsolutePath( const QString &path ) const;
	virtual void		getAttributes( DzPropertySettings &settings ) const;
	void				getAttributes( DzPropertySettings *settings ) const;
	virtual void		setAttributes( const DzPropertySettings &settings );
	void				setAttributes( const DzPropertySettings *settings );

signals:
#ifndef Q_MOC_RUN
private:
#endif
	void filterChanged();

protected slots:
	void emitFilterChanged();

protected:
	DzFileProperty( const DzFileProperty* fprop );
	struct	Data;
};

class DZ_EXPORT DzFilePropertyClipboard : public DzPropertyClipboard {
	Q_OBJECT
	friend class DzFileProperty;
public:
	virtual ~DzFilePropertyClipboard();

public slots:
	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzFilePropertyClipboard( const DzFileProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FILE_PROPERTY_H
