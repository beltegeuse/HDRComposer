#include "QImageLabel.h"
#include <QMessageBox>
#include <QMouseEvent>

QImageLabel::QImageLabel(QWidget *parent)
	: QLabel(parent),
	m_factorX(1.0),
	m_factorY(1.0)
{

}

QImageLabel::~QImageLabel()
{

}

void QImageLabel::UpdateImage(const QImage& I)
{
	setPixmap( QPixmap::fromImage(I, Qt::AutoColor) );
	setAlignment(Qt::AlignCenter);
}

void QImageLabel::mousePressEvent ( QMouseEvent * ev  )
{
	QLabel::mousePressEvent(ev);
	//emit ClickedMouse(ev->x(), ev->y());
}

void QImageLabel::mouseMoveEvent ( QMouseEvent * ev  )
{
	QLabel::mouseMoveEvent(ev);
	if(ev->buttons()==Qt::LeftButton)
	{
		emit ClickedMouse(ev->x()*m_factorX, ev->y()*m_factorY);
	}
}

void QImageLabel::SetFactor(float x, float y)
{
	m_factorX = x;
	m_factorY = y;
}

