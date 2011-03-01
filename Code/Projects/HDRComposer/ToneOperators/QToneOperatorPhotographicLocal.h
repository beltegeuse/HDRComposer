#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorPhotographicLocal : public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_aChamps;
	QDoubleSpinBox* m_tChamps;
	QDoubleSpinBox* m_phiChamps;

public:
	QToneOperatorPhotographicLocal(QWidget* parent);
	virtual ~QToneOperatorPhotographicLocal(void);

protected:
	virtual void ValidPushed();

};
