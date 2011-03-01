
#include "QToneOperatorSchilck.h"

#include <ToneOperators/tpHDRToneOperatorSchlick.h>

QToneOperatorSchilck::QToneOperatorSchilck(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Schlick")
{
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorSchlick;

	// Creation du formulaire
	m_phiChamps = new QDoubleSpinBox(this);
	m_phiChamps->setValue(((tpHDRToneOperatorSchlick*)m_operator)->GetPhi());
	m_phiChamps->setDecimals(6);
    GetFormLayout()->addRow("Phi",m_phiChamps);

	m_kChamps = new QDoubleSpinBox(this);
	m_kChamps->setValue(((tpHDRToneOperatorSchlick*)m_operator)->GetK());
    GetFormLayout()->addRow("k",m_kChamps);
}

QToneOperatorSchilck::~QToneOperatorSchilck(void)
{
}

void QToneOperatorSchilck::ValidPushed()
{
	((tpHDRToneOperatorSchlick*)m_operator)->SetPhi(m_phiChamps->value());
	((tpHDRToneOperatorSchlick*)m_operator)->SetK(m_kChamps->value());
}
