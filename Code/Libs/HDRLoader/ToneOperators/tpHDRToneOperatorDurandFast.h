#pragma once
#ifndef TPHDRTONEOPERATORDURANDSLOW_H_
#define TPHDRTONEOPERATORDURANDSLOW_H_

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"
#include <cmath>
#include <math.h>
#include <stdlib.h>

class TP_EXPORT tpHDRToneOperatorDurandFast  : public tpHDRToneOperatorLumAbstract
{
private:

public:
	tpHDRToneOperatorDurandFast();
	virtual ~tpHDRToneOperatorDurandFast();

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);
};

#endif /* TPHDRTONEOPERATORDURANDSLOW_H_ */
