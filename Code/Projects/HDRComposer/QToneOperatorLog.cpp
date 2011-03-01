
#include "QToneOperatorLog.h"
#include <ToneOperators/tpHDRToneOperatorLog.h>

QToneOperatorLog::QToneOperatorLog(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Log")
{
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorLog;

	// Creation du formulaire
	m_qChamps = new QDoubleSpinBox(this);
	m_qChamps->setValue(((tpHDRToneOperatorLog*)m_operator)->GetQ());
    GetFormLayout()->addRow("q",m_qChamps);

	m_kChamps = new QDoubleSpinBox(this);
	m_kChamps->setValue(((tpHDRToneOperatorLog*)m_operator)->GetK());
    GetFormLayout()->addRow("k",m_kChamps);
}

QToneOperatorLog::~QToneOperatorLog(void)
{
}

void QToneOperatorLog::ValidPushed()
{
	((tpHDRToneOperatorLog*)m_operator)->SetQ(m_qChamps->value());
	((tpHDRToneOperatorLog*)m_operator)->SetK(m_kChamps->value());
}

