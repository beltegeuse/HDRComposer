#pragma once

#include "ToneOperators/QToneOperatorAbstract.h"

class ToneOperatorFactory
{
public:
	static QToneOperatorAbstract* LoadOperator(const QString& nom, QWidget* parent);
};
