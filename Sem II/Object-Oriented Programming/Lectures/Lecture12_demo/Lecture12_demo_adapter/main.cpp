#include "lecture12_demo_adapter.h"
#include <QtWidgets/QApplication>
#include "Controller.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Controller ctrl;
	ctrl.addCastle("Highclere Castle", "highclere.jpg", "England", 4, 4);
	ctrl.addCastle("Chambord Castle", "chambord.jpg", "France", 3.2, 3.2);
	ctrl.addCastle("Windsor Castle", "windsor.jpg", "England", 5.8, 5.8);
	ctrl.addCastle("Scaliger Castle", "scalinger.jpg", "Italy", 2.9, 2.9);

	Lecture12_demo_Adapter w{ ctrl };
	w.show();
	
	return a.exec();
}
