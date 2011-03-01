#include "StdAfx.h"
#include "tpHDRToneOperatorPhotographic.h"
#include "tpHDROperations.h"
#include "tpDynamicToneMappingManager.h"

tpHDRToneOperatorPhotographic::tpHDRToneOperatorPhotographic(double a) :
	m_a(a)
{
	SetDynamic(true);
}

tpHDRToneOperatorPhotographic::~tpHDRToneOperatorPhotographic(void)
{
}

void tpHDRToneOperatorPhotographic::CompressLum(tpImageLuminanceHDR& I)
{
	double mean = tpHDROperations::GetMean(I);

	if(isDynamicMode())
	{
		mean = tpDynamicToneMappingManager::Instance()->GetLuminanceAdaptation();
	}
	else
	{
		mean = tpHDROperations::GetMean(I);
	}

	double factor = m_a / mean;

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = factor*I[i][j];
			I[i][j] = I[i][j] / (I[i][j] + 1);
		}
	}
}

double tpHDRToneOperatorPhotographic::GetA() const
{
	return m_a;
}

void tpHDRToneOperatorPhotographic::SetA(double v)
{
	m_a = v;
}
