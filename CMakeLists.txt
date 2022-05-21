#**********************************************************************
#	Copyright (C) 2002-2020 Daz 3D, Inc. All Rights Reserved.
#
#	This file is part of the DAZ Studio SDK.
#
#	This file may be used only in accordance with the DAZ Studio SDK
#	license provided with the DAZ Studio SDK.
#
#	The contents of this file may not be disclosed to third parties,
#	copied or duplicated in any form, in whole or in part, without the
#	prior written permission of Daz 3D, Inc, except as explicitly
#	allowed in the DAZ Studio SDK license.
#
#	See http://www.daz3d.com to contact DAZ 3D or for more
#	information about the DAZ Studio SDK.
#**********************************************************************

cmake_minimum_required(VERSION 3.4.0)



option(BUILD_SAMPLES "Build the samples" OFF)


if(APPLE)
	set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif(APPLE)

project("DAZ Studio SDK 4.5")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(DAZ_STUDIO_EXE_DIR "" CACHE PATH "Path to DAZ Studio executable directory, needs to be installed to a writeable location" )

if(NOT DAZ_STUDIO_EXE_DIR )
	message("Path to DAZ Studio not provided. Projects will build locally.")
endif()

# Platform checks
if(WIN32)
	set(DZ_LIB_SUFFIX ".lib")
	set(DZ_BIN_SUFFIX ".dll")
	set(DZ_LIB_PREFIX "")
	set(UTIL_EXT ".exe")
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(DZ_PLATFORM x86)
		set(DZ_MIXED_PLATFORM Win32)
		set(DZ_OS_PLATFORM Win32)
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(DZ_PLATFORM x64)
		set(DZ_MIXED_PLATFORM x64)
		set(DZ_OS_PLATFORM Win64)
	else()
		message(FATAL_ERROR "Unknown architecture")
	endif()

elseif(APPLE)
	set(DZ_LIB_SUFFIX ".dylib")
	set(DZ_BIN_SUFFIX ".dylib")
	set(DZ_LIB_PREFIX "lib")
	set(UTIL_EXT "")
	if(CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(DZ_PLATFORM x86)
		set(DZ_MIXED_PLATFORM Mac32)
		set(DZ_OS_PLATFORM Mac32)
	elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(DZ_PLATFORM x64)
		set(DZ_MIXED_PLATFORM Mac64)
		set(DZ_OS_PLATFORM Mac64)
	else()
		message(FATAL_ERROR "Unknown architecture")
	endif()
	set(CMAKE_MACOSX_RPATH TRUE CACHE BOOL "MacOSX rpath" FORCE)
	set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE CACHE BOOL "Build with install rpath" FORCE)
else()
	message(FATAL_ERROR "Unknown architecture")
endif(WIN32)

set(DZSDK_CORE_RELATIVE_PATH "lib/${DZ_MIXED_PLATFORM}/${DZ_LIB_PREFIX}dzcore${DZ_LIB_SUFFIX}")
if(NOT DZSDK_DIR)
	if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${DZSDK_CORE_RELATIVE_PATH})
		set( DZSDK_DIR ${CMAKE_CURRENT_LIST_DIR} )
	else()
		message(FATAL_ERROR "Missing path to DAZ Studio SDK")
	endif()
endif()

message(STATUS "Using DAZ Studio SDK: ${DZSDK_DIR}")
set(DZSDK_DIR ${DZSDK_DIR} CACHE PATH "Path to root of the DAZ Studio SDK" FORCE)
find_package(OpenGL REQUIRED)

#we only have release libraries for dzcore/qt so make sure even in debug they we use MD and undef debug
if(WIN32)
	add_compile_options( "/MD" "/U_DEBUG" )
endif()

# Set dzcore as import target
set(DZSDK_INCLUDE_DIR "${DZSDK_DIR}/include" CACHE FILEPATH "Path to DAZ Studio SDK includes" FORCE)
set(DZSDK_DZCORE_LIB "${DZSDK_DIR}/${DZSDK_CORE_RELATIVE_PATH}" CACHE FILEPATH "Path to dzcore library" FORCE)
if(NOT EXISTS ${DZSDK_DZCORE_LIB})
	message(FATAL_ERROR "The library dzcore${DZ_LIB_SUFFIX} could not be located.  Check the path for DZSDK_DIR.")
	return()
endif()

# DZCore
add_library(dzcore SHARED IMPORTED)
if(WIN32)
	set_property(TARGET dzcore APPEND PROPERTY IMPORTED_IMPLIB ${DZSDK_DZCORE_LIB})
else()
	set_property(TARGET dzcore APPEND PROPERTY IMPORTED_LOCATION ${DZSDK_DZCORE_LIB})
