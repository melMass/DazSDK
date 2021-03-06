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

#ifndef DZ_INFO_DIVIDER_BAR_H
#define DZ_INFO_DIVIDER_BAR_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

#include "dzerrorcodes.h"
#include "dzdividerbar.h"
#include "dztypes.h"

/*****************************
	Forward declarations
*****************************/

class DzInfoTabs;
class DzProductAssetContainer;
class QLineEdit;
class QTextEdit;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzInfoDivider : public QWidget {
	Q_OBJECT
public:
	DzInfoDivider( QWidget *firstWidget, QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzInfoDivider();

	enum MinimizedState{ NotMinimized,HalfMinimized,FullMinimized };
	
	//Methods for manipulating the divider bar
	DzDividerBar::BarStyle	barStyle() const;
	void					setToggleDirection( DzDividerBar::WidgetType toggleDir );
	DzDividerBar*			getDividerBar();
	MinimizedState			toggleState();
	//Methods for affecting this object as a whole
	void					setDividerBar( Qt::Orientation orientation, DzDividerBar::BarStyle barStyle );
	virtual QSize			minimumSizeHint() const;
	virtual QSize			sizeHint() const;
	void					getMinMaxPercent( double &minPercent, double &maxPercent );
	DzDividerBar::WidgetType	getPreferredWidget() const;
	void					setPreferredWidgetExtent( DzDividerBar::WidgetType widget, int extent );
	int						getPreferredWidgetExtent();

public slots:
	void		setFirstWidget( QWidget *first );
	void		toggleMinimized();
	void		moveDivider( int distance );
	void		setPreferredDividerPercent( double position );
	double		getPreferredDividerPercent();
	double		getActualDividerPercent();
	bool		isMinimized();
	bool		isToggled();
	bool		toggleEnabled() const;
	int			margin();
	int			spacing();
	void		setMargin( int margin );
	void		setSpacing( int spacing );
	DzInfoTabs*	getInfoTabs() const;
	void		toggleClosed();
	int			getToggleState();
	void		setToggleState( int state );

protected:
	void			doLayout();
	void			doBothWidgetVLayout();
	void			doBothWidgetHLayout();
	void			setDividerPercentage( QSize &oldSize, QSize &newSize );
	void			correctDividerPercentage();
	virtual void	resizeEvent( QResizeEvent *rEvent );
	virtual void	changeEvent( QEvent *event );
	void			getMinSizes( QSize &firstMin, QSize &secondMin ) const;
protected:
	virtual void	showEvent( QShowEvent *event );
private:
	void	correctDividerPercentageFromExtent();
	void	createDividerBar( Qt::Orientation orientation, DzDividerBar::BarStyle barStyle );
	
	struct	Data;
	Data	*m_data;
};

template <class DataType> class DzTSharedPointer;
typedef DzTSharedPointer<DzProductAssetContainer> DzProductAssetContainerPtr;

class DZ_EXPORT DzInfoTabs : public QWidget {
	Q_OBJECT
public:
	DzInfoTabs(DzInfoDivider *parent, const QString &name);
	~DzInfoTabs();

public slots:
	void	showStack();
	void	hideStack();
	bool	isStackHidden();
	DzError	setTipUIScript( const QString &file );
	void	setInfo( const DzAssetPtr &file );
	void	setFileInfo( const DzAssetPtr &file );
	void	setFileInfoFromContainer( DzProductAssetContainer *con );
	void	setMetaInfo( const DzAssetPtr &file );
	void	showFileTab( bool onOff );
	void	showMetaTab( bool onOff );
	void	showRenderTab( bool onOff );
	void	setCurrentTab( int which );

	QLineEdit*	getRenderAuthorEdit() const;
	QLineEdit*	getRenderCaptionEdit() const;
	QTextEdit*	getRenderDescriptionEdit() const;

	virtual QSize	minimumSizeHint() const;
	void	setRenderApplyButtonEnabled( bool onOff );

signals:
	void	renderApplyClicked();

private slots:
	void	currentChanged( int index );
	void	tabClicked( int index );

private:
	int		indexForTab( const QString &text );
	void	buildFileInfo();
	void	buildMetaInfo();
	void	buildRenderInfo();

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzTipPage : public QFrame
{
	Q_OBJECT
public:
	DzTipPage( QWidget *parent = NULL );
	virtual ~DzTipPage();

public slots:
	DzError			setUiScript( const QString &fileName );

protected:
	virtual void	paintEvent( QPaintEvent *e );

private:
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzFileMetaTab : public QWidget
{
	Q_OBJECT
public:
	DzFileMetaTab( QWidget *parent = 0 );
	virtual ~DzFileMetaTab();

public slots:
	void		setAsset( DzAsset *asset );
	DzAsset*	getAsset() const;
	void		applyPressed();

private:
	void		setupUi( QWidget *DzFileMetaWgt );
	void		retranslateUi( QWidget *DzFileMetaWgt );

private:
	struct	Data;
	Data	*m_data;
};

#endif //_DAZ_INFO_DIVIDER_BAR_H
