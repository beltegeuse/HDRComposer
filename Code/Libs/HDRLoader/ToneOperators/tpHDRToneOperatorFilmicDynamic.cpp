#include "StdAfx.h"
#include "tpHDRToneOperatorFilmicDynamic.h"
#include "Operations/tpHDROperations.h"
#include "Managers/tpDynamicToneMappingManager.h"

#include <cmath>
#include <math.h>

tpHDRToneOperatorFilmicDynamic::tpHDRToneOperatorFilmicDynamic(double a) :
	m_a(a)
{
	SetDynamic(true);
}

tpHDRToneOperatorFilmicDynamic::~tpHDRToneOperatorFilmicDynamic(void)
{
}


void tpHDRToneOperatorFilmicDynamic::CompressLum(tpImageLuminanceHDR& I)
{

	//double La = tpHDROperations::GetMean(I);
	double LaD = 0.0;
	if(isDynamicMode())
	{
		LaD = tpDynamicToneMappingManager::Instance()->GetLuminanceAdaptation();
	}
	else
	{
		LaD = tpHDROperations::GetMean(I);
	}

	//double factor = La / LaD;

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			//I[i][j] = factor*I[i][j];
			//sqrt(x)
			//(x / 3)
			//log(1+x)
			I[i][j] = pow((I[i][j]*(6.2*I[i][j]+.5))/(I[i][j]*(6.2*I[i][j]+1.7)+log(1+LaD)),2.2);
		}
	}
}
