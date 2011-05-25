#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpHDRToneOperatorWard.h"
#include "Operations/tpHDROperations.h"
#include "Managers/tpDisplayManager.h"
#include "Managers/tpDynamicToneMappingManager.h"

tpHDRToneOperatorWard::tpHDRToneOperatorWard()
{
	SetDynamic(true);
}

tpHDRToneOperatorWard::~tpHDRToneOperatorWard()
{
}

void tpHDRToneOperatorWard::CompressLum(tpImageLuminanceHDR& I)
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


	double m = (1/ldmax)*std::pow((double)(1.219+ std::pow((float)(ldmax/2.0),(float)0.4)) / (1.219+(std::pow((double)lwa,(double)0.4))), (double)2.5);

	std::cout << "[Info] tpHDRToneOperatorWard => m = " << m << std::endl;

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = std::min(m*I[i][j],1.0);
		}
	}

}


