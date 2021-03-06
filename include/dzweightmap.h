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
	Defines the DzWeightMap class.
**/

#ifndef DAZ_WEIGHT_MAP_H
#define DAZ_WEIGHT_MAP_H

/*****************************
	Include files
*****************************/
#ifndef DSON_IO
#include "dzelement.h"
#else
#include "dzbase.h"
#endif

#include "dzstorable.h"
#include "dztarray.h"
#include "dztsharedpointer.h"
#include "dztsimplearray.h"

/****************************
	Forward declarations
****************************/

class DzFloatProperty;

/*****************************
	Class definitions
*****************************/

#define DZ_WEIGHT_EPSILON 3.0518509476e-5f // 1/((2^15)-1)

class DZ_EXPORT DzWeightMapValues : public DzStorable
{
	Q_OBJECT
public:
	
	DzWeightMapValues();
	virtual ~DzWeightMapValues();
#ifndef DSON_IO
	virtual void			setStorablePaths( const QString &path );
	virtual void			loadSection( DzInFile *file, short sectionID );
	virtual void			setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );	
	virtual void			writeData( DzOutFile *file ) const;
#endif
	unsigned short*			getWeights();
	const unsigned short*	getWeights() const;
	unsigned short			getWeight( int idx ) const;
	float					getFloatWeight( int idx ) const;
	int						getNumWeights() const;
	void					setWeight( int idx, unsigned short val );
	void					setFloatWeight( int idx, float val );
	void					setNumWeights( int nWeights, bool keepExisting = false );
	void					empty();

public slots:

	virtual QString	getExtension() const { return "dsw"; }
	virtual QString	getFiletype() const { return "Weight Map Values"; };
	void			setOverrideStorablePath( const QString &relativePath );
	QString			getOverrideStoreablePath() const;

private:

	struct	Data;
	Data	*m_data;
};

class DzWeightMap;
typedef DzTSharedPointer<DzWeightMap> DzWeightMapPtr;
typedef QVector<DzWeightMapPtr> DzWeightMapList;
typedef DzTSharedPointer<DzWeightMapValues> DzWeightMapValuesPtr;


class DZ_EXPORT DzWeightMap : 
#ifndef DSON_IO
	public DzElement,
#else
	public DzBase,
#endif	
	public DzRefCountedItem {

	Q_OBJECT
	Q_PROPERTY( int numWeights READ getNumWeights )
	Q_PROPERTY( bool isEmpty READ isEmpty )
	friend class DzWeightMapFactory;
public:
	DzWeightMap( const QString &name = QString::null );
	DzWeightMap( int nWeights, const QString &name = QString::null );
	~DzWeightMap();

#ifndef DSON_IO
	virtual void	loadSection( DzInFile *file, short sectionID );
	virtual void	postLoadFile( const DzInFile *file );
	virtual void	setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void	save( DzOutFile *file ) const;
	virtual void	setStorablePaths( const QString &path );
#endif

	unsigned short*			getWeights();
	const unsigned short*	getWeights() const;
	unsigned short			getWeight( int idx ) const;
	void					setWeight( int idx, unsigned short value );
	void					getFloatWeights( DzTSimpleArray<float> &weights ) const;

	DzWeightMapPtr			copy();
	void					setWeightMapValues( DzWeightMapValues *vals );
	DzWeightMapValues*		getWeightMapValues() const;

#ifndef DSON_IO
	virtual void			getRiggingProperties( DzPropertyList &list );
#endif

	static float			weightToFloat( unsigned short weight );
	static unsigned short	floatToWeight( float val );

public slots:

	void				empty();
	void				detach();
	bool				isEmpty() const;
	void				setNumWeights( int nWeights, bool keepExisting = false );
	virtual void		setName( const QString &name );
	int					getNumWeights() const;
	double				getFloatWeight( int idx ) const;
#ifndef DSON_IO
	DzFloatProperty*	getStrengthController();
#endif
	bool				isPersistent() const;
	void				setPersistent( bool onoff );
	void				setLocked( bool onOff);
	bool				isLocked()const;

	virtual void		beginEdit();
	virtual void		finishEdit();
	virtual void		cancelEdit();

public:

	static DzError	normalizeMaps( DzWeightMapList &weightMaps, bool respectLocking = false );
	static DzError	normalizeMaps( DzWeightMapList &weightMaps, DzWeightMap *priority, DzWeightMap *def = NULL, bool respectLocking = false  );
	static DzError	normalizeMapsWithSymmetry( DzWeightMapList &weightMaps, DzWeightMap *priority, DzWeightMap *symMap, DzWeightMap *def = NULL, bool respectLocking = false);

signals:

	void	weightValuesChanged();

protected:

	DzWeightMap( const DzInFile *file );

private:

#ifndef DSON_IO
	void	createProperties();
#endif

	static DzError	buildWeightsList( DzWeightMapList &weightMaps, DzWeightMapList &newList,
						int &weightCount, DzWeightMap *priorityOne , DzWeightMap *priorityTwo );
	
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_WEIGHT_MAP_H
