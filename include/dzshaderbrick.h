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
	Defines the DzShaderBrick class.
**/

#ifndef DZ_SHADERBRICK_H
#define DZ_SHADERBRICK_H
/*****************************
	Include files
*****************************/

#include <QtGui/QAction>
#include <QtGui/QColor>

#include "dzbrickparam.h"
#include "dzbrickset.h"
#include "dzelement.h"
#include "dzsettings.h"
#include "dzvec3.h"

/****************************
	Forward declarations
****************************/

class DzBrickOptionsFrame;
class DzDefaultInParam;
class DzEnumParam;
class DzMatrixParam;
class DzOutParam;
class DzShaderString;
class DzVec3Param;
struct ScopedParam;

/*****************************
	Class definitions
*****************************/

typedef DzTSharedPointer<DzShaderBrick>		DzShaderBrickPtr;
typedef DzTArray<DzShaderBrickPtr>			DzShaderBrickPtrList;
typedef QMap<unsigned int,DzShaderBrickPtr> DzBrickMap;
typedef QMapIterator<unsigned int,DzShaderBrickPtr> DzBrickMapIterator;

//////////////////////////////////////////////////////////////////////////
class DZ_EXPORT DzShaderBrick : public DzElement, public DzRefCountedItem
{
	Q_OBJECT
	friend class DzBrickSet;
public:
	//all bricks must a DzClassFactory that
	//returns a valid brick when createInstance() is called.

	DzShaderBrick();
	virtual ~DzShaderBrick();

	//DzBase
	virtual void		loadSection( DzInFile *file, short sectionID );
	virtual void		setPointer( const DzInFile *file, short sectionID, short pointerID, DzBase *ptr );
	virtual void		save( DzOutFile *file ) const;

	void					getParentBrickList( DzShaderBrickList *list, bool recurse ) const;
	void					getBrickList( bool includeSelf, bool recursive, bool unique, DzShaderBrickList *list ) const;
	void					getFullScopedVariableLists( QStringList &varNames, QList<int> &types, int scope );
	
	virtual bool			shouldSeperateLocalProperties() const;

	//should only be used by an IDzBrickUser
	virtual DzBrickParamIterator	getParameterIterator() const;

	void setBrickID(unsigned int id);
	static const DzClassFactory*	getBrickClassFactory( const QString &name );
	float	getBrickVersion() const;

public slots:
	virtual DzElement*		setAttributes( const DzSettings *settings );
	virtual void			getAttributes( DzSettings *settings ) const;
	virtual bool			writesOwnParameters() const;
	virtual bool			writeConnectionsAsIndexes() const;

	virtual DzBrickParam*	getParameter( int index ) const;
	virtual int				getNumParameters() const;

	virtual bool			insertParameter( int index, DzBrickParam *param );
	virtual bool			addParameter( DzBrickParam *param );
	virtual void			changeParamIndex( DzBrickParam *param, int newIndex );

	virtual bool			deleteParam( DzBrickParam *param );
	
	int					findParameterIndexByArg( const QString &arg ) const;
	int					findParameterIndex( const DzBrickParam *param ) const;
	DzBrickParam*		findParameterByProperty( const DzProperty *prop ) const;
	DzBrickParam*		findParameterByArg( const QString &arg ) const;
	DzBrickParam*		findParameterByName( const QString &name ) const;
	DzBrickParam*		findParameterByLabel( const QString &label ) const;
	bool				deleteParamByName( QString &name );
	bool				deleteParamByLabel( QString &name );
	bool				deleteParam( int index );
	bool				isRootConnected() const;
	void				addConnection( int paramIndex, DzShaderBrick *brick, int brickParamIndex );
	void				removeConnection( int paramIndex, DzShaderBrick *brick, int brickParamIndex, int conIndex = -1 );
	QString				getVarName( const QString &argName, const QStringList &varCallNames, const QStringList varArgNames ) const;
	QString				getNewToken();
	virtual QString		getOptionsFrameClassName() const;
	
	virtual DzBrickSet::ShaderType	type() const = 0;
	//only relevant for light and lightarea shaders
	virtual DzBrickSet::LightType	lightType() const;
	virtual bool					usesLocalShaderSpace() const;

	virtual bool		isScopedBrick();
	
	virtual bool		getNeedsTangentSpaceParams();

	virtual int			getNumOfClassTokens() const;
	virtual QString		getClassTokenName( int i ) const;
	virtual DzBrickParam::ParamType	getClassTokenType( int i ) const;
	virtual QString		getClassTokenDefaultValue( int i ) const;

