#include "QToneOperatorExp.h"
#include <ToneOperators/tpHDRToneOperatorExp.h>

QToneOperatorExp::QToneOperatorExp(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Exp (*)")
{
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorExp;

	// Creation du formulaire
	m_qChamps = new QDoubleSpinBox(this);
	m_qChamps->setValue(((tpHDRToneOperatorExp*)m_operator)->GetQ());
    GetFormLayout()->addRow("q",m_qChamps);

	m_kChamps = new QDoubleSpinBox(this);
	m_kChamps->setValue(((tpHDRToneOperatorExp*)m_operator)->GetK());
    GetFormLayout()->addRow("k",m_kChamps);
}

QToneOperatorExp::~QToneOperatorExp(void)
{
}

void QToneOperatorExp::ValidPushed()
{
	((tpHDRToneOperatorExp*)m_operator)->SetQ(m_qChamps->value());
	((tpHDRToneOperatorExp*)m_operator)->SetK(m_kChamps->value());
}
