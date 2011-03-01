#pragma once
#include "tpHDRToneOperatorLumAbstract.h"
#include "tpMath.h"
#include "Operations/tpImageFilter.hpp"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorAshikhmin : public tpHDRToneOperatorLumAbstract
{
private:
	double m_t;
public:
	tpHDRToneOperatorAshikhmin(double t = 0.5);
	~tpHDRToneOperatorAshikhmin(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetT(double v);
	double GetT();

private:
	tpFilterResultDouble CalculDifference(const tpFilterResultDouble& Is, const tpFilterResultDouble& Is2) const; 
	double C(double v) const;
};
