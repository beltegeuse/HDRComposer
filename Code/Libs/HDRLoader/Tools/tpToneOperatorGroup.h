#pragma once

#include "ToneOperators/tpToneOperatorAbstract.h"
#include "tpImage.hpp"

#include <map>
#include <string>

#include "Operations/tpOperatorCropping.h"

class tpToneOperatorGroup
{
private:
	// ==== Attributs
	typedef std::map<std::string, tpToneOperatorAbstract*> tpToneOperatorMap;
	tpToneOperatorMap m_operators;
public:
	// ==== Constructeur et destructeur
	tpToneOperatorGroup();
	virtual ~tpToneOperatorGroup();

	// ==== Methodes publiques
	void AddOperator(const std::string& opName, tpToneOperatorAbstract* op);
	void AddAllOperators();

	void ApplyAllSaturation(const tpImageColorHDR& image, const std::string& path, const std::string& filename, tpOperatorCropping* crop = NULL, double s = 0.65);
};
