
#include "QToneOperatorRetinex.h"

#include <ToneOperators/tpHDRToneOperatorRetinex.h>

QToneOperatorRetinex::QToneOperatorRetinex(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Retinex")
{
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorRetinex;

	// Creation du formulaire
	m_sigChamps = new QDoubleSpinBox(this);
	m_sigChamps->setValue(((tpHDRToneOperatorRetinex*)m_operator)->GetSig());
    GetFormLayout()->addRow("sig",m_sigChamps);

	m_kChamps = new QDoubleSpinBox(this);
	m_kChamps->setValue(((tpHDRToneOperatorRetinex*)m_operator)->GetK());
    GetFormLayout()->addRow("k",m_kChamps);
}

QToneOperatorRetinex::~QToneOperatorRetinex(void)
{
}

void QToneOperatorRetinex::ValidPushed()
{
	((tpHDRToneOperatorRetinex*)m_operator)->SetSig(m_sigChamps->value());
	((tpHDRToneOperatorRetinex*)m_operator)->SetK(m_kChamps->value());
}


