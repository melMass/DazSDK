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
	Defines the DzStyle class.
**/

#ifndef DAZ_STYLE_H
#define DAZ_STYLE_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"
#include "dzstyledefs.h"

#ifdef Q_OS_WIN
#include <QtGui/QWindowsStyle>
#elif defined Q_OS_MAC
#include "dzmacbasestyle.h"
#endif

#include "dztextstyle.h"
#include "dzerrorcodes.h"
#include "dzapp.h"

/*****************************
	Definitions
*****************************/

/** The default style definition file **/
#define DZ_DEFAULT_STYLE_DEF	"Main Street"

#define DZ_STYLE_MULTI_PIXMAP_ITEMS		13
#define DZ_FILE_ICON_SIZE				91
#define DZ_SMALL_FILE_ICON_SIZE			30

// Additional control types that Studio uses:

// ------ ComplexControls

#define DZ_CC_NumericSlider			((QStyle::ComplexControl)( QStyle::CC_CustomBase + 0 ))
#define DZ_CC_DividerBar			((QStyle::ComplexControl)( QStyle::CC_CustomBase + 1 ))
#define DZ_CC_MouseOverSlider		((QStyle::ComplexControl)( QStyle::CC_CustomBase + 2 )) // make obsolete?
#define DZ_CC_StyledNumericSlider	((QStyle::ComplexControl)( QStyle::CC_CustomBase + 3 ))

// total number of custom complex control items
#define DZ_CC_NumItems		4

// ------ SubControls

// Numeric Slider and MouseOver Slider
#define DZ_SC_SliderBar				((QStyle::SubControl)0x00000001)
#define DZ_SC_SliderLeftNudge		((QStyle::SubControl)0x00000002)
#define DZ_SC_SliderRightNudge		((QStyle::SubControl)0x00000004)
#define DZ_SC_SliderTextArea		((QStyle::SubControl)0x00000008)
#define DZ_SC_SliderEditArea		((QStyle::SubControl)0x00000010)
#define DZ_SC_SliderLabelArea		((QStyle::SubControl)0x00000020)
#define DZ_SC_SliderIndicator		((QStyle::SubControl)0x00000040)

// Divider Bar
#define DZ_SC_DividerGrip			((QStyle::SubControl)0x00000001)

// ------ ControlElements
#define DZ_CE_TabOptionsButton		QStyle::CE_CustomBase
#define DZ_CE_DockWindowTitleBar	((QStyle::ControlElement)( QStyle::CE_CustomBase + 1 ))
#define DZ_CE_WidgetGroupBar		((QStyle::ControlElement)( QStyle::CE_CustomBase + 2 ))
#define DZ_CE_AHButton				((QStyle::ControlElement)( QStyle::CE_CustomBase + 3 )) // make obsolete?
#define DZ_CE_AHUpButton			((QStyle::ControlElement)( QStyle::CE_CustomBase + 4 )) // make obsolete?
#define DZ_CE_AHDnButton			((QStyle::ControlElement)( QStyle::CE_CustomBase + 5 )) // make obsolete?
#define DZ_CE_AHRButton				((QStyle::ControlElement)( QStyle::CE_CustomBase + 6 )) // make obsolete?
#define DZ_CE_AHLButton				((QStyle::ControlElement)( QStyle::CE_CustomBase + 7 )) // make obsolete?

// total number of custom primitive element items
#define DZ_CE_NumItems		8

// Use the platform-specific style as the base for our style.
#ifdef Q_OS_WIN
typedef QWindowsStyle DZ_SYSTEM_STYLE;
#elif defined Q_OS_MAC
// Use QWindowsStyle style even on Mac to avoid special handling of button "hit" sizes in QPushButtton code.
// We don't really get anything from the Mac style anymore anyway.
typedef QWindowsStyle DZ_SYSTEM_STYLE;
#endif

inline QRect DzShrinkRect(QRect const &rect, int amount)
{
	return rect.adjusted(amount, amount, -amount, -amount);
}

/****************************
	Forward declarations
****************************/

