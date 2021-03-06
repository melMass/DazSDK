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
	Defines the DzRenderer class.
**/

#ifndef DAZ_RENDERER_H
#define DAZ_RENDERER_H

/*****************************
	Include files
*****************************/
#include "dzrenderoptions.h"

#include "dzbase.h"
#include "dztypes.h"

/*****************************
	RenderMan type definitions
*****************************/
// These are defined by the RenderMan standard
typedef short	DtBoolean;
typedef int		DtInt;
typedef float	DtFloat;
typedef const char*	DtToken;

typedef DtFloat	DtColor[3];
typedef DtFloat	DtPoint[3];
typedef DtFloat	DtVector[3];
typedef DtFloat	DtNormal[3];
typedef DtFloat	DtHpoint[3];
typedef DtFloat	DtMatrix[4][4];
typedef DtFloat	DtBasis[4][4];
typedef DtFloat	DtBound[6];
typedef DtFloat DtInterval[2];
typedef const char*	DtString;

typedef void*	DtPointer;
#define DtVoid	void
typedef DtFloat	(*DtFilterFunc)( DtFloat, DtFloat, DtFloat, DtFloat );
typedef DtVoid	(*DtErrorHandler)( DtInt code, DtInt severity, const char *msg );
typedef DtVoid	(*DtProcSubdivFunc)( DtPointer, DtFloat );
typedef DtVoid	(*DtProcFreeFunc)( DtPointer );
typedef DtVoid	(*DtArchiveCallback)( DtToken, const char *, ... );

typedef DtVoid	(*DtFunc)();

typedef DtPointer	DtObjectHandle;
typedef DtPointer	DtLightHandle;
typedef DtPointer	DtContextHandle;
typedef DtPointer	DtArchiveHandle;
typedef DtPointer	DtVolumeHandle;

#define DI_FALSE	0
#define DI_TRUE		1
#define DI_INFINITY	(DtFloat)1.0e38
#define DI_EPSILON	(DtFloat)1.0e-10
#define DI_NULL		NULL

extern DZ_EXPORT DtToken	DI_FRAMEBUFFER, DI_FILE;
extern DZ_EXPORT DtToken	DI_RGB, DI_RGBA, DI_RGBZ, DI_RGBAZ, DI_A, DI_Z, DI_AZ;
extern DZ_EXPORT DtToken	DI_PERSPECTIVE, DI_ORTHOGRAPHIC;
extern DZ_EXPORT DtToken	DI_HIDDEN, DI_PAINT;
extern DZ_EXPORT DtToken	DI_RAYTRACE, DI_PHOTON;
extern DZ_EXPORT DtToken	DI_CONSTANT, DI_SMOOTH;
extern DZ_EXPORT DtToken	DI_FLATNESS, DI_FOV;
extern DZ_EXPORT DtToken	DI_AMBIENTLIGHT, DI_POINTLIGHT, DI_DISTANTLIGHT, DI_SPOTLIGHT;
extern DZ_EXPORT DtToken	DI_INTENSITY, DI_LIGHTCOLOR, DI_FROM, DI_TO, DI_CONEANGLE;
extern DZ_EXPORT DtToken	DI_CONEDELTAANGLE, DI_BEAMDISTRIBUTION;
extern DZ_EXPORT DtToken	DI_MATTE, DI_METAL, DI_SHINYMETAL, DI_PLASTIC, DI_PAINTEDPLASTIC;
extern DZ_EXPORT DtToken	DI_KA, DI_KD, DI_KS, DI_ROUGHNESS, DI_KR, DI_TEXTURENAME, DI_SPECULARCOLOR;
extern DZ_EXPORT DtToken	DI_DEPTHCUE, DI_FOG, DI_BUMPY;
extern DZ_EXPORT DtToken	DI_MINDISTANCE, DI_MAXDISTANCE, DI_BACKGROUND, DI_DISTANCE, DI_AMPLITUDE;
extern DZ_EXPORT DtToken	DI_RASTER, DI_SCREEN, DI_CAMERA;
extern DZ_EXPORT DtToken	DI_WORLD, DI_OBJECT;
extern DZ_EXPORT DtToken	DI_INSIDE, DI_OUTSIDE, DI_LH, DI_RH;
extern DZ_EXPORT DtToken	DI_P, DI_PZ, DI_PW, DI_N, DI_NP, DI_CS, DI_OS, DI_S, DI_T, DI_ST;
extern DZ_EXPORT DtToken	DI_BILINEAR, DI_BICUBIC;
extern DZ_EXPORT DtToken	DI_PRIMITIVE, DI_INTERSECTION, DI_UNION, DI_DIFFERENCE;
extern DZ_EXPORT DtToken	DI_PERIODIC, DI_NONPERIODIC, DI_CLAMP, DI_BLACK;
extern DZ_EXPORT DtToken	DI_IGNORE, DI_PRINT, DI_ABORT, DI_HANDLER;
extern DZ_EXPORT DtToken	DI_BOUNDS;
extern DZ_EXPORT DtToken	DI_LIMITS, DI_SHADOW, DI_BIAS0, DI_BIAS1, DI_SAMPLE;
extern DZ_EXPORT DtToken	DI_SEARCHPATH, DI_SHADER, DI_TEXTURE, DI_DISPLAY;
extern DZ_EXPORT DtToken	DI_WIDTH, DI_CONSTANTWIDTH;
extern DZ_EXPORT DtToken	DI_COMMENT, DI_STRUCTURE, DI_VERBATIM;
extern DZ_EXPORT DtToken	DI_IDENTIFIER, DI_NAME, DI_SHADINGGROUP;
extern DZ_EXPORT DtToken	DI_LINEAR, DI_CUBIC;
extern DZ_EXPORT DtToken	DI_BUCKETSENDER, DI_FUNCTION;
extern DZ_EXPORT DtToken	DI_THRESHOLD, DI___THRESHOLD;
extern DZ_EXPORT DtToken	DI_HANDLEID, DI___HANDLEID;
extern DZ_EXPORT DtToken	DI_QUANTIZE, DI_DITHER, DI_EXPOSURE, DI_FILTER, DI_FILTERWIDTH;

