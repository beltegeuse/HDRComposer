#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorExp : public tpHDRToneOperatorLumAbstract
{
private:
	float m_q;
	float m_k;

public:
	tpHDRToneOperatorExp(float q = 1.0, float k = 1.0);

	void SetQ(float v);
	void SetK(float v);
	float GetQ();
	float GetK();

	virtual void CompressLum(tpImageLuminanceHDR& I);
};