class Q3Header;
class QProgressBar;
class QDomElement;
class QFile;
class QFont;
class QIcon;
class QPixmap;
class QPushButton;
class QScrollBar;
class QSlider;
class QString;
class QStyleOptionButton;
class QStyleOptionComboBox;
class QStyleOptionMenuItem;
class QStyleOptionProgressBarV2;
class QStyleOptionQ3ListView;
class QStyleOptionTabV3;
class QStyleOptionToolButton;
class QComboBox;
class QToolButton;
class QStyleOptionSlider;
class Q3ListViewItem;

class DzAppSettingsMgr;
class DzDividerBar;
class DzSlider;
class DzSpinner;
class DzStylePrimitive;
class DzStylePixmap;
class DzStyleTextStyle;
class DzStyleIcon;
class DzWidgetGroupBar;

struct DzStylePrimitiveItem;
struct DzStylePixelMetricItem;
struct DzStyleHintItem;
struct DzStandardPixmapItem;
struct DzStyleTextStyleItem;

/*****************************
	Class definitions
*****************************/

class DzStyleInterface
{
public:
	enum TextStyle
	{
		TS_Default,
		TS_ButtonCommand,
		TS_ButtonDefault,
		TS_TabBarTab,
		TS_ProgressBar,
		TS_MenuBarItem,
		TS_PopupMenuItem,
		TS_ListViewItem,
		// do not add any values below/greater than this
		TS_CustomBase =		0xf0000000
	};

	virtual ~DzStyleInterface() { }

	virtual QRect		commonStyleSubElementRect( QStyle::SubElement subElement,
							const QStyleOption *option, QWidget const *widget ) const = 0;
	virtual QRect		systemStyleSubElementRect( QStyle::SubElement subElement,
							const QStyleOption *option, QWidget const *widget ) const = 0;
	virtual DzTextStyle	textStyle( TextStyle ts, const QStyleOption *option, QWidget const *widget = 0 ) const = 0;
	virtual void		drawPrimitive( QStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, QWidget const *w = 0 ) const = 0;
	virtual QSize		systemStyleSizeFromContents( QStyle::ContentsType ct,
							const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget ) const = 0;
};

class DZ_EXPORT DzStyle : public DZ_SYSTEM_STYLE, public DzStyleInterface
{
	Q_OBJECT
	friend class DzStyleDefinition;
	friend struct DzStylePrimitiveItem;
	friend struct DzStylePixelMetricItem;
	friend struct DzStyleHintItem;
	friend struct DzStandardPixmapItem;
	friend struct DzStyleTextStyleItem;
public:
	enum ExtendedStateFlag
	{
		ExtendedState_None			= 0x00,
		ExtendedState_Left			= 0x01,
		ExtendedState_Right			= 0x02,
		ExtendedState_Minor			= 0x04,
		ExtendedState_Major			= 0x08,
		ExtendedState_ButtonDefault	= 0x10
	};
	Q_DECLARE_FLAGS(ExtendedState, ExtendedStateFlag);

	// For Script Access
	enum PixmapMode {
		Normal = QIcon::Normal,
		Disabled = QIcon::Disabled,
		Active = QIcon::Active,
		Selected = QIcon::Selected
	};
	enum PixmapState {
		On = QIcon::On,
		Off = QIcon::Off
	};
	Q_ENUMS( PixmapMode PixmapState )

	//
	// CONSTRUCTORS/DESTRUCTORS
	//

	DzStyle( const QString &definition );
	virtual ~DzStyle();

	//
	// REIMPLMENTATIONS
	//

	virtual bool		eventFilter( QObject *object, QEvent *event );
	virtual void		polish( QWidget *w );
	virtual void		unpolish( QWidget *w );
	virtual void		polish( QPalette &p );
	virtual void		drawItemText( QPainter *painter, const QRect &rect,
							int flags, const QPalette &pal, bool enabled,
							const QString &text, QPalette::ColorRole textRole = QPalette::NoRole ) const;
	virtual void		drawPrimitive( PrimitiveElement pe, const QStyleOption *opt,
							QPainter *p, QWidget const *widget = 0 ) const;
	virtual void		drawControl( ControlElement element, const QStyleOption *opt,
							QPainter *p, QWidget const *widget = 0 ) const;

