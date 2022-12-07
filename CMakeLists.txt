cmake_minimum_required(VERSION 3.24)

project(
	BeardMaskFix
	VERSION 1.0.0
	LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_IGNORE_PATH "${PROJECT_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/tools/SKSE-CMakeModules/Modules"
)
include(SKSEPlugin)

set(SKSE_USE_XBYAK ON)
set(SKSE_SUPPORT_VR ON)

SKSEPlugin_Add(
	${PROJECT_NAME}
	SOURCE_DIR src
	SOURCES
		.clang-format
		.editorconfig
		README.md
		vcpkg.json
	PRECOMPILE_HEADERS
		src/PCH/PCH.h
)

if(NOT BUILD_SKYRIMVR)
	install(
		FILES "${PROJECT_SOURCE_DIR}/data/SkyrimSE/BeardMaskFix.esp"
		DESTINATION "."
	)
else()
	install(
		FILES "${PROJECT_SOURCE_DIR}/data/SkyrimVR/BeardMaskFix.esp"
		DESTINATION "."
	)
endif()

install(
	FILES "${PROJECT_SOURCE_DIR}/data/SkyrimSE/BeardMaskFix.esp"
	DESTINATION "SkyrimSE"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)

install(
	FILES "${PROJECT_SOURCE_DIR}/data/SkyrimVR/BeardMaskFix.esp"
	DESTINATION "SkyrimVR"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/Meshes/BeardMaskFix/Armor/DBArmor/DBArmorHoodMasked_0.nif"
		"${PROJECT_SOURCE_DIR}/data/Meshes/BeardMaskFix/Armor/DBArmor/DBArmorHoodMasked_1.nif"
		"${PROJECT_SOURCE_DIR}/data/Meshes/BeardMaskFix/Armor/DBArmor/DBArmorHoodMasked_Arg_0.nif"
		"${PROJECT_SOURCE_DIR}/data/Meshes/BeardMaskFix/Armor/DBArmor/DBArmorHoodMasked_Arg_1.nif"
		"${PROJECT_SOURCE_DIR}/data/Meshes/BeardMaskFix/Armor/DBArmor/DBArmorHoodMasked_Kha_0.nif"
		"${PROJECT_SOURCE_DIR}/data/Meshes/BeardMaskFix/Armor/DBArmor/DBArmorHoodMasked_Kha_1.nif"
	DESTINATION "Meshes/BeardMaskFix/Armor/DBArmor"
	COMPONENT Fomod
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/fomod/info.xml"
		"${PROJECT_SOURCE_DIR}/data/fomod/ModuleConfig.xml"
	DESTINATION "fomod"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)

install(
	FILES
		"${PROJECT_SOURCE_DIR}/data/fomod/images/skyrim_se.jpg"
		"${PROJECT_SOURCE_DIR}/data/fomod/images/skyrim_vr.jpg"
	DESTINATION "fomod/images"
	COMPONENT Fomod
	EXCLUDE_FROM_ALL
)
