PROJECT(Amaterasu3D)

#------- Configuration ------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Config/CMake ${CMAKE_MODULE_PATH})

# * -- To install project ---
SET(PROJECT_BUILD_PATH ${CMAKE_SOURCE_DIR}/Build)

# * --- Dependancy ---
# FreeImage : Load all images format
FIND_PACKAGE(FreeImage REQUIRED)
# Qt4 : Interface
set(QT_USE_QTMAIN TRUE)
FIND_PACKAGE(Qt4 REQUIRED)
# OpenMP :
FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(${CCMAKE_CXX_FLAGS} -fopenmp)
    set(${CCMAKE_C_FLAGS} -fopenmp)
    set(${CMAKE_EXE_LINKER_FLAGS} -lgomp)
endif()
# * --Subprojects--
ADD_DEFINITIONS("-Wall -W -fopenmp") #Pour afficher les warning lors de la compilation

ADD_SUBDIRECTORY(Code)
