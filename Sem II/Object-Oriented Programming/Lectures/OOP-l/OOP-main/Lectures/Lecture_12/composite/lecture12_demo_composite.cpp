#include "lecture12_demo_composite.h"
#include "Graphic.h"
#include <algorithm>

Lecture12_demo_Composite::Lecture12_demo_Composite(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->initializeGraphics();
	this->populateList();

	QObject::connect(this->ui.graphicsListWidget, &QListWidget::itemSelectionChanged, this, [&]() {
		QListWidgetItem* item = this->ui.graphicsListWidget->selectedItems().at(0);
		if (item == nullptr)
			return;
		// get the name of the selected item
		std::string name = item->data(Qt::UserRole).toString().toStdString();
		// identify the item in the vector
		auto it = std::find_if(this->graphics.begin(), this->graphics.end(), [name](Graphic* g) {return g->getName() == name; });
		if (it == this->graphics.end())
			return;
		this->ui.widget->graphic = *it;
		this->ui.widget->update();
	});
}

Lecture12_demo_Composite::~Lecture12_demo_Composite()
{
	for (auto g : this->graphics)
		delete g;
}

void Lecture12_demo_Composite::initializeGraphics()
{
	Graphic* n = new Line{ "neck", 200, 120, 200, 140 };
	this->graphics.push_back(n);

	Graphic* h1 = new Line{ "hand1", 150, 160, 60, 200 };
	Graphic* h2 = new Line{ "hand2", 250, 160, 340, 200 };
	this->graphics.push_back(h1);
	this->graphics.push_back(h2);

	Graphic* f1 = new Line{ "foot1", 150, 280, 60, 360 };
	Graphic* f2 = new Line{ "foot2", 250, 280, 340, 360 };
	this->graphics.push_back(f1);
	this->graphics.push_back(f2);

	Graphic* t = new Text{ "text1", 300, 80, "Hello!" };
	this->graphics.push_back(t);

	Graphic* he = new Circle{ "head", 200, 40, 80 };
	Graphic* b = new Circle{ "belly", 200, 140, 160 };
	this->graphics.push_back(he);
	this->graphics.push_back(b);

	Graphic* lines = new Picture{ "lines" };
	lines->add(h1);
	lines->add(h2);
	lines->add(f1);
	lines->add(f2);
	this->graphics.push_back(lines);

	Graphic* circles = new Picture{ "circles" };
	circles->add(he);
	circles->add(b);
	this->graphics.push_back(circles);

	Graphic* p = new Picture{ "stick figure" };
	p->add(n);
	p->add(h1);
	p->add(h2);
	p->add(f1);
	p->add(f2);
	p->add(t);
	p->add(he);
	p->add(b);
	this->graphics.push_back(p);
}

void Lecture12_demo_Composite::populateList()
{
	for (auto g : this->graphics)
	{
		QListWidgetItem* item = new QListWidgetItem{};
		item->setText(QString::fromStdString(g->getName()));
		item->setData(Qt::UserRole, QString::fromStdString(g->getName()));
		this->ui.graphicsListWidget->addItem(item);
	}
}
