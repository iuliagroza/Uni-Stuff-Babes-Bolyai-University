#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

int main(int argc, char* argv[])
{
	QApplication a{ argc, argv };
	QLabel label{ "Hello world!" };
	label.show();
	return a.exec();
}