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
	Defines the DzStyledFloatCardPropertyWgt class.
**/

#ifndef DAZ_STYLED_FLOAT_CARD_PROPERTY_WGT_H
#define DAZ_STYLED_FLOAT_CARD_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstyledpropertywgt.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledFloatCardPropertyWgt : public DzStyledPropertyBaseWgt {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzStyledFloatCardPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledFloatCardPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	removeAllProperties();
	void setLevel( int level );

public slots:

	void			setValue( float val );
	virtual bool	doOptionsDialog();
	void			setHighLightSlider( bool onOff );

protected slots:
	virtual void	updateLabel();
	virtual void	updateValue();
	virtual void	updateFromList();
	virtual void	setPropertyValueLabel( const QString &val );
	void			editBoxChange( const QString &text );
	virtual void	finishTextEdit();
	void			showEdit( const QRect &rect, QString text, const QFont &fnt );
	void			valueLabelClicked();
	int				getLevel();

protected:

	virtual QString	getValueEditText() const;
	virtual void	valueTextChanged( const QString &text );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	changeEvent( QEvent *e );

private slots:

	void			propertyChangeNotify();
	void			propStateChangeNotify();
	void			startEdit();
	void			finishEdit();
	void			cancelEdit();

private:	
	void			setupFromStyle();
	void			drawLabel( QPainter &p );

	struct	Data;
	Data	*m_data;
};
#endif // DAZ_STYLED_FLOAT_CARD_PROPERTY_WGT_H
