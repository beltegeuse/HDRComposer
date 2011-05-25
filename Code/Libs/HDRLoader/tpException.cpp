#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpException.hpp"
#include <sstream>

tpException::tpException(const std::string& reason):
  _reason(reason)
{}

tpException::~tpException() throw()
{
}

const char* tpException::what() const throw()
{
  return _reason.c_str();
}

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param File :    Fichier source contenant l'erreur
/// \param Line :    Ligne a laquelle se trouve l'erreur dans le fichier source
/// \param Message : Message d'erreur
///
////////////////////////////////////////////////////////////
tpAssertException::tpAssertException(const std::string& File, int Line, const std::string& Message) :
tpException("")
{
	std::ostringstream oss;
	oss << File << " (" << Line << ") : " << Message << std::endl;
	_reason = oss.str();
}

////////////////////////////////////////////////////////////
// Constructeur
//
// [in] File :    Fichier
// [in] Message : Message d'erreur
//
////////////////////////////////////////////////////////////
tpLoadingFailed::tpLoadingFailed(const std::string& File, const std::string& Message) :
	tpException("")
{
    // Formatage du message d'erreur
    std::ostringstream oss;
    oss << "Erreur dans le chargement de " << File << std::endl << std::endl << Message;

    _reason = oss.str();
}


