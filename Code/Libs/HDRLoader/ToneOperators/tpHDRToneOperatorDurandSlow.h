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
	float m_sig_d;
	float m_sig_r;
public:
	tpHDRToneOperatorDurandSlow(int halfSize = 9, int sig_d = 10, int sig_r = 30);
	virtual ~tpHDRToneOperatorDurandSlow();

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetHalfSize(int halfSize);
	int GetHalfSize();
	void SetSigD(float v);
	float GetSigD();
	void SetSigR(float v);
	float GetSigR();

};

#endif /* TPHDRTONEOPERATORDURANDSLOW_H_ */
