#ifdef WIN32
#include "StdAfx.h"
#endif
#include "Operations/tpOperatorCropping.h"

#include <vector>
#include <algorithm>

tpOperatorCropping::tpOperatorCropping(double percentB, double percentW) :
	m_b(percentB),
	m_w(percentW)
{
	Assert(percentB <= 1 && percentB >= 0);
	Assert(percentW <= 1 && percentW >= 0);
}

tpOperatorCropping::~tpOperatorCropping()
{
}

void tpOperatorCropping::Cropping(tpImageLuminanceHDR& I)
{
	int taille = I.getWidth()*I.getHeight();

	// ==== On copie l'image dans un vecteur
	std::vector<double> v(taille);
	v.assign(I._bitmap,I._bitmap+taille);

	// ==== On trie le vecteur
	std::sort(v.begin(),v.end());

	// ==== Calcul des indices
	int iB = (int)(m_b*taille);	
	int iW = taille - (int)(m_w*taille);

	// ==== On recupere les valeurs seuil
	double Vb = v[iB]; 
	double Vw = v[iW];

	// ==== On croppe :p
	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = std::min(std::max(Vb,I[i][j]),Vw);
		}
	}
}
