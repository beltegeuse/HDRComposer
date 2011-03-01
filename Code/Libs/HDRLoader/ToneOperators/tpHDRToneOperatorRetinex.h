#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorRetinex : public tpHDRToneOperatorLumAbstract
{
private:
	double m_k;
	double m_sig;

public:
	tpHDRToneOperatorRetinex(double k = 0.5, double sig = 5.0);
	~tpHDRToneOperatorRetinex(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetK(double v);
	void SetSig(double v);
	double GetK() const;
	double GetSig() const;
};
