#ifdef WIN32
#include "StdAfx.h"
#endif

#include "tpHDRToneOperatorTumblin.h"
#include "Managers/tpDisplayManager.h"
#include "Operations/tpHDROperations.h"
#include "Managers/tpDynamicToneMappingManager.h"

#include <cmath>
#include <math.h>

tpHDRToneOperatorTumblin::tpHDRToneOperatorTumblin(double scale_factor) :
m_scale_factor(scale_factor)
{
	SetGammaCorrected(true);
	SetDynamic(true);
}

tpHDRToneOperatorTumblin::~tpHDRToneOperatorTumblin(void)
{
}

void tpHDRToneOperatorTumblin::CompressLum(tpImageLuminanceHDR& I)
{
	double Lda = tpDisplayManager::Instance()->GetLuminanceAdaptation();
	double Lwa;
	
	if(isDynamicMode())
	{
		Lwa = tpDynamicToneMappingManager::Instance()->GetLuminanceAdaptation();
	}
	else
	{
		Lwa = tpHDROperations::GetMean(I);
	}
	
	double f = Gamma(Lwa) / Gamma(Lda);

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = Lda*pow(I[i][j] / Lwa, f) / 255.0;
		}
	}
}

double tpHDRToneOperatorTumblin::Gamma(double L)
{
	if(L > 100)
	{
		return 2.655;
	}
	else
	{
		return 1.855 + 0.4*log10(L + 0.0000023);
	}
}

void tpHDRToneOperatorTumblin::SetScaleFactor(double v)
{
	m_scale_factor = v;
}

double tpHDRToneOperatorTumblin::GetScaleFactor() const
{
	return m_scale_factor;
}

