
#include "QWidgetCentral.h"

QWidgetCentral::QWidgetCentral(QWidget* parent) :
	QWidget(parent),
	m_parent(parent),
	m_mix_value(0.5),
	m_width(1024),
	m_height(768)
{
	// Garde fou
	m_imDb = false;
	m_imGb = false;

    QHBoxLayout *layout = new QHBoxLayout;
	m_label = new QImageLabel(this);
	layout->addWidget(m_label,0,Qt::AlignCenter);
	setLayout(layout);


	m_imCentral = QImage("no_image.jpg");

	m_label->UpdateImage(m_imCentral);

	//  === Connexions
	QObject::connect(m_label, SIGNAL(ClickedMouse(int,int)), parent , SLOT(MoveMouse(int,int)));	
}

QWidgetCentral::~QWidgetCentral(void)
{
}

void QWidgetCentral::RefreshImage(int id, tpImageColor* image)
{
	//QMessageBox::information(this, "Debug", "QWidgetCentral::RefreshImage");
	if(id == 1)
	{
		FillImageFromTpImage(m_imD, *image);
		m_imDb = true;
	}
	else if(id == 0)
	{
		FillImageFromTpImage(m_imG, *image);
		m_imGb = true;
	}
	else
	{
		QMessageBox::critical(this, "FillImage", "Impossible de connaitre la source.");
		return;
	}

	MixImages();
	m_label->UpdateImage(m_imCentral);
}

void QWidgetCentral::FillImageFromTpImage(QImage& image, const tpImageColor& tpIm)
{
	// On met a la bonne taille
	image = QImage(tpIm.getWidth(), tpIm.getHeight(), QImage::Format_ARGB32);

	for (int y = 0; y < image.height(); y++) 
	{
		QRgb* rgb = (QRgb*)image.scanLine(image.height()-(y+1)); // Il faut que l'image soit en ARGB32 (je pense, voir la doc)
		for (int x = 0; x < image.width(); x++) 
		{
			rgb[x] = qRgba(tpIm[y][x].r, tpIm[y][x].g, tpIm[y][x].b, 255);
		}
	}

	image = image.scaled(m_width,m_height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	
	m_label->SetFactor(tpIm.getHeight() / (float)image.height(), tpIm.getWidth() / (float)image.width());
}

void QWidgetCentral::MixImages()
{
	if(!(m_imDb && m_imGb))
	{
		return;
	}

	// On met a la bonne taille
	m_imCentral = QImage(std::min(m_imD.width(),m_imG.width()),std::min(m_imD.height(),m_imG.height()), QImage::Format_ARGB32);

	int indice = (int)(m_mix_value*m_imD.width());

	for (int y = 0; y < m_imCentral.height(); y++) 
	{
		QRgb* rgb = (QRgb*)m_imCentral.scanLine(m_imCentral.height()-(y+1));
		QRgb* rgbD = (QRgb*)m_imD.scanLine(m_imCentral.height()-(y+1)); // Il faut que l'image soit en ARGB32 (je pense, voir la doc)
		QRgb* rgbG = (QRgb*)m_imG.scanLine(m_imCentral.height()-(y+1));

		for (int x = 0; x < m_imCentral.width(); x++) 
		{
			if(x < indice)
			{
				rgb[x] = qRgba(qRed(rgbG[x]), qGreen(rgbG[x]), qBlue(rgbG[x]), 255);
			}
			else
			{
				rgb[x] = qRgba(qRed(rgbD[x]), qGreen(rgbD[x]), qBlue(rgbD[x]), 255);
			}
		}
	}
}

void QWidgetCentral::SetMixValue(float value)
{
	Assert(value >= 0 && value <= 1);
	m_mix_value = value;

	MixImages();
	m_label->UpdateImage(m_imCentral);
}

