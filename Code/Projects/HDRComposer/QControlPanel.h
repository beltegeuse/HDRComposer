#pragma once

#include <QtGui>

#include "QChooseOperator.h"
#include "QToneOperator.h"
#include "QToneOperatorAbstract.h"

class QToneOperator;

class QControlPanel : public QWidget
{
	Q_OBJECT
	
private:
	// ==== Attributs
	QWidget* m_parent;
	QVBoxLayout *m_layout;
	// * Les QWidget qui compose le pannel
	QChooseOperator* m_choose;
	QToneOperatorAbstract* m_paramOp1;
	QToneOperatorAbstract* m_paramOp2;

	tpImageColorHDR m_image;

public:
	// ==== Constructeur et destructeur
	QControlPanel(QWidget* parent);
	~QControlPanel(void);

private:
	void InitializeWidget();
	void ApplyImage(tpImageColorHDR& image, QToneOperatorAbstract* widget);
	void RemoveOperator(QToneOperatorAbstract** op, const QString& name, bool isUpper);

public slots:
	void slotLoadOperator(QString nameOp1, bool dynamic1, QString nameOp2, bool dynamic2);
	void LoadNewImage(tpImageColorHDR* image);
	void RefreshImage(QToneOperatorAbstract* source);
	void RefreshToneMapping();

signals:
	void RefreshImage(int id, tpImageColor* image);
};