	void				drawControlToolButtonLabel( const QStyleOptionToolButton *toolbutton,
							const QWidget *widget, const QStyleOption *opt, QPainter *p ) const;
	virtual QRect		subControlRect( ComplexControl cc, const QStyleOptionComplex *opt,
							SubControl sc, QWidget const *widget = 0 ) const;
	virtual QRect		subElementRect( SubElement subElement, const QStyleOption *option,
							QWidget const *widget = 0 ) const;
	virtual void		drawComplexControl( ComplexControl cc, const QStyleOptionComplex *opt,
							QPainter *p, QWidget const *w = 0 ) const;
	virtual SubControl	hitTestComplexControl( ComplexControl cc, const QStyleOptionComplex *opt,
							const QPoint &pnt, QWidget const *w ) const;
	virtual int			pixelMetric( PixelMetric m, const QStyleOption *option = 0, QWidget const *widget = 0 ) const;
	virtual QSize		sizeFromContents( ContentsType ct, const QStyleOption *opt,
							const QSize &contentsSize, QWidget const *widget = 0 ) const;
	virtual QPixmap		standardPixmap( StandardPixmap standardPixmap, const QStyleOption *opt = 0,
							QWidget const *widget = 0 ) const;
	virtual QIcon		actionIcon( const QString &actionClass ) const;
	virtual int			styleHint( StyleHint hint, const QStyleOption *option = 0,
							QWidget const *widget = 0, QStyleHintReturn *returnData = 0 ) const;
	QPalette			getColors() const;
	virtual DzTextStyle	textStyle( TextStyle ts, const QStyleOption *option,
							QWidget const *widget = 0 ) const;

public slots:

	int		getNumInterfaceColors() const;
	QString	getInterfaceColorDescription( int which ) const;
	QColor	getInterfaceColor( const QString &name ) const;
	QColor	getInterfaceColor( int which ) const;
	QColor	getInterfaceColorDefault( int which ) const;
	void	setInterfaceColor( int which, const QColor &color );

#ifndef Q_MOC_RUN
	static
#endif
	DzError	compileStyleDefinition( const QString &infile, const QString &outfile );

	QString	getStyleDefinition() const;

	// For Script Access
	QFont	textStyle( const QString &styleName );
	QColor	textStyleColor( const QString &styleName );
	int		pixelMetric( const QString &metricName );
	QPixmap	standardPixmap( const QString &pixmapName );
	QPixmap	actionPixmap( const QString &className, PixmapMode mode, PixmapState state );

	static int	getNumPrimitiveElements();
	static int	getNumPixelMetrics();
	static int	getNumStyleHints();
	static int	getNumStandardPixmaps();
	static int	getNumTextStyles();

	static QString	getPrimitiveElementName( int which );
	static QString	getPixelMetricName( int which );
	static QString	getStyleHintName( int which );
	static QString	getStandardPixmapName( int which );
	static QString	getTextStyleName( int which );

	static int	findPrimitiveElement( const QString &name );
	static int	findPixelMetric( const QString &name );
	static int	findStyleHint( const QString &name );
	static int	findStandardPixmap( const QString &name );
	static int	findTextStyle( const QString &name );

public:

	// ------------- Convenience functions
	static QPixmap*		adjustHSV( QImage img, const QColor &c, const QColor &bgColor, bool blend );
	static QImage		adjustHSVImage( QImage img, const QColor &c, const QColor &bgColor, bool blend );
	static void			adjustHSV( QPixmap &pix, const QColor &c );
	static void			adjustHSV( QPixmap &pix, QPalette::ColorRole role );
	static QImage		fadeHSVImage( QImage img, const QColor &c, const QColor &bgColor );
	static void			blendImage( QImage front, QImage back );
	static QString		getComponentsPath() { return dzApp->getResourcesPath() + "/images/components"; }
	static QString		getIconsPath() { return dzApp->getResourcesPath() + "/images/icons"; }
	static QIcon		icon( StandardPixmap stylepixmap );
	static QIcon		icon( const QPixmap &def, const QPixmap &on, const QPixmap &dis,
								const QPixmap &disOn, const QPixmap &act, const QPixmap &actOn );
	static QIcon		icon( const QPixmap &def, const QPixmap &on, const QPixmap &dis,
							const QPixmap &disOn, const QPixmap &act, const QPixmap &actOn, 
							const QPixmap &sel, const QPixmap &selOn );
	static QPixmap		findStandardPixmapForState( QStyle *style, QStyle::StandardPixmap standard,
							QStyle::State state, QWidget const *widget = 0 );
	bool				primitiveHasDrawList( QStyle::PrimitiveElement pe ) const;
	static void			setDefaultHintsAndMetrics( int *metrics, int *hints );

