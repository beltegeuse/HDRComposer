#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorFilmic : public tpHDRToneOperatorLumAbstract
{
public:
	tpHDRToneOperatorFilmic(void);
	virtual ~tpHDRToneOperatorFilmic(void);

	virtual void CompressLum(tpImageLuminanceHDR& I);
};
