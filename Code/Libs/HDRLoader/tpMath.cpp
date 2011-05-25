#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpMath.h"

#include "tpException.hpp"

#include <cmath>
#include <math.h>
#include <iostream>

tpFilter tpMath::GaussianKernel2D(float sig, int taille)
{
	Assert(taille % 2 != 0);
	int dc = (taille - 1) / 2;
	
	std::cout << "[Info] [GaussianKernel] Taille : " << taille << std::endl;
	std::cout << "[Info] [GaussianKernel] Sig : " << sig << std::endl;

	tpImage<float> I;
	float sum = 0.0;

	I.resize(taille,taille);
	
	for(int i = 0; i < taille; i++)
	{
		for(int j = 0; j < taille; j++)
		{
			I[i][j] = exp(- (pow((float)i-dc,2) + pow((float)j-dc,2)) / (2.0*pow((float)sig,2)));
			sum += I[i][j];
		}
	}

	std::cout << "[Info] [GaussianKernel] norm terms : " << sum << std::endl;

	for(int i = 0; i < taille; i++)
	{
		for(int j = 0; j < taille; j++)
		{
			I[i][j] = I[i][j] / sum;
		}
	}

	return I;
}

tpFilter tpMath::GaussianKernel2D(float sig)
{
	int taille = 8*sig+1;
	return GaussianKernel2D(sig, taille);
}

tpFilter tpMath::GaussianKernel2D(int taille)
{
	Assert(taille % 2 != 0);
	return GaussianKernel2D((taille - 1) / 8.0, taille);
}

tpFilter tpMath::ConstantKernel2D(int taille)
{
	tpFilter I;
	
	I.resize(taille,taille);

	for(int i = 0; i < taille; i++)
	{
		for(int j = 0; j < taille; j++)
		{
			I[i][j] = 1.0 / ((float)(taille*taille));
		}
	}

	return I;
}

