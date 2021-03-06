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
	Defines the DzStyledFilePropertyWgt class.
**/

#ifndef DAZ_STYLED_FILE_PROPERTY_WGT_H
#define DAZ_STYLED_FILE_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstyledpropertywgt.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledFilePropertyWgt : public DzStyledPropertyWgt {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStyledFilePropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledFilePropertyWgt();

	//////////////////////////
	// from DzPropertyWgt

	virtual DzError addProperty( DzProperty *prop );
	virtual void	removeAllProperties();

public slots:
	virtual bool	doOptionsDialog();

protected slots:
	virtual void	showEvent( QShowEvent *e );
	virtual void	updateValue();

private slots:
	void	propertyChangeNotify();
	void	changeSelection( int );
signals:
	void	fileChanged();
private:
	void	openFile();
	void	clearFile();
	void	showFile( const QString &item );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STYLED_FILE_PROPERTY_WGT_H