extern DtBasis	DiBezierBasis, DiBSplineBasis, DiCatmullRomBasis,
				DiHermiteBasis, DiPowerBasis;

#define DI_BEZIERSTEP		((DtInt)3)
#define DI_BSPLINESTEP		((DtInt)1)
#define DI_CATMULLROMSTEP	((DtInt)1)
#define DI_HERMITESTEP		((DtInt)2)
#define DI_POWERSTEP		((DtInt)4)

extern DtInt	DiLastError;

/*****************************
	Error codes
*****************************/
//	 1 - 10		System and File errors
//	11 - 20		Program Limitations
//	21 - 40		State Errors
//	41 - 60		Parameter and Protocol Errors
//	61 - 80		Execution Errors

#define DIE_NOERROR			0

#define DIE_NOMEM			1		/* Out of memory */
#define DIE_SYSTEM			2		/* Miscellaneous system error */
#define DIE_NOFILE			3		/* File nonexistant */
#define DIE_BADFILE			4		/* Bad file format */
#define DIE_VERSION			5		/* File version mismatch */
#define DIE_DISKFULL		6		/* Target disk is full */

#define DIE_INCAPABLE		11		/* Optional DI feature */
#define DIE_OPTIONAL		11		/* Optional DI feature */
#define DIE_UNIMPLEMENT		12		/* Unimplemented feature */
#define DIE_LIMIT			13		/* Arbitrary program limit */
#define DIE_BUG				14		/* Probably a bug in renderer */

#define DIE_NOTSTARTED		23		/* DiBegin not called */
#define DIE_NESTING			24		/* Bad begin-end nesting */
#define DIE_NOTOPTIONS		25		/* Invalid state for options */
#define DIE_NOTATTDIBS		26		/* Invalid state for attributes */
#define DIE_NOTPDIMS		27		/* Invalid state for primitives */
#define DIE_ILLSTATE		28		/* Other invalid state */
#define DIE_BADMOTION		29		/* Badly formed motion block */
#define DIE_BADSOLID		30		/* Badly formed solid block */

#define DIE_BADTOKEN		41		/* Invalid token for request */
#define DIE_RANGE			42		/* Parameter out of range */
#define DIE_CONSISTENCY		43		/* Parameters inconsistent */
#define DIE_BADHANDLE		44		/* Bad object/light handle */
#define DIE_NOSHADER		45		/* Can't load requested shader */
#define DIE_MISSINGDATA		46		/* Required parameters not provided */
#define DIE_SYNTAX			47		/* Declare type syntax error */
#define DIE_TOKENREDECLARED 48		/* Redeclaration of token */

#define DIE_MATH			61		/* Zerodivide, noninvert matrix, etc. */

#define DIE_BADATTRIB		140		/* Unsupported attribute */
#define DIE_BADOPTION		141		/* Unsupported option */
#define DIE_SPACEREDECLARED	142		/* Redeclaration of space */
#define DIE_NODISPLAY		143		/* Can't load requested display server */
#define DIE_ERRRERTOOBID	144		/* Image resolution too big */
#define DIE_ERRBADSHADERPARAM 145	/* Parameter is not in shader param list */
#define DIE_ERRSHADERPARAMMISMATCH 146		/* Value for parameter does not match declaration */
#define DIE_ERRBADARRAYACCESSINSHADER 147	/* Invalid array index done in a shader */

