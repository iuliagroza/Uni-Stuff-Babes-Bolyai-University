#include "Graphic.h"

void Line::draw(QPainter * p) const
{
	if (p == nullptr)
		return;

	p->drawLine(this->x1, this->y1, this->x2, this->y2);
}

void Text::draw(QPainter * p) const
{
	if (p == nullptr)
		return;

	QFont font;
	font.setPixelSize(28);
	p->setFont(font);
	p->drawText(this->x, this->y, QString::fromStdString(this->text));
}

void Circle::draw(QPainter * p) const
{
	if (p == nullptr)
		return;

	p->drawEllipse(this->x - this->radius/2, this->y, this->radius, this->radius);
}

void Picture::draw(QPainter * p) const
{
	if (p == nullptr)
		return;

	// draw components (children)
	for (auto c : this->components)
	{
		if (c == nullptr)
			continue;
		c->draw(p);
	}
}

void Picture::add(Graphic * g)
{
	this->components.push_back(g);
}
