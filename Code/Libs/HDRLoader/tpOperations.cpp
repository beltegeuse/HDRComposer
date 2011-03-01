#include "StdAfx.h"
#include "tpOperations.h"

#include "tpImageConvert.hpp"
#include "tpDisplayManager.h"

#include <vector>
#include <algorithm>

#include <cmath>
#include <math.h>

double tpOperations::ValueOfPercent(const tpImageLuminanceHDR& I, double vPercent)
{
	Assert(vPercent >= 0 && vPercent <= 1);

	int taille = I.getWidth()*I.getHeight();

	// ==== On copie l'image dans un vecteur
	std::vector<double> v(taille);
	v.assign(I._bitmap,I._bitmap+taille);

	// ==== On trie le vecteur
	std::sort(v.begin(),v.end());

	// ==== Calcul des indices
	int iB = (int)(vPercent*taille);	

	return v[iB];
}

void tpOperations::Distance(const tpImageGray& I1, const tpImageGray& I2, tpImageGray& res)
{
	DistanceTemplate(I1,I2,res);
}

void tpOperations::Distance(const tpImageLuminanceHDR& I1, const tpImageLuminanceHDR& I2, tpImageLuminanceHDR& res)
{
	DistanceTemplate(I1,I2,res);
}

void tpOperations::Distance(const tpImageColor& I1, const tpImageColor& I2, tpImageColor& res)
{
	DistanceTemplateColor<tpImageColor, tpImageGray>(I1,I2,res);
}

void tpOperations::Distance(const tpImageColorHDR& I1, const tpImageColorHDR& I2, tpImageColorHDR& res)
{
	DistanceTemplateColor<tpImageColorHDR, tpImageLuminanceHDR>(I1,I2,res);
}

template < typename T >
void tpOperations::DistanceTemplate(const T& I1, const T& I2, T& res)
{
	Assert(I1.getWidth() == I2.getWidth() && I1.getHeight() == I2.getHeight());

	res.resize(I1.getHeight(), I1.getWidth());

	#pragma omp parallel for
	for(int i = 0; i < I1.getHeight(); i++)
	{
		for(int j = 0; j < I1.getWidth(); j++)
		{
			if(I1[i][j] > I2[i][j])
				res[i][j] = I1[i][j] - I2[i][j];
			else
				res[i][j] = I2[i][j] - I1[i][j];
		}
	}
}

template < class T, class TRes >
void tpOperations::DistanceTemplateColor(const T& I1, const T& I2, T& res)
{
	TRes cR1,cG1,cB1;
	TRes cR2,cG2,cB2;
	TRes cR,cG,cB;

	res.resize(I1.getHeight(), I1.getWidth());

	tpImageConvert::CopyChannel(I1, cR1, tpImageConvert::R);
	tpImageConvert::CopyChannel(I1, cG1, tpImageConvert::G);
	tpImageConvert::CopyChannel(I1, cB1, tpImageConvert::B);

	tpImageConvert::CopyChannel(I2, cR2, tpImageConvert::R);
	tpImageConvert::CopyChannel(I2, cG2, tpImageConvert::G);
	tpImageConvert::CopyChannel(I2, cB2, tpImageConvert::B);

	Distance(cR1, cR2, cR);
	Distance(cG1, cG2, cG);
	Distance(cB1, cB2, cB);

	tpImageConvert::ParseChannel(cR, res, tpImageConvert::R);
	tpImageConvert::ParseChannel(cG, res, tpImageConvert::G);
	tpImageConvert::ParseChannel(cB, res, tpImageConvert::B);
}

template < class T >
bool tpOperations::isAllBlackTemplate(const T& I)
{

	for(unsigned int i = 0; i < I.getHeight(); i++)
	{
		for(unsigned int j = 0; j < I.getWidth(); j++)
		{
			if(I[i][j].r != 0 || I[i][j].g != 0 || I[i][j].b != 0)
			{
				std::cout << "[Info] [isAllBlackTemplate] Non black pixel : " << i << "x" << j << std::endl;
				return false;
			}
		}
	}

	return true;
}

template < class T >
bool tpOperations::isBlackTemplate(const T& I)
{
	for(unsigned int i = 0; i < I.getHeight(); i++)
	{
		for(unsigned int j = 0; j < I.getWidth(); j++)
		{
			if(I[i][j] != 0)
			{
				std::cout << "[Info] [isAllBlackTemplate] Non black pixel : " << i << "x" << j << std::endl;
				return false;
			}
		}
	}

	return true;
}

bool tpOperations::isAllBlack(const tpImageColor& I)
{
	return isAllBlackTemplate<tpImageColor>(I);
}

bool tpOperations::isAllBlack(const tpImageColorHDR& I)
{
	return isAllBlackTemplate<tpImageColorHDR>(I);
}

bool tpOperations::isAllBlack(const tpImageLuminanceHDR& I)
{
	return isBlackTemplate<tpImageLuminanceHDR>(I);
}

bool tpOperations::isAllBlack(const tpImageGray& I)
{
	return isBlackTemplate<tpImageGray>(I);
}

void tpOperations::CorrectGamma(tpImageColor& I)
{
	int w = I.getWidth();
	int h = I.getHeight();

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			I[x][y].r = (unsigned char)(pow(I[x][y].r/255.0,tpDisplayManager::Instance()->GetGammaCorrection())*255);
			I[x][y].g = (unsigned char)(pow(I[x][y].g/255.0,tpDisplayManager::Instance()->GetGammaCorrection())*255);
			I[x][y].b = (unsigned char)(pow(I[x][y].b/255.0,tpDisplayManager::Instance()->GetGammaCorrection())*255);
		}
	}
}


