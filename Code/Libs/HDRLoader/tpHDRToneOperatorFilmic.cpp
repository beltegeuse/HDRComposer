#include "StdAfx.h"
#include "tpHDRToneOperatorFilmic.h"

#include <math.h>
#include <cmath>

tpHDRToneOperatorFilmic::tpHDRToneOperatorFilmic(void)
{
	SetGammaCorrected(true);
}

tpHDRToneOperatorFilmic::~tpHDRToneOperatorFilmic(void)
{
}

void tpHDRToneOperatorFilmic::CompressLum(tpImageLuminanceHDR& I)
{

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = pow((I[i][j]*(6.2*I[i][j]+.5))/(I[i][j]*(6.2*I[i][j]+1.7)+0.06),2.2);
		}
	}
}
