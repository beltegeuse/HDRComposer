#include "QToneOperatorPhotographic.h"

#include <tpHDRToneOperatorPhotographic.h>

QToneOperatorPhotographic::QToneOperatorPhotographic(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Photographic (*)")
{	
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorPhotographic;

	// Creation du formulaire
	m_aChamps = new QDoubleSpinBox(this);
	m_aChamps->setValue(((tpHDRToneOperatorPhotographic*)m_operator)->GetA());
    GetFormLayout()->addRow("a",m_aChamps);
}

QToneOperatorPhotographic::~QToneOperatorPhotographic(void)
{
}

void QToneOperatorPhotographic::ValidPushed()
{
	((tpHDRToneOperatorPhotographic*)m_operator)->SetA(m_aChamps->value());
}
