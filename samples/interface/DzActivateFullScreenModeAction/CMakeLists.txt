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

set(CMAKE_AUTOMOC OFF)

set(DZ_PLUGIN_TGT_NAME sdk_activatefullscreenmodeaction)
set(DZ_PLUGIN_PROJECT_NAME "Activate Full Screen Mode Action")

if(WIN32)
	set(OS_SOURCES
		DzActivateFullScreenModeAction.rc
		dzactivatefullscreenmodeaction.def
	)
elseif(APPLE)
	set(OS_SOURCES "")
endif()

SET(PLUGIN_MOC_SOURCES "")
if( DZ_SDK5_BUILD )
	qt5_wrap_cpp( PLUGIN_MOC_SOURCES dzactivatefullscreenmodeaction.h
		OPTIONS
			-fdzactivatefullscreenmodeaction.h )
else()
	qt4_wrap_cpp( PLUGIN_MOC_SOURCES dzactivatefullscreenmodeaction.h
		OPTIONS
			-fdzactivatefullscreenmodeaction.h )
endif()

add_library( ${DZ_PLUGIN_TGT_NAME} SHARED
	dzactivatefullscreenmodeaction.cpp
	dzactivatefullscreenmodeaction.h
	pluginmain.cpp
	version.h
	${OS_SOURCES}
	${PLUGIN_MOC_SOURCES}
)

target_link_libraries(${DZ_PLUGIN_TGT_NAME}
	PRIVATE
	dzcore
	${DZSDK_QT_CORE_TARGET}
	${DZSDK_QT_GUI_TARGET}
	${DZSDK_QT_SCRIPT_TARGET}
)

target_include_directories(${DZ_PLUGIN_TGT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties (${DZ_PLUGIN_TGT_NAME}
	PROPERTIES
	FOLDER "SDK Samples/Interface"
	PROJECT_LABEL ${DZ_PLUGIN_PROJECT_NAME}
)

source_group("Resource Files" REGULAR_EXPRESSION ".*\\.(rc)")
