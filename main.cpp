#include "MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QFont font = app.font();
	font.setPointSize(14);
	font.setHintingPreference(QFont::PreferFullHinting);
	app.setFont(font);

	MainWindow window;
	window.show();

	return app.exec();
}
