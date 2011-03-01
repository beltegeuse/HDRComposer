#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorDrago: public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_pChamps;

public:
	QToneOperatorDrago(QWidget* parent);
	virtual ~QToneOperatorDrago(void);

protected:
	virtual void ValidPushed();
};
