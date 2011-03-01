
#include "QToneOperatorDrago.h"

#include <tpHDRToneOperatorDrago.h>

QToneOperatorDrago::QToneOperatorDrago(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Drago (*)")
{	
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorDrago;

	// Creation du formulaire
	m_pChamps = new QDoubleSpinBox(this);
	m_pChamps->setValue(((tpHDRToneOperatorDrago*)m_operator)->GetP());
    GetFormLayout()->addRow("p",m_pChamps);
}

QToneOperatorDrago::~QToneOperatorDrago(void)
{
}

void QToneOperatorDrago::ValidPushed()
{
	((tpHDRToneOperatorDrago*)m_operator)->SetP(m_pChamps->value());
}