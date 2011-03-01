#include "QToneOperatorAbstract.h"

#include "Operations/tpOperations.h"
#include "Operations/tpImageConvert.hpp"
#include "tpImage.hpp"
#include "Managers/tpDisplayManager.h"

QToneOperatorAbstract::QToneOperatorAbstract(QWidget* parent) :
	QFrame(parent),
	m_operator(NULL)
{
	setFrameShape(QFrame::StyledPanel);

	m_imageHDR.resize(1,1,true);

	QObject::connect(this, SIGNAL(RefreshImage(QToneOperatorAbstract*)), parent, SLOT(RefreshImage(QToneOperatorAbstract*)));	
}

QToneOperatorAbstract::~QToneOperatorAbstract()
{
	if(m_operator != NULL)
	{
		delete m_operator;
	}
}

tpImageColor* QToneOperatorAbstract::GetImage()
{
	return &m_image;
}

void QToneOperatorAbstract::Compress(const tpImageColorHDR& I)
{
	if(m_operator == NULL)
	{
		QMessageBox::critical(this, "Erreur", "Impossible de compress avec operateur NULL");
		return;
	}

	m_imageHDR.copy(I);

	tpImageColorHDR temp;
	temp.copy(m_imageHDR);

	// On compress le tout
	m_operator->Compress(temp);

	// Puis on calcul la nouvelle image couleur
	tpImageConvert::createColorImage(temp, m_image);

	// On fait la correction gamma
	if(!m_operator->isGammaCorrected() && (!tpDisplayManager::Instance()->isGammaCorrected()) )
	{
		tpOperations::CorrectGamma(m_image);
	}

	emit RefreshImage(this);
}

tpToneOperatorAbstract* QToneOperatorAbstract::GetOperator()
{
	return m_operator;
}

void QToneOperatorAbstract::UpdateCompress()
{
	if(m_operator == NULL)
	{
		QMessageBox::critical(this, "Erreur", "Impossible de compress avec operateur NULL");
		return;
	}

	tpImageColorHDR temp;
	temp.copy(m_imageHDR);

	// On compress le tout
	m_operator->Compress(temp);

	// Puis on calcul la nouvelle image couleur
	tpImageConvert::createColorImage(temp, m_image);

	// On fait la correction gamme
	if(!m_operator->isGammaCorrected() && (!tpDisplayManager::Instance()->isGammaCorrected()) )
	{
		tpOperations::CorrectGamma(m_image);
	}

	emit RefreshImage(this);
}



