#include "QToneOperatorFormAbstract.h"

QToneOperatorFormAbstract::QToneOperatorFormAbstract(QWidget* parent, const QString& name) :
	QToneOperatorAbstract(parent),
	m_name(name)
{
	m_layout = new QFormLayout;

	// Creation du button
	m_bValid = new QPushButton("Valid", this);

	// Construction de la layout principale
	QVBoxLayout *layoutPrincipale = new QVBoxLayout;
	layoutPrincipale->addLayout(m_layout);
	layoutPrincipale->addWidget(m_bValid);

	setLayout(layoutPrincipale);

	// Connexions
	QObject::connect(m_bValid, SIGNAL(clicked()), (QToneOperatorFormAbstract*)this, SLOT(slotValid()));	
}

QToneOperatorFormAbstract::~QToneOperatorFormAbstract(void)
{
}

void QToneOperatorFormAbstract::slotValid()
{
	ValidPushed();
	UpdateCompress();
}

QFormLayout* QToneOperatorFormAbstract::GetFormLayout()
{
	return m_layout;
}


const QString& QToneOperatorFormAbstract::GetName() const
{
	return m_name;
}
