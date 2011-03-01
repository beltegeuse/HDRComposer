#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorSchilck : public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_phiChamps;
	QDoubleSpinBox* m_kChamps;

public:
	QToneOperatorSchilck(QWidget* parent);
	virtual ~QToneOperatorSchilck(void);

protected:
	virtual void ValidPushed();

};
