#include "StdAfx.h"

#include "tpHDRToneOperatorExp.h"
#include "Operations/tpHDROperations.h"
#include "Managers/tpDynamicToneMappingManager.h"

#include <cmath>
#include <math.h>

tpHDRToneOperatorExp::tpHDRToneOperatorExp(float q, float k) :
	m_q(q),
	m_k(k)
{
	SetDynamic(true);
}


void tpHDRToneOperatorExp::CompressLum(tpImageLuminanceHDR& I)
{
	double mean;
	
	if(isDynamicMode())
	{
		mean = tpDynamicToneMappingManager::Instance()->GetLuminanceAdaptation();
	}
	else
	{
		mean = tpHDROperations::GetMean(I);
	}

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = 1 - exp(- (I[i][j] / (mean + I[i][j])));
		}
	}
}

void tpHDRToneOperatorExp::SetQ(float v)
{
	m_q = v;
}

void tpHDRToneOperatorExp::SetK(float v)
{
	m_k = v;
}

float tpHDRToneOperatorExp::GetQ()
{
	return m_q;
}

float tpHDRToneOperatorExp::GetK()
{
	return m_k;
}

