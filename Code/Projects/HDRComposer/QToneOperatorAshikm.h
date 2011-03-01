#pragma once

#include "QToneOperatorFormAbstract.h"

class QToneOperatorAshikm: public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_tChamps;

public:
	QToneOperatorAshikm(QWidget* parent);
	virtual ~QToneOperatorAshikm(void);

protected:
	virtual void ValidPushed();
};