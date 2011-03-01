#include "StdAfx.h"
#include "tpDisplayManager.h"

tpDisplayManager::tpDisplayManager(void) :
	m_lda(70.0),
	m_ldmin(30.0),
	m_ldmax(100.0),
	m_correctGamma(false),
	m_gamma(0.4545)
{
}

tpDisplayManager::~tpDisplayManager(void)
{
}


void tpDisplayManager::Initialise(float lda, float ldmin, float ldmax, bool gamma, double gammaC)
{
	m_lda = lda;
	m_ldmin = ldmin;
	m_ldmax = ldmax;
	m_correctGamma = gamma;
	m_gamma = gammaC;
}

float tpDisplayManager::GetLuminanceAdaptation() const
{
	return m_lda;
}

float tpDisplayManager::GetLuminanceMax() const
{
	return m_ldmax;
}

float tpDisplayManager::GetLuminanceMin() const
{
	return m_ldmin;
}

void tpDisplayManager::SetLuminanceAdaptation(float L)
{
	m_lda = L;
}

void tpDisplayManager::SetLuminanceMax(float L)
{
	m_ldmax = L;
}

void tpDisplayManager::SetLuminanceMin(float L)
{
	m_ldmin = L;
}

void tpDisplayManager::SetGammaCorrected(bool v)
{
	m_correctGamma = v;
}

bool tpDisplayManager::isGammaCorrected() const
{
	return m_correctGamma;
}

double tpDisplayManager::GetGammaCorrection() const
{
	return m_gamma;
}

void tpDisplayManager::SetGammaCorrection(double v)
{
	m_gamma = v;
}
