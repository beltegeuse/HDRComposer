#ifndef tpReadOption_h
#define tpReadOption_h

#include "tpConfig.h"

/*!
  \file tpReadOption.hpp
  \brief Command line option management.
*/

/*!

  \class tpReadOption
  \brief Command line option management
*/
class tpReadOption
{

public:
	static  int getoption (int argc, char** argv, char* pszValidOpts, char** ppszParam);
	
};

#endif
