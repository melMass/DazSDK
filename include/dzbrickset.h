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
 
#ifndef DZ_BRICK_SET_H
#define DZ_BRICK_SET_H

/*****************************
	Include files
*****************************/

#include "dzrefcounteditem.h"
#include "dzrenderer.h"

/****************************
	Forward declarations
****************************/

class DzCoShaderInfo;
class DzMatrix4;
class DzRenderSettings;
class DzShaderCompilerProcess;
class DzVec3;
class IDzBrickUser;
class QColor;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBrickSet : public QObject, public DzRefCountedItem
{
	Q_OBJECT		
	Q_ENUMS( ShaderType )
	Q_ENUMS( LightType )
	friend class DzBrickSetCompilerMgr;
	friend class DzShaderCompilerProcess;
public:
	
	enum ShaderType {
		None = 0,
		Surface,
		Light,
		LightArea,
		VolumeAtmosphere,
		VolumeInterior,
		VolumeExterior,
		Displacement,
		Imager
	};

	enum LightType {
		NullLight = 0,
		AmbientLight,
		PointLight,
		DistantLight,
		SpotLight
	};

	DzBrickSet( DzShaderBrick *rootBrick, IDzBrickUser *user );
	virtual ~DzBrickSet();

	virtual void	setName( const QString &newName );
	virtual QString getName() const;

public slots:

	QString	getNewToken();
	// Render-Time Functions
	void	setFloatAttrib( const QString &attrib, const QString &token, float val ) const;
	void	setIntegerAttrib( const QString &attrib, const QString &token, int val ) const;
	void	setColorAttrib( const QString &attrib, const QString &token, float r, float g, float b,bool isFloat = false ) const;
	void	setColorAttrib( const QString &attrib, const QString &token, const QColor &val ) const;
	void	setColorAttrib( const QString &attrib, const QString &token, const DzVec3 &vec ) const;
	void	setStringAttrib( const QString &attrib, const QString &token, const QString &val ) const;
	void	setPointAttrib( const QString &attrib, const QString &token, const DzVec3 &vec ) const;
	void	setVectorAttrib( const QString &attrib, const QString &token, const DzVec3 &vec ) const;
	void	setNormalAttrib( const QString &attrib, const QString &token, const DzVec3 &vec ) const;
	void	setMatrixAttrib( const QString &attrib, const QString &token, const DzMatrix4 &mtx ) const;

	void	setFloatToken( const QString &token, float val ) const;
	void	setIntegerToken( const QString &token, int val ) const;
	void	setColorToken( const QString &token, const QColor &val ) const;
	void	setStringToken( const QString &token, const QString &val ) const;
	void	setPointToken( const QString &token, const DzVec3 &vec ) const;
	void	setVectorToken( const QString &token, const DzVec3 &vec ) const;
	void	setNormalToken( const QString &token, const DzVec3 &vec ) const;
	void	setMatrixToken( const QString &token, const DzMatrix4 &mtx ) const;
	void	setDisplacementBound(float displacementBound)const;

	QColor	getBackgroundColor() const;
	//
	// ACCESSORS
	//

	DzElement		*getOwner() const;
	IDzBrickUser	*getBrickUserOwner() const;
	
	ShaderType		getShaderType() const;
	QString			getShaderFile() const;
	
	bool	isActiveInShadowPass() const;
	bool	isOnlyInShadowPass() const;
	bool	isActiveInBakePass() const;
	bool	isActiveInBeautyPass() const;

	DzShaderBrick*	getRoot() const;
	void			invalidateFiles();
	bool			allowsAutoBake() const;

	QString	getFullShaderPath() const;

	const DzRenderSettings*	getRenderSettings() const;
	const DzRenderSettings*	getBakeSettings() const;

	bool	isShadowPass() const;
	bool	isBeautyPass() const;
	bool	isBakePass() const;

	void	sendForUpdate();

public:
	DzError	generateFiles();
	void	setShader( DzCoShaderInfo* info, const DzRenderSettings &settings, DzShaderBrick *brick, const QString &shaderFileName );

