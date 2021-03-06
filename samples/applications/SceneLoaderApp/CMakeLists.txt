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

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
	set(OS_SOURCES
		SceneLoaderApp.rc
	)
elseif(APPLE)
	set(OS_SOURCES "")
endif()

set(APPLICATION_TGT_NAME "SDK_SceneLoaderApp")

add_executable( ${APPLICATION_TGT_NAME}
	dzsceneloader.cpp
	dzsceneloader.h
	main.cpp
	version.h
	${OS_SOURCES}
)

target_link_libraries(${APPLICATION_TGT_NAME}
	PRIVATE
	dzcore
	${DZSDK_QT_CORE_TARGET}
	${DZSDK_QT_GUI_TARGET}
)

if(APPLE)
	set_target_properties (${APPLICATION_TGT_NAME}
		PROPERTIES
		INSTALL_RPATH "@loader_path/Frameworks"
	)
elseif(WIN32)
	target_compile_definitions( ${APPLICATION_TGT_NAME}
		PRIVATE
		-D_CONSOLE
	)
endif()

set_target_properties (${APPLICATION_TGT_NAME}
	PROPERTIES
	FOLDER "SDK Samples/Applications"
)

source_group("Resource Files" REGULAR_EXPRESSION ".*\\.(rc|ico|icns)")
