#include "StdAfx.h"
#include "tpHDRToneOperatorLog.h"
#include "tpHDROperations.h"
#include <cmath>
#include <math.h>

tpHDRToneOperatorLog::tpHDRToneOperatorLog(float q, float k) :
	m_q(q),
	m_k(k)
{
}

void tpHDRToneOperatorLog::CompressLum(tpImageLuminanceHDR& I)
{
	double max = tpHDROperations::GetMax(I);


	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = log10(1 + m_q*I[i][j]) / log10(1 + m_k*max);
		}
	}
}

void tpHDRToneOperatorLog::SetQ(float v)
{
	m_q = v;
}

void tpHDRToneOperatorLog::SetK(float v)
{
	m_k = v;
}

float tpHDRToneOperatorLog::GetQ()
{
	return m_q;
}

float tpHDRToneOperatorLog::GetK()
{
	return m_k;
}

