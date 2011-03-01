// Include Qt
#include <QtGui/QPushButton>
// Include Projet
#include <QFenetrePrincipale.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFenetrePrincipale fen;
	fen.show();

	return app.exec();
}
