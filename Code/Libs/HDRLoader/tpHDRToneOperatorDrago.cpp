#include "StdAfx.h"
#include "tpHDRToneOperatorDrago.h"
#include "tpHDROperations.h"
#include "tpDisplayManager.h"
#include "tpDynamicToneMappingManager.h"

#include <cmath>
#include <math.h>

tpHDRToneOperatorDrago::tpHDRToneOperatorDrago(float p) :
	m_p(p)
{
	SetDynamic(false);
}

tpHDRToneOperatorDrago::~tpHDRToneOperatorDrago()
{
}

void tpHDRToneOperatorDrago::CompressLum(tpImageLuminanceHDR& I)
{
	double lwa = tpHDROperations::GetMean(I);
	
	if(isDynamicMode())
	{
		lwa = tpDynamicToneMappingManager::Instance()->GetLuminanceAdaptation();
	}
	else
	{
		lwa = tpHDROperations::GetMean(I);
	}

	double lwmax = tpHDROperations::GetMax(I);
	float ldmax = tpDisplayManager::Instance()->GetLuminanceMax();
	float lda = tpDisplayManager::Instance()->GetLuminanceAdaptation();

	double f = 1 / log10(1 + lwmax); 

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = f*( (log10(1 + I[i][j]) / log10( 2+8*std::pow( I[i][j] / lwmax, log10(m_p) / log10(0.5) ) )));
		}
	}
}

void tpHDRToneOperatorDrago::SetP(float v)
{
	m_p = v;
}

float tpHDRToneOperatorDrago::GetP()
{
	return m_p;
}
