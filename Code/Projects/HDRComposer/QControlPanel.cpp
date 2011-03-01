
#include "QControlPanel.h"
#include "ToneOperatorFactory.h"

#include <QMessageBox>

#include <Managers/tpDynamicToneMappingManager.h>
#include <Operations/tpImageConvert.hpp>

QControlPanel::QControlPanel(QWidget* parent) :
	QWidget(parent),
	m_parent(parent),
	m_choose(NULL),
	m_paramOp1(NULL),
	m_paramOp2(NULL)
{

	m_image.resize(1,1,true);

	InitializeWidget();

	QObject::connect(m_choose, SIGNAL(signalLoadOperator(QString, bool, QString, bool)), this, SLOT(slotLoadOperator(QString, bool, QString, bool)));	
	QObject::connect(parent, SIGNAL(LoadNewImage(tpImageColorHDR*)), this, SLOT(LoadNewImage(tpImageColorHDR*)));	
	QObject::connect(parent, SIGNAL(RefreshToneMapping()), this, SLOT(RefreshToneMapping()));

	show();
}

QControlPanel::~QControlPanel(void)
{
}

void QControlPanel::InitializeWidget()
{
	// Creation de la layout
	m_layout = new QVBoxLayout;

	// Creation des QWidget qui compose notre widget
	m_choose = new QChooseOperator(this);
	m_paramOp1 = ToneOperatorFactory::LoadOperator("Linear", this) ;
	m_paramOp2 = ToneOperatorFactory::LoadOperator("Linear", this);

	// Ajout a la layout
	m_layout->addWidget(m_choose);
	m_layout->addWidget(m_paramOp1);
	m_layout->addWidget(m_paramOp2);

	// On ajout la layout a notre QWidget
	setLayout(m_layout);
}

void QControlPanel::RemoveOperator(QToneOperatorAbstract** op, const QString& name, bool isUpper)
{
	if((*op)->GetName() != name)
	{
		if((*op) != NULL)
		{
			m_layout->removeWidget(*op);
			delete (*op);
		}

		(*op) = ToneOperatorFactory::LoadOperator(name, this);

		if(isUpper)
		{
			m_layout->insertWidget(1,*op);
		}
		else
		{
			m_layout->addWidget(*op);
		}
	}
}

void QControlPanel::slotLoadOperator(QString nameOp1, bool dynamic1, QString nameOp2, bool dynamic2)
{
	// ==== Param1
	RemoveOperator(&m_paramOp1, nameOp1, true);
	m_paramOp1->GetOperator()->SetDynamicMode(dynamic1);
	m_paramOp1->Compress(m_image);
	
	
	// ==== Param2
	RemoveOperator(&m_paramOp2, nameOp2, false);
	m_paramOp2->GetOperator()->SetDynamicMode(dynamic2);
	m_paramOp2->Compress(m_image);
}


void QControlPanel::LoadNewImage(tpImageColorHDR* image)
{
	// On garde bien la copie
	m_image.copy(*image);

	// On converti pour notre manager
	tpImageLuminanceHDR I;
	tpImageConvert::createLuminanceImage(*image, I);
	tpDynamicToneMappingManager::Instance()->SetImage(I);

	// Puis on les applique aux operateurs
	ApplyImage(*image, m_paramOp1);
	ApplyImage(*image, m_paramOp2);
}

void QControlPanel::ApplyImage(tpImageColorHDR& image, QToneOperatorAbstract* widget)
{
	if(widget == NULL)
		return;

	widget->Compress(image);
}

void QControlPanel::RefreshImage(QToneOperatorAbstract* source)
{
	//QMessageBox::information(this, "Debug", "QControlPanel::RefreshImage");

	if(m_paramOp1 == source)
	{
		emit RefreshImage(0, source->GetImage());
	}
	else if(m_paramOp2 == source)
	{
		emit RefreshImage(1, source->GetImage());
	}
	else
	{
		QMessageBox::critical(this, "Source inconnue", "Demande de RefreshImage provenant d'une source inconnue.");
	}
}

void QControlPanel::RefreshToneMapping()
{
	if(m_paramOp1->GetOperator()->isDynamicActiveNow())
	{
		//QMessageBox::critical(this, "Debug", "Update !");
		m_paramOp1->Compress(m_image);
	}
	
	if(m_paramOp2->GetOperator()->isDynamicActiveNow())
	{
		//QMessageBox::critical(this, "Debug", "Update !");
		m_paramOp2->Compress(m_image);
	}
}

