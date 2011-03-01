#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorLog : public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_qChamps;
	QDoubleSpinBox* m_kChamps;

public:
	QToneOperatorLog(QWidget* parent);
	virtual ~QToneOperatorLog(void);

protected:
	virtual void ValidPushed();

};
