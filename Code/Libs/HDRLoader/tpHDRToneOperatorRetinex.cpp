#include "StdAfx.h"
#include "tpHDRToneOperatorRetinex.h"
#include "tpMath.h"
#include "tpImageFilter.hpp"
#include <cmath>
#include <math.h>
tpHDRToneOperatorRetinex::tpHDRToneOperatorRetinex(double k, double sig) :
	m_k(k),
	m_sig(sig)
{
}

tpHDRToneOperatorRetinex::~tpHDRToneOperatorRetinex(void)
{
}


void tpHDRToneOperatorRetinex::CompressLum(tpImageLuminanceHDR& I)
{
	tpFilterResultDouble Lblur;
	tpFilter kernel = tpMath::GaussianKernel2D((float)m_sig);

	tpImageFilter::ApplyFilter(I, Lblur, kernel);

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = std::min(exp(log(I[i][j]) - m_k*log(Lblur[i][j])),1.0);
		}
	}
}

void tpHDRToneOperatorRetinex::SetK(double v)
{
	m_k = v;
}
void tpHDRToneOperatorRetinex::SetSig(double v)
{
	m_sig = v;
}

double tpHDRToneOperatorRetinex::GetK() const
{
	return m_k;
}

double tpHDRToneOperatorRetinex::GetSig() const
{
	return m_sig;
}
