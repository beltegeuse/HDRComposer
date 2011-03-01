#pragma once

#include "tpImage.hpp"

class tpToneOperatorAbstract
{
private:
	// Attributs
	// * Parametres de gamma
	bool m_gammaCorrect;
	// * On est en quelle mode est l'operateur
	bool m_isDynamic;
	// * Modes
	bool m_isDynamicMode;

public:
	tpToneOperatorAbstract();
	virtual ~tpToneOperatorAbstract(void);

	// Methodes publiques
	// * Les modes de l'operateur
	bool isGammaCorrected() const;
	bool isDynamic() const;
	// * Si on met l'operateur en mode dynamic ou non
	void SetDynamicMode(bool v);
	bool isDynamicMode() const;
	// * Methode pour savoir si il est en train de faire du dynamic
	bool isDynamicActiveNow();

	// Virtual pure
	virtual void Compress(tpImageColorHDR& I) = 0;

protected:
	// Setter
	void SetGammaCorrected(bool v);
	void SetDynamic(bool v);
};
