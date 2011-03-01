#pragma once
#include "tpToneOperatorAbstract.h"
#include "tpImage.hpp"

class TP_EXPORT tpHDRToneOperatorLumAbstract : public tpToneOperatorAbstract
{
public:
	// Constructeurs et destructeurs
	tpHDRToneOperatorLumAbstract();
	virtual ~tpHDRToneOperatorLumAbstract(void);

	// Methodes virtuelles pure
	virtual void CompressLum(tpImageLuminanceHDR& I) = 0;
	virtual void Compress(tpImageColorHDR& I);
};
