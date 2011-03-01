#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorChui : public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_sigChamps;
	QDoubleSpinBox* m_kChamps;

public:
	QToneOperatorChui(QWidget* parent);
	virtual ~QToneOperatorChui(void);

protected:
	virtual void ValidPushed();

};