	static PrimitiveElement	getPrimitiveElement( int which );
	static PixelMetric		getPixelMetric( int which );
	static StyleHint		getStyleHint( int which );
	static StandardPixmap	getStandardPixmap( int which );
	static TextStyle		getTextStyle( int which );

	static PrimitiveElement	nameToPrimitiveElement( const QString &name );
	static QString			primitiveElementToName( PrimitiveElement pe );
	static PixelMetric		nameToPixelMetric( const QString &name );
	static QString			pixelMetricToName( PixelMetric pm );
	static StyleHint		nameToStyleHint( const QString &name );
	static QString			styleHintToName( StyleHint sh );
	static StandardPixmap	nameToStandardPixmap( const QString &name );
	static QString			standardPixmapToName( StandardPixmap sp );
	static TextStyle		nameToTextStyle( const QString &name );
	static QString			textStyleToName( TextStyle ts );

signals:

	void	interfaceColorsChanged();

private:
	// DzStyleInterface methods
	virtual QRect	commonStyleSubElementRect( QStyle::SubElement subElement, const QStyleOption *option, QWidget const *widget ) const;
	virtual QRect	systemStyleSubElementRect( QStyle::SubElement subElement, const QStyleOption *option, QWidget const *widget ) const;
	virtual QSize	systemStyleSizeFromContents( QStyle::ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget ) const;

	// Disable copying for this style.
	DzStyle( const DzStyle & );
	DzStyle&	operator=( const DzStyle & );

	DzError	loadStyleDefinition( const QString &name );

	void	drawComplexControlComboBox(QStyleOptionComboBox const *opt, QPainter *p, QComboBox const *widget) const;
	void	drawComplexControlToolButton(QStyleOptionToolButton const *opt, QPainter *p, QToolButton const *w) const;
	void	drawComplexControlScrollBar(QStyleOptionSlider const *opt, QPainter *p, QScrollBar const *w) const;
	void	drawComplexControlScrollBarRect(State sflags, SubControl subControls, ControlElement element,
				QStyleOptionSlider const *option, QPainter *painter, QWidget const *widget, QRect extraRect = QRect()) const;
	void	drawComplexControlSlider(QStyleOptionComplex const *opt, QPainter *p, QSlider const *w) const;
	void	drawComplexControlListView(QStyleOptionQ3ListView const *opt, QPainter *p, QWidget const *w) const;
	bool	itemHasVisibleChildren( Q3ListViewItem *item ) const;
	void	drawComplexControlNumericSlider(QStyleOptionComplex const *opt, QPainter *p, const DzSlider *slider) const;
	void	drawComplexControlStyledNumericSlider(QStyleOptionComplex const *opt, QPainter *p, const DzSlider *slider) const;

