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
	Defines the DzElement class.
**/

#ifndef DAZ_ELEMENT_H
#define DAZ_ELEMENT_H

/*****************************
	Include files
*****************************/

#include <QtCore/QStringList>

#include "dzbase.h"
#include "dzscriptcontext.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzElementClipboard;
class DzPropertyGroupTree;
class DzSettings;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzElement : public DzBase {
	Q_OBJECT
	friend class DzProperty;
	friend class DzPropertyListUndoItem;
	friend class DzObjectModifierLoadHelper;
public:
	//
	// CREATORS
	//

	DzElement( const QString &name = QString::null );
	virtual ~DzElement();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			save( DzOutFile *file ) const;

public slots:

	//
	// MANIPULATORS
	//
	virtual DzElement*	setAttributes( const DzSettings *settings );
	virtual void		setName( const QString &name );
	virtual DzError		setLabel( const QString &name );
	virtual void		update();
	void				clearAnimData( const DzTimeRange &range );
	void				clearAllAnimData();

	//Standard Properties
	DzError			addProperty( DzProperty *prop );
	DzError			insertProperty( int index, DzProperty *prop );
	DzError			removeProperty( DzProperty *prop );
	DzError			removeProperty( const QString &name );
	DzError			moveProperty( DzProperty *prop, DzElement *element );

	//Private Properties
	DzError			addPrivateProperty( DzProperty *prop );
	DzError			insertPrivateProperty( int index, DzProperty *prop );
	DzError			removePrivateProperty( DzProperty *prop );
	DzError			removePrivateProperty( const QString &name );
	DzError			movePrivateProperty(DzProperty *prop, DzElement *element);
	
	DzError			addDataItem( DzElementData *item );
	DzError			removeDataItem( DzElementData *item );
	DzError			deleteDataItem( DzElementData *item );
	virtual void	copyFrom( const DzElement *source );
	void			setLoadScript( DzScript *script );
	
	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();

	virtual bool		shouldSortOnLoad() const;
	
public:
	//
	// ACCESSORS
	//
	DzPropertyListIterator	privatePropertyListIterator() const;
	DzPropertyListIterator	propertyListIterator() const;
	DzElementListIterator	elementChildIterator() const;

public slots:

	QString						getLabel() const;
	
	virtual void				getAttributes( DzSettings *settings ) const;
	//Standard Properties
	int							getNumProperties() const;
	DzProperty*					getProperty( int index ) const;
	QObjectList					getPropertyList() const;
	bool						isPropertyNameUnique( QString &name, bool makeUnique = false ) const;
	DzProperty*					findProperty( const QString &name ) const;
	DzProperty*					findProperty( const QString &name, bool caseSensitive ) const;
	DzProperty*					findPropertyByLabel( const QString &label ) const;
	DzProperty*					findPropertyByLabel( const QString &label, bool caseSensitive ) const;
	DzPropertyGroupTree*		getPropertyGroups() const;
	virtual DzProperty *		findMatchingProperty( DzProperty *srcProp);
	//Private Properties
	int							getNumPrivateProperties() const;
	DzProperty*					getPrivateProperty( int index ) const;
	QObjectList					getPrivatePropertyList() const;
	bool						isPrivatePropertyNameUnique( QString &name, bool makeUnique = false ) const;
	DzProperty*					findPrivateProperty( const QString &name ) const;
	DzProperty*					findPrivateProperty( const QString &name, bool caseSensitive ) const;
	DzProperty*					findPrivatePropertyByLabel( const QString &label ) const;
	DzProperty*					findPrivatePropertyByLabel( const QString &label, bool caseSensitive ) const;
	DzPropertyGroupTree*		getPrivatePropertyGroups() const;
	

	int							getNumDataItems() const;
	DzElementData*				getDataItem( int index ) const;
	QObjectList					getDataItemList() const;
	bool						isDataItemNameUnique( QString &dataName, bool makeUnique = false ) const;
	DzElementData*				findDataItem( const QString &dataName ) const;
	DzScript*					getLoadScript() const;
	virtual DzElementClipboard*	copyToClipboard( const QStringList &contentTypes = QStringList() ) const;
	int							getNumElementChildren() const;
	DzElement*					getElementChild( int which ) const;
	DzElement*					getElementParent() const;
	bool						inEdit() const;

	void						duplicateMissingCustomData(DzElement* tgt)const;
	void						duplicateMissingProperties(DzElement* tgt)const;
	void						duplicateMissingPrivateProperties(DzElement* tgt)const;

signals:

	void			propertyAdded( DzProperty *prop );
	void			propertyRemoved( DzProperty *prop );
	void			propertyListChanged();
	void			propertyTreeChanged();

	void			privatePropertyAdded( DzProperty *prop );
	void			privatePropertyRemoved( DzProperty *prop );
	void			privatePropertyListChanged();
	void			privatePropertyTreeChanged();

	void			labelChanged( const QString &newLabel );
	void			parentChanged();

protected:
	DzElement( const DzElement* element, bool copyDataItems = true );

	void			addElementChild( DzElement *child );
	void			removeElementChild( DzElement *child );
	void			setIsPropertyTreeOwnedByParent( bool onoff );
	bool			getIsPropertyTreeOwnedByParent() const;


private:

	void						setElementParent( DzElement *elem, bool regroup );
	void						regroupProperties( DzPropertyGroupTree *tree );
	void						regroupPrivateProperties( DzPropertyGroupTree *tree );
	static DzPropertyGroupTree*	defaultPropertyGroupTree();
	DzError						addPropertyToList( DzProperty *prop );
	void						addPropertyInternal( DzProperty * newprop );
	DzError						insertPropertyInList( int &index, DzProperty *prop );

	DzError						addPrivatePropertyToList( DzProperty *prop );

	void addPrivatePropertyInternal( DzProperty * newprop );
	DzError						insertPrivatePropertyInList( int &index, DzProperty *prop );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzElementClipboard : public QObject {
	Q_OBJECT
	friend class DzElement;
public:
	virtual ~DzElementClipboard();

public slots:

	virtual DzError	paste( DzElement *elem, const QStringList &contentTypes = QStringList() ) const;
	QString			getElementName() const;

protected:
	DzElementClipboard( const DzElement *elem, const QStringList &contentTypes );

private:
	struct	Data;
	Data	*m_data;
};

class DzElemLoadScriptContext : public DzScriptContext {
	Q_OBJECT
public:
	DzElemLoadScriptContext( DzElement *elem );

public slots:

	DzElement*	element() const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_ELEMENT_H
