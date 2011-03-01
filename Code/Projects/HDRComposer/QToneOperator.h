#pragma once

#include <QtGui>
#include <tpToneOperatorAbstract.h>

#include "QToneOperatorAbstract.h"

class QToneOperator : public QToneOperatorAbstract
{
	Q_OBJECT

private:
	// ==== Attributs
	QWidget* m_parent;
	QString m_name;

public:
	QToneOperator(QWidget* parent, const QString& name);
	~QToneOperator(void);

	virtual const QString& GetName() const;

private:
	// Pour connaitre quel operateur que l'on va charger
	void LoadOp(const QString& nom);
};
