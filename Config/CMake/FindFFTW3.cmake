#
# Try to find FFTW3 library and include path.
# Once done this will define
#
# FFTW3_FOUND
# FFTW3_INCLUDE_DIR
# FFTW3_LIBRARY
# 
# Need LibFindMacros & LibFindVSPath (Win32 only)

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(FFTW3_PKGCONF fftw3)

IF(WIN32)
	include(LibFindVSPath)

	find_path(FFTW3_INCLUDE_DIR
 	 NAMES fftw3.h
  	 PATHS 
  	    ${FFTW3_ROOT_DIR}/include
  	 	${FFTW3_PKGCONF_INCLUDE_DIRS} 
  	 	${VS_DIR}/VC/include
  	 	C:/MinGW/include
  	 DOC "The directory where fftw3.h resides"
	)
	
	find_library(FFTW3_LIBRARY
 	 NAMES libfftw3 fftw3
  	 PATHS 
  	    ${FFTW3_ROOT_DIR}/lib
  	 	${FFTW3_PKGCONF_LIBRARY_DIRS} 
  	 	${VS_DIR}/VC/lib
  	 	C:/MinGW/lib
  	 DOC "The fftw3 library"
	)
	
ELSE(WIN32)
	find_path(FFTW3_INCLUDE_DIR
 	 NAMES fftw3.h
  	 PATHS 
  	 	${FFTW3_ROOT_DIR}/include
  	 	${FFTW3_PKGCONF_INCLUDE_DIRS} 
  	 	/usr/include
  	 	/usr/local/include
		/sw/include
		/opt/local/include
  	 DOC "The directory where fftw3.h resides"
	)
	
	find_library(FFTW3_LIBRARY
 	 NAMES libfftw3 fftw3
  	 PATHS 
  	 	${FFTW3_ROOT_DIR}/include
  	 	${FFTW3_PKGCONF_LIBRARY_DIRS} 
  	 	/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
  	 DOC "The fftw3 library"
	)
ENDIF(WIN32)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(FFTW3_PROCESS_INCLUDES FFTW3_INCLUDE_DIR)
set(FFTW3_PROCESS_LIBS FFTW3_LIBRARY)
libfind_process(FFTW3)