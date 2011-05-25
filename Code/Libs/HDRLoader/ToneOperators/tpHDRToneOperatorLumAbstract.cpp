#ifdef WIN32
#include "StdAfx.h"
#endif
#include "tpHDRToneOperatorLumAbstract.h"
#include "Operations/tpImageConvert.hpp"
#include "Managers/tpDynamicToneMappingManager.h"

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
