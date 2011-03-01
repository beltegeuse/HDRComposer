#include "StdAfx.h"

#include "tpImageFilter.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

bool tpImageFilter::ApplyFilter(const tpImageGray& I, tpFilterResult& O, const tpFilter& F)
{
	return ApplyFilter<tpImageGray,tpFilterResult>(I,O,F);
}

bool tpImageFilter::ApplyFilter(const tpImageLuminanceHDR& I, tpFilterResultDouble& O, const tpFilter& F)
{
	return ApplyFilter<tpImageLuminanceHDR,tpFilterResultDouble>(I,O,F);
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


