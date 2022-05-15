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

#ifndef DAZ_REGISTRATION_H
#define DAZ_REGISTRATION_H

/****************************
	Forward declarations
****************************/

class QString;
class QStringList;
class DzActivationPolicy;
class DzGuid;

/*****************************
	Class definitions
*****************************/

class DzRegistration {
	friend class DzPlugin;
	friend class DzPluginMgr;
public:
	DzRegistration();
	DzRegistration( const DzRegistration &reg );
	~DzRegistration();

	DzRegistration&	operator=( const DzRegistration &reg );

	void	setActivationPolicy( const DzGuid &guid, DzActivationPolicy *policy );
	void	addRegistrationPrefix( const QString &prefix, const QString &description );
	bool	alreadyRegistered();
	bool	withinEvaluationPeriod();
	QString	getEvaluationInformation() const;

private:

	QStringList	getPrefixes() const;
	QString		getPrefixDescription( const QString &prefix ) const;
	bool		validateSerialNumber( const QString &serialNumber, bool saveIfValid );
	bool		usesRegistration();

	struct	Data;
	Data	*m_data;
};

#endif //DAZ_REGISTRATION_H
