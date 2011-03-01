#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorChiu :  public tpHDRToneOperatorLumAbstract
{
private:
	// ==== Attributs
	float m_k;
	float m_sig;

public:
	// ==== Constructeur et destructeurs
	tpHDRToneOperatorChiu(float k = 2.0, float sig = 5.0);
	~tpHDRToneOperatorChiu(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	float GetSig() const;
	float GetK() const;
	void SetSig(float v);
	void SetK(float v);
};
