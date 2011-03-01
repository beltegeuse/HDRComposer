#pragma once

#include <QtGui>
#include <map>

class QChooseOperator : public QFrame
{

	Q_OBJECT

private:
	// ==== Attributs
	QWidget* m_parent;
	QComboBox* m_combo1;
	QComboBox* m_combo2;
	QPushButton * m_bValib;
	QCheckBox* m_check1;
	QCheckBox* m_check2;

public:
	// ==== Constructeur et destructeur
	QChooseOperator(QWidget* parent);
	virtual ~QChooseOperator(void);

private:
	void InitializeCombo(QComboBox* box);

public slots:
	void slotValid();

signals:
	void signalLoadOperator(QString nameOp1, bool dynamic1, QString nameOp2, bool dynamic2);
};
