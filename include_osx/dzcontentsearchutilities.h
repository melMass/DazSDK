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

#ifndef DAZ_CONTENT_SEARCH_THREADS_H
#define DAZ_CONTENT_SEARCH_THREADS_H

/*****************************
	Include files
*****************************/

#include <QtCore/QThread>

#include "dzproductassetcontainer.h"
#include "dztoplevelassetcontainer.h"
#include "dzdbcontenttable.h"
#include "dzdbcontentfolderstable.h"

/*****************************
	Forward declarations
*****************************/

class DzContentSearchOptions;
class DzDBContentFoldersTable;
class DzDBContentTable;
class DzDBCriteria;
class DzDBSelect;
class IDzObjectDatabase;
class QScriptValue;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSearchThreadHelper : public QObject
{
	Q_OBJECT
public:
	DzSearchThreadHelper();
	virtual ~DzSearchThreadHelper();

	void	setToQuit();
	bool	quit();
	void	stepProgress();
	void	busyProgress( bool onOff );
	void	setWidth( int width );

signals:
#ifndef Q_MOC_RUN
public:
#endif
	void	insertAsset( const DzAssetPtr asset );
	void	insertAssets( const DzAssetList &assets );
	void	insertContainer( const DzProductAssetContainerPtr &container );
	void	setProgressRange( int min, int max );
	void	finish();
	void	setProgressValue( int val );
	void	setCurrentContainer( const DzAbstractAssetContainerPtr &cur );

private:
	struct	Data;
	Data* m_data;
};

inline bool static dzCaseInsensitiveLessThanForFileStrings(const QString &s1, const QString &s2)
{
	return QString::compare(s1 ,s2, Qt::CaseInsensitive) < 0;
}

inline bool static dzContentInstanceLessThanFunction( const DzDBContentInstanceTablePtr& ptr1, const DzDBContentInstanceTablePtr& ptr2 )
{
	return dzCaseInsensitiveLessThanForFileStrings ( (ptr1 ? ptr1->getFilename() : QString()), 
		(ptr2 ? ptr2->getFilename() : QString()) );
}

inline bool static dzContentFoldersLessThanFunction( const DzDBContentFoldersTablePtr& ptr1, const DzDBContentFoldersTablePtr& ptr2 )
{
	return dzCaseInsensitiveLessThanForFileStrings ( (ptr1 ? ptr1->getContentFolderName() : QString()), 
		(ptr2 ? ptr2->getContentFolderName() : QString()) );
}

