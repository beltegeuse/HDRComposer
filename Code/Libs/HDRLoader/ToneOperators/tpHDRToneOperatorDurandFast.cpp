/*
 * tpHDRToneOperatorDurandSlow.cpp
 *
 *  Created on: Mar 1, 2011
 *      Author: Adrien
 */

#include "tpHDRToneOperatorDurandFast.h"
#include "tpMath.h"
#include "Operations/tpHDROperations.h"
tpHDRToneOperatorDurandFast::tpHDRToneOperatorDurandFast()
{
}

tpHDRToneOperatorDurandFast::~tpHDRToneOperatorDurandFast()
{
}

void tpHDRToneOperatorDurandFast::CompressLum(tpImageLuminanceHDR& I)
{
	int w = I.getWidth();
	int h = I.getHeight();

	tpFilter f = tpMath::GaussianKernel2D(5.0f);

	// Create new image to store the result
	tpImageLuminanceHDR J;
	J.resize(h,w,true);
	tpImageLuminanceHDR G;
	G.resize(h,w,true);
	tpImageLuminanceHDR H;
	H.resize(h,w,true);

	tpFilterResultDouble K;
	tpFilterResultDouble Hstar;
	// number of segments
	int nbSegments = 10;
	double intensityFactor = 0.1;

	double minI = tpHDROperations::GetMin(I);
	double maxI = tpHDROperations::GetMax(I);
	double dynamic = maxI - minI;

	for(int j = 0; j < nbSegments; j++)
	{
		double i_j = minI + j*dynamic/((float)nbSegments);
		for(int x = 0; x < h; x++)
			for(int y = 0; y < w; y++)
				G[x][y] = intensityFactor*(I[x][y]-i_j);
		tpImageFilter::ApplyFastFilter(G,K,f);
		for(int x = 0; x < h; x++)
			for(int y = 0; y < w; y++)
				H[x][y] = G[x][y]*I[x][y];
		tpImageFilter::ApplyFastFilter(H,Hstar,f);
		for(int x = 0; x < h; x++)
			for(int y = 0; y < w; y++)
				J[x][y] = J[x][y]+Hstar[x][y]/K[x][y];


	}

	// copy result
	for(int x = 0; x < h; x++)
		for(int y = 0; y < w; y++)
		{
			I[x][y] = J[x][y];
		}
}
