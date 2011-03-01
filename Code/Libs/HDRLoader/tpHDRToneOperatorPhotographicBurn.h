#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorPhotographicBurn :  public tpHDRToneOperatorLumAbstract
{
private:
	double m_a;
	double m_burn;

public:
	tpHDRToneOperatorPhotographicBurn(double a = 0.18, double burn = 0.75);
	virtual ~tpHDRToneOperatorPhotographicBurn(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetA(double a);
	void SetBurn(double v);
	double GetA() const;
	double GetBurn() const;
};
