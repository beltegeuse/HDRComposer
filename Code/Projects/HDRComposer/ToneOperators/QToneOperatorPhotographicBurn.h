#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorPhotographicBurn : public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_aChamps;
	QDoubleSpinBox* m_burnChamps;

public:
	QToneOperatorPhotographicBurn(QWidget* parent);
	virtual ~QToneOperatorPhotographicBurn(void);

protected:
	virtual void ValidPushed();

};
