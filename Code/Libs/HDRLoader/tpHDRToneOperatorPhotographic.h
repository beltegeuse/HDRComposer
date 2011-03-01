#pragma once

#include "tpHDRToneOperatorLumAbstract.h"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorPhotographic : public tpHDRToneOperatorLumAbstract
{
private:
	double m_a;
public:
	tpHDRToneOperatorPhotographic(double a = 0.18);
	~tpHDRToneOperatorPhotographic(void);

	double GetA() const;
	void SetA(double v);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);
};
