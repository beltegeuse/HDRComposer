#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorLog : public tpHDRToneOperatorLumAbstract
{
private:
	float m_q;
	float m_k;
public:
	tpHDRToneOperatorLog(float q = 1 , float k = 1);
	
	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetQ(float v);
	void SetK(float v);
	float GetQ();
	float GetK();
};
