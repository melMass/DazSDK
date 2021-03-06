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
	Defines the ::DzError type, the ::getErrorMessage() function, and the error codes that are
	returned by various DAZ Studio SDK functions.
**/

#ifndef DAZ_ERROR_CODES_H
#define DAZ_ERROR_CODES_H

/*****************************
	Includes
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Types
*****************************/

typedef unsigned int DzError;

/*****************************
	Forward declarations
*****************************/

class QString;

/*****************************
	Error codes
*****************************/

#define DZ_NO_ERROR							0x00000000
#define DZ_ALREADY_EXISTS_ERROR				0x00000050
#define DZ_DOES_NOT_EXIST_ERROR				0x00000051
#define DZ_NON_UNIQUE_NAME_ERROR			0x00000052
#define DZ_ILLEGAL_HIERARCHY_ERROR			0x00000053
#define DZ_INDEX_OUT_OF_RANGE_ERROR			0x00000054
#define DZ_INVALID_ENUM_ERROR				0x00000055
#define DZ_ILLEGAL_ARGUMENT_ERROR			0x00000060
#define DZ_ILLEGAL_OPERATION_ERROR			0x00000061
#define DZ_OPERATION_FAILED_ERROR			0x00000062
#define DZ_NO_MATCH_ERROR					0x00000063
#define DZ_USER_CANCELLED_OPERATION			0x00000064
#define DZ_UNHANDLED_EXCEPTION_ERROR		0x00000065
#define DZ_TYPE_MISMATCH_ERROR				0x00000070
#define DZ_CLASS_FACTORY_NOT_FOUND_ERROR	0x00000071
#define DZ_SCRIPT_PARSE_ERROR				0x00000080
#define DZ_MEMORY_ALLOCATION_ERROR			0x00000090
#define DZ_PROFILE_NOT_SUPPORTED_ERROR		0x00000100
#define DZ_ALREADY_BOUND_ERROR				0x00000101
#define DZ_NOT_BOUND_ERROR					0x00000102
#define DZ_UNABLE_TO_OPEN_FILE_ERROR		0x00000200
#define DZ_SECTION_NOT_OPEN_ERROR			0x00000201
#define DZ_SECTION_LENGTH_EXCEEDED_ERROR	0x00000202
#define DZ_FORMAT_NOT_SUPPORTED_ERROR		0x00000203
#define DZ_FILE_FORMAT_ERROR				0x00000204
#define DZ_FILE_FORMAT_TOO_NEW_ERROR		0x00000205
#define DZ_FILE_FORMAT_TOO_OLD_ERROR		0x00000206
#define DZ_MISSING_FILES_ERROR				0x00000207
#define DZ_MISSING_ITEMS_ERROR				0x00000208
#define DZ_FILE_NOT_FOUND_ERROR				0x00000209
#define DZ_INVALID_FILE_ERROR				0x00000210
#define DZ_INVALID_SELECTION_ERROR			0x00000300
#define DZ_UI_NOT_AVAILABLE_ERROR			0x00000400
#define DZ_VERTEX_COUNT_MISMATCH_ERROR		0x00000501

/*****************************
	Functions
*****************************/

DZ_EXPORT QString	getErrorMessage( DzError errCode );

#endif // DAZ_ERROR_CODES_H