	virtual int			getNumOfInstanceTokensNeeded() const;
	virtual DzBrickParam::ParamType	getInstanceTokenType( int i ) const;
	virtual QString		getInstanceTokenDefaultValue( int i ) const;

	virtual DzSettings*	getBrickSettings() const;
	virtual QStringList	getBrickActionList() const;

	virtual QStringList	getIncludePaths();
	virtual QString		getBrickClass() const;
	virtual QString		getPreferredName() const;
	virtual QString		getDefaultCategory() const;
	virtual QString		getDescription() const;
	
	virtual int			getNumScopedParams();
	virtual QString		getScopedParamName( int i );
	virtual DzBrickParam::ParamType	getScopedParamType( int i );
	virtual int			getScopedParamScope( int i );
	virtual int			getScopedParamIndex( const QString &name );

	virtual void		addScopedParam( int paramType, const QString &name, int scope = -1 );
	virtual	void		removeScopedParam( const QString &name );
	
	virtual QStringList		getFullScopedVariableLists( int scope = -1 );
	virtual QVariantList	getFullScopedVariableListsTypes( int scope = -1 );

	QString				getInstanceToken( int i ) const;

	//list of required params
	virtual void		getFullRequiredScopedVariableLists( QStringList &varNames, QList<int> &types, bool recurse = true );
	virtual int			getNumRequiredScopedParams();
	virtual	QString		getRequiredScopedParam( int i );
	virtual DzBrickParam::ParamType	getRequiredScopedParamType( int i );

	virtual void		addRequiredParam( int paramClass, const QString &name );
	virtual	void		removeRequiredParam( const QString &name );

	virtual bool		providesParam( const QString &paramName, int paramType, int scope = -1, bool recurse = true );
	virtual bool		providesParams( DzShaderBrick *brick, const DzBrickParam *param );
	
	//Only relevant for non-function bricks
	virtual bool		isActiveInShadowPass() const;
	virtual bool		isOnlyInShadowPass() const;
	virtual bool		isActiveInBakePass() const;
	virtual bool		isActiveInBeautyPass() const;

	bool				brickIsParent( DzShaderBrick *brick ) const;
	bool				brickIsChild( DzShaderBrick *brick ) const;
	unsigned int		getBrickID() const;
	QObjectList			getParentBrickList( bool recurse ) const;
	QObjectList			getChildBrickList( bool includeSelf, bool recursive, bool unique ) const;

	DzPropertyParam*	addFloatParameter( const QString &path,const QString &argName, const QString &label,
										const QString &propName, float val = 0, float defaultValue = 0,
										float min = -1e38, float max = 1e38,
										bool clamp = false, const QString &mapVar = QString::null );
	DzPropertyParam*	addIntParameter( const QString &path, const QString &argName, const QString &label,
									const QString &propName, int val = 0, int defaultValue = 0,
									int min = -1000, float max = 1000,
									bool clamp = false, const QString &mapVar = QString::null );
	DzPropertyParam*	addColorParameter( const QString &path, const QString &argName, const QString &label,
										const QString &propName, const QColor &val = QColor(),
										const QString &mapVar = QString::null );
	DzPropertyParam*	addEnumPropertyParameter( const QString &path, const QString &argName, const QString &label,
												const QString &propName, const QStringList &strings,
												int val = 0, int defaultValue = 0 );
	DzPropertyParam*	addBoolParameter( const QString &path, const QString &argName, const QString &label,
										const QString &propName, bool val = false, bool defaultValue = false );
	DzVec3Param*		addVec3Parameter( const QString &path, int type, const QString &argName, const QString &label,
										const DzVec3 &val = DzVec3( 0, 0, 0 ), const DzVec3 &defaultValue = DzVec3( 0, 0, 0 ) );
	DzMatrixParam*		addMatrixParameter( const QString &path, const QString &argName, const QString &label );
	DzPropertyParam*	addImageParameter( const QString &path, const QString &argName, const QString &label,
										const QString &propName, const DzTexture *val = NULL );
	DzPropertyParam*	addStringParameter( const QString &Path, const QString &argName, const QString &label,
										const QString &propName, const QString &val = QString::null,
										const QString &defaultValue = QString::null );
	DzPropertyParam*	addFileParameter( const QString &path, const QString &argName, const QString &label,
										const QString &propName, const QString &filter= "Any File(*.*)",
										int type = 0, const QString &val = QString::null,
										const QString &defaultValue = QString::null );
	DzEnumParam*		addEnumParameter( const QString &path, const QString &argName, const QString &label,
										const QStringList &strings, const QList<QVariant> &values, DzBrickParam::ParamType type,
										int val = 0, int defaultValue = 0 );

