#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorHistogramme:  public tpHDRToneOperatorLumAbstract
{
public:
	tpHDRToneOperatorHistogramme(void);
	~tpHDRToneOperatorHistogramme(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);
};
