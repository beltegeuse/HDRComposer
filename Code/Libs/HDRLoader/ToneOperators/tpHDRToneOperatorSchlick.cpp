#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpHDRToneOperatorSchlick.h"
#include "Operations/tpHDROperations.h"

tpHDRToneOperatorSchlick::tpHDRToneOperatorSchlick(double phi , double k) :
	m_phi(phi),
	m_k(k)
{
}

tpHDRToneOperatorSchlick::~tpHDRToneOperatorSchlick(void)
{
}

void tpHDRToneOperatorSchlick::CompressLum(tpImageLuminanceHDR& I)
{
	double min = tpHDROperations::GetMin(I);
	double max = tpHDROperations::GetMax(I);

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			double p = std::max(std::min((m_phi / 256.0)* (max / min)*(1 + m_k + m_k*(I[i][j] / sqrt(min*max))),1.0),0.0);
			I[i][j] = std::max(std::min((p*I[i][j]) / ((1-p)*I[i][j] + max),1.0),0.0);
		}
	}
}

void tpHDRToneOperatorSchlick::SetK(double k)
{
	m_k = k;
}

void tpHDRToneOperatorSchlick::SetPhi(double v)
{
	m_phi = v;
}

double tpHDRToneOperatorSchlick::GetK() const
{
	return m_k;
}

double tpHDRToneOperatorSchlick::GetPhi() const
{
	return m_phi;
}

