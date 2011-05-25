#ifdef WIN32
#include "StdAfx.h"
#endif
#include "Operations/tpHDROperations.h"
#include "Operations/tpImageConvert.hpp"

TP_EXPORT double tpHDROperations::GetMin(const tpImageLuminanceHDR& I)
{
	return GetMin<tpImageLuminanceHDR,double>(I);
}

TP_EXPORT double tpHDROperations::GetMax(const tpImageLuminanceHDR& I)
{
	return GetMax<tpImageLuminanceHDR,double>(I);
}

TP_EXPORT double tpHDROperations::GetMean(const tpImageLuminanceHDR& I)
{
	return GetMean<tpImageLuminanceHDR,double>(I);
}

float tpHDROperations::GetMin(const tpFilterResult& I)
{
	return GetMin<tpFilterResult, float>(I);
}

float tpHDROperations::GetMax(const tpFilterResult& I)
{
	return GetMax<tpFilterResult, float>(I);
}
float tpHDROperations::GetMean(const tpFilterResult& I)
{
	return GetMean<tpFilterResult, float>(I);
}

double tpHDROperations::GetMinColor(const tpImageColorHDR& I)
{
	tpImageLuminanceHDR cR, cG, cB;

	tpImageConvert::CopyChannel(I, cR, tpImageConvert::R);
	tpImageConvert::CopyChannel(I, cG, tpImageConvert::G);
	tpImageConvert::CopyChannel(I, cB, tpImageConvert::B);

	double r, g, b, res;
	r = GetMin(cR);
	g = GetMin(cG);
	b = GetMin(cB);
	res = std::min(std::min(r,g),b);

	std::cout << "[Debug] [GetMinColor] (" << r << ";" << g << ";" << b << ") => " << res << std::endl;  

	return res;
}

double tpHDROperations::GetMaxColor(const tpImageColorHDR& I)
{
	tpImageLuminanceHDR cR, cG, cB;

	tpImageConvert::CopyChannel(I, cR, tpImageConvert::R);
	tpImageConvert::CopyChannel(I, cG, tpImageConvert::G);
	tpImageConvert::CopyChannel(I, cB, tpImageConvert::B);

	double r, g, b, res;
	r = GetMax(cR);
	g = GetMax(cG);
	b = GetMax(cB);
	res = std::max(std::max(r,g),b);

	std::cout << "[Debug] [GetMaxColor] (" << r << ";" << g << ";" << b << ") => " << res << std::endl;  

	return res;
}

double tpHDROperations::GetMeanColor(const tpImageColorHDR& I)
{
	tpImageLuminanceHDR cR, cG, cB;

	tpImageConvert::CopyChannel(I, cR, tpImageConvert::R);
	tpImageConvert::CopyChannel(I, cG, tpImageConvert::G);
	tpImageConvert::CopyChannel(I, cB, tpImageConvert::B);

	return (GetMean(cR) + GetMean(cG) + GetMean(cB)) / 3.0;
}

void tpHDROperations::PrintInformation(const tpImageColorHDR& I, const std::string& title)
{
	std::cout << " ***** Information ***** " << std::endl;
	std::cout << "  - Description : " << title << std::endl;
	std::cout << "  - Range : [" << GetMinColor(I) << ";" << GetMaxColor(I) << "]" << std::endl;
	std::cout << "  - Mean : " << GetMeanColor(I) << std::endl;
}

void tpHDROperations::PrintInformation(const tpImageLuminanceHDR& I, const std::string& title)
{
	std::cout << " ***** Information ***** " << std::endl;
	std::cout << "  - Description : " << title << std::endl;
	std::cout << "  - Range : [" << GetMin(I) << ";" << GetMax(I) << "]" << std::endl;
	std::cout << "  - Mean : " << GetMean(I) << std::endl;
}

