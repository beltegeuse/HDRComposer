#include "StdAfx.h"
#include "tpHDRToneOperatorPhotographicBurn.h"
#include "Operations/tpHDROperations.h"

tpHDRToneOperatorPhotographicBurn::tpHDRToneOperatorPhotographicBurn(double a, double burn) :
	m_a(a),
	m_burn(burn)
{
}

tpHDRToneOperatorPhotographicBurn::~tpHDRToneOperatorPhotographicBurn(void)
{
}

void tpHDRToneOperatorPhotographicBurn::CompressLum(tpImageLuminanceHDR& I)
{
	double mean = tpHDROperations::GetMean(I);
	double factor = m_a / mean;

	#pragma omp parallel for
	for(int i = 0; i < I.getHeight(); i++)
	{
		for(int j = 0; j < I.getWidth(); j++)
		{
			I[i][j] = factor*I[i][j];
			I[i][j] = (I[i][j]*(1+(I[i][j] / (m_burn*m_burn)))) / (I[i][j] + 1);
		}
	}
}


void tpHDRToneOperatorPhotographicBurn::SetA(double a)
{
	m_a = a;
}

void tpHDRToneOperatorPhotographicBurn::SetBurn(double v)
{
	m_burn = v;
}

double tpHDRToneOperatorPhotographicBurn::GetA() const
{
	return m_a;
}

double tpHDRToneOperatorPhotographicBurn::GetBurn() const
{
	return m_burn;
}
