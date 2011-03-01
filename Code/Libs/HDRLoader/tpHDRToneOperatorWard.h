#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpImage.hpp"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorWard : public tpHDRToneOperatorLumAbstract
{
public:
	tpHDRToneOperatorWard(void);
	virtual ~tpHDRToneOperatorWard(void);

	virtual void CompressLum(tpImageLuminanceHDR& I);
};
