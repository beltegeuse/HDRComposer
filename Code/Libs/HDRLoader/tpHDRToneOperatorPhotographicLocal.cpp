#include "StdAfx.h"
#include "tpHDRToneOperatorPhotographicLocal.h"
#include "tpHDROperations.h"
#include "tpDisplayManager.h"
#include "tpMath.h"
#include <vector>
#include <map>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

tpHDRToneOperatorPhotographicLocal::tpHDRToneOperatorPhotographicLocal(double a, double phi, double t) :
	m_a(a),
	m_phi(phi),
	m_t(t)
{
}

tpHDRToneOperatorPhotographicLocal::~tpHDRToneOperatorPhotographicLocal(void)
{
}

void tpHDRToneOperatorPhotographicLocal::CompressLum(tpImageLuminanceHDR& I)
{
	// On recupere min et max
	double max = tpHDROperations::GetMax(I);
	double min = tpHDROperations::GetMin(I);
	double mean = tpHDROperations::GetMean(I);

	// On applique precalcul les resultats
	double CLwmax = max;
	double CLwmin = min;

	// Les differents filtre que l'on doit calculer
	int small = 3;
	int mv[] = {23,19,15,11,9,7,5,3};
	std::vector<int> v(mv, mv + sizeof(mv) / sizeof(int));
	std::vector<int>::iterator itV = v.begin();
	
	std::cout << "[Info] [tpHDRToneOperatorPhotographicLocal] Creation blur ... " << std::endl;

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

	std::cout << "[Info] [tpHDRToneOperatorPhotographicLocal] Merging ... " << std::endl;
	
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
		vBlur[*itVFinal] = ( CalculDifference(filtrage[*itVFinal], filtrage[2*(*itVFinal) + 1], *itVFinal) );
		Result[*itVFinal] = 0;
		++itVFinal;
	}
	

	std::cout << "[Info] [tpHDRToneOperatorPhotographicLocal] Compute right value ... " << std::endl;
	
	for(unsigned int i = 0; i < I.getHeight(); i++)
	{
		for(unsigned int j = 0; j < I.getWidth(); j++)
		{
			std::vector<int>::iterator it = vFinal.begin();
			double Lwa = (m_a / mean)*(I[i][j] / (1 + (filtrage[small])[i][j]));
			while(it != vFinal.end())
			{
				if((vBlur[*it])[i][j] < m_t)
				{
					// On a trouver notre meilleur approximation
					Lwa = (m_a / mean)*(I[i][j] / (1 + (filtrage[*it])[i][j]));
					Result[*it]++;
					break;
				}

				++it;
			}

			if(it == vFinal.end())
			{
				Result[small]++;
			}

			I[i][j] = Lwa; // tpDisplayManager::Instance()->GetLuminanceMax()
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

tpFilterResultDouble tpHDRToneOperatorPhotographicLocal::CalculDifference(const tpFilterResultDouble& Is1, const tpFilterResultDouble& Is2, float s) const
{

	tpFilterResultDouble res;
	res.resize(Is1.getHeight(), Is1.getWidth());

	#pragma omp parallel for
	for(int i = 0; i < Is1.getHeight(); i++)
	{
		for(int j = 0; j < Is1.getWidth(); j++)
		{
			res[i][j] = (abs(Is1[i][j] - Is2[i][j]) / (pow(2,m_phi)*(m_a/(s*s))+Is1[i][j]));
		}
	}

	return res;
}

void tpHDRToneOperatorPhotographicLocal::SetA(double a)
{
	m_a = a;
}

void tpHDRToneOperatorPhotographicLocal::SetPhi(double phi)
{
	m_phi = phi;
}

void tpHDRToneOperatorPhotographicLocal::SetT(double v)
{
	m_t = v;
}

double tpHDRToneOperatorPhotographicLocal::GetA() const
{
	return m_a;
}

double tpHDRToneOperatorPhotographicLocal::GetPhi() const
{
	return m_phi;
}

double tpHDRToneOperatorPhotographicLocal::GetT() const
{
	return m_t;
}

