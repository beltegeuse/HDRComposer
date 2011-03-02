#include "StdAfx.h"

#include "Operations/tpImageFilter.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fftw3.h>

bool tpImageFilter::ApplyFilter(const tpImageGray& I, tpFilterResult& O, const tpFilter& F)
{
	return ApplyFilter<tpImageGray,tpFilterResult>(I,O,F);
}

bool tpImageFilter::ApplyFilter(const tpImageLuminanceHDR& I, tpFilterResultDouble& O, const tpFilter& F)
{
	return ApplyFilter<tpImageLuminanceHDR,tpFilterResultDouble>(I,O,F);
}

bool tpImageFilter::ApplyFastFilter(const tpImageGray& I, tpFilterResult& O, const tpFilter& F)
{
	return ApplyFastFilter<tpImageGray,tpFilterResult>(I,O,F);
}

bool tpImageFilter::ApplyFastFilter(const tpImageLuminanceHDR& I, tpFilterResultDouble& O, const tpFilter& F)
{
	return ApplyFastFilter<tpImageLuminanceHDR,tpFilterResultDouble>(I,O,F);
}


template < typename T, typename TRes >
bool tpImageFilter::ApplyFastFilter(const T& I, TRes& O, const tpFilter& F)
{
	int L = I.getWidth();
	int M = I.getHeight();
	std::cout << "[INFO] Create complex caches numbers : " << L << "x" << M << std::endl;
	fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof (fftw_complex)*M*L);
	fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof (fftw_complex)*M*L);
	fftw_plan p;
	fftw_plan p_inv;
	//  Fill fftw_complex
	for(int i = 0; i < M; i++)
		for(int j = 0; j < L; j++)
		{
			in[i*L+j][0] = I[i][j];
			in[i*L+j][1] = 0;
		}
	// Create the plan (need by fftw)
	p = fftw_plan_dft_2d(M, L, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	// Apply the transform
	fftw_execute(p);
	// Apply filter
	int w2 = (int)floor(F.getWidth() / 2.0);
	int h2 = (int)floor(F.getHeight() / 2.0);
	int centerX = (int)ceil(M / 2.0);
	int centerY = (int)ceil(M / 2.0);
	for(int x = 0; x < M; x++)
			for(int y = 0; y < L; y++)
			{
				if(((centerX - h2) < x) & ((centerX + h2) >= x) & ((centerY - w2) < y) & ((centerY + w2) >= y))
				{
					int vX = x - (centerX - h2);
					int vY = y - (centerY - w2);
					in[x*L+y][0] = F[vX][vY]*out[x*L+y][0];
					in[x*L+y][1] = F[vX][vY]*out[x*L+y][1];
				}
				else
				{
					in[x*L+y][0] = 0;
					in[x*L+y][1] = 0;
				}
			}
	// Reverse the transform ...
	p_inv = fftw_plan_dft_2d(M, L, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(p_inv);
	// Copy result
	for(int i = 0; i < M; i++)
		for(int j = 0; j < L; j++)
			O[i][j] = in[i*L+j][0];
	// Free memory
	fftw_destroy_plan(p);
	fftw_destroy_plan(p_inv);
	fftw_free(in);
	fftw_free(out);
}

template < typename T, typename TRes >
bool tpImageFilter::ApplyFilter(const T& I, TRes& O, const tpFilter& F)
{
	int w = I.getWidth();
	int h = I.getHeight();

	std::cout << "To => " << w << "x" << h << std::endl;

	// Offset filter
	unsigned int w2 = (unsigned int)ceil(F.getWidth() / 2.0);
	unsigned int h2 = (unsigned int)ceil(F.getHeight() / 2.0);

	std::cout << "Demi-Size : " << h2 << "x" << w2 << std::endl;

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [ApplyFilter] Resize ... " << std::endl;
		O.resize(h,w);
	}

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			ApplyFilterPixel<T,TRes>(I, O, F, x, y, h2, w2);
		}
	}

	return true;
}

template < typename T, typename TRes >
void tpImageFilter::ApplyFilterPixel(const T& I,
									TRes& O,
									const tpFilter& F,
									const int h,const int w,
									const int h2,const int w2)
{

	double s = 0.0;

	for(int x = -h2; x < ((int)F.getHeight())-h2; x++)
	{
		for(int y = -w2; y < ((int)F.getWidth())-w2; y++)
		{
			int a = h+x;
			int b = w+y;

			ComputeRightCoord(a,b,I.getHeight(),I.getWidth());

			s += I[a][b]*F[x+h2][y+w2];
		}
	}

	O[h][w] = s;
}


void tpImageFilter::ComputeRightCoord(int& x, int& y, const int h, const int w)
{
	// Traitement sur X
	if(x < 0)
	{
		x = abs((int)x);
	}
	else if(x >= h)
	{
		x =  2*h - x - 1;
	}

	// Traitement sur Y
	if(y < 0)
	{
		y = abs((int)y);
	}
	else if(y >= w)
	{
		y =  2*w - y - 1;
	}
}

std::ostream& operator<<(std::ostream& out, const tpFilter v)
{
	for(unsigned int w = 0; w < v.getWidth(); w++)
	{
		out << "| ";
		for(unsigned int h = 0; h < v.getHeight(); h++)
		{
			out << v[h][w] << " ";
		}
		out << "|\n";
	}
	return out;
}

tpFilter tpImageFilter::CreateFilter(unsigned int h, unsigned int w, float* values, double factNorm)
{
	tpFilter res;
	res.resize(h,w);

	std::cout << "Creation d'un filtre : " << w << "x" << h << std::endl;

	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			std::cout << values[x+y*h] << "*" << factNorm << "=" << values[x*w+y]*factNorm << std::endl;
			res[x][y] = values[x+y*h]*factNorm;
		}
	}
	return res;
}


