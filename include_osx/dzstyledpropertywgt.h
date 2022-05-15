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

#ifndef DAZ_STYLED_PROPERTY_WGT_H
#define DAZ_STYLED_PROPERTY_WGT_H

/*****************************
	Include files
*****************************/

#include <QtGui/QLabel>

#include "dzaction.h"
#include "dzactionmgr.h"
#include "dzbasicdialog.h"
#include "dzpresentation.h"
#include "dzpropertywgt.h"
#include "dzstyledbutton.h"

/****************************
	Forward declarations
****************************/

class DzStyledPropertyHeaderWidget;
class DzStyledPropertyBodyWidget;
class DzStyledBoolButton;
class DzStyledImageWidget;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledPropertyBaseWgt : public DzPropertyWgt {
	Q_OBJECT
public:
	enum PresentationMapType
	{
		PMT_Large = 0,
		PMT_Small
	};

	//
	// CREATORS
	//
	DzStyledPropertyBaseWgt( QWidget *parent = 0, const QString &name = QString::null, 
							PresentationMapType mapType = PMT_Small );
	
	virtual ~DzStyledPropertyBaseWgt();
	
	virtual DzError	addProperty( DzProperty *prop );
	virtual void	resetProperties(bool allowUndo = false);

	void	showMenuBtn(bool show);
	void	enableMenuBtn(bool enable);
	void	showOverrideBtn(bool show);
	void	showLockBtn(bool show);
	bool	inOverrideState() const;
	bool	inLockState() const;
	void	overrideControllers(bool onOff, bool onlyRegioned = false);
	virtual	bool	isEditing() const;

	PresentationMapType	getPresentationMapType() const;

	//internal
	virtual void	removeAllProperties();
	virtual void	setPropertyList(const DzPropertyList &list);
	virtual void	clearPropertyList();
	virtual void	updateSetup();

public slots:
	DzPersistentMenu*	getContextMenu();
	DzPresentationPtr	getPresentation() const;
	QPixmap				getPresentationMap() const;
	QColor				getPresentationColorA() const;
	QColor				getPresentationColorB() const;

protected slots:
	virtual void	updateFromList();
	virtual void	presentationMapChanged(){}

