#pragma once

#include "tpImage.hpp"
#include "tpImageFilter.hpp"
#include <cmath>
#include <math.h>
#include "tpConfig.h"

class TP_EXPORT tpHDROperations
{

public:
	/*
	 * Methodes publiques
	 */
	static double GetMin(const tpImageLuminanceHDR& I);
	static double GetMax(const tpImageLuminanceHDR& I);
	static double GetMean(const tpImageLuminanceHDR& I);

	static float GetMin(const tpFilterResult& I);
	static float GetMax(const tpFilterResult& I);
	static float GetMean(const tpFilterResult& I);

	static double GetMinColor(const tpImageColorHDR& I);
	static double GetMaxColor(const tpImageColorHDR& I);
	static double GetMeanColor(const tpImageColorHDR& I);

	static void PrintInformation(const tpImageColorHDR& I, const std::string& title);
	static void PrintInformation(const tpImageLuminanceHDR& I, const std::string& title);
private:

	/*
	 * Les templates pour les algorithmes
	 */

	template < typename T, class TRes >
	static TRes GetMin(const T& image)
	{
		// FIXME: Faire assertion Empty !
		TRes min = image[0][0]; 
		for(unsigned int i = 0; i < image.getHeight(); i++)
		{
			for(unsigned int j = 0; j < image.getWidth(); j++)
			{
				TRes temp = image[i][j];
				if(min > temp)
				{
					min = temp;
				}
			}
		}

		return min;
	}
	
	template < typename T, class TRes >
	static TRes GetMax(const T& image)
	{
		// FIXME: Faire assertion Empty !
		TRes max = image[0][0]; 
		for(int i = 0; i < image.getHeight(); i++)
		{
			for(int j = 0; j < image.getWidth(); j++)
			{
				TRes temp = image[i][j];
				if(max < temp)
				{
					max = temp;
				}
			}
		}

		return max;
	}

	template < typename T, class TRes >
	static TRes GetMean(const T& image)
	{
		// FIXME: Faire assertion Empty !
		TRes mean = 0; 
		for(int i = 0; i < image.getHeight(); i++)
		{
			for(int j = 0; j < image.getWidth(); j++)
			{
				if(image[i][j] != 0)
					mean += log(image[i][j]);
			}
		}

		mean = (1 / ((float)image.getWidth()*image.getHeight()))*mean;

		return exp(mean);
	}
};

//#include "tpHDROperations.cpp"

