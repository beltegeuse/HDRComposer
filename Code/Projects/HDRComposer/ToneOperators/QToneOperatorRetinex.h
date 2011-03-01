#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorRetinex : public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_sigChamps;
	QDoubleSpinBox* m_kChamps;

public:
	QToneOperatorRetinex(QWidget* parent);
	virtual ~QToneOperatorRetinex(void);

protected:
	virtual void ValidPushed();

};
