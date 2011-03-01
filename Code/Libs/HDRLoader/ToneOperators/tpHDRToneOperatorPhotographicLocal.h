#pragma once
#include "tpHDRToneOperatorLumAbstract.h"
#include "tpMath.h"
#include "Operations/tpImageFilter.hpp"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorPhotographicLocal : public tpHDRToneOperatorLumAbstract
{
private:
	double m_a;
	double m_phi;
	double m_t;
public:
	tpHDRToneOperatorPhotographicLocal(double a = 0.18, double phi = 16.0, double t = 0.1);
	~tpHDRToneOperatorPhotographicLocal(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);
	tpFilterResultDouble CalculDifference(const tpFilterResultDouble& Is, const tpFilterResultDouble& Is2, float s) const; 

	void SetA(double a);
	void SetPhi(double phi);
	void SetT(double v);
	double GetA() const;
	double GetPhi() const;
	double GetT() const;
};
