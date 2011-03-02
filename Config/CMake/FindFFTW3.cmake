# Variables
IF(WIN32)
SET(FFTW3_PATH_SEARCH_INCLUDE
	C:/cygwin/usr/local/include
	C:/msys/local/include
  	C:/MinGW/include
	T:/INC/MinGW/include
  	NO_DEFAULT_PATH
)
ELSE(WIN32)
SET(FFTW3_PATH_SEARCH_INCLUDE
	/usr/include/SFML
  	/usr/local/include/SFML
	/temporaire/reseau/INC/SeaGull/include/SFML
	/temporaire/reseau/INC/SeaGull/include
  	NO_DEFAULT_PATH
)
ENDIF(WIN32)
SET(FFTW3_PATH_SEARCH_LIB
	/usr/lib
 	/usr/local/lib
	/temporaire/reseau/INC/SeaGull/lib
  	C:/MinGW/lib
	T:/INC/MinGW/lib
  	NO_DEFAULT_PATH
)

# ------- Include ----------------

FIND_PATH(FFTW3_INCLUDE_DIR fftw3.h
	${FFTW3_PATH_SEARCH_INCLUDE}
)

FIND_PATH(FFTW3_INCLUDE_DIR FreeImage.h)

# ------- FreeImage ---------------

FIND_LIBRARY(FFTW3_LIBRARY NAMES libfftw3 fftw3 PATHS 
  ${FFTW3_PATH_SEARCH_LIB}
)

FIND_LIBRARY(FFTW3_LIBRARY NAMES libfftw3 fftw3)

MESSAGE("FFTW3_LIBRARY is ${FFTW3_LIBRARY}")