#pragma once
#include "tpHDRToneOperatorLumAbstract.h"

class tpHDRToneOperatorFilmicDynamic :
	public tpHDRToneOperatorLumAbstract
{
private:
	double m_a;

public:
	tpHDRToneOperatorFilmicDynamic(double a = 0.18);
	virtual ~tpHDRToneOperatorFilmicDynamic(void);

	virtual void CompressLum(tpImageLuminanceHDR& I);
};
