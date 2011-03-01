#pragma once

#include "tpImage.hpp"

class tpOperations
{

public:
	/*
	 * Methodes de distances
	 */
	static  void Distance(const tpImageGray& I1, const tpImageGray& I2, tpImageGray& res);
	static  void Distance(const tpImageLuminanceHDR& I1, const tpImageLuminanceHDR& I2, tpImageLuminanceHDR& res);
	static  void Distance(const tpImageColor& I1, const tpImageColor& I2, tpImageColor& res);
	static  void Distance(const tpImageColorHDR& I1, const tpImageColorHDR& I2, tpImageColorHDR& res);

	/*
	 * Methodes de tests
	 */
	static  bool isAllBlack(const tpImageColor& I);
	static  bool isAllBlack(const tpImageColorHDR& I);
	static bool isAllBlack(const tpImageLuminanceHDR& I);
	static bool isAllBlack(const tpImageGray& I);

	/*
	 * Crop
	 */
	static  double ValueOfPercent(const tpImageLuminanceHDR& I, double v);

	/*
	 * Autres
	 */
	static void CorrectGamma(tpImageColor& I);

public:
	/*
	 * Operations sur les images
	 */

	template < typename T >
	static  void Resize(const T& I, T& O, unsigned int x0, unsigned int y0, unsigned int width, unsigned int height)
	{
		unsigned int w = std::min(x0+width,I.getWidth());
		unsigned int h = std::min(y0+height,I.getHeight());
		
		O.resize(width,height,true);

		#pragma omp parallel for
		for(int i = 0; i < h - y0; i++)
		{
			for(int j = 0; j < w - x0; j++)
			{
				O[i][j] = I[i][j];
			}
		}
	}

	template < typename T >
	static  void Mult(T& I, double factor)
	{
		#pragma omp parallel for
		for(int i = 0; i < I.getHeight(); i++)
		{
			for(int j = 0; j < I.getWidth(); j++)
			{
				I[i][j] = I[i][j] * factor;
			}
		}
	}

	template < typename T >
	static T Difference(T& I1, T& I2)
	{
		//TODO:Verif
		T I = I1;
#pragma omp parallel for
		for(int i = 0; i < I.getHeight(); i++)
		{
			for(int j = 0; j < I.getWidth(); j++)
			{
				I[i][j] = abs(I1[i][j] - I2[i][j]);
			}
		}
		return I;
	}

	template < typename T >
	static void FlipHorizontal(T& I)
	{
		if(I.getHeight() < 2)
		{
			return;
		}

		T temp;
		temp.copy(I);

		int h = I.getHeight() - 1;
		#pragma omp parallel for
		for(int i = 0; i < I.getHeight(); i++)
		{
			for(int j = 0; j < I.getWidth(); j++)
			{
				I[i][j] = temp[h-i][j];
			}
		}
	}

	template < typename T >
	static void FlipVertical(T& I)
	{
		if(I.getWidth() < 2)
		{
			return;
		}

		T temp;
		temp.copy(I);

		int w = I.getWidth() - 1;
		//#pragma omp parallel for
		for(int i = 0; i < I.getHeight(); i++)
		{
			for(int j = 0; j < I.getWidth(); j++)
			{
				I[i][j] = temp[i][w-j];
			}
		}
	}

private:
	template < typename T >
	static  void DistanceTemplate(const T& I1, const T& I2, T& res);

	template < class T, class TRes >
	static  void DistanceTemplateColor(const T& I1, const T& I2, T& res);

	template <class T >
	static  bool isAllBlackTemplate(const T& I);

	template<class T>
	static bool isBlackTemplate(const T& I);
};
