
#include "QToneOperatorAshikm.h"

#include <ToneOperators/tpHDRToneOperatorAshikhmin.h>

QToneOperatorAshikm::QToneOperatorAshikm(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Ashikhim")
{	
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorAshikhmin;

	// Creation du formulaire
	m_tChamps = new QDoubleSpinBox(this);
	m_tChamps->setValue(((tpHDRToneOperatorAshikhmin*)m_operator)->GetT());
    GetFormLayout()->addRow("t",m_tChamps);
}

QToneOperatorAshikm::~QToneOperatorAshikm(void)
{
}

void QToneOperatorAshikm::ValidPushed()
{
	((tpHDRToneOperatorAshikhmin*)m_operator)->SetT(m_tChamps->value());
}
