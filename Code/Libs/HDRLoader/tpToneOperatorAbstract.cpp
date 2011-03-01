#include "StdAfx.h"
#include "tpToneOperatorAbstract.h"

tpToneOperatorAbstract::tpToneOperatorAbstract() :
	m_gammaCorrect(false),
	m_isDynamic(false),
	m_isDynamicMode(false)
{
}

tpToneOperatorAbstract::~tpToneOperatorAbstract(void)
{
}

bool tpToneOperatorAbstract::isGammaCorrected() const
{
	return m_gammaCorrect;
}

void tpToneOperatorAbstract::SetGammaCorrected(bool v)
{
	m_gammaCorrect = v;
}

void tpToneOperatorAbstract::SetDynamicMode(bool v)
{
	m_isDynamicMode = v;
}

bool tpToneOperatorAbstract::isDynamicMode() const
{
	return m_isDynamicMode;
}

bool tpToneOperatorAbstract::isDynamic() const
{
	return m_isDynamic;
}

void tpToneOperatorAbstract::SetDynamic(bool v)
{
	m_isDynamic = v;
}

bool tpToneOperatorAbstract::isDynamicActiveNow()
{
	return (isDynamic() && isDynamicMode());
}