#define DIE_SHADER_PRINTF	199		/* output of a shader's printf() */

/* Error severity levels */
#define DIE_INFO			0		/* Rendering stats & other info */
#define DIE_WARNING			1		/* Something seems wrong, maybe okay */
#define DIE_ERROR			2		/* Problem. Results may be wrong */
#define DIE_SEVERE			3		/* So bad you should probably abort */


/*****************************
	Shader Language Interogation types
*****************************/
typedef enum
{
	DSLO_TYPE_UNKNOWN,
	DSLO_TYPE_POINT,
	DSLO_TYPE_COLOR,
	DSLO_TYPE_SCALAR,
	DSLO_TYPE_STRING,
	DSLO_TYPE_SURFACE,
	DSLO_TYPE_LIGHT,
	DSLO_TYPE_DISPLACEMENT,
	DSLO_TYPE_VOLUME,
	DSLO_TYPE_TRANSFORMATION,
	DSLO_TYPE_IMAGER,
	/* New types (RiSpec 3.1) */
	DSLO_TYPE_VECTOR,
	DSLO_TYPE_NORMAL,
	DSLO_TYPE_MATRIX,
	DSLO_TYPE_SHADER

} DSLO_TYPE;

/* Storage class of the symbol */
typedef enum
{
	DSLO_STOR_UNKNOWN,
	DSLO_STOR_CONSTANT,
	DSLO_STOR_VARIABLE,
	DSLO_STOR_TEMPORARY,
	DSLO_STOR_PARAMETER,
	DSLO_STOR_OUTPUTPARAMETER,
	DSLO_STOR_GSTATE
} DSLO_STORAGE;

/* Variance of the symbol. Of course, in a shader, only varying & consant
	are useful */
typedef enum
{
	DSLO_DETAIL_UNKNOWN,
	DSLO_DETAIL_VARYING,
	DSLO_DETAIL_UNIFORM
} DSLO_DETAIL;

typedef struct {
	float xval;
	float yval;
	float zval;
} DSLO_POINT;

typedef float DSLO_SCALAR;

typedef float* DSLO_MATRIX;

typedef struct dslovissymdef
{
	/* name of symbol */
	const char *svd_name;

	DSLO_TYPE svd_type;
	DSLO_STORAGE svd_storage;
	DSLO_DETAIL svd_detail;

	/* name of space in which to interpret symbol's value */
	const char *svd_spacename;

	union
	{
		/* pointers to default value */
		const DSLO_POINT *pointval;
		const DSLO_SCALAR *scalarval;
		const char *stringval;
		const float *matrixval;
	} svd_default;

	/* set to 0 if the value is not valid */
	unsigned svd_valisvalid:1;

	/* array length if the variable is an array */
	int svd_arraylen;

} DSLO_VISSYMDEF;

/*
	This is returned by Slo_GetMethod
*/
typedef struct dslomethod
{
	const char *name;

	unsigned num_parameters;
	unsigned num_optionals;	

	DSLO_VISSYMDEF *parameters;
	DSLO_VISSYMDEF *optionals;

	DSLO_VISSYMDEF *returnvalue;
} DSLO_METHOD;


/****************************
	Forward declarations
****************************/

class QString;
class DzCamera;
class DzLight;
class DzTexture;
class DzRenderHandler;
class DzBakerOptions;
class DzTextureConvertorOptions;
class DzScene;
class DzNode;
class DzOptionsFrame;

/*********************************
	Shader parameter description
*********************************/

class DZ_EXPORT DzShaderParameter : public QObject {
	Q_OBJECT
	Q_ENUMS( DzShaderParamType )
	Q_PROPERTY( int type READ getTypeAsInt )
public:
	enum DzShaderParamType { UnknownType, PointType, NormalType, VectorType,
		ColorType, ScalarType, StringType, MatrixType };

	DzShaderParameter( const char *paramName, const DtVector &v, DzShaderParamType type );
	DzShaderParameter( const char *paramName, DtFloat v );
	DzShaderParameter( const char *paramName, const DtString str );
	DzShaderParameter( const char *paramName, const DtMatrix m );
	~DzShaderParameter();

