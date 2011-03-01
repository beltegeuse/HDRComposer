#include "QToneOperatorDurandSlow.h"

#include <ToneOperators/tpHDRToneOperatorDurandSlow.h>

QToneOperatorDurandSlow::QToneOperatorDurandSlow(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Durand Slow")
{	
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorDurandSlow;

	// Creation du formulaire
	m_pChamps = new QDoubleSpinBox(this);
	m_pChamps->setValue(((tpHDRToneOperatorDurandSlow*)m_operator)->GetHalfSize());
    GetFormLayout()->addRow("Half Size",m_pChamps);
}

QToneOperatorDurandSlow::~QToneOperatorDurandSlow(void)
{
}

void QToneOperatorDurandSlow::ValidPushed()
{
	((tpHDRToneOperatorDurandSlow*)m_operator)->SetHalfSize(m_pChamps->value());
}
