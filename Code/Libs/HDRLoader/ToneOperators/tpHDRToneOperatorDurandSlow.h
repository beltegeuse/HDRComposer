#pragma once
#ifndef TPHDRTONEOPERATORDURANDSLOW_H_
#define TPHDRTONEOPERATORDURANDSLOW_H_

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"
#include <cmath>
#include <math.h>
#include <stdlib.h>

class TP_EXPORT tpHDRToneOperatorDurandSlow  : public tpHDRToneOperatorLumAbstract
{
private:
	int m_half_size;
public:
	tpHDRToneOperatorDurandSlow(int halfSize = 9);
	virtual ~tpHDRToneOperatorDurandSlow();

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetHalfSize(int halfSize);
	int GetHalfSize();

};

#endif /* TPHDRTONEOPERATORDURANDSLOW_H_ */
