#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class tpHDRToneOperatorDurand: public tpHDRToneOperatorLumAbstract
{
public:
	tpHDRToneOperatorDurand(void);
	~tpHDRToneOperatorDurand(void);

	virtual void CompressLum(tpImageLuminanceHDR& I);
};
