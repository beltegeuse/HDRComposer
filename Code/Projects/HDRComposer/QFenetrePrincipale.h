#pragma once

#include <QtGui>
#include "QWidgetCentral.h"
#include "QControlPanel.h"
#include <tpImageIO.hpp>

class QFenetrePrincipale : public QMainWindow
{
	 Q_OBJECT

public:
	QFenetrePrincipale(void);
	~QFenetrePrincipale(void);

signals:
	// Chargement d'une nouvelle image
	void LoadNewImage(tpImageColorHDR* image);
	void RefreshToneMapping();

private slots:
	void OuvrirFichier();
	void OuvrirDisplayConfig();
	void OuvrirDynamicConfig();
public slots:
	// Les slots
	void sliderReleased();
	void sliderMoved();
	void MoveMouse(int x, int y);

private:
	// ==== Methodes privee
	void CreationMenu();

private:
	// ==== Attributs
	// Mdi area
	QWidgetCentral *m_zoneCentrale;
	// MenuBar
	QMenu *m_menuFichier;
    QMenu *m_menuEdition;
	// Right panel
	QControlPanel* m_panel;
	// Le silder
	QSlider* m_slider;

	int m_heightValue;
};
