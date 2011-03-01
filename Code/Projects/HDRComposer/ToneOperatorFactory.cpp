#include "ToneOperatorFactory.h"
#include "QToneOperatorAbstract.h"
#include "QToneOperator.h"
#include "QToneOperatorPhotographic.h"
#include "QToneOperatorExp.h"
#include "QToneOperatorLog.h"
#include "QToneOperatorDrago.h"
#include "QToneOperatorTumblin.h"
#include "QToneOperatorAshikm.h"
#include "QToneOperatorChui.h"
#include "QToneOperatorPhotographicBurn.h"
#include "QToneOperatorPhotographicLocal.h"
#include "QToneOperatorRetinex.h"
#include "QToneOperatorSchilck.h"
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
	else
	{
		return new QToneOperator(parent, nom);
	}
}
