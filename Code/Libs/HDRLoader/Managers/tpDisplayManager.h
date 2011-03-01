#pragma once

#include "tpSingleton.h"

class TP_EXPORT tpDisplayManager : public tpSingleton<tpDisplayManager>
{
private:
	// ==== Attributs
	float m_lda;
	float m_ldmin;
	float m_ldmax;
	
	bool m_correctGamma;
	double m_gamma;

public:
	// ==== Methodes publiques
	// * Initialiser
	void Initialise(float lda, float ldmin, float ldmax, bool gamma = false, double gammaC = 0.4545);

	// * Accesseurs
	float GetLuminanceAdaptation() const;
	float GetLuminanceMax() const;
	float GetLuminanceMin() const;
	bool isGammaCorrected() const;
	double GetGammaCorrection() const;

	void SetLuminanceAdaptation(float L);
	void SetLuminanceMax(float L);
	void SetLuminanceMin(float L);
	void SetGammaCorrected(bool v);
	void SetGammaCorrection(double v);

private:
	friend class tpSingleton<tpDisplayManager>;
	// ==== Constructeurs et destructeurs en prive
	tpDisplayManager(void);
	~tpDisplayManager(void);
};
