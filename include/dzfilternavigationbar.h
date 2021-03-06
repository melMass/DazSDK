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
	@script
	@file
	Defines the DzFilterNavigationBar class.
**/

#ifndef DZ_FILTER_NAVIGATION_BAR_H
#define DZ_FILTER_NAVIGATION_BAR_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>
#include <QtGui/QStyle>
#include <QtGui/QCompleter>
#include <QtCore/QAbstractItemModel>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/
class DzNavigationCompleterModel;

class DZ_EXPORT DzFilterNavigationBar : public QWidget
{
	Q_OBJECT
public:
	DzFilterNavigationBar( QWidget *parent );
	~DzFilterNavigationBar();

public slots:
	void	clearFilter();
	
	void	decrementPage();
	void	incrementPage();

	QString	getFilterHint() const;
	void	setFilterHint( const QString &text );
	QString	getFilterText() const;
	void	setFilterText( const QString &text);
	QString	getPageLabel() const;
	void	setPageLabel( const QString &text );
	int		getMaxPages() const;
	void	setMaxPages( int max );
	int		getPageValue() const;
	void	setPageValue( int page );
	void	selectIconView();
	void	selectListView();

	void	setFilterFieldVisible( bool visible );
	void	setPageLabelVisible( bool visible );
	void	setPageNavigationVisible( bool visible );
	void	setPageSizeVisible( bool visible );
	void	setPageViewVisible( bool visible );


	bool	getAutoHidePageNavigation() const;
	void	setAutoHidePageNavigation( bool autoHide );
	void	updatePageNavigationVisibility();
	void	updateFilterWidgets();
	void	startProgress();
	void	stopProgress();
	void	setAutoCompleteActive(bool onOff);
	bool	isAutoCompleteActive()const;

	DzNavigationCompleterModel* getNavModel()const;

private slots:
	void	filterTextChanged( const QString &text );
	void	autoCompleteUpdate();
	void	timeout();

signals:
	void	filterChanged( const QString &text );
	void	filterEditFinished();
	void	filterCleared();
	void	pageValueChanged( int val );
	void	pageSizeDecremented();
	void	pageSizeIncremented();
	void	iconViewSelected();
	void	listViewSelected();
	void	progressButtonClicked();

protected:
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &oldStyle );

private:
	void	updateToStyle();

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzNavigationResult : public QWidget
{
	Q_OBJECT
public:
	DzNavigationResult( QWidget *parent );
	~DzNavigationResult();
	
protected:
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &oldStyle );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzNavigationSideBase : public QWidget
{
	Q_OBJECT
public:
	DzNavigationSideBase( QWidget *parent );
	~DzNavigationSideBase();

	void	setCustomPrimitive( QStyle::PrimitiveElement prim );
	
protected:
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &oldStyle );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzNavigationCompleter : public QCompleter
{
	Q_OBJECT
public:
	DzNavigationCompleter(QObject * parent = 0);
	~DzNavigationCompleter();

	virtual QString pathFromIndex(const QModelIndex &index) const;
    virtual QStringList splitPath(const QString &path) const;
	void updatePaths(const QString& txt);
	DzNavigationCompleterModel* getNavModel()const;
private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzNavigationCompleterModel : public QAbstractItemModel {
public:
	DzNavigationCompleterModel(QObject *parent = 0);
	~DzNavigationCompleterModel();

	//
	// REIMPLEMENTATIONS
	//
	virtual QModelIndex	index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
	virtual QModelIndex	parent( const QModelIndex &index ) const;
	virtual int			rowCount( const QModelIndex &parent = QModelIndex() ) const;
	virtual int			columnCount( const QModelIndex &parent = QModelIndex() ) const;
	virtual QVariant	data( const QModelIndex &index, int role = Qt::DisplayRole ) const;

	void				setCurrentPrefixPath(const QStringList& list);
	QString				pathFromIndex( const QModelIndex &index ) const;
	QStringList			buildSearchTerms();


	QStringList			getCateogries()const;
	QStringList			getCompatibilityBases()const;
	QStringList			getContentTypes()const;
	int					getLimit()const;

	void				setCateogries(const QStringList& cateogries)const;
	void				setCompatibilityBases(const QStringList& compatibilityBases);
	void				setContentTypes(const QStringList& contentTypes);
	void				setLimit(int limit);

private:
	struct	Data;
	Data	*m_data;
};

#endif //DZ_SEARCH_NAVIGATION_BAR_H
