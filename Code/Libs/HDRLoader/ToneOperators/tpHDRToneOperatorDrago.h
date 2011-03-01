#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class  TP_EXPORT tpHDRToneOperatorDrago : public tpHDRToneOperatorLumAbstract
{
private:
	float m_p;
public:
	// ==== Constructeur et destructeur
	tpHDRToneOperatorDrago(float p = 0.85);
	virtual ~tpHDRToneOperatorDrago();

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetP(float v);
	float GetP();
};
