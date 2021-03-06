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
	Defines the DzNodeDlg class.
**/

#ifndef DAZ_NODE_DIALOG_H
#define DAZ_NODE_DIALOG_H

/*****************************
	Include files
*****************************/

#include <QtGui/QAbstractItemView>

#include "dzbasicdialog.h"
#include "dztypes.h"

/****************************
	Forward declarations
****************************/

class DzNodeListFilter;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzNodeDlg : public DzBasicDialog {
	Q_OBJECT
public:

	DzNodeDlg( QWidget *parent, DzNode *initNode = NULL, const QString &nodeType = QString( "DzNode" ), 
		bool expanded = true, QAbstractItemView::SelectionMode mode = QAbstractItemView::SingleSelection,
		DzNodeListFilter *filter = NULL );
	DzNodeDlg( QWidget *parent, DzNode *initNode, const QString &nodeType, bool expanded, bool allowNone,
		QAbstractItemView::SelectionMode mode = QAbstractItemView::SingleSelection,
		DzNodeListFilter *filter = NULL );
	~DzNodeDlg();

	DzNode*		getNode() const;
	DzNodeList	getSelectedNodes() const;
	void		setMessage( const QString &message );
	bool		isEmpty();

protected:
	bool event( QEvent *e );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_NODE_DIALOG_H