	void	drawComplexControlDividerBar(const QStyleOptionComplex *opt, QPainter *p, DzDividerBar const *w) const;
	void	drawComplexControlMouseOverSlider(QStyleOptionComplex const *opt, QPainter *p, const DzSlider *slider) const;
	void	drawControlScrollBar(QStyle::PrimitiveElement pe, QStyleOption const *opt, QPainter *p, QWidget const *w) const;
	void	drawControlPushButton(QStyleOptionButton const *opt, QPainter *p, QPushButton const *btn) const;
	void	drawControlPushButtonLabel(QStyleOptionButton const *opt, QPainter *p, QPushButton const *btn) const;
	void	drawControlCheckBoxLabel(QStyleOption const *opt, QPainter *p,QWidget const *lbl) const;
	void	drawControlTabBarTab(QStyleOptionTabV3 const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlTabBarTabShape(QStyleOptionTabV3 const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlTabBarTabLabel(QStyleOptionTabV3 const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlProgressBarGroove(QStyleOptionProgressBarV2 const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlProgressBarContents(QStyleOptionProgressBarV2 const *opt, QPainter *p, QProgressBar const *progress) const;
	void	drawControlProgressBarLabel(QStyleOptionProgressBarV2 const *opt, QPainter *p, QProgressBar const *widget) const;
	void	drawControlMenuBarItem(QStyleOptionMenuItem const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlMenuBarEmptyArea(QStyleOption const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzTabOptionsButton(QStyleOptionButton const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzAHButton(QStyleOptionButton const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzAHUpButton(QStyleOptionButton const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzAHDnButton(QStyleOptionButton const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzAHRButton(QStyleOptionButton const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzAHLButton(QStyleOptionButton const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzDockWindowTitleBar(QStyleOption const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlDzWidgetGroupBar(QStyleOption const *opt, QPainter *p, DzWidgetGroupBar const *groupBar) const;
	void	drawControlDzMouseOverButton(PrimitiveElement element, QStyleOptionButton const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlRadioButtonLabel(QStyleOption const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlToolBoxTabLabel(QStyleOption const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlMenuItem(QStyleOption const *opt, QPainter *p, QWidget const *widget) const;
	void	drawControlToolBar(ControlElement element, const QStyleOption *opt,QPainter *p, const QWidget *widget) const;
	void	drawControlHeaderSection(ControlElement element, const QStyleOption *opt,QPainter *p, const QWidget *widget) const;
	QRect	subControlRectScrollBar( const QScrollBar *sb, SubControl subcontrol,
										const QStyleOptionComplex *opt ) const;
	QRect	subControlRectNumericSlider( const DzSlider *slider, SubControl subcontrol,
										const QStyleOptionComplex *opt ) const;
	QRect	subControlRectMouseOverSlider( const DzSlider *slider, SubControl subcontrol,
										const QStyleOptionComplex *opt ) const;

	void				setDefaults();
	void				setDefaultColors( QPalette::ColorGroup role );
	void				setColor( QPalette::ColorRole role, const QColor &color );
	int					addInterfaceColor( const QString &name, const QString &desc, const QColor &defColor );
	void				clearInterfaceColors();
	void				addActionIcon( const QString &name, DzStyleIcon *icon );
	void				clearActionIcons();
	void				setPixelMetric( QStyle::PixelMetric pm, int value );
	static void			setPixelMetric( QStyle::PixelMetric pm, int value, int *metrics );
	void				setStyleHint( QStyle::StyleHint sh, int value );
	static void			setStyleHint( QStyle::StyleHint sh, int value, int *hints );
	DzStylePixmap*		getStylePixmap( QStyle::StandardPixmap sp );
	DzStylePrimitive*	getPrimitive( QStyle::PrimitiveElement pe ) const;
	DzStyleTextStyle*	getTextStyle( TextStyle ts );

	static void	addPrimitiveElement( DzStylePrimitiveItem *item );
	static void	addPixelMetric( DzStylePixelMetricItem *item );
	static void	addStyleHint( DzStyleHintItem *item );
	static void	addStandardPixmap( DzStandardPixmapItem *item );
	static void	addTextStyle( DzStyleTextStyleItem *item );

	struct	Data;
	Data	*m_data;
};

/**
	Struct to combine QStyle::State with additional DAZ state flags.
**/
class DzExtendedStateBundle
{
public:
	DzExtendedStateBundle(QStyle::State _state = QStyle::State_None,
		DzStyle::ExtendedState _extended = DzStyle::ExtendedState_None)
		: state(_state),
		extendedState(_extended)
	{
	}

	QStyle::State			state;
	DzStyle::ExtendedState	extendedState;
};

#endif // DAZ_STYLE_H
