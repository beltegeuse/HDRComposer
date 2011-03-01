#pragma once
#include "tpHDRToneOperatorLumAbstract.h"
#include "tpImage.hpp"
#include "tpConfig.h"

class TP_EXPORT tpHDRToneOperatorSchlick : public tpHDRToneOperatorLumAbstract
{
private:
	double m_phi;
	double m_k;

public:
	tpHDRToneOperatorSchlick(double phi = 0.00001 , double k = 0.2);
	~tpHDRToneOperatorSchlick(void);

	// ==== Methodes publiques
	virtual void CompressLum(tpImageLuminanceHDR& I);

	void SetK(double k);
	void SetPhi(double v);
	double GetK() const;
	double GetPhi() const;
};
