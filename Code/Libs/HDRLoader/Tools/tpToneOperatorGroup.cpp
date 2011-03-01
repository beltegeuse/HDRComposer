#include "StdAfx.h"
#include "tpToneOperatorGroup.h"
#include "tpImage.hpp"
#include "tpImageIO.hpp"
#include "Operations/tpImageConvert.hpp"
#include "Operations/tpHDROperations.h"
#include "Operations/tpOperations.h"

// ==== Les includes des operators
#include "ToneOperators/tpHDRToneOperatorLinear.h"
#include "ToneOperators/tpHDRToneOperatorSigmoid.h"
#include "ToneOperators/tpHDRToneOperatorExp.h"
#include "ToneOperators/tpHDRToneOperatorLog.h"
#include "ToneOperators/tpHDRToneOperatorWard.h"
#include "ToneOperators/tpHDRToneOperatorDrago.h"
#include "ToneOperators/tpHDRToneOperatorChiu.h"
#include "ToneOperators/tpHDRToneOperatorSchlick.h"
#include "ToneOperators/tpHDRToneOperatorRetinex.h"
#include "ToneOperators/tpHDRToneOperatorAshikhmin.h"
#include "ToneOperators/tpHDRToneOperatorFilmic.h"
#include "ToneOperators/tpHDRToneOperatorPhotographic.h"
#include "ToneOperators/tpHDRToneOperatorPhotographicBurn.h"
#include "ToneOperators/tpHDRToneOperatorPhotographicLocal.h"
#include "ToneOperators/tpHDRToneOperatorTumblin.h"

#include <iostream>

tpToneOperatorGroup::tpToneOperatorGroup(void)
{
}

tpToneOperatorGroup::~tpToneOperatorGroup(void)
{
	// Free all op
	tpToneOperatorMap::iterator it = m_operators.begin();
	while(it != m_operators.end())
	{
		delete it->second;
		++it;
	}
}

void tpToneOperatorGroup::AddOperator(const std::string& opName, tpToneOperatorAbstract* op)
{
	//FIXME: Attention a l'ecrasement .... (fa	ire un find)
	m_operators[opName] = op;
}

void tpToneOperatorGroup::AddAllOperators()
{
	AddOperator("Linear", new tpHDRToneOperatorLinear());
	AddOperator("Exp", new tpHDRToneOperatorExp());
	AddOperator("Sigmoid", new tpHDRToneOperatorSigmoid());
	AddOperator("Log", new tpHDRToneOperatorLog());
	AddOperator("Ward", new tpHDRToneOperatorWard());
	AddOperator("Drago", new tpHDRToneOperatorDrago());
	AddOperator("Chiu", new tpHDRToneOperatorChiu());
	AddOperator("Schlick", new tpHDRToneOperatorSchlick());
	AddOperator("Retinex", new tpHDRToneOperatorRetinex());
	AddOperator("Ashikhmin",new tpHDRToneOperatorAshikhmin());
	AddOperator("Filmic",new tpHDRToneOperatorFilmic());
	AddOperator("Photographic",new tpHDRToneOperatorPhotographic());
	AddOperator("PhotographicBurn",new tpHDRToneOperatorPhotographicBurn());
	AddOperator("PhotographicLocal",new tpHDRToneOperatorPhotographicLocal());
	AddOperator("Thumblin",new tpHDRToneOperatorTumblin());
}


void tpToneOperatorGroup::ApplyAllSaturation(const tpImageColorHDR& imageC, const std::string& path, const std::string& filename, tpOperatorCropping* crop, double s)
{
	std::cout << "[Info] ============ tpToneOperatorGroup (ApplyAllSaturation) ============" << std::endl;
	tpToneOperatorMap::iterator it = m_operators.begin();

	while(it != m_operators.end())
	{
		std::cout << " * Apply " << it->first << std::endl;
	
		// Construct the right path
		std::string pathFull = path + it->first + "_" + filename;

		// Compression ...
		tpImageColorHDR temp;
		temp.copy(imageC);
		it->second->Compress(temp);
		
		// Convert
		tpImageColor I;
		tpImageConvert::createColorImage(temp,I);

		// And write :)
		std::cout << " Write : " << pathFull << std::endl;
		tpImageIO::write(I,pathFull);

		++it;
	}
}


