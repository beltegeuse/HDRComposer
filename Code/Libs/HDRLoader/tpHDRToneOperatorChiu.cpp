#include "StdAfx.h"
#include "tpHDRToneOperatorChiu.h"
#include "tpMath.h"
#include "tpImageFilter.hpp"

tpHDRToneOperatorChiu::tpHDRToneOperatorChiu(float k, float sig) :
	m_k(k),
	m_sig(sig)
{
}

tpHDRToneOperatorChiu::~tpHDRToneOperatorChiu(void)
{
}

void tpHDRToneOperatorChiu::CompressLum(tpImageLuminanceHDR& I)
{
	tpFilterResultDouble Lblur;
	tpFilter kernel = tpMath::GaussianKernel2D((float)m_sig);

	tpImageFilter::ApplyFilter(I, Lblur, kernel);

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = std::min(I[i][j] / (m_k*Lblur[i][j]),1.0);
		}
	}
}

float tpHDRToneOperatorChiu::GetSig() const
{
	return m_sig;
}

float tpHDRToneOperatorChiu::GetK() const
{
	return m_k;
}

void tpHDRToneOperatorChiu::SetSig(float v)
{
	m_sig = v;
}

void tpHDRToneOperatorChiu::SetK(float v)
{
	m_k = v;
}
