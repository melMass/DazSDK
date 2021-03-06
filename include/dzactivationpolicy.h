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
	Defines the DzActivationPolicy class.
**/

#ifndef DAZ_ACTIVATION_POLICY_H
#define DAZ_ACTIVATION_POLICY_H

/*****************************
	Include files
*****************************/

#include "dzrefcounteditem.h"

/****************************
	Forward declarations
****************************/

class DzGuid;

/*****************************
	Class definitions
*****************************/
class DZ_EXPORT DzActivationPolicy : public DzRefCountedItem
{
public:
	virtual ~DzActivationPolicy();

	virtual void		initialize( const DzGuid &guid ) {}
	virtual bool		activated() { return true; }
	virtual bool		usesRegistration() { return false; }
	virtual QString		getEvaluationInformation() const { return ""; }
};

class DZ_EXPORT DzNoEvaluationActivationPolicy : public DzActivationPolicy
{
public:
	virtual ~DzNoEvaluationActivationPolicy();

	virtual void		initialize( const DzGuid &guid ) {}
	virtual bool		activated() { return false; }
	virtual bool		usesRegistration() { return true; }
	virtual QString		getEvaluationInformation() const { return "Unregistered"; }
};

class DZ_EXPORT DzExpirationDateActivationPolicy : public DzActivationPolicy
{
public:
	DzExpirationDateActivationPolicy( int year, int month, int day );
	virtual ~DzExpirationDateActivationPolicy();

	void		initialize( const DzGuid &guid );
	bool		activated();
	bool		usesRegistration() { return true; }
	QString		getEvaluationInformation() const;

private:
	struct	Data; 
	Data	*m_data;
};

class DZ_EXPORT DzTrialDaysActivationPolicy : public DzActivationPolicy
{
public:
	DzTrialDaysActivationPolicy( int days );
	virtual ~DzTrialDaysActivationPolicy();

	void		initialize( const DzGuid &guid );
	bool		activated();
	bool		usesRegistration() { return true; }
	QString		getEvaluationInformation() const;

private:
	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_ACTIVATION_POLICY_H
