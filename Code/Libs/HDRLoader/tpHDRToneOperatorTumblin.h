#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorTumblin :  public tpHDRToneOperatorLumAbstract
{
private:
	double m_scale_factor;

public:
	tpHDRToneOperatorTumblin(double scale_factor = 1.0);
	~tpHDRToneOperatorTumblin(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetScaleFactor(double v);
	double GetScaleFactor() const;

private:
	double Gamma(double value);
};
