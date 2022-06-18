#pragma once
#include <qwidget.h>
#include "Graphic.h"

class MyWidget: public QWidget
{
public:
	MyWidget(QWidget* parent, Graphic* g = nullptr);
	~MyWidget();
	QPainter* painter;
	Graphic* graphic;

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

