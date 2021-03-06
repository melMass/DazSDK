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
	Defines the DzSkeleton class.
**/

#ifndef DAZ_FIGURE_H
#define DAZ_FIGURE_H

/*****************************
	Include files
*****************************/

#include "dzskeleton.h"

/****************************
	Forward declarations
****************************/

struct DzGraftingPnt;
class DzSkinBinding;

/*****************************
	Class definitions
*****************************/
class DzFigure;

typedef QList< QPointer<DzFigure> > DzWeakFigureList;
typedef QListIterator< QPointer<DzFigure> > DzWeakFigureListIterator;

class DZ_EXPORT DzFigure : public DzSkeleton {
	Q_OBJECT
	friend class DzFigureFactory;
public:
	//
	// CREATORS
	//

	DzFigure();
	virtual ~DzFigure();

	//
	// REIMPLEMENTATIONS
	//

	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	virtual void			update( bool isRender = false );
	virtual void			finalize( bool isRender = false, bool allowResChange = true );
	virtual void			setObject( DzObject *object );
	virtual QPixmap			getPixmap( QStyle::State state = QStyle::State_None ) const;
	virtual QIcon			getIcon() const;

	virtual void			draw( const DzDrawStyle &style ) const;
	virtual void			render( const DzRenderSettings &settings ) const;
	
	const int*				getFollowTargetHiddenFacesPtr() const;
	void					setFollowTargetHiddenFaces( const QVector<int> &faces );

	void					setWeldPointsFromFaceList( DzFigure *target, const QVector<int> &faces );

	DzWeakFigureListIterator graftFigureIterator() const;
	DzWeakFigureList		getGraftFigureList() const;
	bool					acceptGraftFigure( const DzFigure *other );
	bool					acceptCullFigure(const DzFigure* other);

	DzWeakFigureListIterator cullFigureIterator() const;
	DzWeakFigureList		 getCullFigureList() const;

public:
	const DzGraftingPnt*	getWeldPoints() const;
	void					setWeldPoints( const QVector<DzGraftingPnt> &weld );

public slots:

	DzSkinBinding*	getSkinBinding() const;

	int			getNumGraftFigures() const;
	DzFigure*	getGraftFigure( int which ) const;

	int			getNumCullFigures() const;
	DzFigure*	getCullFigure( int which ) const;

	int		getFollowTargetFaceCount() const;
	void	setFollowTargetFaceCount( int num );

	int		getFollowTargetVertexCount() const;
	void	setFollowTargetVertexCount( int num );

	int		getNumFollowTargetHiddenFaces() const;
	void	presizeFollowTargetHiddenFaces( int num );
	void	addFollowTargetHiddenFace( int faceIdx );
	void	clearFollowTargetHiddenFaces();		
	bool	isGraftFollowing() const;

	int		getNumWeldPoints() const;
	int		getFollowerWeldIndex( int which ) const;
	int		getFollowTargetWeldIndex( int which ) const;
	void	presizeWeldPoints( int num );
	void	addWeldPoint( int followerIdx, int targetIdx, bool notifyChange = true );

#ifndef Q_MOC_RUN
	static
#endif
	DzFigure*	convertPropToFigure( DzNode *srcNode, const QString &rootBoneName, bool localMaps = true, bool inheritSkeleton = true );

signals:

	void	followTargetHiddenListChanged();
	void	weldListChanged();
	void	graftListChanged();
	void	cullingListChanged();

protected:

	DzFigure( const DzInFile *file );

	virtual void	makePureVirtual() { };
	virtual void	removeFollower( DzSkeleton *oldFollower );
	virtual void	addFollower( DzSkeleton *newFollower );
	void			setIsGraftFollowing( bool onOff );

	virtual DzBox3			calcLocalBoundingBox() const;
	virtual DzOrientedBox3	calcLocalOrientedBoundingBox() const;

private slots:		

	void	graftRemoved();
	void	graftReAdded();
	void	rebuildGrafts();
	void	modifyGeometryAsset();	

private:

	bool	removeGraftFollower( DzSkeleton *oldFollow );
	virtual DzFollowHelper*	createFollowHelper();
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FIGURE_H
