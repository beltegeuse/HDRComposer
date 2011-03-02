#include "StdAfx.h"

#include "Operations/tpImageFilter.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fftw3.h>

bool tpImageFilter::ApplyFilter(const tpImageGray& I, tpFilterResult& O, const tpFilter& F)
{
	return ApplyFastFilterTemplate<tpImageGray,tpFilterResult>(I,O,F);
}

bool tpImageFilter::ApplyFilter(const tpImageLuminanceHDR& I, tpFilterResultDouble& O, const tpFilter& F)
{
	return ApplyFastFilterTemplate<tpImageLuminanceHDR,tpFilterResultDouble>(I,O,F);
}

bool tpImageFilter::ApplyFastFilter(const tpImageGray& I, tpFilterResult& O, const tpFilter& F)
{
	return ApplyFastFilterTemplate<tpImageGray,tpFilterResult>(I,O,F);
}

bool tpImageFilter::ApplyFastFilter(const tpImageLuminanceHDR& I, tpFilterResultDouble& O, const tpFilter& F)
{
	return ApplyFastFilterTemplate<tpImageLuminanceHDR,tpFilterResultDouble>(I,O,F);
}

template < typename T, typename TRes >
bool tpImageFilter::ApplyFastFilterTemplate(const T& I, TRes& O, const tpFilter& F)
{
	int L = I.getWidth();
	int width = L;
	int M = I.getHeight();
	int height = M;
	const double factor = 1.0/sqrt(height*width);
	O.resize(height, width);

	std::cout << "[INFO] Create complex caches numbers : " << L << "x" << M << std::endl;
	fftw_complex* in = (fftw_complex*)fftw_malloc(sizeof (fftw_complex)*M*L);
	fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof (fftw_complex)*M*L);
	fftw_complex* kernel = (fftw_complex*)fftw_malloc(sizeof (fftw_complex)*M*L);
	fftw_plan p;
	fftw_plan p_inv;

	int w2 = (int)floor(F.getWidth() / 2.0);
	int h2 = (int)floor(F.getHeight() / 2.0);
	int centerX = (int)ceil(M / 2.0);
	int centerY = (int)ceil(L / 2.0);
	std::cout << "[INFO] Filtering size : " << F.getHeight() << "x" << F.getWidth() << std::endl;
	std::cout << "[INFO] half Filtering size : " << h2 << "x" << w2 << std::endl;
	//  Fill fftw_complex for kernel
	for(int x = 0; x < M; x++)
		for(int y = 0; y < L; y++)
		{
			if(((centerX - h2) < x) & ((centerX + h2) >= x) & ((centerY - w2) < y) & ((centerY + w2) >= y))
			{
				int vX = x - (centerX - h2);
				int vY = y - (centerY - w2);
				in[x*L+y][0] = F[vX][vY];
				in[x*L+y][1] = F[vX][vY];
			}
			else
			{
				in[x*L+y][0] = 0;
				in[x*L+y][1] = 0;
			}
		}
	// Create the plan (need by fftw)
	p = fftw_plan_dft_2d(M, L, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	// Apply the transform (kernel)
	fftw_execute(p);
	for(int i = 0; i < M; i++)
		for(int j = 0; j < L; j++)
		{
			kernel[i*L+j][0] = out[i*L+j][0];
			kernel[i*L+j][1] = out[i*L+j][1];
		}
	// Apply transform (image)
	for(int i = 0; i < M; i++)
		for(int j = 0; j < L; j++)
		{
			in[i*L+j][0] = I[i][j];
			in[i*L+j][1] = 0;
		}
	fftw_execute(p);
	// Apply filter
	for(int i = 0; i < M; i++)
		for(int j = 0; j < L; j++)
		{
			out[i*L+j][0] = out[i*L+j][0]*kernel[i*L+j][0];
			out[i*L+j][1] = out[i*L+j][1]*kernel[i*L+j][1];
		}

	// Reverse the transform ...
	p_inv = fftw_plan_dft_2d(M, L, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(p_inv);
	// Copy result
	for(int i = 0; i < centerX; i++)
		for(int j = 0; j < centerY; j++)
		{
			O[i][j] = in[(i+centerX)*width + j+centerY][0]*factor*factor;
			O[i][j+centerY] = in[(i+centerX)*width + j][0]*factor*factor;
			O[i+centerX][j+centerY] = in[(i)*width + j][0]*factor*factor;
			O[i+centerX][j] = in[(i)*width + j + centerY][0]*factor*factor;
		}
	// Free memory
	fftw_destroy_plan(p);
	fftw_destroy_plan(p_inv);
	fftw_free(in);
	fftw_free(out);
	fftw_free(kernel);
}

template < typename T, typename TRes >
bool tpImageFilter::ApplyFilterTemplate(const T& I, TRes& O, const tpFilter& F)
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


