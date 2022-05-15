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
#ifndef DAZ_DYNAMIC_DIVIDER_WGT_H
#define DAZ_DYNAMIC_DIVIDER_WGT_H

/*****************************
	Include files
*****************************/

#include "dzdividerbar.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDynamicDividerWgt : public QWidget {
	Q_OBJECT
public:
	enum ResizeType
	{
		RTStretchFirst,
		RTStretchSecond,
		RTStretchBoth
	};

	DzDynamicDividerWgt( QWidget *parent = 0, const QString &name = QString::null );
	DzDynamicDividerWgt( QWidget *parent, QWidget *firstItem, QWidget *secondItem );
	DzDynamicDividerWgt( QWidget *firstItem, QWidget *secondItem, QWidget *parent, Qt::Orientation orientation,
		const QString &name = QString::null, DzDividerBar::BarStyle barStyle = DzDividerBar::BSFull );

	virtual ~DzDynamicDividerWgt();
	
	DzDividerBar::BarStyle		getBarStyle() const;
	ResizeType					getResizeType() const;
	bool						getToggleEnabled() const;
	int							getMargin() const;
	int							getSpacing() const;
	bool						getToggled() const;
	DzDividerBar::WidgetType	getToggleDirection() const;
	void						getMinMaxPercent( double &minPercent, double &maxPercent ) const;
	double						getActualDividerPercent() const;
	double						getPreferredDividerPercent() const;
	bool						getMinimized() const;
	Qt::Orientation				getDividerOrientation() const;
	bool						getMoveDisabled() const;
	int							getPreferredWidgetExtent() const;
	DzDividerBar::WidgetType	getPreferredWidget() const;
	DzDividerBar*				getDividerBar();

	void	setMargin( int margin );
	void	setSpacing( int spacing );
	void	setResizeType( ResizeType type );
	void	setPreferredDividerPercent( double percentage );
	void	setMoveDisabled( bool onOff = true );
	void	setDividerOrientation( Qt::Orientation orientation );
	void	setToggleDirection( DzDividerBar::WidgetType toggleDir );
	void	setToggleEnabled( bool onOff );
	void	setBarStyle( DzDividerBar::BarStyle style );

	virtual QSize	minimumSizeHint() const;

	bool	isMinimized() const;

public slots:

	void		toggleWidget();
	void		setToggleState( bool minimized );
	void		moveDivider( int distance );
	void		setDividerBar( Qt::Orientation orientation, DzDividerBar::BarStyle barStyle );
	void		setFirstWidget( QWidget *first );
	void		setSecondWidget( QWidget *second );
	void		setPreferredWidgetExtent( DzDividerBar::WidgetType widget, int extent );
	QWidget*	getFirstWidget();
	QWidget*	getSecondWidget();
	
signals:
	void		dividerToggled( bool minimized );
	
protected:
	virtual void	resizeEvent( QResizeEvent *rEvent );
	virtual void	styleChange( QStyle &oldStyle );

private:
	void	createDividerBar( Qt::Orientation orientation, DzDividerBar::BarStyle barStyle );
	void	doLayout();
	void	doBothWidgetVLayout();
	void	doBothWidgetHLayout();
	void	setDividerPercentage( QSize &oldSize, QSize &newSize );
	void	correctDividerPercentage( bool correctExtent = false );
	void	correctDividerPercentageFromExtent();
	void	getMinSizes( QSize &firstMin, QSize &secondMin ) const;
	QSize	smartMinSize( QWidget *w ) const;

	struct	Data;
	Data	*m_data;
};

#endif //DAZ_DYNAMIC_DIVIDER_WGT_H
