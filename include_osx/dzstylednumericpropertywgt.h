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
	Defines the DzStyledNumericPropertyWgt class.
**/

#ifndef DAZ_STYLED_NUMERIC_PROPERTY_WGT_H
#define DAZ_STYLED_NUMERIC_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstyledpropertywgt.h"

/****************************
	Forward declarations
****************************/

class DzTexture;
class QLabel;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledNumericPropertyWgt : public DzStyledPropertyWgt {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStyledNumericPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledNumericPropertyWgt();

public slots:

	//
	// MANIPULATORS
	//

	void	setImageWidgetPixmap( const QPixmap &pix);

	//
	// ACCESSORS
	//
signals:

	void	mapChanged( const DzTexture *map );

protected slots:
	virtual void	showEvent( QShowEvent *e );

	virtual void	updateValue();
	void			changeMap( const DzTexture *map );
	bool			isIndeterminateMap();

protected: 
	virtual void	presentationMapChanged();
	virtual void	setMap( const DzTexture *map, bool indeterminate );
	virtual void	styleChange( QStyle &oldStyle );
	QLabel*			getIconLabel() const;

private:

	struct	Data;
	Data	*m_data;
};


#endif // DAZ_STYLED_NUMERIC_PROPERTY_WGT_H
