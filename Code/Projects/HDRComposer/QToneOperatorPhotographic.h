#pragma once

#include "QToneOperatorFormAbstract.h"

class QToneOperatorPhotographic: public QToneOperatorFormAbstract
{
private:
	QDoubleSpinBox* m_aChamps;

public:
	QToneOperatorPhotographic(QWidget* parent);
	virtual ~QToneOperatorPhotographic(void);

protected:
	virtual void ValidPushed();
};
