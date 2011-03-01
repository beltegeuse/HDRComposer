#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorDurandSlow: public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_pChamps;

public:
	QToneOperatorDurandSlow(QWidget* parent);
	virtual ~QToneOperatorDurandSlow(void);

protected:
	virtual void ValidPushed();
};
