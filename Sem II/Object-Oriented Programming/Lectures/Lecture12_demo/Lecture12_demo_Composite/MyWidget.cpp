#include "MyWidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget* parent, Graphic* g) : QWidget{ parent }, graphic{ g }
{
	this->painter = new QPainter{ this };
}

MyWidget::~MyWidget()
{
}

void MyWidget::paintEvent(QPaintEvent *event)
{
	if (this->graphic == nullptr)
		return;

	this->painter->begin(this);
	this->painter->eraseRect(this->rect());

	QBrush brush{ Qt::red, Qt::FDiagPattern };
	this->painter->setBrush(brush);

	// draw the graphic
	this->graphic->draw(this->painter);
	this->painter->end();
}