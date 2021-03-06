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
#ifndef DAZ_CONTENT_SEARCH_OPTIONS_H
#define DAZ_CONTENT_SEARCH_OPTIONS_H

/*****************************
	Include files
*****************************/

#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/****************************
	Class definitions
*****************************/

class DZ_EXPORT DzContentSearchOptions : public QObject , public DzRefCountedItem
{
	Q_OBJECT
	Q_ENUMS( SortBy SortOrder SaleItems PlatinumClub PlatinumSale Vendor )
	Q_PROPERTY( SortBy sortBy READ getSortBy WRITE setSortBy )
	Q_PROPERTY( SortOrder sortOrder READ getSortOrder WRITE setSortOrder )
	Q_PROPERTY( SaleItems saleItems READ getSaleItems WRITE setSaleItems )
	Q_PROPERTY( PlatinumClub platinumClub READ getPlatinumClub WRITE setPlatinumClub )
	Q_PROPERTY( PlatinumSale platinumSale READ getPlatinumSale WRITE setPlatinumSale )
	Q_PROPERTY( Vendor vendor READ getVendor WRITE setVendor )
	Q_PROPERTY( bool saleItemFilter READ getSaleItemFilter WRITE setSaleItemFilter )
	Q_PROPERTY( bool platClubFilter READ getPlatClubFilter WRITE setPlatClubFilter )
	Q_PROPERTY( bool platSaleFilter READ getPlatSaleFilter WRITE setPlatSaleFilter )
	Q_PROPERTY( bool vendorFilter READ getVendorFilter WRITE setVendorFilter )
	Q_PROPERTY( Store storeFilter READ getStoreFilter WRITE setStoreFilter )

public:
	enum SortBy { None, Popularity, Date, Price, Alphabetical };
	enum SortOrder{ Ascending, Descending };
	enum SaleItems{ OnSale, NotOnSale };
	enum PlatinumClub { PlatClub, NonPlatClub };
	enum PlatinumSale { PlatSale, NonPlatSale };
	enum Vendor { DazOriginal, PublishedArtist };
	enum Store { Standard = 0x01, Developer = 0x02, All = Standard | Developer };


	DzContentSearchOptions();
	DzContentSearchOptions( const DzContentSearchOptions *other );
	virtual ~DzContentSearchOptions();

	SortBy			getSortBy();
	void			setSortBy( SortBy val );
	void			setSortOrder( SortOrder val );
	void			setSaleItems( SaleItems val );
	SortOrder		getSortOrder();
	SaleItems		getSaleItems();
	PlatinumClub	getPlatinumClub();
	void			setPlatinumClub( PlatinumClub val );
	PlatinumSale	getPlatinumSale();
	void			setPlatinumSale( PlatinumSale val );
	Vendor			getVendor();
	void			setVendor( Vendor val );
	bool			getSaleItemFilter();
	void			setSaleItemFilter( bool val );
	bool			getPlatClubFilter();
	void			setPlatClubFilter( bool val );
	bool			getPlatSaleFilter();
	void			setPlatSaleFilter( bool val );
	bool			getVendorFilter();
	void			setVendorFilter( bool val );
	Store			getStoreFilter();
	void			setStoreFilter( Store val );

private:
	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzContentSearchOptions> DzContentSearchOptionsPtr;
Q_DECLARE_METATYPE(DzContentSearchOptionsPtr);

#endif //DAZ_CONTENT_SEARCH_OPTIONS_H