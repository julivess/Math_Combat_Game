#include "MathCombat.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// Загрузка стилей
	QFile styleFile("Resource/Style.qss");

	if (styleFile.open(QFile::ReadOnly)) {
		QString styleSheet = QLatin1String(styleFile.readAll());
		app.setStyleSheet(styleSheet);
		styleFile.close();
	}

	MathCombat w;
	w.show();
	return app.exec();
}
