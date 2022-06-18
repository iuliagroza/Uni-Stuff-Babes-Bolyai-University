#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QFormLayout>

int editExample(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget w{};
	QLineEdit lineEdit;
	QLabel label("&Hello :)");
	label.setBuddy(&lineEdit);
	QVBoxLayout layout{ &w };
	layout.addWidget(&label);
	layout.addWidget(&lineEdit);
	w.show();

	return a.exec();
}

int buttonExample(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// button - example
	QPushButton button("&This is a button.\nPush it!");

	// set tooltip
	button.setToolTip("Look! I'm a button!");
	button.setToolTipDuration(2000);

	// set font
	QFont font("Courier", 50, 10, true);
	button.setFont(font);

	// set background image
	QIcon icon("Peacock.JPG");
	button.setIcon(icon);
	button.setIconSize(QSize(400, 400));

	button.show();

	return a.exec();
}

int listExample(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QListWidget list;
	new QListWidgetItem("Gone With the Wind", &list);
	new QListWidgetItem("The Three Musketeers", &list);

	// add a QListWidgetItem, with a different font
	QListWidgetItem *item3 = new QListWidgetItem("The Wizard of Oz");
	QFont font("Courier", 20, 10, true);
	item3->setFont(font);
	list.insertItem(0, item3);
	
	list.show();

	return a.exec();
}

int hBoxLayout(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget wnd{};
	QHBoxLayout hLay{};
	QPushButton btn1{ "Button 1" };
	QPushButton btn2{ "Button 2" };
	QPushButton btn3{ "Button 3" };
	hLay.addWidget(&btn1);
	hLay.addWidget(&btn2);
	hLay.addWidget(&btn3);
	wnd.setLayout(&hLay);
	wnd.show();

	return a.exec();
}

int vBoxLayout(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget *wnd = new QWidget{};
	QVBoxLayout *vLay = new QVBoxLayout{};
	QPushButton *btn1 = new QPushButton{ "Button 1" };
	QPushButton *btn2 = new QPushButton{ "Button 2" };
	QPushButton *btn3 = new QPushButton{ "Button 3" };
	vLay->addWidget(btn1);
	vLay->addWidget(btn2);
	vLay->addWidget(btn3);
	wnd->setLayout(vLay);
	wnd->show();

	return a.exec();
}

int formLayout(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFormLayout *formLayout = new QFormLayout{};

	// create labels and textboxes
	QLineEdit* nameTextBox = new QLineEdit{};
	QLabel* nameLabel = new QLabel{ "&Name:" };
	nameLabel->setBuddy(nameTextBox);

	QLineEdit* ageTextBox = new QLineEdit{};
	QLabel* ageLabel = new QLabel{ "&Age:" };
	ageLabel->setBuddy(ageTextBox);

	QLineEdit* emailTextBox = new QLineEdit{};
	QLabel* emailLabel = new QLabel{ "&Email:" };
	emailLabel->setBuddy(emailTextBox);

	formLayout->addRow(nameLabel, nameTextBox);
	formLayout->addRow(ageLabel, ageTextBox);
	formLayout->addRow(emailLabel, emailTextBox);

	QWidget *wnd = new QWidget{};
	wnd->setLayout(formLayout);
	wnd->show();

	return a.exec();
}

int gridLayout(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGridLayout *gridLayout = new QGridLayout{};

	// add some buttons
	gridLayout->addWidget(new QPushButton("Add"), 0, 0);
	gridLayout->addWidget(new QPushButton("Delete"), 0, 1);
	gridLayout->addWidget(new QPushButton("Update"), 0, 2);
	gridLayout->addWidget(new QPushButton("Filter"), 1, 1);
	gridLayout->addWidget(new QPushButton("Sort"), 2, 0, 1, 3); // row span = 1, column span = 3

	QWidget *wnd = new QWidget{};
	wnd->setLayout(gridLayout);
	wnd->show();

	return a.exec();
}

int multipleLayouts(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget *wnd = new QWidget{};
	QVBoxLayout *vL = new QVBoxLayout{};
	wnd->setLayout(vL);

	//create an information widget, with a QFormLayout
	QWidget *details = new QWidget{};
	QFormLayout *fL = new QFormLayout{};
	details->setLayout(fL);
	QLabel *labelName = new QLabel{ "&Name" };
	QLineEdit *textBoxName = new QLineEdit{};
	labelName->setBuddy(textBoxName);

	fL->addRow(labelName, textBoxName);

	QLabel *labelAge = new QLabel{ "&Age" };
	QLineEdit *textBoxAge = new QLineEdit{};
	labelAge->setBuddy(textBoxAge);
	fL->addRow(labelAge, textBoxAge);

	//add the information widget to the window
	vL->addWidget(details);
	
	// create a widget with two buttons for two possible actions: Save or Cancel
	// this widget will have a QHBoxLayout
	QWidget* actions = new QWidget{};
	QHBoxLayout* hL = new QHBoxLayout{};
	QPushButton *store = new QPushButton{ "&Save" };
	QPushButton *cancel = new QPushButton{ "&Cancel" };
	hL->addWidget(store);
	hL->addWidget(cancel);
	actions->setLayout(hL);

	// add the actions widget to the window
	vL->addWidget(actions);
	
	//show window
	wnd->show();

	return a.exec();
}

// create the same GUI with absolute positioning and with layouts
int createAbsolute(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget* main = new QWidget{};
	QLabel* lbl = new QLabel("Name:", main);
	lbl->setGeometry(10, 10, 40, 20);
	QLineEdit* txt = new QLineEdit(main);
	txt->setGeometry(60, 10, 100, 20);
	main->show();
	main->setWindowTitle("Absolute");

	return a.exec();
}

int createWithLayout(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget* main = new QWidget{};
	QFormLayout *fL = new QFormLayout(main);
	QLabel* lbl = new QLabel("Name:", main);
	QLineEdit* txt = new QLineEdit(main);
	fL->addRow(lbl, txt);
	main->show();
	main->setWindowTitle("Layout");
	//fix the height to the "ideal" height
	main->setFixedHeight(main->sizeHint().height());	// Sets both the minimum and maximum heights of the widget to the given height.
														// sizeHint - holds the recommended size for the widget.

	return a.exec();
}

//int main(int argc, char *argv[])
//{
//	return editExample(argc, argv);

//	return buttonExample(argc, argv);
//	return listExample(argc, argv);
//
//	return hBoxLayout(argc, argv);
//	return vBoxLayout(argc, argv);
//	return formLayout(argc, argv);
//	return gridLayout(argc, argv);
//	return multipleLayouts(argc, argv);
//
//	return createAbsolute(argc, argv);
//	return createWithLayout(argc, argv);
//}
