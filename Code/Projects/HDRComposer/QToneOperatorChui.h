#pragma once

#include "QToneOperatorFormAbstract.h"

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