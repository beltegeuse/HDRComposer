#pragma once

#include "tpImage.hpp"
#include "ToneOperators/tpToneOperatorAbstract.h"

#include <QtGui>

class QToneOperatorAbstract : public QFrame
{
	Q_OBJECT

protected:
	// * Pour sauvegarder quelques images
	tpImageColor m_image;
	tpImageColorHDR m_imageHDR;
	tpToneOperatorAbstract* m_operator;

public:
	// Constructeur et destructeur
	QToneOperatorAbstract(QWidget* parent);
	virtual ~QToneOperatorAbstract();

	// Methodes publiques
	tpImageColor* GetImage();
	virtual void Compress(const tpImageColorHDR& I);
	void UpdateCompress();
	virtual tpToneOperatorAbstract* GetOperator();

	// Methodes virtuelles pure
	virtual const QString& GetName() const= 0;

signals:
	void RefreshImage(QToneOperatorAbstract* src);
};