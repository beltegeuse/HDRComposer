#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpHDRToneOperatorAshikhmin.h"
#include "Operations/tpHDROperations.h"
#include "Managers/tpDisplayManager.h"
#include <vector>
#include <map>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

tpHDRToneOperatorAshikhmin::tpHDRToneOperatorAshikhmin(double t) :
	m_t(t)
{
}

tpHDRToneOperatorAshikhmin::~tpHDRToneOperatorAshikhmin(void)
{
}

void tpHDRToneOperatorAshikhmin::CompressLum(tpImageLuminanceHDR& I)
{
	// On recupere min et max
	double max = tpHDROperations::GetMax(I);
	double min = tpHDROperations::GetMin(I);

	// On applique precalcul les resultats
	double CLwmax = C(max);
	double CLwmin = C(min);

	if(I.getHeight() < 23 || I.getWidth() < 23)
	{
		std::cout << "[Warning] tpHDRToneOperatorAshikhmin : Impossible d'appliquer cet operateur sur une image pas assez grande (23)." << std::endl;
		return;
	}

	// Les differents filtre que l'on doit calculer
	int small = 3;
	int mv[] = {23,19,15,11,9,7,5,3};
	std::vector<int> v(mv, mv + sizeof(mv) / sizeof(int));
	std::vector<int>::iterator itV = v.begin();
	
	std::cout << "[Info] [tpHDRToneOperatorAshikhmin] Creation blur ... " << std::endl;

	// Creation des differentes valeurs du filtres
	std::map<int,tpFilterResultDouble> filtrage;
	while(itV != v.end())
	{
		std::cout << " * Filtrage : " << (*itV) << std::endl;

		tpFilterResultDouble temp;
		tpFilter kernel = tpMath::GaussianKernel2D((int)*itV);
		
		tpImageFilter::ApplyFilter(I, temp, kernel);

		filtrage[*itV] = temp;
		
		++itV;
	}

	std::cout << "[Info] [tpHDRToneOperatorAshikhmin] Merging ... " << std::endl;
	
	// Pour connaitre le % de repartitions
	std::map<int, int> Result;
	
	// Les valeurs finales
	int mvFinal[] =  {11,9,7,5,3};
	std::vector<int> vFinal(mvFinal, mvFinal + sizeof(mvFinal) / sizeof(int));
	std::vector<int>::iterator itVFinal = vFinal.begin();

	// On rempli le vBlur et on initialise Result
	std::map<int, tpFilterResultDouble> vBlur;
	while(itVFinal != vFinal.end())
	{
		std::cout << " * Merge : " << (*itVFinal) << std::endl;
		vBlur[*itVFinal] = ( CalculDifference(filtrage[*itVFinal], filtrage[2*(*itVFinal) + 1]) );
		Result[*itVFinal] = 0;
		++itVFinal;
	}
	

	std::cout << "[Info] [tpHDRToneOperatorAshikhmin] Compute right value ... " << std::endl;
	
	for(unsigned int i = 0; i < I.getHeight(); i++)
	{
		for(unsigned int j = 0; j < I.getWidth(); j++)
		{
			std::vector<int>::iterator it = vFinal.begin();
			double Lwa = (filtrage[small])[i][j];
			while(it != vFinal.end())
			{
				if((vBlur[*it])[i][j] < m_t)
				{
					// On a trouver notre meilleur approximation
					Lwa = (filtrage[*it])[i][j];
					Result[*it]++;
					break;
				}

				++it;
			}

			if(it == vFinal.end())
			{
				Result[small]++;
			}

			I[i][j] = (1*( ( C(Lwa) - CLwmin ) / ( CLwmax - CLwmin ) ) )*(I[i][j] / Lwa); // tpDisplayManager::Instance()->GetLuminanceMax()
		}
	}

	std::cout << "[Info] [tpHDRToneOperatorAshikhmin] Resultat : " << std::endl;

	// On affiche nos resultats
	std::map<int, int>::iterator itRes = Result.begin();
	while(itRes != Result.end())
	{
		std::cout << " * " << itRes->first << " : " << (100*(itRes->second / (float)(I.getHeight()*I.getWidth()))) << "%" << std::endl;
		++itRes;
	}

}


tpFilterResultDouble tpHDRToneOperatorAshikhmin::CalculDifference(const tpFilterResultDouble& Is, const tpFilterResultDouble& Is2) const
{

	tpFilterResultDouble res;
	res.resize(Is.getHeight(), Is.getWidth());

	#pragma omp parallel for
	for(int i = 0; i < Is.getHeight(); i++)
	{
		for(int j = 0; j < Is.getWidth(); j++)
		{
			res[i][j] = (abs(Is[i][j] - Is2[i][j]) / Is[i][j]);
		}
	}

	return res;
}

double tpHDRToneOperatorAshikhmin::C(double L) const
{
	if(L < 0.0034)
	{
		return L / 0.0014;
	}
	else if(L < 1)
	{
		return 2.4483 + log10(L / 0.0034) / 0.4027;
	}
	else if( L < 7.2444)
	{
		return 16.5630 + (L - 1) / 0.4027;
	}
	else
	{
		return 32.0693 + log10( L / 7.2444) / 0.0556;
	}
}

void tpHDRToneOperatorAshikhmin::SetT(double v)
{
	m_t = v;
}

double tpHDRToneOperatorAshikhmin::GetT()
{
	return m_t;
}


