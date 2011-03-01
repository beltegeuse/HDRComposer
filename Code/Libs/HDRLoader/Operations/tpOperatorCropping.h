#pragma once

#include "tpImage.hpp"

class tpOperatorCropping
{
private:
	// ==== Attributs
	double m_b;
	double m_w;

public:
	// ==== Constructeurs et destructeurs
	tpOperatorCropping(double percentB, double percentW);
	virtual ~tpOperatorCropping();

	// ==== Methodes publiques
	void Cropping(tpImageLuminanceHDR& I);
};
