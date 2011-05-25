/*
 * tpPreformances.cpp
 *
 *  Created on: 26 févr. 2010
 *      Author: beltegeuse
 */
#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpPerformances.hpp"
#include <iostream>

#ifdef LINUX
timeval tpPerformances::m_time;
#endif

void tpPerformances::Tic()
{
#ifdef LINUX
	gettimeofday(&m_time, NULL);
#endif
}
void tpPerformances::Toc()
{
#ifdef LINUX
	timeval end;
	gettimeofday(&end, NULL);

	int ecart = (end.tv_usec - m_time.tv_usec) % 1000;
	int diff = difftime(end.tv_sec, m_time.tv_sec);

	//std::cout << "[DEBUG] ecart : " << ecart << std::endl;
	//std::cout << "[DEBUG] diff sec : " << diff << std::endl;

	if(diff > 0)
	{
		ecart += diff*1000;
	}

	std::cout << "=== Temps : " << ecart << " ms === " << std::endl;
#endif
}



