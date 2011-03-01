#pragma once

#include <QtGui>
#include <tpImage.hpp>

#include "QImageLabel.h"

class QWidgetCentral : public QWidget 
{
	Q_OBJECT

private:
	QImageLabel* m_label;

	// ==== Attributs
	QWidget * m_parent;

	// * La pixmapCentral
	QImage m_imCentral;

	// * Les pixmap temporaires
	QImage m_imD;
	bool m_imDb;
	QImage m_imG;
	bool m_imGb;

	// * Valeur de mix
	float m_mix_value;

	// * Les tailles max
	int m_width;
	int m_height;

public:
	// ==== Constructeur et destructeur
	QWidgetCentral(QWidget* parent);
	~QWidgetCentral(void);

	// ==== Certaines methodes ....
	void SetMixValue(float value);


public slots:
	void RefreshImage(int id, tpImageColor* image);

private:
	void UpdateImage();
	void FillImageFromTpImage(QImage& image, const tpImageColor& tpImage);
	void MixImages();

};
