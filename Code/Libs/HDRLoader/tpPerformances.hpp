/*
 * tpPreformances.h
 *
 *  Created on: 26 févr. 2010
 *      Author: beltegeuse
 */

#ifndef TPPREFORMANCES_H_
#define TPPREFORMANCES_H_

#include "tpConfig.h"

#ifdef LINUX
#include <sys/time.h>
#endif

/*!
  \file tpPerformances.hpp
  \brief performance compare management.
*/

/*!

  \class tpPerformances
  \brief performance compare management.
*/

class tpPerformances {
public:
	// ========== Methode publique ============
	/*!
	 * Register the current time.
	 */
	static  void Tic();
	/*!
	 * Compare the current time with the register time.
	 */
	static  void Toc();
private:
	// ========== Attributs ============
#ifdef LINUX
	static  timeval m_time;
#endif
};

#endif /* TPPREFORMANCES_H_ */
