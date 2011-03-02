/*
 * tpHDRToneOperatorDurandSlow.cpp
 *
 *  Created on: Mar 1, 2011
 *      Author: Adrien
 */

#include "tpHDRToneOperatorDurandSlow.h"
#include "tpMath.h"

tpHDRToneOperatorDurandSlow::tpHDRToneOperatorDurandSlow(int halfSize, int sig_d, int sig_r) :
	m_half_size(halfSize),
	m_sig_d(sig_d),
	m_sig_r(sig_r)
{
}

tpHDRToneOperatorDurandSlow::~tpHDRToneOperatorDurandSlow()
{
}

void tpHDRToneOperatorDurandSlow::CompressLum(tpImageLuminanceHDR& I)
{
	int w = I.getWidth();
	int h = I.getHeight();

	// Create new image to store the result
	tpImageLuminanceHDR O;
	O.resize(h,w,true);

	// Get Gaussian Kernel
	int taille = m_half_size*2+1;
	// And sigma factor
	tpFilter GaussianFilter = tpMath::GaussianKernel2D(m_sig_d, taille);

    #pragma omp parallel for
	for(int x = 0; x < h; x++)
		for(int y = 0; y < w; y++)
		{
			double k = 0.0;
			double v = I[x][y];
			for(int i = -m_half_size; i <= m_half_size; i++)
				for(int j = -m_half_size; j <= m_half_size; j++)
				{
					// Global coordinates
					int vI = x+i;
					int vJ = y+j;
					// Edge conditions
					if(vI < 0)
						vI = abs(vI);
					if(vI >= h)
						vI = 2*h - (vI+1);
					if(vJ < 0)
						vJ = abs(vJ);
					if(vJ >= w)
						vJ = 2*w - (vJ+1);
					// Compute values
					double diff = v-I[vI][vJ];
					double gaussianIntensity = exp(- (pow((float)diff,2)) / (pow((float)m_sig_r,2)));
					double factor = GaussianFilter[i+m_half_size][j+m_half_size]*gaussianIntensity;
					O[x][y] += factor*I[vI][vJ];
					k += factor;
				}
			O[x][y] /= k;
		}

	// copy result
	for(int x = 0; x < h; x++)
		for(int y = 0; y < w; y++)
		{
			I[x][y] = O[x][y];
		}
}

void tpHDRToneOperatorDurandSlow::SetHalfSize(int halfSize)
{
	m_half_size = halfSize;
}

int tpHDRToneOperatorDurandSlow::GetHalfSize()
{
	return m_half_size;
}

void tpHDRToneOperatorDurandSlow::SetSigD(float v)
{
	m_sig_d = v;
}
float tpHDRToneOperatorDurandSlow::GetSigD()
{
	return m_sig_d;
}
void tpHDRToneOperatorDurandSlow::SetSigR(float v)
{
	m_sig_r = v;
}
float tpHDRToneOperatorDurandSlow::GetSigR()
{
	return m_sig_r;
}
