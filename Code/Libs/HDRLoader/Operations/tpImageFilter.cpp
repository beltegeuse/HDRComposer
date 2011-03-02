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

/* real part of signal
 imaginary part of signal
 real part of spectrum
 imaginary part of spectrum
 row/col dim of image
  1=fwd xform, -1=inverse xform
void fft2d(float *xReal,float *xImag,float *XReal,float *XImag,int height,int    direction)
{
    fftw_complex *pass;            array for passing data to/from fftw
    fftw_plan Plan;                structure for fftw3 planning
    float one_on_n;                1 / (no. data points in signal)
    int i;                         counter
    int n;                         no. data points in signal
    int so2;                       size over 2
    int row,col;                   loop counters

    n = size * size;
    so2 = (size >> 1);
    pass  = fftw_malloc(n*sizeof(fftw_complex));

    if (direction == 1 ) {  forward transform
      Plan = fftw_plan_dft_2d(size,size,pass,pass,FFTW_FORWARD,FFTW_ESTIMATE);

      * Set up the data in the pass array and call fftw3

      for (i=0; i<n; i++) {
        pass[i][0] = xReal[i];
        pass[i][1] = xImag[i];
      }
      fftw_execute(Plan);


      * Center the spectrum returned by fftw3

      for (row=0; row<so2; row++) {
        for (col=0; col<so2; col++) {

          // Quadrant I
          XReal[(row+so2)*size + col+so2] = pass[row*size + col][0];
          XImag[(row+so2)*size + col+so2] = pass[row*size + col][1];

          // Quadrant II
          XReal[(row+so2)*size + col] = pass[row*size + col+so2][0];
          XImag[(row+so2)*size + col] = pass[row*size + col+so2][1];

          // Quadrant III
          XReal[row*size + col] = pass[(row+so2)*size + col+so2][0];
          XImag[row*size + col] = pass[(row+so2)*size + col+so2][1];

          // Quadrant IV
          XReal[row*size + col+so2] = pass[(row+so2)*size + col][0];
          XImag[row*size + col+so2] = pass[(row+so2)*size + col][1];

        }    // for col
      }      // for row
    }        // if (direction == 1)


    else {
      if (direction == -1) {  reverse transform
        Plan = fftw_plan_dft_2d(size,size,pass,pass,FFTW_BACKWARD,FFTW_ESTIMATE);
        one_on_n = (float)1.0 / (float)n;


        * "un" Center the given spectrum for passing to fftw3

        for (row=0; row<so2; row++) {
          for (col=0; col<so2; col++) {

            // Quadrant I
            pass[row*size + col][0] = XReal[(row+so2)*size + col+so2];
            pass[row*size + col][1] = XImag[(row+so2)*size + col+so2];

            // Quadrant II
            pass[row*size + col+so2][0] = XReal[(row+so2)*size + col];
            pass[row*size + col+so2][1] = XImag[(row+so2)*size + col];

            // Quadrant III
            pass[(row+so2)*size + col+so2][0] = XReal[row*size + col];
            pass[(row+so2)*size + col+so2][1] = XImag[row*size + col];

            // Quadrant IV
            pass[(row+so2)*size + col][0] = XReal[row*size + col+so2];
            pass[(row+so2)*size + col][1] = XImag[row*size + col+so2];

          }    // for col
        }      // for row

        fftw_execute(Plan);


        * Copy data back out of pass array and scale

        for (i=0; i<n; i++) {
          xReal[i] = pass[i][0] * one_on_n;
          xImag[i] = pass[i][1] * one_on_n;
        }
      }    // else

      else {
        printf("\nERROR: fft2d: unknown value %d specified for direction.\n",
               direction);
        exit(-1);
      }
    }
    fftw_destroy_plan(Plan);
    fftw_free(pass);
    return;
}*/

template < typename T, typename TRes >
bool tpImageFilter::ApplyFastFilter(const T& I, TRes& O, const tpFilter& F)
{
	int L = I.getWidth();
	int width = L;
	int M = I.getHeight();
	int height = M;

	O.resize(height, width);

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
	//Refocus
	for (int j = 0; j <height; j++)
		for (int i = 0; i <width; i++)
		{
			int x = i;
			int y = j;
			if (i <width / 2 && j <height / 2)
			{
				x = i + width / 2;
				y = j + height / 2;
			}
			if (i >= width / 2 && j < height / 2)
			{
				x = i - width / 2;
				y = j + height / 2;
			}
			if (i < width /2 && j>= height / 2)
			{
				x = i + width / 2;
				y = j - height / 2;
			}
			if (i>= width / 2 && j >= height / 2)
			{
				x = i-width / 2;
				y = j-height / 2;
			}
			in [y * width + x][0] = out[j * width + i][0];
			in [y * width + x][1] = out[j * width + i][1];
		}
	// Apply filter
	int w2 = (int)floor(F.getWidth() / 2.0);
	int h2 = (int)floor(F.getHeight() / 2.0);
	int centerX = (int)ceil(M / 2.0);
	int centerY = (int)ceil(M / 2.0);
	std::cout << "[INFO] Filtering size : " << F.getHeight() << "x" << F.getWidth() << std::endl;
	std::cout << "[INFO] half Filtering size : " << h2 << "x" << w2 << std::endl;
	for(int x = 0; x < M; x++)
		for(int y = 0; y < L; y++)
		{
			if(((centerX - h2) < x) & ((centerX + h2) >= x) & ((centerY - w2) < y) & ((centerY + w2) >= y))
			{
				int vX = x - (centerX - h2);
				int vY = y - (centerY - w2);
				in[x*L+y][0] = F[vX][vY]*in[x*L+y][0];
				in[x*L+y][1] = F[vX][vY]*in[x*L+y][1];
			}
			else
			{
				in[x*L+y][0] = 0;
				in[x*L+y][1] = 0;
			}
		}
	// Reverse the transform ...
	p_inv = fftw_plan_dft_2d(M, L, out, in, FFTW_BACKWARD, FFTW_ESTIMATE);
	for (int j = 0; j <height; j++)
			for (int i = 0; i <width; i++)
			{
				int x = i;
				int y = j;
				if (i <width / 2 && j <height / 2)
				{
					x = i + width / 2;
					y = j + height / 2;
				}
				if (i >= width / 2 && j < height / 2)
				{
					x = i - width / 2;
					y = j + height / 2;
				}
				if (i < width /2 && j>= height / 2)
				{
					x = i + width / 2;
					y = j - height / 2;
				}
				if (i>= width / 2 && j >= height / 2)
				{
					x = i-width / 2;
					y = j-height / 2;
				}
				out [y * width + x][0] = in[j * width + i][0];
				out [y * width + x][1] = in[j * width + i][1];
			}
	fftw_execute(p_inv);
	// Copy result
	for(int i = 0; i < M; i++)
		for(int j = 0; j < L; j++)
			O[i][j] = in[i*L+j][0] / sqrt(height*width);
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


