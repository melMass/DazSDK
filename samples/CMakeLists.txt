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

# if DAZ_STUDIO_EXE_DIR is not defined the compiled result will be placed in
# the default CMake binary folder

# if building an executable and you want it placed next to the DAZStudio executable
if(DAZ_STUDIO_EXE_DIR)
	foreach(curConfig ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${curConfig} curConfig)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${curConfig} ${DAZ_STUDIO_EXE_DIR})
	endforeach()
endif()

add_subdirectory(applications)

# if building a plugin and you want the compiled result placed in the Daz Studio ./plugins directory
if(DAZ_STUDIO_EXE_DIR)
	foreach(curConfig ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${curConfig} curConfig)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${curConfig} ${DAZ_STUDIO_EXE_DIR}/plugins)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${curConfig} ${DAZ_STUDIO_EXE_DIR}/plugins)
	endforeach()
endif()

add_subdirectory(interface)
add_subdirectory(modifiers)
add_subdirectory(saving)
add_subdirectory(shaderbricks)
add_subdirectory(Tools)
