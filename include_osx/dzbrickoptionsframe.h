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

#ifndef DZ_BRICK_OPTIONS_FRAME_H
#define DZ_BRICK_OPTIONS_FRAME_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzBrickParam;
class DzShaderBrick;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBrickOptionsFrame : public QFrame {
	Q_OBJECT
public:
	DzBrickOptionsFrame();
	virtual ~DzBrickOptionsFrame();

	virtual QPointF	getParamPosition( DzBrickParam *param ) const;
	QWidget*		getTopParent() const;

	virtual void			setFrameParent( QWidget *parent ) = 0;
	virtual void			setBrick( DzShaderBrick *brick ) = 0;
	virtual float			getParamVerticalPosition( DzBrickParam *param ) const = 0;
	virtual int				getParamHeight( DzBrickParam *param ) const = 0;
	virtual DzShaderBrick*	getShaderBrick() const = 0;

public slots:
	virtual bool	isRightToLeft();
	virtual void	setIsRightToLeft( bool onOff );

	bool	hidesAdvanced() const;
	void	setHideAdvanced( bool onOff );

signals:
	void	rightToLeftChanged();
	void	hideAdvancedChanged();

private:
	struct	Data;
	Data	*m_data;
};

#endif // DZ_BRICK_OPTIONS_FRAME_H
