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
	Defines the DzSparseWeightMap class.
**/

#ifndef DAZ_SPARSE_WEIGHT_MAP_H
#define DAZ_WEIGHT_MAP_H

/*****************************
	Include files
*****************************/

#include "dzelement.h"
#include "dzstorable.h"
#include "dztarray.h"
#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class DzFloatProperty;
class DzWeightMap;

/*****************************
	Class definitions
*****************************/

#define DZ_WEIGHT_EPSILON 3.0518509476e-5f // 1/((2^15)-1)

class DZ_EXPORT DzSparseWeightMapValues : public DzStorable
{
	Q_OBJECT
public:
	
	DzSparseWeightMapValues();
	virtual ~DzSparseWeightMapValues();

	virtual void	setStorablePaths( const QString &path );
	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );	
	virtual void	writeData( DzOutFile *file ) const;
	virtual QString	getExtension() const { return "dsw"; }
	virtual QString	getFiletype() const { return "Weight Map Values"; };

	float*			getWeights();
	const float*	getWeights() const;
	float			getWeight( int idx ) const;
	int*			getIndices();
	const int*		getIndices() const;
	int				getIndex( int idx ) const;
	int				getNumWeights() const;
	void			setMaxWeights( int maxWeights );
	int				getMaxWeights() const;
	void			setWeight( int idx, float val );
	void			setIndex( int idx, int val );
	void			addWeight( int vIdx, float val );
	void			setNumWeights( int nWeights, bool keepExisting = false );
	void			empty();

public slots:

	void	setOverrideStorablePath( const QString &relativePath );
	QString	getOverrideStoreablePath() const;

private:

	bool	findIndex( int vIdx, int &idx );
	void	requireSpace( int num = 1 );

	struct	Data;
	Data	*m_data;
};

class DzSparseWeightMap;
typedef DzTSharedPointer<DzSparseWeightMap> DzSparseWeightMapPtr;
typedef DzTArray<DzSparseWeightMapPtr> DzSparseWeightMapList;
typedef DzTSharedPointer<DzSparseWeightMapValues> DzSparseWeightMapValuesPtr;

class DZ_EXPORT DzSparseWeightMap : public DzElement, public DzRefCountedItem {
	Q_OBJECT
	Q_PROPERTY( int numWeights READ getNumWeights )
	Q_PROPERTY( bool isEmpty READ isEmpty )
	friend class DzSparseWeightMapFactory;
public:
	DzSparseWeightMap( const QString &name = QString::null );
	DzSparseWeightMap( int maxWeights, const QString &name = QString::null );
	~DzSparseWeightMap();
	
	float*			getWeights();
	const float*	getWeights() const;

	int*			getIndices();
	const int*		getIndices() const;

	void					empty();
	DzSparseWeightMapPtr	copy();
	void					detach();
	bool					isEmpty() const;
	void					setMaxWeights( int maxWeights );
	int						getMaxWeights() const;
	int						getNumWeights() const;
	void					setWeightMapValues( DzSparseWeightMapValues *vals );
	DzSparseWeightMapValues*	getWeightMapValues() const;
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			postLoadFile( const DzInFile *file );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void			save( DzOutFile *file ) const;
	virtual void			setStorablePaths( const QString &path );

public slots:

	virtual void	setName( const QString &name );
	double			getWeight( int idx ) const;
	int				getIndex( int idx ) const;

	virtual void	beginEdit();
	virtual void	finishEdit();
	virtual void	cancelEdit();

	void			toWeightMap( DzWeightMap *map ) const;
	void			fromWeightMap( const DzWeightMap *map );

public:

	static DzError	normalizeMaps( DzSparseWeightMapList &weightMaps );
	static DzError	normalizeMaps( DzSparseWeightMapList &weightMaps, DzSparseWeightMap *priority, 
						DzSparseWeightMap *def = NULL );
	static DzError	normalizeWeights( DzTArray<float*> &weights );
	static DzError	normalizeWeights( DzTArray<float*> &weights, float priority, float *def = NULL );

signals:

	void	weightValuesChanged();

protected:

	DzSparseWeightMap( const DzInFile *file );

private:

	static DzError	buildWeightsList( DzSparseWeightMapList &weightMaps, DzTArray<unsigned short*> &weights,
						int &weightCount, DzSparseWeightMap *priority );

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_WEIGHT_MAP_H
