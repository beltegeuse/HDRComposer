#pragma once

#include "QToneOperatorFormAbstract.h"

class QToneOperatorTumblin: public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_sChamps;

public:
	QToneOperatorTumblin(QWidget* parent);
	virtual ~QToneOperatorTumblin(void);

protected:
	virtual void ValidPushed();
};