	virtual void	setShader( DzCoShaderInfo* info, const DzRenderSettings &settings, bool beforeWorldBegin=false ) const;
	DtLightHandle	getLightHandle();
	
private slots:
	void			rootRemoved();
	void			ready();

private:
	//internal functions
	void	setUpBricks( DzShaderBrickIterator &brickIt, bool beforeWorldBegin ) const;

	void	setUpObjectSpaceTokens() const;
	void	compileSetIfNeeded() const;
	void	writeShaderToRib( DzCoShaderInfo* info, DzBrickSet::ShaderType type, const QString &shaderName ) const;
	void	prepareBricks( DzShaderBrick *root, bool beforeWorldBegin ) const;

	void	prepareFileGen();
	void	generateCodeRecurse( DzShaderBrick *brick,int indentLevel,
									DzShaderBrickList &vistedBricks,
									DzShaderBrickList &tokenWrittenBricks,
									QStringList &writtenClasses, QStringList &aovs );

	void	doLoopRecurse( DzShaderBrick *brick, int indentLevel,
								DzShaderBrickList &vistedBricks,
								DzShaderBrickList &tokenWrittenBricks,
								QStringList &writtenClasses, QStringList &aovs,
								QStringList &varCallNames, QStringList &varArgNames );

	void	prepareArgs( DzShaderBrick *brick, DzShaderBrickList &tokenWrittenBricks,
							QStringList &varCallNames, QStringList &varArgNames );
	
	void	prepareParam( DzBrickParam *param, DzShaderBrickList &tokenWrittenBricks, 
						QStringList &varCallNames, QStringList &varArgNames );
	
	QString resolveInput( DzBrickParam *param, DzBrickParam *outParam, 
						int argIndex, DzShaderBrickList &tokenWrittenBricks );

	void	doTokens( DzBrickParam *param );
	void	doTokens( DzShaderBrick *brick );


	void	doAOVs( DzShaderBrick *brick, QStringList &aovs );
	void	doClassTokens( DzShaderBrick *brick );
	void	doInstanceTokens( DzShaderBrick *brick );

	void	updateLastInvalidate();
	DzError	generateBrickPreview( DzShaderBrick *brick, const QString &outputArgName );

	//data
	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzBrickSet>	DzBrickSetPtr;
typedef DzTArray<DzBrickSetPtr>			DzBrickSetList;

///////////////////////////////////////////////////////////////////////
// DzBrickSetCompilerMgr
///////////////////////////////////////////////////////////////////////

class DZ_EXPORT DzBrickSetCompilerMgr : public QObject
{
	Q_OBJECT
	friend class DzBrickSet;

public slots:
	void forceCompileFinish();
public:
	static DzBrickSetCompilerMgr*	getBrickSetCompilerMgr();

	int getNumBrickSetsToCompile() const;
	void clearSets();
	void queueBrickSet( DzBrickSet *set );
	void removeBrickSet( DzBrickSet *set );
	void updateCompilierSettings();

	void queueSetsForRecompile(bool forceRecompile = false);

	QStringList getEnviromentSettings();
	bool		getDoDSOCompile();

private slots:
	void rendererChanged();
	void compileNext();
	void compileComplete( DzShaderCompilerProcess *proc );
	void aboutToRender();

private:
	void readEnivromentSettings( const QString &fileName );
	void addBrickToGlobalSet( DzBrickSet *brick );
	void removeBrickFromGlobalSet( DzBrickSet *brick );

	DzBrickSetCompilerMgr();
	~DzBrickSetCompilerMgr();
	bool shouldCompile( DzBrickSet *set ) const;

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzShaderCompilerProcess : public QObject
{
	Q_OBJECT
public:
	DzShaderCompilerProcess( DzBrickSet *set );
	DzShaderCompilerProcess( DzBrickSet *set, DzShaderBrick *brick,
		const QString &arg, const QString &shaderName );
	~DzShaderCompilerProcess();

public:
	bool		run();
	DzBrickSet*	getSet() const;

signals:
	void completed( DzShaderCompilerProcess *self );

private slots:
	void handleOutput();
	void finished();
	void buildProcessArgs( QStringList &args, QString path, QStringList &includes );

private:
	struct	Data;
	Data	*m_data;
};


#endif //DZ_BRICK_SET_H