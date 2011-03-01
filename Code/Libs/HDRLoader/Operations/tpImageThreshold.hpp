#pragma once

#include "tpImage.hpp"
#include "tpConfig.h"

class tpImageThreshold {
public:
	/**
	* Binarize the input image with a threshold.
	* @param I : The input image.
	* @param threshold : The threshold.
	* @param O : The output image.
	*/
	static  bool threshold(const tpImage<unsigned char> &I, unsigned char threshold, tpImage<unsigned char> &O);
	static  void Cropping(tpImageLuminanceHDR& I, double percentB, double percentW);
};

