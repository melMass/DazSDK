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
	Defines the DzProperty class.
**/

#ifndef DAZ_PROPERTY_H
#define DAZ_PROPERTY_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "idzsceneasset.h"
#include "dztimerange.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzGeometryRegion;
class DzPresentation;
class DzPropertyClipboard;
class DzPropertyGroupTree;
class DzPropertySettings;
class DzPropertyClipboard;
class DzGeometryRegion;
struct DzPropertyDefinition;
 
/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzProperty : public DzBase, public DzSceneAsset {
	Q_OBJECT
	Q_INTERFACES( IDzSceneAsset )
	friend class DzElement;
	friend class DzNode;
	friend class DzController;
	friend class DzPropertyGroup;
	friend class DzRiggingPropertyListUndoItem;
	friend class DzPropertyListUndoItem;
	friend class DzPropertyGroupUndoItem;
	friend class DzPropertyFlagsUndoItem;
public:
	//
	// CREATORS
	//

	DzProperty();
	DzProperty( const QString &name, bool canAnimate, bool isUserProperty );
	virtual ~DzProperty();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	virtual void			postLoadFile( const DzInFile *file );
	virtual const QObject*	toQObject() const;
	virtual QObject*		toQObject();
	virtual AssetType		getAssetType() const;
	virtual QString			getAssetId() const;
	virtual DzPropertyDefinition* getPropertyDefinition()const;
	int						getFlags()const;
	virtual DzProperty*		duplicate()const = 0;
	
	static  DzProperty*		ensurePropertyType( DzProperty* prop, const DzProperty* srcProp);
	template<typename T>
	static inline T* typedDuplicate( const T* srcProp ){
		DzProperty* newProp = srcProp->duplicate();
		return static_cast<T*>( ensurePropertyType(newProp,srcProp) );
	}	
	struct	Data;

public slots:

	//
	// MANIPULATORS
	//

	virtual void	beginEdit();
	virtual void	finishEdit();
	virtual void	cancelEdit();
	virtual bool	isEditing() const;
	void			setLabel( const QString &label );
	void			setHidden( bool yesNo );
	void			setPath( const QString &path );
	void			setIsUserProperty( bool yesNo );
	void			setIsRigProperty( bool yesNo );
	virtual void	setCanAnimate( bool yesNo );
	virtual void	selectKey( int i, bool onOff = true );
	virtual int		selectKeys( const DzTimeRange &range, bool onOff );
	virtual int		selectAllKeys( bool onOff = true );
	virtual int		deleteKeys( const DzTimeRange &interval );
	virtual int		deleteKeys( int start, int end );
	virtual int		deleteSelectedKeys();
	virtual void	deleteAllKeys();
	virtual void	copyFrom( DzProperty *prop ) = 0;
	virtual void	lock( bool onOff );
	virtual void	removeController( int idx );
	virtual void	removeController( DzController *ctrl );
	virtual void	removeAllControllers();
	virtual bool	moveControllerToIndex( int curIdx, int newIdx );
	virtual bool	moveControllerToIndex( DzController *ctrl, int newIdx );
	virtual void	setCurrentAttributesAsDefinition();
	virtual bool	doCurrentAttributesMatchDefinition()const;
	QString			getGroupOnlyPath() const;
	void			setIsManipulator( bool onOff );
	void			setIsFavorite( bool onOff );
	void			setIsGlobalFavorite( bool onOff );
	void			setSelected( bool onOff );
	virtual void	setCanAutoFollow( bool onOff );
	void			setOverrideControllers( bool onOff );
	void			setNew( bool onOff );
	virtual void	setAttributes( const DzPropertySettings &settings );
	void			setAttributes( const DzPropertySettings *settings );
	void			removeController( DzProperty *prop );
	virtual bool	isCombinable( DzProperty *prop );
	virtual bool	currentValueIsDefaultValue() const = 0;
	DzProperty*		findMatchingProperty( DzNode *node );

	virtual DzPresentation*	getPresentation() const;
	virtual void			setPresentation( DzPresentation *pres );

	DzGeometryRegion*	getRegion() const;
	void				setRegion( DzGeometryRegion *reg );
	void				clearRegion( bool preservePath = true );
	virtual bool		modifyAsset();
	virtual bool		modifyAsset( const DzUri &newUri );
	DzProperty*			propertyDuplicate()const;
public:
	//
	// ACCESSORS
	//

	virtual DzControllerListIterator	controllerListIterator() const;
	virtual DzControllerListIterator	slaveControllerListIterator() const;
	bool								definitionLoadFromDAZ()const;

public slots:

	virtual bool		isNumeric() const = 0;
	virtual bool		isAlias() const;
	virtual DzProperty*	getAliasTarget() const;
	virtual DzProperty*	createAlias() = 0;
	QString				getLabel() const;
	virtual bool		canAnimate() const;
	bool				isUserProperty() const;
	bool				isRigProperty() const;
	bool				isPrivateProperty() const;
	bool				isHidden() const;
	DzElement*			getOwner() const;
	DzPropertyGroup*	getGroup() const;
	QString				getPath() const;
	virtual bool		hasKeys() const;
	virtual int			getNumKeys() const;
	virtual int			getNumKeys( const DzTimeRange &range ) const;
	virtual DzTimeRange	getKeyRange() const;
	virtual DzTimeRange	getSelectedKeyRange() const;
	virtual int			getNumSelectedKeys() const;
	virtual DzTime		getKeyTime( int i ) const;
	virtual int			getKeyIndexRange( const DzTimeRange &iv, int &start ) const;
	virtual bool		isKey( DzTime t, int &index ) const;
	virtual bool		isKeySelected( int i ) const;
	virtual bool		isLocked() const;
	virtual QString		getWidgetClass(bool styled=true) const = 0;

	virtual int				getNumControllers() const;
	virtual DzController*	getController( int idx ) const;
	virtual QObjectList		getControllerList() const;
	virtual bool			hasControllers() const;

	virtual int				getNumSlaveControllers() const;
	virtual int				getIndexOfSlaveControllers(DzController* cntrl) const;
	virtual DzController*	getSlaveController( int idx ) const;
	virtual QObjectList		getSlaveControllerList() const;
	virtual bool			hasSlaveControllers() const;

	bool			isManipulator() const;
	bool			isFavorite() const;
	bool			isGlobalFavorite() const;
	bool			isSelected() const;
	bool			canAutoFollow() const;
	bool			isOverridingControllers() const;
	bool			isNew() const;
	virtual void	getAttributes( DzPropertySettings &settings ) const;
	void			getAttributes( DzPropertySettings *settings ) const;
	void			emitRemoved() { emit removed(); }

	int			getNumAliases() const;
	DzProperty*	getAlias( int index ) const;

	virtual DzPropertyClipboard*	copyToClipboard() const;

signals:

	void	labelChanged( const QString &newLabel );
	void	hiddenChanged( bool hidden );
	void	isFavoriteChanged( bool onOff );
	void	isGlobalFavoriteChanged( bool onOff );
	void	groupChanged( DzPropertyGroup *newGroup );
	void	selectionStateChanged();
	void	newStateChanged();
	void	propertyDeleted( DzProperty *thisProperty );
	void	removed();
	void	presentationIconChanged();
	void	regionChanged();

#ifndef Q_MOC_RUN
private:
#endif
	void	currentValueChanged();
	void	valueChanged( const DzTimeRange &range );
	void	isUserPropertyChanged( bool isUserProp );
	void	isManipulatorChanged( bool isManip );
	void	canAnimateChanged( bool enabled );
	void	keySelectionChanged( const DzTimeRange &range );
	void	lockStateChanged();
	void	canAutoFollowChanged( bool canAutoFollow );
	void	overridingControllersChanged( bool overriding );
	void	editFinished();
	void	assetModified();
	void	assetWasSaved();

protected slots:
	void	emitCurrentValueChanged();
	void	emitValueChanged( const DzTimeRange &range );
	void	emitIsUserPropertyChanged( bool isUserProp );
	void	emitIsManipulatorChanged( bool isManip );
	void	emitCanAnimateChanged( bool enabled );
	void	emitKeySelectionChanged( const DzTimeRange &range );
	void	emitLockStateChanged();
	void	emitCanAutoFollowChanged( bool canAutoFollow );
	void	emitOverridingControllersChanged( bool overriding );
	void	emitEditFinished();

protected:
	friend struct Data;

	DzProperty( DzProperty::Data *data );
	DzProperty( const QString &name, bool canAnimate, bool isUserProperty, DzProperty::Data *data );

	Data	*m_d;

	virtual void	setFlags( unsigned int flags );
	void			insertController( DzController *controller, int idx = -1 );
	bool			valueIsReplaced() const;
	void			addAlias( DzProperty *alias );
	void			copyBaseData(DzProperty* prop)const;
	static void		removeAlias( DzProperty *prop, const DzProperty *alias );
	static void		addAlias( DzProperty *prop, const DzProperty *alias );

	virtual void	setOwner( DzElement *owner );
	virtual void	addSlaveController(DzController* control);
	virtual void	removeSlaveController(DzController* control);

private slots:

	void	updateTime();
	void	updateControllerState();
	void	setIsPrivateProperty( bool yesNo );

private:
	
	void	regroup( DzPropertyGroupTree *tree );
	void	setGroup( DzPropertyGroup *group );
	void	clearGroup();
};

class DZ_EXPORT DzPropertyClipboard : public QObject {
	Q_OBJECT
	friend class DzProperty;
public:
	virtual ~DzPropertyClipboard();

public slots:

	virtual DzError	paste( DzProperty *prop ) const;

protected:
	DzPropertyClipboard( const DzProperty *prop );

private:
	struct	Data;
	Data	*m_data;
};

inline uint qHash( const QPointer<DzProperty> &key ) { return qHash( key.data() ); }

#endif // DAZ_PROPERTY_H
