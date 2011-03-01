
#include "QToneOperatorChui.h"

#include <tpHDRToneOperatorChiu.h>

QToneOperatorChui::QToneOperatorChui(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Chiu")
{
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorChiu;

	// Creation du formulaire
	m_sigChamps = new QDoubleSpinBox(this);
	m_sigChamps->setValue(((tpHDRToneOperatorChiu*)m_operator)->GetSig());
    GetFormLayout()->addRow("sig",m_sigChamps);

	m_kChamps = new QDoubleSpinBox(this);
	m_kChamps->setValue(((tpHDRToneOperatorChiu*)m_operator)->GetK());
    GetFormLayout()->addRow("k",m_kChamps);
}

QToneOperatorChui::~QToneOperatorChui(void)
{
}

void QToneOperatorChui::ValidPushed()
{
	((tpHDRToneOperatorChiu*)m_operator)->SetSig(m_sigChamps->value());
	((tpHDRToneOperatorChiu*)m_operator)->SetK(m_kChamps->value());
}

