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
	Defines the DzStyledColorPropertyWgt class.
**/

#ifndef DAZ_STYLED_Color_PROPERTY_WGT_H
#define DAZ_STYLED_Color_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include "dzstylednumericpropertywgt.h"

/****************************
	Forward declarations
****************************/

class DzStyledColorWellWidget;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledColorPropertyWgt : public DzStyledNumericPropertyWgt {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStyledColorPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledColorPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	removeAllProperties();
	virtual	bool	isEditing() const;

public slots:
	virtual bool	doOptionsDialog();
	void			changeColor( const QColor &color );

protected:

	virtual void	updateValue();
	virtual QString getValueEditText() const;
	virtual void	styleChange( QStyle &oldStyle );

	
private slots:

	void	propertyChangeNotify();
	void	propStateChangeNotify();
	void	beginEdit();
	void	finishEdit();

private:
	struct	Data;
	Data	*m_data;
};

class DzStyledPropertyRGBLabel : public QWidget {
	Q_OBJECT
public:
	DzStyledPropertyRGBLabel( QWidget *parent );
	virtual ~DzStyledPropertyRGBLabel();

	void	setText( const QString &label );
	QString	text() const;
	void	setMinText(const QString &minText);

signals:
	void	clicked();

protected:
	virtual void	mousePressEvent( QMouseEvent *event );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &oldStyle );

private:
	void	setHieghtForContents();

	struct	Data;
	Data	*m_data;
};

class DzStyledColorWellWidget : public QWidget {
	Q_OBJECT
public:
	DzStyledColorWellWidget( QWidget *parent );
	virtual ~DzStyledColorWellWidget();

	QColor	getColor() const;
	void	setColor( const QColor &color );

	void	setIndeterminate( bool onOff );

signals:
	void	clicked();

protected:
	virtual void	mousePressEvent( QMouseEvent *event );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &oldStyle );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STYLED_Color_PROPERTY_WGT_H