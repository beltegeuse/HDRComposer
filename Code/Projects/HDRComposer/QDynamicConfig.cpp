#include "QDynamicConfig.h"

#include <QMessageBox>

QDynamicConfig::QDynamicConfig(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Initialisation de la map qui va nous servir de lien entre QComboBox et le type
	m_map["Gaussian"] = tpDynamicToneMappingManager::Gaussian;
	m_map["Constant"] = tpDynamicToneMappingManager::Constant;

	// On met la bonne valeur dans le champs rayon
	ui.rayonSpinBox->setValue(tpDynamicToneMappingManager::Instance()->GetRayon());

	// On choisi le bon mode
	ComboMethodeMap::iterator it = m_map.begin();
	while(it != m_map.end())
	{
		if(tpDynamicToneMappingManager::Instance()->GetMethode() == it->second)
		{
			int indice = ui.typeComboBox->findText(it->first);
			if(indice == -1)
			{
				QMessageBox::critical(this, "Initialisation", "Impossible de trouver le blinding de : " + it->first);
			}
			else
			{
				ui.typeComboBox->setCurrentIndex(indice);
			}

			break;
		}

		++it;
	}

	// On met la bonne valeur dans la ponderation
	ui.ponderationDoubleSpinBox->setValue(tpDynamicToneMappingManager::Instance()->GetPonderation());

	// On met si on calibre ou non
	ui.calibrationCheckBox->setCheckState((tpDynamicToneMappingManager::Instance()->isNeedCalibration() ? Qt::Checked : Qt::Unchecked));

	// On connect ! 
	QObject::connect(ui.bApply, SIGNAL(clicked()), this, SLOT(Apply()));
	QObject::connect(ui.bApply, SIGNAL(clicked()), this, SLOT(close()));
}

QDynamicConfig::~QDynamicConfig()
{

}

void QDynamicConfig::Apply()
{
	tpDynamicToneMappingManager::Instance()->SetRayon(ui.rayonSpinBox->value());
	tpDynamicToneMappingManager::Instance()->SetPonderation(ui.ponderationDoubleSpinBox->value());

	ComboMethodeMap::iterator it = m_map.find(ui.typeComboBox->currentText());
	if(it != m_map.end())
	{
		tpDynamicToneMappingManager::Instance()->SetMethode(it->second);
	}
	else
	{
		QMessageBox::critical(this, "Initialisation", "Impossible de trouver le blinding pour : " + ui.typeComboBox->currentText());
	}

	tpDynamicToneMappingManager::Instance()->SetCalibration(ui.calibrationCheckBox->checkState() == Qt::Checked);

	emit Refresh();
}
