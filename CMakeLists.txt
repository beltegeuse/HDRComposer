PROJECT(Amaterasu3D)

#------- Configuration ------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Config/CMake ${CMAKE_MODULE_PATH})

# * -- To install project ---
SET(PROJECT_BUILD_PATH ${CMAKE_SOURCE_DIR}/Build)

# * --- Dependancy ---
FIND_PACKAGE(FreeImage REQUIRED)

# * --Subprojects--
ADD_DEFINITIONS("-Wall -W") #Pour afficher les warning lors de la compilation

ADD_SUBDIRECTORY(Code)
