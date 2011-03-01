
#include "QToneOperator.h"
#include <tpHDRToneOperatorAshikhmin.h>
#include <tpImageConvert.hpp>
#include <tpOperations.h>
#include <tpDisplayManager.h>

#include <tpHDRToneOperatorAshikhmin.h>
#include <tpHDRToneOperatorChiu.h>
#include <tpHDRToneOperatorDrago.h>
#include <tpHDRToneOperatorExp.h>
#include <tpHDRToneOperatorFilmic.h>
#include <tpHDRToneOperatorLinear.h>
#include <tpHDRToneOperatorLog.h>
#include <tpHDRToneOperatorRetinex.h>
#include <tpHDRToneOperatorSchlick.h>
#include <tpHDRToneOperatorSigmoid.h>
#include <tpHDRToneOperatorWard.h>
#include <tpHDRToneOperatorPhotographic.h>
#include <tpHDRToneOperatorPhotographicBurn.h>
#include <tpHDRToneOperatorPhotographicLocal.h>
#include <tpHDRToneOperatorTumblin.h>
#include <tpHDRToneOperatorFilmicDynamic.h>

QToneOperator::QToneOperator(QWidget* parent, const QString& name): 
	QToneOperatorAbstract(parent),
	m_parent(parent),
	m_name(name)
{
	LoadOp(name);

	QHBoxLayout *layout = new QHBoxLayout;
	QLabel* l = new QLabel("ToneOperator Automatique : " + name, this);
	layout->addWidget(l,0,Qt::AlignCenter);
	setLayout(layout);
}

QToneOperator::~QToneOperator(void)
{
}

void QToneOperator::LoadOp(const QString& nom)
{
	if(m_operator != NULL)
	{
		delete m_operator;
		m_operator = NULL;
	}

	if(nom == "Ashikhim")
	{
		m_operator =  new tpHDRToneOperatorAshikhmin ;
	}
	else if(nom == "Chiu")
	{
		m_operator = new tpHDRToneOperatorChiu;
	}
	else if(nom == "Filmic")
	{
		m_operator = new tpHDRToneOperatorFilmic;
	}
	else if(nom == "Linear")
	{
		m_operator = new tpHDRToneOperatorLinear;
	}
	else if(nom == "Log")
	{
		m_operator = new tpHDRToneOperatorLog;
	}
	else if(nom == "Retinex")
	{
		m_operator = new tpHDRToneOperatorRetinex;
	}
	else if(nom == "Schlick")
	{
		m_operator = new tpHDRToneOperatorSchlick;
	}
	else if(nom == "Sigmoid (*)")
	{
		m_operator = new tpHDRToneOperatorSigmoid;
	}
	else if(nom == "Photographic Burn")
	{
		m_operator = new tpHDRToneOperatorPhotographicBurn;
	}
	else if(nom == "Photographic Local")
	{
		m_operator = new tpHDRToneOperatorPhotographicLocal;
	}
	else if(nom == "Drago (*)")
	{
		m_operator = new tpHDRToneOperatorDrago;
	}
	else if(nom == "Ward (*)")
	{
		m_operator = new tpHDRToneOperatorWard;
	}
	else if(nom == "Photographic (*)")
	{
		m_operator = new tpHDRToneOperatorPhotographic;
	}
	else if(nom == "Exp (*)")
	{
		m_operator = new tpHDRToneOperatorExp;
	}
	else if(nom == "Thumblin (*)")
	{
		m_operator = new tpHDRToneOperatorTumblin;
	}
	else if(nom == "Filmic Dynamic (*)")
	{
		m_operator = new tpHDRToneOperatorFilmicDynamic;
	}
	else
	{
		QMessageBox::critical(this, "Erreur chargement operateur", "Impossible de trouver une équivalence operateur avec : " + nom);
	}
}

const QString& QToneOperator::GetName() const
{
	return m_name;
}
