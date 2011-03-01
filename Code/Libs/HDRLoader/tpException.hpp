#ifndef __Image__tpException
#define __Image__tpException

#include "tpConfig.h"

#include <string>

/*!
  \file tpException.hpp
  \brief Exception.
*/

/*!

  \class tpException
  \brief Exception
*/

class TP_EXPORT tpException: public std::exception
{
public:
	/*!
	 * Constructor.
	 * \param reason : The text which display when the exception raise.
	 */
	tpException(const std::string& reason);

	  /*!
  	 * Destructor.
  	 */
	virtual ~tpException() throw();

	/*!
	 * Constructor.
	 * \retrun : return the error description.
	 */
	virtual const char* what() const throw();
protected:
  std::string _reason;
};

// Class Assertion

////////////////////////////////////////////////////////////
/// Exception lance si une condition n'est pas vrifie
////////////////////////////////////////////////////////////
struct TP_EXPORT tpAssertException : public tpException
{
    tpAssertException(const std::string& File, int Line, const std::string& Message);
};
#ifdef _DEBUG
#   define Assert(condition) if (!(condition)) throw tpAssertException(__FILE__, __LINE__, "Condition non satisfaite\n" #condition)
#else
    inline void DoNothing(bool) {}
#   define Assert(condition) DoNothing(!(condition))
#endif

//==========================================================
// Exception lancee lors d'erreur de chargement de fichiers
//==========================================================
struct tpLoadingFailed : public tpException
{
	tpLoadingFailed(const std::string& File, const std::string& Message);
};


#endif
