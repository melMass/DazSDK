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
	Defines the DzAssetMetadata class.
**/

#ifndef DAZ_ASSET_METADATA_H
#define DAZ_ASSET_METADATA_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward declare
*****************************/

class DzAsset;
class DzDBContentInstanceTable;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzAssetMetadata : public QObject 
{
	Q_PROPERTY( QString originalPath READ getOriginalPath WRITE setOriginalPath )
	Q_PROPERTY( QString originalFilename READ getOriginalFilename WRITE setOriginalFilename )
	Q_PROPERTY( int type READ getType WRITE setType )
	Q_PROPERTY( QString keywords READ getKeywords WRITE setKeywords )
	Q_PROPERTY( QString userKeywords READ getUserKeywords WRITE setUserKeywords )
	Q_PROPERTY( QString description READ getDescription WRITE setDescription )
	Q_PROPERTY( bool newItem READ isNewItem WRITE setIsNewItem )
	Q_PROPERTY( int audience READ getAudience WRITE setAudience )
	Q_PROPERTY( quint32 compatibilityBase READ getCompatibilityBase WRITE setCompatibilityBase )
	Q_OBJECT

public:
	DzAssetMetadata( DzAsset *owner = NULL );
	virtual ~DzAssetMetadata();

	QString	getOriginalPath() const;
	void	setOriginalPath( const QString &path );

	QString	getOriginalFilename() const;
	void	setOriginalFilename( const QString &filename );

	int		getType() const;
	void	setType( int type );
	
	QString	getKeywords() const;
	void	setKeywords( const QString &keywords );

	QString	getUserKeywords() const;
	void	setUserKeywords( const QString &userKeywords );

	QString	getDescription() const;
	void	setDescription( const QString &description );

	int		getAudience() const;
	void	setAudience( int rating );

	quint32	getCompatibilityBase();
	void	setCompatibilityBase( quint32 compatibilityBase );

	bool	isNewItem() const;
	void	setIsNewItem( bool yesNo );

public slots:
	bool	isValid() const;
	void	setDataItem( DzDBContentInstanceTable *data );

	DzDBContentInstanceTable*	getTableData();

	DzAsset*	getOwner() const;
	bool		update();

private:
	struct	Data; 
	Data*	m_data;
};

#endif // DAZ_ASSET_METADATA_H
