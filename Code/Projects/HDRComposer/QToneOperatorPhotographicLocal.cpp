
#include "QToneOperatorPhotographicLocal.h"

#include <tpHDRToneOperatorPhotographicLocal.h>

QToneOperatorPhotographicLocal::QToneOperatorPhotographicLocal(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Photographic Local")
{
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorPhotographicLocal;

	// Creation du formulaire
	m_aChamps = new QDoubleSpinBox(this);
	m_aChamps->setValue(((tpHDRToneOperatorPhotographicLocal*)m_operator)->GetA());
    GetFormLayout()->addRow("a",m_aChamps);

	m_tChamps = new QDoubleSpinBox(this);
	m_tChamps->setValue(((tpHDRToneOperatorPhotographicLocal*)m_operator)->GetT());
    GetFormLayout()->addRow("t",m_tChamps);

	m_phiChamps = new QDoubleSpinBox(this);
	m_phiChamps->setValue(((tpHDRToneOperatorPhotographicLocal*)m_operator)->GetPhi());
    GetFormLayout()->addRow("phi",m_phiChamps);
}

QToneOperatorPhotographicLocal::~QToneOperatorPhotographicLocal(void)
{
}

void QToneOperatorPhotographicLocal::ValidPushed()
{
	((tpHDRToneOperatorPhotographicLocal*)m_operator)->SetA(m_aChamps->value());
	((tpHDRToneOperatorPhotographicLocal*)m_operator)->SetT(m_tChamps->value());
	((tpHDRToneOperatorPhotographicLocal*)m_operator)->SetPhi(m_phiChamps->value());
}

