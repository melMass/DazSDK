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
	Defines the DAZ Studio Drag and Drop classes.
**/

#ifndef DAZ_DRAG_OBJECTS_H
#define DAZ_DRAG_OBJECTS_H

/****************************
	Include files
****************************/
#include <QtCore/QMimeData>

#include "dztypes.h"
#include "dztarray.h"

/****************************
	Forward declarations
****************************/

class DzPane;
class QMimeSource;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzMimeData : public QMimeData {
public:
	DzMimeData();

protected:

	static void		encodeShort( QByteArray &bytes, short val );
	static void		encodeUShort( QByteArray &bytes, unsigned short val );
	static void		encodeInt( QByteArray &bytes, int val );
	static void		encodeUInt( QByteArray &bytes, unsigned int val );
	static void		encodeString( QByteArray &bytes, const QString &str );

	template <class T>
	static void			encodePtr( QByteArray &bytes, const T *val );
	template <class T>
	static void			encodePtrList( QByteArray &bytes, const QList<T*> &list );
	template <class T>
	static void			encodePtrList( QByteArray &bytes, const QList< DzTSharedPointer<T> > &list );

	static short			decodeShort( QByteArray &bytes );
	static unsigned short	decodeUShort( QByteArray &bytes );
	static int				decodeInt( QByteArray &bytes );
	static unsigned int		decodeUInt( QByteArray &bytes );
	static QString			decodeString( QByteArray &bytes );

	template <class T>
	static T*			decodePtr( QByteArray &bytes );
	template <class T>
	static void			decodePtrList( QByteArray &bytes, QList<T*> &list );
	template <class T>
	static void			decodePtrList( QByteArray &bytes, QList< DzTSharedPointer<T> > &list );

private:
	static void		encodeVal( QByteArray &bytes, const void *val, int size );
	static bool		decodeVal( QByteArray &bytes, void *val, int size );
};

class DZ_EXPORT DzNodeListDrag : public DzMimeData {
public:
	DzNodeListDrag( const DzNodeList &nodeList );

	static QByteArray	encode( const DzNodeList &nodeList );
	static void			decode( const QMimeData *src, DzNodeList &nodeList );

	static const QString	s_mimeType;
};

class DZ_EXPORT DzPropertyListDrag : public DzMimeData {
public:
	DzPropertyListDrag( const DzPropertyList &propertyList );

	static QByteArray	encode( const DzPropertyList &propList );
	static void			decode( const QMimeData *src, DzPropertyList &propList );
	static bool			decode( const QMimeSource *src, DzPropertyList &propList );

	static const QString	s_mimeType;
};

class DZ_EXPORT DzPropertyGroupListDrag : public DzMimeData {
public:
	DzPropertyGroupListDrag( const DzPropertyGroupList &propGroupList );

	static QByteArray	encode( const DzPropertyGroupList &propGroupList );
	static void			decode( const QMimeData *src, DzPropertyGroupList &propGroupList );
	static bool			decode( const QMimeSource *src, DzPropertyGroupList &propGroupList );

	static const QString	s_mimeType;
};

class DZ_EXPORT DzContentFileDrag : public DzMimeData {
public:

	DzContentFileDrag( const DzContentFile *contentFile );

	static QByteArray		encode( const DzContentFile *contentFile );
	static DzContentFile	*decode( const QMimeData *src );

	static const QString	s_mimeType;
};

class DZ_EXPORT DzPaneDrag : public DzMimeData {
public:

	DzPaneDrag( const DzPane *pane );

	static QByteArray	encode( const DzPane *pane );
	static DzPane*		decode( const QMimeData *src );

	static const QString	s_mimeType;
};

class DZ_EXPORT DzContentCategoryDrag : public DzMimeData {
public:

	DzContentCategoryDrag( QList<int> &categoryIndexList );

	static QByteArray	encode( QList<int> &categoryIndexList );
	static void			decode( const QMimeData *src, QList<int> &categoryIndexList );

	static const QString	s_mimeType;
};

class DZ_EXPORT DzContentLocation{
public:
	quint32 m_databaseItemIndex;
	quint32 m_databaseCategoryIndex;
	quint32 m_folderType;
	QString m_fileName;
	QString m_folderPath;
};

typedef DzTArray<DzContentLocation> ContentLocationList;

class DZ_EXPORT DzContentListDrag : public DzMimeData {
public:

	DzContentListDrag( const ContentLocationList &contentList );

	static QByteArray	encode( const ContentLocationList &contentList );
	static void			decode( const QMimeData *src, ContentLocationList &contentList );

	static const QString	s_mimeType;
};

/****************************
	Template functions
****************************/

template <class T>
void DzMimeData::encodePtr( QByteArray &bytes, const T *val )
{
	encodeVal( bytes, &val, sizeof( T* ) );
}

template <class T>
void DzMimeData::encodePtrList( QByteArray &bytes, const QList<T*> &list )
{
	encodeInt( bytes, list.count() );

	QListIterator<T*>	listIt( list );

	while( listIt.hasNext() ){
		T	*val = listIt.next();
		encodeVal( bytes, &val, sizeof( T* ) );
	}
}

template <class T>
void DzMimeData::encodePtrList( QByteArray &bytes, const QList< DzTSharedPointer<T> > &list )
{
	encodeInt( bytes, list.count() );

	QListIterator< DzTSharedPointer<T> >	listIt( list );

	while( listIt.hasNext() ){
		T	*val = listIt.next();
		encodeVal( bytes, &val, sizeof( T* ) );
	}
}

template <class T>
T* DzMimeData::decodePtr( QByteArray &bytes )
{
	T	*val;

	if( !decodeVal( bytes, &val, sizeof( T* ) ) )
		return NULL;

	return val;
}

template <class T>
void DzMimeData::decodePtrList( QByteArray &bytes, QList<T*> &list )
{
	int	nVals = decodeInt( bytes );

	for( int i = 0; i < nVals; i++ ){
		T*	val;
		if( !decodeVal( bytes, &val, sizeof( T* ) ) )
			return;
		list.append( val );
	}
}

template <class T>
void DzMimeData::decodePtrList( QByteArray &bytes, QList< DzTSharedPointer<T> > &list )
{
	int	nVals = decodeInt( bytes );

	for( int i = 0; i < nVals; i++ ){
		T*	val;
		if( !decodeVal( bytes, &val, sizeof( T* ) ) )
			return;
		list.append( val );
	}
}

#endif // DAZ_DRAG_OBJECTS_H
