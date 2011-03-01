#include "ToneOperatorFactory.h"
#include "ToneOperators/QToneOperatorAbstract.h"
#include "ToneOperators/QToneOperator.h"
#include "ToneOperators/QToneOperatorPhotographic.h"
#include "ToneOperators/QToneOperatorExp.h"
#include "ToneOperators/QToneOperatorLog.h"
#include "ToneOperators/QToneOperatorDrago.h"
#include "ToneOperators/QToneOperatorTumblin.h"
#include "ToneOperators/QToneOperatorAshikm.h"
#include "ToneOperators/QToneOperatorChui.h"
#include "ToneOperators/QToneOperatorPhotographicBurn.h"
#include "ToneOperators/QToneOperatorPhotographicLocal.h"
#include "ToneOperators/QToneOperatorRetinex.h"
#include "ToneOperators/QToneOperatorSchilck.h"
#include "ToneOperators/QToneOperatorDurandSlow.h"
#include <tpException.hpp>


QToneOperatorAbstract* ToneOperatorFactory::LoadOperator(const QString& nom, QWidget* parent)
{
	if(nom == "Photographic (*)")
	{
		return new QToneOperatorPhotographic(parent);
	}
	else if(nom == "Exp (*)")
	{
		return new QToneOperatorExp(parent);
	}
	else if(nom == "Log")
	{
		return new QToneOperatorLog(parent);
	}
	else if(nom == "Drago (*)")
	{
		return new QToneOperatorDrago(parent);
	}
	/*else if(nom == "Thumblin (*)")
	{
		return new QToneOperatorTumblin(parent);
	}*/
	else if(nom == "Ashikhim")
	{
		return new QToneOperatorAshikm(parent);
	}
	else if(nom == "Chiu")
	{
		return new QToneOperatorChui(parent);
	}
	else if(nom == "Photographic Burn")
	{
		return new QToneOperatorPhotographicBurn(parent);
	}
	else if(nom == "Photographic Local")
	{
		return new QToneOperatorPhotographicLocal(parent);
	}
	else if(nom == "Retinex")
	{
		return new QToneOperatorRetinex(parent);
	}
	else if(nom == "Schlick")
	{
		return new QToneOperatorSchilck(parent);
	}
	else if(nom == "Durand Slow")
		return new QToneOperatorDurandSlow(parent);
	else
	{
		return new QToneOperator(parent, nom);
	}
}
