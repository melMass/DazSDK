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
	Defines the DzTextStyledLabel class.
**/

#ifndef DZ_TEXT_STYLED_LABEL_H
#define DZ_TEXT_STYLED_LABEL_H

/*****************************
	Include files
*****************************/

#include <QtGui/QLabel>

#include "dzstyle.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTextStyledLabel : public QLabel {
	Q_OBJECT
public:
	DzTextStyledLabel( DzStyle::TextStyle txt, QWidget *parent = NULL);
	virtual ~DzTextStyledLabel();

protected:
	virtual void	styleChange( QStyle &oldStyle );
	void			setupFromStyle();
private:
	struct	Data;
	Data	*m_data;
};
#endif // DZ_TEXT_STYLED_LABEL_H