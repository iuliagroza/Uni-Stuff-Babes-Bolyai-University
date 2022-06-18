#include "Lecture10_demo.h"
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QSlider>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget* w = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ w };
	QSpinBox* spinner = new QSpinBox{};
	// set font
	QFont font("Courier", 50, 10, true);
	spinner->setFont(font);

	QSlider* slider = new QSlider{ Qt::Horizontal };
	slider->setMinimumHeight(50);
	slider->setMinimumWidth(400);

	hLayout->addWidget(spinner);
	hLayout->addWidget(slider);

	//Synchronise the spinner and the slider
	//Connect spin box - valueChanged to slider setValue
	//QObject::connect(spinner, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
	QObject::connect(spinner, &QSpinBox::valueChanged, slider, &QSlider::setValue);

	//Connect - slider valueChanged to spin box setValue
	QObject::connect(slider, &QSlider::valueChanged, spinner, &QSpinBox::setValue);

	w->show();

	return a.exec();

}
