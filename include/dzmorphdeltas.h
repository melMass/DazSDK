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
	Defines the DzMorphDeltas class.
**/

#ifndef DAZ_MORPH_DELTAS_H
#define DAZ_MORPH_DELTAS_H

/*****************************
	Include files
*****************************/

#include "dztypes.h"
#include "dzstorable.h"
#include "dzvec3.h"
#include "dztsharedpointer.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMorphDelta {
public:
	DzMorphDelta();
	DzMorphDelta( int vertIdx, const DzVec3 &vals );
	DzMorphDelta( int vertIdx, const DzPnt3 vals );
	DzMorphDelta( const DzMorphDelta &delta );

	DzMorphDelta&	operator=( const DzMorphDelta &delta );

	int				m_vertIdx;		/**< Vertex index for the delta */
	DzPnt3			m_vals;			/**< Delta vector */
	unsigned char	m_ignoreDelta;	/**< Delta Flag */
};

class DZ_EXPORT DzMorphDeltas : public DzStorable {
	Q_OBJECT
	Q_ENUMS( MapMethod )
public:

	//
	// CREATORS
	//

	DzMorphDeltas();
	virtual ~DzMorphDeltas();

	//
	// REIMPLEMENTATIONS
	//

#ifndef DSON_IO
	virtual void	loadSection( DzInFile *file, short sectionID );
#endif
	virtual void	setStorablePaths( const QString &path );
	virtual bool	usesDeferredLoading() const { return true; }
	virtual QString	getExtension() const { return "dsd"; }
	virtual QString	getFiletype() const { return "Morph Deltas"; }
	bool			needsSave( const QString &filename ) const;
	int				addDeltas( const DzIntArray &indexes, const DzTArray<DzVec3> &deltas,
								bool checkForDuplicates = true );
	int				addDeltas( const DzIntArray &indexes, const DzTArray<DzVec3> &deltas,const DzTArray<unsigned char> ignoreDeltaFlags,
								bool checkForDuplicates = true );
	void			clearVertCount();

public slots:

	//
	// MANIPULATORS
	//

	void	setVertCount( int vertCount );
	void	removeVertex( int vertIdx );
	void	removeDelta( int deltaIdx );
	void	preSize( int nDeltas );
	int		addDelta( int vertIdx, const DzVec3 &delta,
				bool checkForDuplicates = true, unsigned char deltaFlag = 0 );
	int		addDelta( int vertIdx, float deltaX, float deltaY, float deltaZ,
				bool checkForDuplicates = true, unsigned char deltaFlag = 0 );	
	DzError	setDelta( int index, const DzVec3 &delta );
	void	removeDuplicateDeltas();
	void	removeAllDeltas();
	bool	loadDeltas();
	void	unLoadDeltas();
	void	finishDeltasLoad();
	DzMorphDeltas*	removeIgnoredDeltas()const;
	
	DzMorphDeltas* copyDeltas()const;

public:

	DzMorphDelta*	getDeltas();

	//
	// ACCESSORS
	//

	const DzMorphDelta*	getDeltas() const;
	const float*		getDelta( int i ) const;

public slots:

	int		getVertCount() const;
	bool	hasDeltas() const;
	int		getNumDeltas() const;
	int		getDeltaIndex( int i ) const;
	DzVec3	getDeltaVec( int i ) const;
	int		getVertexDeltaIndex( int vertIdx ) const;

signals:

	void	deltaListChanged();
	void	deltaValueChanged();

protected:
	//////////////////////////////
	// from DzStorable
#ifndef DSON_IO
	virtual void	writeData( DzOutFile *file ) const;
#endif
private:

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzMorphDeltas> DzMorphDeltasPtr;

#endif // DAZ_MORPH_DELTAS_H
