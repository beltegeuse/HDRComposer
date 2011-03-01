
#include "QToneOperatorPhotographicBurn.h"

#include <tpHDRToneOperatorPhotographicBurn.h>

QToneOperatorPhotographicBurn::QToneOperatorPhotographicBurn(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Photographic Burn")
{
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorPhotographicBurn;

	// Creation du formulaire
	m_aChamps = new QDoubleSpinBox(this);
	m_aChamps->setValue(((tpHDRToneOperatorPhotographicBurn*)m_operator)->GetA());
    GetFormLayout()->addRow("a",m_aChamps);

	m_burnChamps = new QDoubleSpinBox(this);
	m_burnChamps->setValue(((tpHDRToneOperatorPhotographicBurn*)m_operator)->GetBurn());
    GetFormLayout()->addRow("Burn",m_burnChamps);
}

QToneOperatorPhotographicBurn::~QToneOperatorPhotographicBurn(void)
{
}

void QToneOperatorPhotographicBurn::ValidPushed()
{
	((tpHDRToneOperatorPhotographicBurn*)m_operator)->SetA(m_aChamps->value());
	((tpHDRToneOperatorPhotographicBurn*)m_operator)->SetBurn(m_burnChamps->value());
}

