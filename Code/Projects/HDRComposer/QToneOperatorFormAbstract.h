#pragma once

#include "QToneOperatorAbstract.h"

class QToneOperatorFormAbstract : public QToneOperatorAbstract
{
	Q_OBJECT

private:
	QPushButton* m_bValid;
	QFormLayout *m_layout;
	QString m_name;

public:
	QToneOperatorFormAbstract(QWidget* parent, const QString& name);
	virtual ~QToneOperatorFormAbstract(void);

protected:
	virtual void ValidPushed() = 0;
	QFormLayout* GetFormLayout();
	virtual const QString& GetName() const;

public slots:
	void slotValid();

};
