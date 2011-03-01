#include "QDisplayConfig.h"
#include <Managers/tpDisplayManager.h>
#include <QMessageBox>
QDisplayConfig::QDisplayConfig(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	// Connections
	QObject::connect(ui.bApply, SIGNAL(clicked()), this, SLOT(Apply()));
	QObject::connect(ui.bCancel, SIGNAL(clicked()), this, SLOT(Cancel()));
	QObject::connect(ui.bApply, SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(ui.bCancel, SIGNAL(clicked()), this, SLOT(close()));

	LoadValues();
}

QDisplayConfig::~QDisplayConfig()
{

}

void QDisplayConfig::Cancel()
{
}


void QDisplayConfig::Apply()
{
	tpDisplayManager::Instance()->SetGammaCorrected(ui.gammaCorrectedCheckBox->checkState() == Qt::Checked || ui.gammaCorrectedCheckBox->checkState() == Qt::PartiallyChecked);
	tpDisplayManager::Instance()->SetLuminanceAdaptation(ui.luminanceAdaptationDoubleSpinBox->value());
	tpDisplayManager::Instance()->SetLuminanceMax(ui.luminanceMaxDoubleSpinBox->value());
	tpDisplayManager::Instance()->SetLuminanceMin(ui.luminanceMinDoubleSpinBox->value());
	tpDisplayManager::Instance()->SetGammaCorrection(ui.gammaCorrectionDoubleSpinBox->value());

	emit Refresh();
}

void QDisplayConfig::LoadValues()
{
	ui.luminanceAdaptationDoubleSpinBox->setValue(tpDisplayManager::Instance()->GetLuminanceAdaptation());
	ui.luminanceMaxDoubleSpinBox->setValue(tpDisplayManager::Instance()->GetLuminanceMax());
	ui.luminanceMinDoubleSpinBox->setValue(tpDisplayManager::Instance()->GetLuminanceMin());
	ui.gammaCorrectionDoubleSpinBox->setValue(tpDisplayManager::Instance()->GetGammaCorrection());
	ui.gammaCorrectedCheckBox->setCheckState((tpDisplayManager::Instance()->isGammaCorrected() ? Qt::Checked : Qt::Unchecked));
}
