#ifndef HDRCOMPOSER_H
#define HDRCOMPOSER_H

#include <QtGui/QMainWindow>
#include "ui_hdrcomposer.h"

class HDRComposer : public QMainWindow
{
	Q_OBJECT

public:
	HDRComposer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HDRComposer();

private:
	Ui::HDRComposerClass ui;
};

#endif // HDRCOMPOSER_H
