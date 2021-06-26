cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(sixteen_games CXX)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
else()
  if (CMAKE_CXX_STANDARD VERSION_LESS 20)
    message(FATAL_ERROR "CMAKE_CXX_STANDARD of 20 or later required.")
  endif()
endif()
if (NOT DEFINED CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if (MSVC)
	add_definitions(-D_UNICODE -DUNICODE -DWIN32_LEAN_AND_MEAN -DNOMINMAX -DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
	add_definitions(-D_ATL_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()


add_subdirectory(original)


#find_package(SDL2 CONFIG REQUIRED)
#find_package(sdl2-image CONFIG REQUIRED)
#find_package(sdl2-ttf CONFIG REQUIRED)
#find_package(sdl2-mixer CONFIG REQUIRED)
#
#include_directories(include)
#
#file(GLOB_RECURSE PROJ_SRC_FILES
#	CONFIGURE_DEPENDS
#	src/*.cpp 
#)
#
#add_executable(cursor_custodian WIN32
#	${PROJ_SRC_FILES}
#)
#
#
#target_link_options(cursor_custodian PRIVATE "/ENTRY:mainCRTStartup")
#
#target_link_libraries(cursor_custodian PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image SDL2::SDL2_mixer SDL2::SDL2_ttf)
#
#add_custom_command(
#        TARGET cursor_custodian POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#                ${CMAKE_CURRENT_SOURCE_DIR}/res/
#                ${CMAKE_CURRENT_BINARY_DIR}/res/        
#)
#