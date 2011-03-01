#include "StdAfx.h"
#include "tpHDRToneOperatorLinear.h"
#include "tpHDROperations.h"
#include <cmath>
#include <math.h>

void tpHDRToneOperatorLinear::CompressLum(tpImageLuminanceHDR& I)
{
	double max = tpHDROperations::GetMax(I);

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = I[i][j] / max;
		}
	}
}
