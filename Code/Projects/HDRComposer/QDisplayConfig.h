#ifndef QDISPLAYCONFIG_H
#define QDISPLAYCONFIG_H

#include <QWidget>
#include <ui_QDisplayConfig.h>

class QDisplayConfig : public QWidget
{
	Q_OBJECT

private:
	Ui::QDisplayConfigClass ui;

public:
	// ==== Constructeurs et destructeurs
	QDisplayConfig(QWidget *parent = 0);
	~QDisplayConfig();

private:
	void LoadValues();

private slots:
	void Cancel();
	void Apply();

signals:
	void Refresh();
};

#endif // QDISPLAYCONFIG_H
