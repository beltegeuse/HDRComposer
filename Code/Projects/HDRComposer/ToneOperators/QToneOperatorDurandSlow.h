#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorDurandSlow: public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_pChamps;
	QDoubleSpinBox* m_sigDChamps;
	QDoubleSpinBox* m_sigRChamps;
public:
	QToneOperatorDurandSlow(QWidget* parent);
	virtual ~QToneOperatorDurandSlow(void);

protected:
	virtual void ValidPushed();
};
