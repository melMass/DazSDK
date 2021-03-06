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
	Defines the DzBase class.
**/

#ifndef DAZ_BASE_H
#define DAZ_BASE_H

/*****************************
	Include files
*****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzClassFactory;
class DzInFile;
class DzOutFile;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBase : public QObject {
	Q_OBJECT
	Q_PROPERTY( QString name READ getName WRITE setName )
public:


	DzBase( QObject *parent = 0, const QString &name = QString::null );
	virtual ~DzBase();

	QString			getName() const;
	virtual void	setName( const QString &newName );

	//
	// MANIPULATORS
	//

	virtual void	startLoad( const DzInFile *file );
	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual DzError	finishLoad( const DzInFile *file );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	setStorablePaths( const QString &path );

	//
	// ACCESSORS
	//

	virtual void			save( DzOutFile *file ) const;
	DzBase*					assertCast( const char *className ) const;
	const DzClassFactory*	getClassFactory() const;

	static void		makePersistent( QObject *obj );

public slots:

	virtual QString	className() const;
	virtual void	makePersistent();
	virtual bool	inherits( const QString &string ) const;

	// deprecated
	bool			iskindof( const QString &clname );
	QString			getName();


signals:

	void			nameChanged( const QString &name );
};

/*****************************
Definitions
*****************************/

template <typename T>
T *DzAssertCast(DzBase *base)
{
	if ( !base )
	{
		return (T*)base;
	}
	T *derived = qobject_cast<T *>(base);
	if (!derived)
	{
		QString message = QString( QObject::tr("Failure to cast DzAssertCast: %1 pointer cannot be cast to %2 pointer") )
			.arg(base->metaObject()->className()).arg(T::staticMetaObject.className());
		throw message;
	}
	return derived;
}
#define DZ_ASSERT_CAST( dzBase, className ) DzAssertCast<className>(dzBase)

#endif // DAZ_BASE_H
