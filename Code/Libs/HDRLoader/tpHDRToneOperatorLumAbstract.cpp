#include "StdAfx.h"
#include "tpHDRToneOperatorLumAbstract.h"
#include "tpImageConvert.hpp"
#include "tpDynamicToneMappingManager.h"

tpHDRToneOperatorLumAbstract::tpHDRToneOperatorLumAbstract() :
tpToneOperatorAbstract()
{

}

tpHDRToneOperatorLumAbstract::~tpHDRToneOperatorLumAbstract(void)
{
}

void tpHDRToneOperatorLumAbstract::Compress(tpImageColorHDR& I)
{
	// Creation de la luminance
	tpImageLuminanceHDR image;
	tpImageConvert::createLuminanceImage(I, image);
	
	// On calibre la luminance
	if(tpDynamicToneMappingManager::Instance()->isNeedCalibration())
	{
		tpImageConvert::Calibration(image);
	}

	// On compress la luminance
	CompressLum(image);
	
	// Puis on retransforme
	tpImageColorHDR temp;
	tpImageConvert::createColorImageHDR(image, I, temp); // FIXME: Pouvoir changer la saturation
	I.copy(temp);
}
