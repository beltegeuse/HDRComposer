#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorLinear : public tpHDRToneOperatorLumAbstract
{
public:
	virtual void CompressLum(tpImageLuminanceHDR& I);
};
