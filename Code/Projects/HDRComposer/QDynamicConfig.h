#ifndef QDYNAMICCONFIG_H
#define QDYNAMICCONFIG_H

#include <QWidget>
#include "ui_QDynamicConfig.h"

#include <map>

#include <tpDynamicToneMappingManager.h>

class QDynamicConfig : public QWidget
{
	Q_OBJECT

public:
	QDynamicConfig(QWidget *parent = 0);
	~QDynamicConfig();

private:
	Ui::QDynamicConfigClass ui;

	typedef std::map<QString, tpDynamicToneMappingManager::TypeMethode> ComboMethodeMap;
	ComboMethodeMap m_map;

private slots:
	void Apply();

signals:
	void Refresh();

};

#endif // QDYNAMICCONFIG_H
