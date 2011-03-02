
#include "QChooseOperator.h"

#include <QMessageBox>
#include <iostream>

QChooseOperator::QChooseOperator(QWidget* parent) :
	QFrame(parent),
	m_parent(parent)
{
	setFrameShape(QFrame::StyledPanel);

	// Create layout general
	QVBoxLayout *layout = new QVBoxLayout;

	// Create layout buttom
	QGridLayout* layoutChoice = new QGridLayout;

	// Create comboBox
	m_combo1 = new QComboBox(this);
	m_combo2 = new QComboBox(this);
	
	InitializeCombo(m_combo1);
	InitializeCombo(m_combo2);

	// Create checkBox
	m_check1 = new QCheckBox(this);
	m_check2 = new QCheckBox(this);

	// Build layout
	layoutChoice->addWidget(new QLabel("Operateur 1 :"),0,0);
	layoutChoice->addWidget(m_combo1,0,1);
	layoutChoice->addWidget(m_check1,0,2);
	layoutChoice->addWidget(new QLabel("Operateur 2 :"),1,0);
	layoutChoice->addWidget(m_combo2,1,1);
	layoutChoice->addWidget(m_check2,1,2);

	// On ajoute notre layout a la principale
	layout->addLayout(layoutChoice);

	// Create bottom
	m_bValib = new QPushButton("Valid");
	layout->addWidget(m_bValib);

	QObject::connect(m_bValib, SIGNAL(clicked()), this, SLOT(slotValid()));	

	// Add layout
	setLayout(layout);
}

QChooseOperator::~QChooseOperator(void)
{
}

void QChooseOperator::InitializeCombo(QComboBox* c)
{
	c->addItem("Ashikhim");
    c->addItem("Chiu");
	c->addItem("Filmic");
	c->addItem("Linear");
	c->addItem("Log");
	c->addItem("Photographic Burn");
	c->addItem("Photographic Local");
	c->addItem("Retinex");
	c->addItem("Schlick");
	c->addItem("Durand Slow");
	c->addItem("Durand Fast");
	// Les operateurs dynamics
	c->addItem("Photographic (*)");
	c->addItem("Exp (*)");
	c->addItem("Thumblin (*)");
	c->addItem("Filmic Dynamic (*)");
	c->addItem("Ward (*)");
	c->addItem("Drago (*)");
	c->addItem("Sigmoid (*)");
}

void QChooseOperator::slotValid()
{
	std::cout << "[Info] [Slot] Valid : Called ! " << std::endl;

	// Probleme si les deux operateur sont equivalents
	if(m_combo1->currentText() == m_combo2->currentText() && (m_check1->isChecked() == m_check2->isChecked()))
	{
		QMessageBox::critical(this, "Operator Choose", "Impossible de choisir deux fois le même operateur.");
	}
	else
	{
		emit signalLoadOperator(
			m_combo1->currentText(), m_check1->isChecked(),
			m_combo2->currentText(), m_check2->isChecked());
	}
}
