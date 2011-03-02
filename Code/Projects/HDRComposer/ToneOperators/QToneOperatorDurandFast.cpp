#include "QToneOperatorDurandFast.h"

#include <ToneOperators/tpHDRToneOperatorDurandFast.h>

QToneOperatorDurandFast::QToneOperatorDurandFast(QWidget* parent) :
	QToneOperatorFormAbstract(parent, "Durand Fast")
{	
	// Creation de l'operator
	m_operator = new tpHDRToneOperatorDurandFast;

	// Creation du formulaire
}

QToneOperatorDurandFast::~QToneOperatorDurandFast(void)
{
}

void QToneOperatorDurandFast::ValidPushed()
{
}
