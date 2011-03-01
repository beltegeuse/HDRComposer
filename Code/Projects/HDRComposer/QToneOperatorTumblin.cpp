
#include "QToneOperatorTumblin.h"

#include <tpHDRToneOperatorTumblin.h>

QToneOperatorTumblin::QToneOperatorTumblin(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Thumblin (*)")
{	
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorTumblin;

	// Creation du formulaire
	m_sChamps = new QDoubleSpinBox(this);
	m_sChamps->setValue(((tpHDRToneOperatorTumblin*)m_operator)->GetScaleFactor());
    GetFormLayout()->addRow("Scale factor",m_sChamps);
}

QToneOperatorTumblin::~QToneOperatorTumblin(void)
{
}

void QToneOperatorTumblin::ValidPushed()
{
	((tpHDRToneOperatorTumblin*)m_operator)->SetScaleFactor(m_sChamps->value());
}