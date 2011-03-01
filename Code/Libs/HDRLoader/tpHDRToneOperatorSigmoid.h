#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorSigmoid : public tpHDRToneOperatorLumAbstract
{
public:
	tpHDRToneOperatorSigmoid();
	~tpHDRToneOperatorSigmoid();

	virtual void CompressLum(tpImageLuminanceHDR& I);
};