	DzShaderParamType	getType() const;
	int					getTypeAsInt() const { return (int) getType(); }

private:
	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzShaderDescription : public QObject {
	Q_OBJECT
	Q_ENUMS( DzShaderType )
	Q_PROPERTY( int type READ getTypeAsInt )
public:
	enum DzShaderType { SurfaceShader, LightShader, DisplacementShader,
		VolumeShader, ImageShader };

	DzShaderDescription( DzShaderType type );
	~DzShaderDescription();

	void			addParameter( DzShaderParameter *param );
	DzShaderType	getType() const;
	int				getTypeAsInt() const { return (int) getType(); }

public slots:

	int							getNumParameters() const;
	const DzShaderParameter*	getParameter( int i ) const;

private:

	struct	Data;
	Data	*m_data;
};

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRenderer : public DzBase {
	Q_OBJECT
public:
	DzRenderer();
	virtual ~DzRenderer();

	// ------------------ Basic control flow, scoping, stacks

	virtual DtVoid			DiWorldBegin() = 0;
	virtual DtVoid			DiWorldEnd() = 0;
	virtual DtContextHandle DiGetContext() = 0;
	virtual DtVoid			DiContext( DtContextHandle handle ) = 0;
	virtual DtVoid			DiAttributeBegin() = 0;
	virtual DtVoid			DiAttributeEnd() = 0;
	virtual DtVoid			DiTransformBegin() = 0;
	virtual DtVoid			DiTransformEnd() = 0;
	virtual DtVoid			DiSolidBegin( DtToken type ) = 0;
	virtual DtVoid			DiSolidEnd() = 0;
	DtVoid					DiMotionBegin( DtInt N, ... );
	virtual DtVoid			DiMotionBeginV( DtInt N, DtFloat times[] ) = 0;
	virtual DtVoid			DiMotionEnd() = 0;
	virtual DtToken			DiDeclare( const char *name, const char *declaration ) = 0;
	virtual DtVoid			DiScreenWindow( DtFloat left, DtFloat right, DtFloat bot, DtFloat top ) = 0;
	DtVoid					DiIfBegin( DtToken expression, ... );
	virtual DtVoid			DiIfBeginV( DtToken expression, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiElseIf( DtToken expression, ... );
	virtual DtVoid			DiElseIfV( DtToken expression, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiElse() = 0;
	virtual DtVoid			DiIfEnd() = 0;
	virtual DtVoid			DiErrorHandler( DtErrorHandler handler ) = 0;
	virtual DtVoid			DiSynchronize( DtToken ) = 0;


	// ------------------ Attributes

	DtVoid					DiAttribute( DtToken name, ... );
	virtual DtVoid			DiAttributeV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiBound( DtBound bound ) = 0;
	virtual DtVoid			DiColor( DtColor Cs ) = 0;
	virtual DtVoid			DiDetail( DtBound bound ) = 0;
	virtual DtVoid			DiDetailRange( DtFloat minvis, DtFloat lowtran,
								DtFloat uptran, DtFloat maxvis ) = 0;
	virtual DtVoid			DiGeometricApproximation( DtToken type, DtFloat value ) = 0;
	virtual DtVoid			DiIlluminate( DtLightHandle light, DtBoolean onoff ) = 0;
	virtual DtVoid			DiMatte( DtBoolean onoff ) = 0;
	virtual DtVoid			DiMultiplyShadingRate( DtFloat ratemultiplier ) = 0;
	virtual DtVoid			DiOpacity( DtColor Cs ) = 0;
	virtual DtVoid			DiOrientation( DtToken orientation ) = 0;
	virtual DtVoid			DiReverseOrientation() = 0;
	virtual DtVoid			DiShadingInterpolation( DtToken type ) = 0;
	virtual DtVoid			DiShadingRate( DtFloat size ) = 0;
	virtual DtVoid			DiSides( DtInt nsides ) = 0;
	virtual DtVoid			DiTextureCoordinates( DtFloat s1, DtFloat t1, DtFloat s2, DtFloat t2,
								DtFloat s3, DtFloat t3, DtFloat s4, DtFloat t4 ) = 0;


	// ------------------ Shaders

	DtLightHandle			DiAreaLightSource( DtToken name, ... );
	virtual DtLightHandle	DiAreaLightSourceV( DtToken name, DtInt n,
								const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiAtmosphere( DtToken name, ... );
	virtual DtVoid			DiAtmosphereV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiDisplacement( DtToken name, ... );
	virtual DtVoid			DiDisplacementV( DtToken name, DtInt n,
								const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiExterior( DtToken name, ... );
	virtual DtVoid			DiExteriorV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiImager( DtToken name, ... );
	virtual DtVoid			DiImagerV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiInterior( DtToken name, ... );
	virtual DtVoid			DiInteriorV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtLightHandle			DiLightSource( DtToken name, ... );
	virtual DtLightHandle	DiLightSourceV( DtToken name, DtInt n,
								const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiShader( DtToken name, DtToken handle, ... );
	virtual DtVoid			DiShaderV( DtToken name, DtToken handle, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiSurface( DtToken name, ... );
	virtual DtVoid			DiSurfaceV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;


	// ------------------ Transformations

	virtual DtVoid			DiConcatTransform( DtMatrix transform ) = 0;
	virtual DtVoid			DiCoordinateSystem( DtToken space ) = 0;
	virtual DtVoid			DiCoordSysTransform( DtToken space ) = 0;
	virtual DtVoid			DiIdentity() = 0;
	virtual DtVoid			DiPerspective( DtFloat fov ) = 0;
	virtual DtVoid			DiRotate( DtFloat angle, DtFloat dx, DtFloat dy, DtFloat dz ) = 0;
	virtual DtVoid			DiScale( DtFloat dx, DtFloat dy, DtFloat dz ) = 0;
	virtual DtVoid			DiScopedCoordinateSystem( DtToken space ) = 0;
	virtual DtVoid			DiSkew( DtFloat angle, DtFloat dx1, DtFloat dy1, DtFloat dz1,
								DtFloat dx2, DtFloat dy2, DtFloat dz2 ) = 0;
	virtual DtVoid			DiTransform( DtMatrix transform ) = 0;
	virtual DtPoint*		DiTransformPoints( DtToken fromspace, DtToken tospace,
								DtInt npoints, DtPoint *points ) = 0;
	virtual DtVoid			DiTranslate( DtFloat dx, DtFloat dy, DtFloat dz ) = 0;


	// ------------------ Geometric Primitives

	virtual DtVoid			DiBasis( DtBasis ubasis, DtInt ustep, DtBasis vbasis, DtInt vstep ) = 0;
	DtVoid					DiBlobby( DtInt nleaf, DtInt ncode, DtInt code[],
								DtInt nflt, DtFloat flt[], DtInt nstr, DtString str[], ... );
	virtual DtVoid			DiBlobbyV( DtInt nleaf, DtInt ncode, DtInt code[],
								DtInt nflt, DtFloat flt[], DtInt nstr, DtString str[],
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiCone( DtFloat height, DtFloat radius, DtFloat thetamax, ... );
	virtual DtVoid			DiConeV( DtFloat height, DtFloat radius, DtFloat thetamax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiCurves( DtToken degree, DtInt ncurves,
								DtInt nverts[], DtToken wrap, ... );
	virtual DtVoid			DiCurvesV( DtToken degree, DtInt ncurves, DtInt nverts[], DtToken wrap,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiCylinder( DtFloat radius, DtFloat zmin, DtFloat zmax,
								DtFloat thetamax, ... );
	virtual DtVoid			DiCylinderV( DtFloat radius, DtFloat zmin, DtFloat zmax, DtFloat thetamax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiDisk( DtFloat height, DtFloat radius, DtFloat thetamax, ... );
	virtual DtVoid			DiDiskV( DtFloat height, DtFloat radius, DtFloat thetamax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiGeneralPolygon( DtInt nloops, DtInt *nverts, ... );
	virtual DtVoid			DiGeneralPolygonV (DtInt nloops, DtInt *nverts,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiGeometry( DtToken type, ... );
	virtual DtVoid			DiGeometryV( DtToken type, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiHyperboloid( DtPoint point1, DtPoint point2, DtFloat thetamax, ... );
	virtual DtVoid			DiHyperboloidV( DtPoint point1, DtPoint point2, DtFloat thetamax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiNuCurves( DtInt ncurves, DtInt nvertices[],
								DtInt order[], DtFloat knot[], DtFloat min[], DtFloat max[], ... );
	virtual DtVoid			DiNuCurvesV( DtInt ncurves, DtInt nvertices[], 
								DtInt order[], DtFloat knot[], DtFloat min[], DtFloat max[],
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiNuPatch( DtInt nu, DtInt uorder, DtFloat *uknot,
								DtFloat umin, DtFloat umax, DtInt nv, DtInt vorder,
								DtFloat *vknot, DtFloat vmin, DtFloat vmax, ... );
	virtual DtVoid			DiNuPatchV( DtInt nu, DtInt uorder, DtFloat *uknot,
								DtFloat umin, DtFloat umax, DtInt nv, DtInt vorder,
								DtFloat *vknot, DtFloat vmin, DtFloat vmax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiParaboloid( DtFloat rmax, DtFloat zmin,
								DtFloat zmax, DtFloat thetamax, ... );
	virtual DtVoid			DiParaboloidV( DtFloat rmax, DtFloat zmin, DtFloat zmax, DtFloat thetamax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiPatch( DtToken type, ... );
	virtual DtVoid			DiPatchV( DtToken type, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiPatchMesh( DtToken type, DtInt nu, DtToken uwrap,
								DtInt nv, DtToken vwrap, ... );
	virtual DtVoid			DiPatchMeshV( DtToken type, DtInt nu, DtToken uwrap, DtInt nv,
								DtToken vwrap, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiPoints( DtInt npts, ... );
	virtual DtVoid			DiPointsV( DtInt npts, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiPointsGeneralPolygons( DtInt npolys, DtInt *nloops,
								DtInt *nverts, DtInt *verts, ... );
	virtual DtVoid			DiPointsGeneralPolygonsV( DtInt npolys, DtInt *nloops,
								DtInt *nverts, DtInt *verts,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiPointsPolygons( DtInt npolys, DtInt *nverts, DtInt *verts, ... );
	virtual DtVoid			DiPointsPolygonsV( DtInt npolys, DtInt *nverts, DtInt *verts,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiPolygon( DtInt nvertices, ... );
	virtual DtVoid			DiPolygonV( DtInt nvertices, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiSphere( DtFloat radius, DtFloat zmin,
								DtFloat zmax, DtFloat thetamax, ... );
	virtual DtVoid			DiSphereV( DtFloat radius, DtFloat zmin, DtFloat zmax, DtFloat thetamax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiSubdivisionMesh( DtToken scheme, DtInt nfaces,
								DtInt nvertices[], DtInt vertices[],
								DtInt ntags, const DtToken tags[], DtInt nargs[],
								DtInt intargs[], DtFloat floatargs[], ... );
	virtual DtVoid			DiSubdivisionMeshV( DtToken scheme, DtInt nfaces,
								DtInt nvertices[], DtInt vertices[],
								DtInt ntags, const DtToken tags[], DtInt nargs[],
								DtInt intargs[], DtFloat floatargs[],
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiHierarchicalSubdivisionMesh(	DtToken scheme,
								DtInt nfaces, DtInt nvertices[], DtInt vertices[],
								DtInt ntags, const DtToken tags[], DtInt nargs[],
								DtInt intargs[], DtFloat floatargs[], const DtToken stringargs[], ... );
	virtual DtVoid			DiHierarchicalSubdivisionMeshV(	DtToken scheme,
								DtInt nfaces, DtInt nvertices[], DtInt vertices[],
								DtInt ntags, const DtToken tags[], DtInt nargs[],
								DtInt intargs[], DtFloat floatargs[], const DtToken stringargs[],
								DtInt n, const DtToken tokens[], DtPointer params[]) = 0;
	DtVoid					DiTorus( DtFloat majorrad, DtFloat minorrad, DtFloat phimin,
								DtFloat phimax, DtFloat thetamax, ... );
	virtual DtVoid			DiTorusV( DtFloat majorrad, DtFloat minorrad, DtFloat phimin,
								DtFloat phimax, DtFloat thetamax,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiTrimCurve( DtInt nloops, DtInt *ncurves, DtInt *order,
								DtFloat *knot, DtFloat *amin, DtFloat *amax,
								DtInt *n, DtFloat *u, DtFloat *v, DtFloat *w ) = 0;


	// ------------------ Procedural primitives

	virtual DtVoid			DiProcedural( DtPointer data, DtBound bound,
								DtVoid (*subdivfunc) (DtPointer, DtFloat),
								DtVoid (*freefunc) (DtPointer) ) = 0;
	virtual DtVoid			DiProcDelayedReadArchive (DtPointer data, DtFloat detail) = 0;
	virtual DtVoid			DiProcRunProgram (DtPointer data, DtFloat detail) = 0;
	virtual DtVoid			DiProcDynamicLoad (DtPointer data, DtFloat detail) = 0;


	// ------------------ Object Instancing

	virtual DtObjectHandle	DiObjectBegin() = 0;
	virtual DtObjectHandle	DiObjectBeginV( DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiObjectEnd() = 0;
	virtual DtVoid			DiObjectInstance( DtObjectHandle handle ) = 0;

	
	// ------------------ Resourcing
	
	DtVoid					DiResource(DtToken handle, DtToken type, ...);
	virtual DtVoid			DiResourceV(DtToken handle, DtToken type,
								 DtInt n, const DtToken tokens[], DtPointer params[]) = 0;
	virtual DtVoid			DiResourceBegin() = 0;
	virtual DtVoid			DiResourceEnd() = 0;

	
	// ------------------ Texture map creation */
	
	DtVoid					DiMakeBrickMap( DtInt nptc, const char *const *ptcnames, const char *bkmname, ... );
	virtual DtVoid			DiMakeBrickMapV( DtInt nptc, const char *const *ptcnames, const char *bkmname,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiMakeBump( const char *picturename, const char *texturename,
								 DtToken swrap, DtToken twrap,
								 DtFilterFunc filterfunc,
								 DtFloat swidth, DtFloat twidth, ... );	
	virtual DtVoid			DiMakeBumpV( const char *picturename, const char *texturename,
								 DtToken swrap, DtToken twrap,
								 DtFilterFunc filterfunc,
								 DtFloat swidth, DtFloat twidth,
								 DtInt n, const DtToken tokens[],
								 DtPointer params[] ) = 0;
	DtVoid					DiMakeCubeFaceEnvironment( const char *px, const char *nx, const char *py,
								const char *ny, const char *pz, const char *nz,
								const char *tex, DtFloat fov, DtFilterFunc filterfunc,
								DtFloat swidth, DtFloat twidth, ... );
	virtual DtVoid			DiMakeCubeFaceEnvironmentV( const char *px, const char *nx, const char *py,
								const char *ny, const char *pz, const char *nz,
								const char *tex, DtFloat fov, DtFilterFunc filterfunc,
								DtFloat swidth, DtFloat twidth,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiMakeLatLongEnvironment( const char *pic, const char *tex, DtFilterFunc filterfunc,
								DtFloat swidth, DtFloat twidth, ... );
	virtual DtVoid			DiMakeLatLongEnvironmentV( const char *pic, const char *tex, DtFilterFunc filterfunc,
								DtFloat swidth, DtFloat twidth,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiMakeShadow( const char *pic, const char *tex, ... );
	virtual DtVoid			DiMakeShadowV( const char *pic, const char *tex,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiMakeTexture( const char *pic, const char *tex, DtToken swrap, DtToken twrap,
								DtFilterFunc filterfunc, DtFloat swidth, DtFloat twidth, ... );
	virtual DtVoid			DiMakeTextureV( const char *pic, const char *tex, DtToken swrap, DtToken twrap,
								DtFilterFunc filterfunc, DtFloat swidth, DtFloat twidth,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;


	// ------------------ Reading and writing archive files

	virtual DtVoid			DiArchiveRecord( DtToken type, const char *format, ... ) = 0;
	DtVoid					DiReadArchive( DtString filename, DtArchiveCallback callback, ... );
	virtual DtVoid			DiReadArchiveV( DtString filename, DtArchiveCallback callback,
								int n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtArchiveHandle			DiArchiveBegin( DtToken archivename, ... );
	virtual DtArchiveHandle	DiArchiveBeginV( DtToken archivename, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiArchiveEnd() = 0;


	// ------------------ Renderer options

	DtVoid					DiCamera( DtToken camera, ... );
	virtual DtVoid			DiCameraV( DtToken camera, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiClipping( DtFloat hither, DtFloat yon ) = 0;
	virtual DtVoid			DiClippingPlane( DtFloat x, DtFloat y, DtFloat z, DtFloat nx, DtFloat ny, DtFloat nz ) = 0;
	virtual DtVoid			DiColorSamples( DtInt N, DtFloat *nRGB, DtFloat *RGBn ) = 0;
	virtual DtVoid			DiCropWindow( DtFloat xmin, DtFloat xmax, DtFloat ymin, DtFloat ymax ) = 0;
	virtual DtVoid			DiDepthOfField( DtFloat fstop, DtFloat focallength, DtFloat focaldistance ) = 0;
	DtVoid					DiDisplay( const char *name, DtToken type, DtToken mode, ... );
	virtual DtVoid			DiDisplayV( const char *name, DtToken type, DtToken mode,
								DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiDisplayChannel( const char *channel, ... );
	virtual DtVoid			DiDisplayChannelV( const char *channel, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiExposure( DtFloat gain, DtFloat gamma ) = 0;
	virtual DtVoid			DiFormat( DtInt xres, DtInt yres, DtFloat aspect ) = 0;
	virtual DtVoid			DiFrameAspectRatio( DtFloat aspect ) = 0;
	DtVoid					DiHider( DtToken type, ... );
	virtual DtVoid			DiHiderV( DtToken type, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	DtVoid					DiOption( DtToken name, ... );
	virtual DtVoid			DiOptionV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiPixelFilter( DtFilterFunc function, DtFloat xwidth, DtFloat ywidth ) = 0;
	virtual DtVoid			DiPixelSamples( DtFloat xsamples, DtFloat ysamples ) = 0;
	virtual DtVoid			DiPixelVariance( DtFloat variation ) = 0;
	DtVoid					DiProjection( DtToken name, ... );
	virtual DtVoid			DiProjectionV( DtToken name, DtInt n, const DtToken tokens[], DtPointer params[] ) = 0;
	virtual DtVoid			DiQuantize( DtToken type, DtInt one, DtInt qmin, DtInt qmax, DtFloat ampl ) = 0;
	virtual DtVoid			DiRelativeDetail( DtFloat relativedetail ) = 0;
	virtual DtVoid			DiShutter( DtFloat smin, DtFloat smax ) = 0;

	
	// ------------------ Shader Language Interrogation

	virtual int				DSlo_SetPath(const char *i_path) = 0;
	virtual int				DSlo_SetShader(const char *i_name) = 0;
	virtual const char*		DSlo_GetName() = 0;
	virtual DSLO_TYPE		DSlo_GetType() = 0;
	virtual int				DSlo_HasMethod(const char *i_name) = 0;
	virtual const char* const*	DSlo_GetMethodNames() = 0;
	virtual int				DSlo_GetNArgs() = 0;

	virtual DSLO_VISSYMDEF*	DSlo_GetArgById(int i_id) = 0;
	virtual DSLO_VISSYMDEF*	DSlo_GetArgByName(const char *i_name) = 0;
	virtual DSLO_VISSYMDEF*	DSlo_GetArrayArgElement(DSLO_VISSYMDEF *i_array, int i_index) = 0;

	virtual int				DSlo_GetNAnnotations() = 0;
	virtual const char*		DSlo_GetAnnotationKeyById(int i_id) = 0;
	virtual const char*		DSlo_GetAnnotationByKey(const char *i_key) = 0;

	virtual void			DSlo_EndShader() = 0;
	virtual const char*		DSlo_TypetoStr(DSLO_TYPE i_type) = 0;
	virtual const char*		DSlo_StortoStr(DSLO_STORAGE i_storage) = 0;
	virtual const char*		DSlo_DetailtoStr(DSLO_DETAIL i_detail) = 0;


	// ------------------ Rendering
	virtual bool			render( DzRenderHandler *handler, DzCamera *camera, const DzRenderOptions &opt ) = 0;
	virtual bool			customRender( DzRenderHandler *handler, DzCamera *camera, DzLightList &lights, 
								DzNodeList &nodes, const DzRenderOptions &opt ) = 0;

public slots:

	//
	// MANIPULATORS
	//

	bool						render( DzRenderHandler *handler, DzCamera *camera, const DzRenderOptions *opt );
	bool						customRender( DzRenderHandler *handler, DzCamera *camera, QObjectList lights, 
										QObjectList nodes, const DzRenderOptions *opt );
	virtual void					prepareImage( const DzTexture *img, const QString &filename );
	virtual QString					compileShader( const QString &shaderPath );
	virtual QString					compileShader( const QString &shaderPath, QString &output ) = 0;
	virtual DzShaderDescription*	getShaderInfo( const QString &shaderPath ) = 0;
	virtual void					killRender() = 0;

	virtual bool				bake( DzRenderHandler *handler, DzCamera *camera, DzLightListIterator &lights,
										DzNodeListIterator &nodes, const DzBakerOptions &opt ) { return false; }
	virtual bool				autoBake( DzRenderHandler *handler, DzCamera *camera, DzLightListIterator &lights, 
										DzNodeListIterator &nodes, const DzBakerOptions &opt ) { return false; }
	virtual void				stopBaking() { }
	virtual void				saveBakeImage( const DzBakerOptions &opt, bool wait ) { }
	
	virtual bool				textureConvert( DzRenderHandler *handler, DzCamera *camera, 
										const DzTextureConvertorOptions &opt ) { return false; }
	//
	// ACCESSORS
	//

	virtual QString			getShaderCompilerPath() = 0;
	virtual QString			getTextureUtilityPath() = 0;

	virtual QStringList		getShaderSearchPaths() const;
	virtual QString			processShaderName( const QString &shaderName ) const;
	virtual QString			getShaderPath( const QString &shaderName, bool withExtension = true ) const;
	virtual QString			getShaderFileName( const QString &shaderName ) const;
	virtual QString			getShaderExtension() const = 0;
	virtual bool			isRendering() const = 0;
	virtual QString			getName() const = 0;
	virtual DzNode*			getCurrentNode() const = 0;

public:

	virtual DzOptionsFrame*	getOptionsFrame() const = 0;
	virtual DtFilterFunc	getFilterFunction( DzRenderOptions::PixelFilter filterType ) const = 0;

signals:

	void					aboutToRender( DzRenderer *r );
	void					renderFinished( DzRenderer *r );
	void					imagePrepared( const DzTexture *img, const QString &filename );

protected:

	// ------------------ Basic control flow, scoping, stacks

	virtual DtVoid			DiBegin( DtToken name ) = 0;
	virtual DtVoid			DiEnd() = 0;
	virtual DtVoid			DiFrameBegin( DtInt number ) = 0;
	virtual DtVoid			DiFrameEnd() = 0;

	void					renderRecurse( DzNode *node );
	static void				errorFunc( DtInt code, DtInt severity, char *msg );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_RENDERER_H
