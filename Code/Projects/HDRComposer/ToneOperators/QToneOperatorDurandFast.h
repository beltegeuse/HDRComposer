#pragma once

#include "ToneOperators/QToneOperatorFormAbstract.h"

class QToneOperatorDurandFast: public QToneOperatorFormAbstract
{
public:
	QToneOperatorDurandFast(QWidget* parent);
	virtual ~QToneOperatorDurandFast(void);

protected:
	virtual void ValidPushed();
};
