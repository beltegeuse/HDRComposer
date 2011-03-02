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

    m_sigDChamps = new QDoubleSpinBox(this);
    m_sigDChamps->setValue(((tpHDRToneOperatorDurandSlow*)m_operator)->GetSigD());
    GetFormLayout()->addRow("Sig G",m_sigDChamps);

    m_sigRChamps = new QDoubleSpinBox(this);
    m_sigRChamps->setValue(((tpHDRToneOperatorDurandSlow*)m_operator)->GetSigR());
    GetFormLayout()->addRow("Sig R",m_sigRChamps);
}

QToneOperatorDurandSlow::~QToneOperatorDurandSlow(void)
{
}

void QToneOperatorDurandSlow::ValidPushed()
{
	((tpHDRToneOperatorDurandSlow*)m_operator)->SetHalfSize(m_pChamps->value());
	((tpHDRToneOperatorDurandSlow*)m_operator)->SetSigD(m_sigDChamps->value());
	((tpHDRToneOperatorDurandSlow*)m_operator)->SetSigR(m_sigRChamps->value());
}
