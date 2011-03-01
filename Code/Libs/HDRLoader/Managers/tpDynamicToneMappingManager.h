#pragma once

#include "tpSingleton.h"
#include "tpImage.hpp"
#include "Operations/tpImageFilter.hpp"

class tpDynamicToneMappingManager : public tpSingleton<tpDynamicToneMappingManager>
{
public:
	enum TypeMethode
	{
		Gaussian,
		Constant
	};


private:
	// Attributs
	
	// * Les parametres de calcul de la luminance d'adaptation
	int m_rayon;
	TypeMethode m_methode;
	tpFilter m_filtre;
	double m_ponderation;
	
	// * Stockage des informations sur l'image
	tpImageLuminanceHDR m_image;
	double m_laImage;
	int m_x, m_y;
	
	// * Cache du calcul
	double m_La;

	// * Pour savoir si on doit calibrer ou non
	bool m_calib;

	// * Pour appliquer un gaussien
	tpImageLuminanceHDR m_imageCache;

public:
	// Pour modifier les parametres de notre manager
	void SetImage(const tpImageLuminanceHDR& I);
	void SetPixel(int x, int y);
	void SetRayon(int v);
	void SetMethode(TypeMethode m);
	void SetPonderation(double v);
	void SetCalibration(bool v);

	// Pour recuperer des informations sur le point cible
	int GetX() const;
	int GetY() const;
	
	// Pour recuperer les informations de luminances
	double GetLuminanceAdaptation() const;
	double GetPonderation() const;

	// Pour recuperer les parametres de calcul de la luminance d'adaptation
	int GetRayon() const;
	TypeMethode GetMethode() const;

	// Modification du Gaussien
	void ResetModification(bool recompute = true);
	void BlurImage(int taille);

	// Autre
	bool isNeedCalibration() const;

private:
	friend class tpSingleton<tpDynamicToneMappingManager>;

	tpDynamicToneMappingManager(void);
	~tpDynamicToneMappingManager(void);

	void UpdateFilter();
	void ComputeLuminance();
};
