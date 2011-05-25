#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpHDRToneOperatorSigmoid.h"
#include "Operations/tpHDROperations.h"
#include "Managers/tpDynamicToneMappingManager.h"

tpHDRToneOperatorSigmoid::tpHDRToneOperatorSigmoid()
{
	SetDynamic(true);
}

tpHDRToneOperatorSigmoid::~tpHDRToneOperatorSigmoid()
{
}

void tpHDRToneOperatorSigmoid::CompressLum(tpImageLuminanceHDR& I)
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
			I[i][j] = pow(I[i][j] / (mean + I[i][j]),2.2);
		}
	}
}
