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
	Defines the DzJsonDom classes
**/

#ifndef DZ_JSON_DOM_H
#define DZ_JSON_DOM_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"
#include "idzjsonio.h"
#include "dztsharedpointer.h"

/****************************
	Class definitions
****************************/

class DzJsonArray;
class DzJsonObject;
class DzJsonElement;

typedef QList<DzJsonElement> DzJsonElementList;
typedef QListIterator<DzJsonElement> DzJsonElementIterator;

class DZ_EXPORT DzJsonElement
{
public:
	friend class DzJsonArray;
	friend class DzJsonObject;

	DzJsonElement();
	DzJsonElement( const DzJsonElement& elem );
	explicit DzJsonElement(const QString& str );
	explicit DzJsonElement(const char* str );
	explicit DzJsonElement(bool val );
	explicit DzJsonElement(double val );
	explicit DzJsonElement(int val );
	explicit DzJsonElement(unsigned int val );

	virtual ~DzJsonElement();

	DzJsonElement& operator=(const DzJsonElement &def);

	enum ElementType{ Null, Object, Array, Boolean, Number, String };
	ElementType elementType() const;

	DzJsonObject toObject()const;
	DzJsonArray  toArray()const;

	QString	stringValue(const QString& name=QString())const;
	bool	boolValue(bool defVal = false)const;
	double	numberValue(double defVal=0)const;

	bool	isNull()const;
	bool	isObject()const;
	bool	isArray()const;
	bool	isStringValue()const;
	bool	isNumberValue()const;
	bool	isBooleanValue()const;

	DzJsonElement clone()const;
	bool	write( IDzJsonIO* io )const;
	bool	write( const QString& member, IDzJsonIO* io )const;

	bool	isSameElement(const DzJsonElement& other)const;
	bool	isEquivalent(const DzJsonElement& other, double tolerance=0.000000000001 )const;

	struct Data;
protected:
	DzTSharedPointer<Data> m_data;

	DzJsonElement(Data* data);
};

struct DZ_EXPORT DzJsonMember
{
	DzJsonMember();
	DzJsonMember(const QString& tag, const DzJsonElement& val);

	QString m_tag;
	DzJsonElement m_value;
};

typedef QList<DzJsonMember> DzJsonMemberList;
typedef QListIterator<DzJsonMember> DzJsonMemberIterator;

class DZ_EXPORT DzJsonObject : public DzJsonElement
{
public:
	friend class DzJsonElement;

	DzJsonObject();
	DzJsonObject(const DzJsonObject& obj);
	virtual ~DzJsonObject();
	
	int			  getNumMembers()const;
	bool		  isEmpty()const;

	DzJsonMemberList getMembers()const;
	DzJsonMemberIterator memberIterator()const;
	void		  setMembers(const DzJsonMemberList& items);

	DzJsonElement getMember(const QString& name)const;
	ElementType	  getMemberElementType(const QString& name)const;
	bool		  hasMember(const QString& name)const;

	void		  clear();
	void		  removeMember(const QString& name);
	bool		  shouldMultiLine()const;
	
	DzJsonObject  startMemberObject( const QString& name );
	DzJsonArray   startMemberArray( const QString& name );
	void		  addMember(const QString& name, const DzJsonElement& item );
	void		  addMember(const QString& name, const QString& val );
	void		  addMember(const QString& name, const char* val );
	void		  addMember(const QString& name, bool val );
	void		  addMember(const QString& name, double val );
	void		  addMember(const QString& name, int val );
	void		  addMember(const QString& name, unsigned int val );
	void		  addMember(const QString& name, float val );
	void		  addMemberNull(const QString& name );

	bool		  writeToIO( IDzJsonIO* io, bool root=false )const;

private:
	struct Data;
	DzJsonObject(Data* data);
};

class DZ_EXPORT DzJsonArray : public DzJsonElement
{
public:
	friend class DzJsonElement;

	DzJsonArray();
	DzJsonArray(const DzJsonArray& obj);
	virtual ~DzJsonArray();

	bool				isEmpty()const;
	int					itemCount()const;
	DzJsonElement		getItem(int i);
	DzJsonElementList	getItems()const;
	DzJsonElementIterator itemIterator()const;

	void				setItems(DzJsonElementList items);
	void				clear();
	void				removeItem(int i);
	bool				shouldMultiLine()const;

	DzJsonObject  startObject();
	DzJsonArray   startArray();
	void		  addItem(const DzJsonElement& item );
	void		  addItem(const QString& val );
	void		  addItem(const char* val);
	void		  addItem(bool val );
	void		  addItem(double val );
	void		  addItem(int val );
	void		  addItem(unsigned int val );
	void		  addItem(float val );
	void		  addItemNull();

	bool		  writeToIO( IDzJsonIO* io, bool root=false )const;

private:
	struct Data;
	DzJsonArray(Data* data);
};


class DZ_EXPORT DzJsonDomParser : public IDzJsonIO {
public:
	DzJsonDomParser();
	virtual ~DzJsonDomParser();

	DzJsonElement	getRoot()const;

	virtual bool	startObject( bool multiLine );
	virtual bool	startArray( bool multiLine );

	virtual bool	startMemberObject( const QString &name, bool multiLine );
	virtual bool	startMemberArray( const QString &name, bool multiLine );

	virtual bool	finishObject();
	virtual bool	finishArray();

	virtual bool	skipObject();
	virtual bool	skipArray();

	virtual bool	addMember( const QString &name, const QString &val );
	virtual bool	addMember( const QString &name, int val );
	virtual bool	addMember( const QString &name, float val );
	virtual bool	addMember( const QString &name, double val );
	virtual bool	addMember( const QString &name, bool val );
	virtual bool	addMemberNull( const QString &name );

	virtual bool	addItem( const QString &val );
	virtual bool	addItem( int val );
	virtual bool	addItem( float val );
	virtual bool	addItem( double val );
	virtual bool	addItem( bool val );
	virtual bool	addItemNull();

	virtual QString	getLastError();

private:
	void	popItem();
	
	struct Data;
	Data* m_data;
};

#endif // DZ_JSON_DOM_H