endif(WIN32)
set_property(TARGET dzcore APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${DZSDK_INCLUDE_DIR}" )

# DPC
set(DZSDK_DPC_EXE "${DZSDK_DIR}/bin/${DZ_MIXED_PLATFORM}/dpc${UTIL_EXT}" CACHE FILEPATH "Path to DAZ Studio SDK dpc executable" )
if(NOT EXISTS ${DZSDK_DPC_EXE})
	message(FATAL_ERROR "The dpc executable could not be located.  Check the path for DZSDK_DIR.")
	return()
endif()
add_executable(dpc IMPORTED)
set_property(TARGET dpc APPEND PROPERTY IMPORTED_LOCATION ${DZSDK_DPC_EXE})

# Setup Qt from the DAZ SDK & Export
if(WIN32)
	set(DZSDK_QTCORE_LIBRARY "${DZSDK_DIR}/lib/${DZ_MIXED_PLATFORM}/QtCore4.lib" CACHE FILEPATH "Path to DAZ Studio SDK QtCore library" FORCE)
elseif(APPLE)
	set(DZSDK_QTCORE_LIBRARY "${DZSDK_DIR}/lib/${DZ_MIXED_PLATFORM}/QtCore.framework" CACHE FILEPATH "Path to DAZ Studio SDK QtCore library" FORCE)
endif()

# the qt find module needs this folder but our build does not so just fake it
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/DUMMY_MKSPECS/default" )
set(QT_MKSPECS_DIR "${CMAKE_CURRENT_BINARY_DIR}/DUMMY_MKSPECS" CACHE PATH "Path to dummy mkspecs directory" FORCE)



set(DZ_LIB_SUFFIX ${DZ_LIB_SUFFIX} CACHE STRING "DZ Library suffix" FORCE)
set(DZ_BIN_SUFFIX ${DZ_BIN_SUFFIX} CACHE STRING "DZ Binary suffix" FORCE)
set(DZ_LIB_PREFIX ${DZ_LIB_PREFIX} CACHE STRING "DZ Library prefix" FORCE)
set(UTIL_EXT ${UTIL_EXT} CACHE STRING "DZ Utility extension" FORCE)

set(DZ_PLATFORM ${DZ_PLATFORM} CACHE STRING "DZ Platform" FORCE)
set(DZ_MIXED_PLATFORM ${DZ_MIXED_PLATFORM} CACHE STRING "DZ Mixed platform" FORCE)
set(DZ_OS_PLATFORM ${DZ_OS_PLATFORM} CACHE STRING "DZ OS Platform" FORCE)
set(DZ_PLATFORM ${DZ_PLATFORM} CACHE STRING "DZ Platform" FORCE)
set(DZ_MIXED_PLATFORM ${DZ_MIXED_PLATFORM} CACHE STRING "DZ Mixed platform" FORCE)
set(DZ_OS_PLATFORM ${DZ_OS_PLATFORM} CACHE STRING "DZ OS Platform" FORCE)

set(QT_QTCORE_LIBRARY_RELEASE ${DZSDK_QTCORE_LIBRARY})
set(QT_QMAKE_EXECUTABLE "${DZSDK_DIR}/bin/${DZ_MIXED_PLATFORM}/qmake${UTIL_EXT}" CACHE FILEPATH "Path to DAZ Studio SDK qmake executable" )
set(QT_BINARY_DIR "${DZSDK_DIR}/bin/${DZ_MIXED_PLATFORM}" CACHE PATH "Path to Qt binaries"  FORCE)
set(QT_HEADERS_DIR "${DZSDK_DIR}/include" CACHE PATH "Path to Qt headers" FORCE)
set(QT_QTCORE_INCLUDE_DIR "${DZSDK_DIR}/include/QtCore" CACHE PATH "Path to QtCore include directory" FORCE)

find_package(Qt4 4.8.1 REQUIRED QtCore QtGui QtScript QtOpenGL QtNetwork QtSql QtXml)
set(DZSDK_QT_CORE_TARGET Qt4::QtCore PARENT_SCOPE)
set(DZSDK_QT_GUI_TARGET Qt4::QtGui PARENT_SCOPE)
set(DZSDK_QT_SCRIPT_TARGET Qt4::QtScript PARENT_SCOPE)
set(DZSDK_QT_OPENGL_TARGET Qt4::QtOpenGL	PARENT_SCOPE)
set(DZSDK_QT_NETWORK_TARGET Qt4::QtNetwork	PARENT_SCOPE)
set(DZSDK_QT_SQL_TARGET	Qt4::QtSql	PARENT_SCOPE)
set(DZSDK_QT_XML_TARGET	Qt4::QtXml	PARENT_SCOPE)

list(APPEND CMAKE_AUTOMOC_MOC_OPTIONS -i)
set(CMAKE_AUTOMOC_MOC_OPTIONS PARENT_SCOPE)
set(CMAKE_AUTOMOC ON PARENT_SCOPE)

if(BUILD_SAMPLES)
	add_subdirectory(samples)
endif()
