#include "lecture10_notepad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Lecture10_Notepad w;
	w.show();
	return a.exec();
}