class DZ_EXPORT DzSearchFolder : public QObject, public DzRefCountedItem
{
	Q_OBJECT
public:
	DzSearchFolder( DzDBContentFoldersTable *folder, const QStringList &filter );
	virtual ~DzSearchFolder();
	void	search( DzSearchThreadHelper *helper ) const;
	void	setMatchExp( const QRegExp &reg );
	void	setCleanOrphans( bool onOff );
	void	addStepFolder();
	int		stepCount() const;
	void	setIsStudioRoot( bool onOff );

private:
	void searchRecurse( DzDBContentFoldersTable *folder, const QString &dir, DzSearchThreadHelper *helper, int depth ) const;

protected:
	virtual void	handleFile( DzDBContentFoldersTable *folder, const QString &path, DzSearchThreadHelper *helper ) const;
	virtual void	handleFiles( const QStringList &fileList, DzDBContentFoldersTable *folder, DzSearchThreadHelper *helper ) const;
	QStringList		getFileFilters() const;
	virtual void	handleFoldersAndClean( const QStringList &fileList, DzDBContentFoldersTable *folder, 
						DzSearchThreadHelper *helper, const QString &fullPath, int depth ) const;
private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzScanFolder : public DzSearchFolder
{
	Q_OBJECT
public:
	DzScanFolder( DzDBContentFoldersTable *folder, const QStringList &filter, bool markFound, bool placeUncategorizedInUnassigned, bool placeOnlyNewInCategories );
	virtual ~DzScanFolder();

protected:
	virtual void	handleFile( DzDBContentFoldersTable *folder, const QString &filename, DzSearchThreadHelper *helper ) const;
	virtual void	handleFiles( const QStringList &fileList, DzDBContentFoldersTable *folder, DzSearchThreadHelper *helper ) const;
private:
	void	addToCategory( DzDBContentTable *tab, const QString &relPath ) const;

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzSearchFolder> DzSearchFolderPtr;
typedef DzTSharedPointer<DzScanFolder> DzScanFolderPtr;
typedef QList<DzSearchFolderPtr> DzSearchFolderPtrList;
typedef QListIterator<DzSearchFolderPtr> DzSearchFolderPtrIterator;

class DZ_EXPORT DzSearchFileThread : public QThread
{
	Q_OBJECT
public:
	DzSearchFileThread();
	virtual ~DzSearchFileThread();
	virtual void run();
	void	addFolder( DzSearchFolderPtr folder );
	void	clearFolders();
	void	setContainer( DzSearchContainerPtr con );
	void	stopSearch();
	void	setMatchExp( const QRegExp &exp );
	void	setProgressObject( QObject *obj );
	void	setFinishObject( QObject *obj );
	void setCleanOrphansOnFinish( bool onOff);

private:
	void cleanOrphans();

	struct	Data;
	Data* m_data;
};

class DZ_EXPORT DzSearchDBThread : public QThread
{
	Q_OBJECT
public:
	DzSearchDBThread();
	virtual ~DzSearchDBThread();
	virtual void run();

	void	setContainer( DzSearchContainerPtr con );
	void	stopSearch();
	void	setProgressObject( QObject *obj );
	void	setFinishObject( QObject *obj );
	void	setChunkingSize( int size );
	void	setInstanceCriteria( const DzDBCriteria &crit );
	void	setDB( IDzObjectDatabase *db );

private:
	void doSearch();
private:
	struct	Data;
	Data*	m_data;
};

class DZ_EXPORT DzSerialAssetSearchDBThread : public QThread
{
	Q_OBJECT
public:
	DzSerialAssetSearchDBThread();
	virtual ~DzSerialAssetSearchDBThread();
	virtual void	run();

	void	stopSearch();
	void	setProgressObject( QObject *obj );
	void	setFinishObject( QObject *obj );
	void	setChunkingSize( int size );
	void	addSelect( DzSearchContainerPtr con, const DzDBSelect &sel );
	void	setDB( IDzObjectDatabase *db );
	void	clear();
	bool	isEmpty();

private:
	void	doSearch();
	void	doSearch( const DzDBSelect &sel );

private:
	struct	Data;
	Data*	m_data;
};

class DZ_EXPORT DzProductSearchDBThread : public QThread
{
	Q_OBJECT
public:
	DzProductSearchDBThread();
	virtual ~DzProductSearchDBThread();
	virtual void run();

	void	setContainer( DzProductHolderContainerPtr con );
	void	stopSearch();
	void	setProgressObject( QObject *obj );
	void	setFinishObject( QObject *obj );
	void	setChunkingSize( int size );
	void	setInternalSelect( const DzDBSelect &sel );
	void	setDB( IDzObjectDatabase *db );
	void setSearchTerm( const QString &searchTerm );

	static void buildProductKeywordSelectFromTerm( DzDBSelect &keywrdSel, const QString &term );
	static void buildCategoryKeywordSelectFromTerm( DzDBSelect& keywrdSel, const QString &term );

private:
	void	doSearch();
private:
	struct	Data;
	Data* m_data;
};

class DZ_EXPORT DzProductSearchStoreThread : public QThread
{
	Q_OBJECT
public:
	DzProductSearchStoreThread();
	virtual ~DzProductSearchStoreThread();
	virtual void run();

	void	setContainer( DzProductHolderContainerPtr con );
	void	stopSearch();
	void	setProgressObject( QObject *obj );
	void	setFinishObject( QObject *obj );
	void	setChunkingSize( int size );
	void	setSearchTerm( const QString &searchTerm );
	void	setOptions( DzContentSearchOptions *options );

private:
	void	doSearch();

	double	doubleFromScriptValue( QScriptValue &val, QString prop );
	QString	stringFromScriptValue( QScriptValue &val, QString prop );
	int		doOneSearch( int curOffset );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzProductSyncThread : public QThread
{
	Q_OBJECT
public:
	DzProductSyncThread();
	virtual ~DzProductSyncThread();
	virtual void run();

	void	setProduct( DzDBProductTable *product );
	void	stopSearch();
	void	setProgressObject( QObject *obj );
	void	setFinishObject( QObject *obj );
private:
	void	doSearch();

	QString	getAbsDirectoryForSupportFile( DzDBProductTable *curProd, QString supportFile );
	bool	hasImageFile( const QString &absSupportPath );

private:
	struct	Data;
	Data*	m_data;
};


#endif //DAZ_CONTENT_SEARCH_THREADS_H