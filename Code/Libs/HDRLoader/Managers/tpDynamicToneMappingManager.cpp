#include "StdAfx.h"
#include "Managers/tpDynamicToneMappingManager.h"
#include "Operations/tpOperations.h"
#include "Operations/tpHDROperations.h"
#include "Operations/tpImageConvert.hpp"
#include "tpMath.h"

#include <math.h>
#include <cmath>

tpDynamicToneMappingManager::tpDynamicToneMappingManager(void) :
	m_x(0),
	m_y(0),
	m_La(0.5),
	m_rayon(0),
	m_methode(tpDynamicToneMappingManager::Constant),
	m_ponderation(0.0),
	m_calib(true)
{
	m_image.resize(1,1,true);
	m_filtre.resize(1,1);
	m_filtre[0][0] = 1.0;
}

tpDynamicToneMappingManager::~tpDynamicToneMappingManager(void)
{
}

void tpDynamicToneMappingManager::SetImage(const tpImageLuminanceHDR& I)
{
	m_image.copy(I);
	tpImageConvert::Calibration(m_image);
	m_imageCache.copy(m_image);

	// On met a jour les coordonnee de pixels
	m_x = std::max(0,std::min((int)m_image.getHeight()-1, m_x));
	m_y = std::max(0,std::min((int)m_image.getWidth()-1, m_y));

	m_laImage = tpHDROperations::GetMean(m_image);

	ComputeLuminance();
}

void tpDynamicToneMappingManager::SetPixel(int x, int y)
{
	m_x = x;
	m_y = y;

	// On fait attentions aux valeurs
	m_x = std::max(0,std::min((int)m_image.getHeight()-1, m_x));
	m_y = std::max(0,std::min((int)m_image.getWidth()-1, m_y));

	ComputeLuminance();
}

void tpDynamicToneMappingManager::ResetModification(bool recompute)
{
	m_image.copy(m_imageCache);

	if(recompute)
	{
		ComputeLuminance();
	}
}

void tpDynamicToneMappingManager::BlurImage(int taille)
{
	ResetModification(false);

	tpFilter g = tpMath::GaussianKernel2D(taille);
	tpFilterResultDouble res;

	tpImageFilter::ApplyFilter(m_image, res, g);

	m_image.copy(res);
	
	ComputeLuminance();
}

int tpDynamicToneMappingManager::GetX() const
{
	return m_x;
}

int tpDynamicToneMappingManager::GetY() const
{
	return m_y;
}

double tpDynamicToneMappingManager::GetLuminanceAdaptation() const
{
	return m_La;
}

void tpDynamicToneMappingManager::ComputeLuminance()
{
	m_La = 0.0;
	
	// TODO: Attention filtre carre
	int demiSize = m_filtre.getHeight() / 2;

	for(int i = 0; i < m_filtre.getHeight(); i++)
	{
		for(int j = 0; j < m_filtre.getWidth(); j++)
		{
			int im = std::max(0, std::min(((int)m_image.getHeight()) - 1,m_x + i - demiSize) );
			int jm = std::max(0, std::min(((int)m_image.getWidth()) - 1,m_y + j - demiSize) );

			m_La += m_filtre[i][j]*m_image[im][jm];
		}
	}

	m_La = m_laImage * m_ponderation + m_La * (1 - m_ponderation);
}

void tpDynamicToneMappingManager::SetRayon(int v)
{
	m_rayon = v;

	UpdateFilter();
	ComputeLuminance();
}

void tpDynamicToneMappingManager::SetMethode(tpDynamicToneMappingManager::TypeMethode m)
{
	m_methode = m;

	UpdateFilter();
	ComputeLuminance();
}

int tpDynamicToneMappingManager::GetRayon() const
{
	return m_rayon;
}

tpDynamicToneMappingManager::TypeMethode tpDynamicToneMappingManager::GetMethode() const
{
	return m_methode;
}

void tpDynamicToneMappingManager::UpdateFilter()
{
	if(m_methode == Gaussian)
	{
		m_filtre = tpMath::GaussianKernel2D(2*m_rayon + 1);
	}
	else if(m_methode == Constant)
	{
		m_filtre = tpMath::ConstantKernel2D(2*m_rayon + 1);
	}
}

void tpDynamicToneMappingManager::SetPonderation(double v)
{
	m_ponderation = v;
}

double tpDynamicToneMappingManager::GetPonderation() const
{
	return m_ponderation;
}

bool tpDynamicToneMappingManager::isNeedCalibration() const
{
	return m_calib;
}

void tpDynamicToneMappingManager::SetCalibration(bool v)
{
	m_calib = v;
}