	DzDefaultInParam*	addDefaultInParameter( int type, const QString &argName, const QString &label, const QString &defaultVal );
	DzOutParam*			addOutParameter( int type, const QString &argName, const QString &label, bool isAov = false );
	
protected slots:
	virtual void		childConnectionChanged();
	void				connectionsChanged();

signals:
#ifndef Q_MOC_RUN
public:
#endif
	void	brickRemoved( DzShaderBrick *self );

signals:
	void	connectionsChanged( DzShaderBrick *self );
	void	invalidateFiles();
	void	generateFilesStarted();
	void	generateFilesFinished();
	void	paramAdded( DzShaderBrick* thisBrick );
	void	paramRemoved( DzShaderBrick* thisBrick );
	void	brickActionListChanged();
	void	brickIDChanged( int oldID );
	void	brickTitleChanged( const QString& title );

public:
	virtual void	ownParamProperties();
	virtual void	giveParamPropertiesToOwner();
	virtual void	postAttributeSet();

protected:
	virtual void	setGlobalBrickRenderSettings( const DzBrickSet *set, DzRenderer *renderer ) const;
	
	virtual void	setBrickRenderSettings( const DzBrickSet *set, DzRenderer *renderer ) const;

	virtual DzShaderString*	getBrickClassShaderCode() const;
	
	virtual DzShaderString*	getShaderCodeCall( const QStringList &varCallNames,
										const QStringList &varArgNames ) const = 0;

	virtual DzShaderString*	getScopedShaderCodeCall( const QStringList &varCallNames,
								const QStringList &varArgNames, int scope ) const;

	virtual int	getNumScopesNeeded() const;

	static void	getAllDefaultScopedParams( QStringList &varNames, QList<int> &types );
	static void	getAllDefaultScopedParams( QSet<ScopedParam> &params );

	void		setBrickVersion( float ver );

private:
	int			getNumScopedParamsInternal();
	QString		getScopedParamNameInternal( int i );
	DzBrickParam::ParamType	getScopedParamTypeInternal( int i );
	int			getNumRequiredScopedParamsInternal();
	QString		getRequiredScopedParamInternal( int i );
	DzBrickParam::ParamType	getRequiredScopedParamTypeInternal( int i );
	void		getFullScopedVariableLists( QSet<ScopedParam> &params, int scope = -1 );
	bool		addParamInternal( DzBrickParam *param );

	struct	Data;
	Data	*m_data;
};

//////////////////////////////////////////////////////////////////////////
class DZ_EXPORT DzBrickFactory
{
public:
	DzBrickFactory();
	DzBrickFactory( const DzBrickFactory &brickFactory );
	DzBrickFactory( const DzClassFactory *factory );
	virtual ~DzBrickFactory();

	void					setClassFactory( const DzClassFactory *factory );
	DzShaderBrick*			generateBrick() const;
	const DzClassFactory*	getFactory() const;
	DzSettings*				getSettings() const;
	virtual DzBrickFactory&	operator=( const DzBrickFactory &val );

protected:
	const DzClassFactory	*m_factory;
	mutable DzSettings		m_set;
};

Q_DECLARE_METATYPE(DzBrickFactory);

DZ_EXPORT QDataStream &operator<<( QDataStream &out, const DzBrickFactory &myObj );
DZ_EXPORT QDataStream &operator>>( QDataStream &in, DzBrickFactory &myObj );

//////////////////////////////////////////////////////////////////////////

class DZ_EXPORT DzBrickAction : public QAction
{
	Q_OBJECT
public:
	DzBrickAction();
	virtual ~DzBrickAction();
public slots:
	virtual void			setBrickOptionsFrame( DzBrickOptionsFrame *frame );
	virtual void			setArgs( const QString &args );
	DzBrickOptionsFrame*	getOptionsFrame() const;
private:
	struct	Data;
	Data	*m_data;
};

//////////////////////////////////////////////////////////////////////////

class DZ_EXPORT DzShaderString : public QObject, public DzRefCountedItem
{
	Q_OBJECT
		friend class DzBrickSet;
public:
	DzShaderString();
	DzShaderString( const QString &str );

public slots:
	void setString( const QString &val );

private:
	~DzShaderString();
	
	struct	Data;
	Data	*m_data;
};
typedef DzTSharedPointer<DzShaderString> DzShaderStringPtr;

#endif //DZ_SHADERBRICK_H