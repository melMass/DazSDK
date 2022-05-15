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
	Defines the DzPropertyWgt class.
**/

#ifndef DAZ_PROPERTY_WGT_H
#define DAZ_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/
#include <QtGui/QStyle>
#include <QtGui/QWidget>

#include "dzerrorcodes.h"
#include "dztypes.h"

/*****************************
	Definitions
*****************************/

#define DZ_PROPERTY_CONTROL_MARGIN		2
#define DZ_PROPERTY_CONTROL_INDENT		10

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPropertyWgt : public QWidget {
	Q_OBJECT
public:
	enum PropertyHiddenState
	{
		PHS_NotHidden = 0,
		PHS_Hidden, 
		PHS_Indeterminate
	};

	//
	// CREATORS
	//

	DzPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzPropertyWgt();

	//
	// MANIPULATORS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	removeAllProperties();
	virtual void	resetProperties( bool allowUndo = false );
	virtual void	showControlOnly( bool onOff );
	virtual void	setSelected( bool onOff );
	virtual void	setLevel( int level ) = 0;

	//
	// ACCESSORS
	//

	int						getNumProperties() const;
	int						getNumTotalProperties() const;
	DzProperty*				getFirstProperty() const;
	DzPropertyListIterator	getProperties() const;
	virtual bool			isShowingControlOnly() const;
	virtual bool			isSelected() const;
	PropertyHiddenState		getPropertyHiddenState() const;

	//DO NOT use these calls - For Internal Use Only
	virtual bool            isFastMode() const;
	virtual void			setFastMode( bool mode );
	virtual void			setPropertyList( const DzPropertyList &list );
	virtual void			clearPropertyList();
	virtual void			updateFromList() = 0;

	virtual void			setViewItemStyleOptions( const QStyle::State &flags );
	virtual QStyle::State	getViewItemStyleOptions();

public slots:
	virtual bool	doOptionsDialog() = 0;

signals:

	void	selectionStateChanged( bool onOff );
	void	fastUpdate();
	void	aboutToShowOptionsDialog();

protected:

	//
	// REIMPLEMENTATIONS
	//

	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseDoubleClickEvent( QMouseEvent *e );

private slots:

	void	removeDeletedProperty( DzProperty *prop );
	void	propertySelectionChanged();

private:
	void	updatePropertyHiddenState();

	struct	Data;
	Data	*m_data;
	bool	m_isUpdatingSelection;
};

#endif // DAZ_PROPERTY_WGT_H


