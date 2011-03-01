#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorExp : public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_qChamps;
	QDoubleSpinBox* m_kChamps;

public:
	QToneOperatorExp(QWidget* parent);
	virtual ~QToneOperatorExp(void);

protected:
	virtual void ValidPushed();

};
