PROJECT(Amaterasu3D)

#------- Configuration ------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Config/CMake ${CMAKE_MODULE_PATH})

# * -- To install project ---
SET(PROJECT_BUILD_PATH ${CMAKE_SOURCE_DIR}/Build)

# * --- Dependancy ---
# Fast Fourier transform
FIND_PACKAGE(FFTW3 REQUIRED)
# FreeImage : Load all images format
FIND_PACKAGE(FreeImage REQUIRED)
# Qt4 : Interface
set(QT_USE_QTMAIN TRUE)
FIND_PACKAGE(Qt4 REQUIRED)
# OpenMP :
FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}) 
    set(CCMAKE_C_FLAGS ${CCMAKE_C_FLAGS} ${OpenMP_C_FLAGS})
    set(${CMAKE_EXE_LINKER_FLAGS} -lgomp)
endif()
# * --Subprojects--
#ADD_DEFINITIONS("-Wall -W") #Pour afficher les warning lors de la compilation

ADD_SUBDIRECTORY(Code)
