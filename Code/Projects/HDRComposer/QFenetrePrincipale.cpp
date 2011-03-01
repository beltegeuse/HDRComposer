#include "QFenetrePrincipale.h"

// Include Qt
#include <QtGui/QFileDialog>
#include <QtCore/QString>

// Include projet
#include <tpImageIO.hpp>
#include <tpDynamicToneMappingManager.h>

#include "QDisplayConfig.h"
#include "QDynamicConfig.h"

QFenetrePrincipale::QFenetrePrincipale(void) :
	m_zoneCentrale(NULL),
	m_heightValue(1)
{

	// Creation de la zone centrale MDI
	m_zoneCentrale = new QWidgetCentral(this);
	setCentralWidget(m_zoneCentrale);

	// Creation dock
	QDockWidget *dock = new QDockWidget("Control Pannel", this);
	addDockWidget(Qt::RightDockWidgetArea, dock);

	// Creation de la zone droite (avec toutes les options pour les operateurs)
	m_panel = new QControlPanel(this);
	dock->setWidget(m_panel);
	
	CreationMenu();

	// Initialisation du slider
	m_slider = new QSlider(Qt::Horizontal,this);
	

	// Creation de la toolbar
	QToolBar *toolBarMix= addToolBar("Mix Value");
	toolBarMix->addWidget(m_slider);


	// Autres attributs de la fenetre
	setWindowTitle("HDRComposer");
    resize(800, 600);
	statusBar()->showMessage("Ready !");

	// Connexions
	QObject::connect(m_panel, SIGNAL(RefreshImage(int, tpImageColor*)), m_zoneCentrale, SLOT(RefreshImage(int,tpImageColor*)));

	// * Connexion du slider
	QObject::connect(m_slider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));	
	QObject::connect(m_slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved()));	
}

QFenetrePrincipale::~QFenetrePrincipale(void)
{
}

void QFenetrePrincipale::CreationMenu()
{
	// Creation des menu (branche principale)
	m_menuFichier = menuBar()->addMenu("&Fichier");
    m_menuEdition = menuBar()->addMenu("&Edition");

	// ==== Ajout des sous menu
	// Pour Fichier
	QAction *actionOuvrir = m_menuFichier->addAction("&Ouvrir...");
	QAction *actionQuitter = m_menuFichier->addAction("&Quitter");
	// Pour Edition
	QAction *actionDisplayConfig = m_menuEdition->addAction("&Display Config ...");
	QAction *actionDynamicConfig = m_menuEdition->addAction("&Dynamic Config ...");
	// Connection des slots
	connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(OuvrirFichier()));
	connect(actionDisplayConfig, SIGNAL(triggered()), this, SLOT(OuvrirDisplayConfig()));
	connect(actionDynamicConfig, SIGNAL(triggered()), this, SLOT(OuvrirDynamicConfig()));
}


void QFenetrePrincipale::OuvrirFichier()
{
	QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.hdr *.exr)");

	tpImageColorHDR image;

	if(!tpImageIO::readHDR(image,fichier.toStdString()))
	{
		QMessageBox::critical(this, "Erreur ouverture ...", "Impossible d'ouvrir le fichier : " + fichier);
	}
	else
	{
		m_heightValue = image.getHeight();
		emit LoadNewImage(&image);
	}
}

void QFenetrePrincipale::sliderReleased()
{
}

void QFenetrePrincipale::sliderMoved()
{
	m_zoneCentrale->SetMixValue(m_slider->value() / ((float)m_slider->maximum()));
}

void QFenetrePrincipale::OuvrirDisplayConfig()
{
	QDisplayConfig* d = new QDisplayConfig();
	d->show();

	QObject::connect(d, SIGNAL(Refresh()), m_panel, SLOT(RefreshToneMapping()));
}

void QFenetrePrincipale::OuvrirDynamicConfig()
{
	QDynamicConfig* d = new QDynamicConfig();
	d->show();

	QObject::connect(d, SIGNAL(Refresh()), m_panel, SLOT(RefreshToneMapping()));
}

void QFenetrePrincipale::MoveMouse(int x, int y)
{
	tpDynamicToneMappingManager::Instance()->SetPixel((m_heightValue - (y+1)),x);
	emit RefreshToneMapping();
	statusBar()->showMessage("Mouse : (" + QString::number(x) + "," + QString::number(y) + ") La : " + QString::number(tpDynamicToneMappingManager::Instance()->GetLuminanceAdaptation()));
}

