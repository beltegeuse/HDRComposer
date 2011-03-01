#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H

#include <QLabel>

class QImageLabel : public QLabel
{
	Q_OBJECT
private:
	float m_factorX;
	float m_factorY;

public:
	QImageLabel(QWidget *parent);
	~QImageLabel();

	void UpdateImage(const QImage& I);
	void SetFactor(float x, float y);

protected:
	virtual void mousePressEvent ( QMouseEvent * ev  );
	virtual void mouseMoveEvent ( QMouseEvent * ev  );
signals:
	void ClickedMouse(int x, int y);
};

#endif // QIMAGELABEL_H
