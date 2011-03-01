#pragma once

#include "tpImage.hpp"
#include "Operations/tpImageFilter.hpp"

class tpMath
{
public:
	static  tpFilter GaussianKernel2D(float sig, int taille);
	static  tpFilter GaussianKernel2D(float sig);
	static  tpFilter GaussianKernel2D(int taille);

	static tpFilter ConstantKernel2D(int taille);
};