	void	menuButtonClicked();	
	void	updateBtnStates();
	void	setOverrideState();
	void	setLockState();
	void	setPresentationMap( const QPixmap &pix);
	void	updatePresentationDrawFlags();
	void	setPresentationMapSize( const QSize &size );

protected:
	DzStyledBoolButton*	getOverideBtn() const;
	DzStyledBoolButton*	getLockBtn() const;
	DzStyledButton*		getMenuBtn() const;
	virtual void		changeEvent( QEvent *e );
	bool				propertiesHaveERC();

private:
	void stylizeBase();

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzStyledPropertyWgt : public DzStyledPropertyBaseWgt {
	Q_OBJECT
public:

	//
	// CREATORS
	//

	DzStyledPropertyWgt( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzStyledPropertyWgt();

	//
	// REIMPLEMENTATIONS
	//

	virtual DzError	addProperty( DzProperty *prop );
	virtual void	setLevel( int level );
	DzStyledPropertyHeaderWidget *	getHeaderWidget();
	DzStyledPropertyBodyWidget *	getBodyWidget();
	virtual	bool	isEditing() const;

protected slots:
	virtual void	updateLabel();
	virtual void	updateValue() = 0;
	virtual void	updateFromList();
	virtual void	setPropertyValueLabel( const QString &val );
	void			editBoxChange( const QString &text );
	virtual void	finishTextEdit();

	void			showEdit( const QRect &rect, QString text, const QFont &fnt );
	void			valueLabelClicked();
	int				getLevel();

protected:
	virtual void	presentationMapChanged();
	void			addWidget( QWidget *wgt, int stretch = 0, Qt::Alignment align = 0 );
	void			addWidgetRow( QWidget *wgt, int stretch=0,Qt::Alignment align=0);
	virtual void	valueTextChanged( const QString &text );
	virtual void	paintEvent( QPaintEvent *e );
	virtual QString	getValueEditText() const;
	void			setValueVisible( bool onOff );
	virtual void	changeEvent( QEvent *e );
	virtual void	mouseDoubleClickEvent( QMouseEvent *e );
	void			stylize();

private:
	void			cleanUpEditBox();
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzStyledBoolButton : public DzStyledButton
{
	Q_OBJECT
public:
	enum ButtonState 
	{
		BStOff = 0,
		BStOn,
		BStMult
	};

	DzStyledBoolButton(QWidget *parent);
	virtual ~DzStyledBoolButton();

	ButtonState getState() const;
	QString		getStateText( ButtonState state ) const;

	void	setState( ButtonState state );
	void	setStateText( ButtonState state, const QString &text );

public slots:
	void	toggleState();

signals:
	void	stateChanged();

protected:
	virtual void setButtonStateFlags( QStyle::State &flags );

private:
	void	updateText();
	void	updateChecked();

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPropertyValueLabel : public QLabel {
	Q_OBJECT
public:
	DzPropertyValueLabel( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzPropertyValueLabel();

	void	setIsDefault( bool onOff );
	bool	isDefault() const;

signals:
	void	clicked();
protected:
	virtual void	mousePressEvent( QMouseEvent *event );
	virtual void	paintEvent( QPaintEvent *e );
private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzStyledPropertyHeaderWidget : public QWidget
{
	Q_OBJECT
public:
	DzStyledPropertyHeaderWidget( QWidget *parent = 0 );
	~DzStyledPropertyHeaderWidget();

	void	setLabel(QString newLabel);
	void	setDisplayHiddenLabel(bool hidden);

	void	draw( QPainter &p, QWidget *parent, QRect &labelRect );

public slots:
	void	selectionChanged( bool onOff );

private:
	void	drawLabel( QPainter &p, QRect &labelRect );
	
	struct	Data; 
	Data	*m_data;
};

struct DzStyledPropertyBodyWidgetData;
class DZ_EXPORT DzStyledPropertyBodyWidget : public QWidget
{
	Q_OBJECT
public:
	enum InterestFlag { NONINTEREST = 0, XINTEREST, YINTEREST, ZINTEREST, ALLINTEREST, INDETERMINATEINTEREST };
	DzStyledPropertyBodyWidget( QWidget *parent = 0);
	~DzStyledPropertyBodyWidget();

	void	setInterest( DzStyledPropertyBodyWidget::InterestFlag value ); 
	void	draw( QPainter &p, QWidget *parent, DzPresentationPtr presentation );

public slots:
	void	selectionChanged( bool onOff );

private:
	void	drawGradient( QStyleOption &opt, QPainter &p, DzPresentationPtr presPtr );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzStyledPropertyMenu : public DzPersistentMenu
{
	Q_OBJECT
public:
	DzStyledPropertyMenu(const QString &name = "Property");
	virtual ~DzStyledPropertyMenu(){}

	virtual void	buildPersistentMenu( DzActionMenu *menu ) const;
	virtual int		getPersistentMenuVersion() const;
};

class DZ_EXPORT DzStyledPropertyAction : public DzAction
{
	Q_OBJECT
public:
	DzStyledPropertyAction( const QString &text = QString(), const QString &desc = QString() );
	~DzStyledPropertyAction(){}

	virtual QString getActionGroup() const;

public slots:
	DzStyledPropertyBaseWgt*	getCurrentWgt() const;
};

class DZ_EXPORT DzStyledPropertyShowSettingsAction : public DzStyledPropertyAction
{
	Q_OBJECT
public:
	DzStyledPropertyShowSettingsAction();
	virtual void	executeAction();
};

class DZ_EXPORT DzStyledPropertyLockAction : public DzStyledPropertyAction
{
	Q_OBJECT
public:
	DzStyledPropertyLockAction();
	virtual void	executeAction();
};

class DZ_EXPORT DzStyledPropertyUnlockAction : public DzStyledPropertyAction
{
	Q_OBJECT
public:
	DzStyledPropertyUnlockAction();
	virtual void	executeAction();
};

class DZ_EXPORT DzStyledPropertyHideAction : public DzStyledPropertyAction
{
	Q_OBJECT
public:
	DzStyledPropertyHideAction();
	virtual void	executeAction();
};

class DZ_EXPORT DzStyledPropertyUnhideAction : public DzStyledPropertyAction
{
	Q_OBJECT
public:
	DzStyledPropertyUnhideAction();
	virtual void	executeAction();
};

class DZ_EXPORT DzStyledPropertyResetAction : public DzStyledPropertyAction
{
	Q_OBJECT
public:
	DzStyledPropertyResetAction();
	virtual void	executeAction();
};

#endif // DAZ_STYLED_PROPERTY_WGT_H
