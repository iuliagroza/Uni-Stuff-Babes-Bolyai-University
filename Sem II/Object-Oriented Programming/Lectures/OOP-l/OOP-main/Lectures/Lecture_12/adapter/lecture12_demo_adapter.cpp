#include "lecture12_demo_adapter.h"
#include <QMessageBox>
#include "Adapter.h"

Lecture12_demo_Adapter::Lecture12_demo_Adapter(Controller &c, QWidget *parent) : QMainWindow(parent), ctrl{ c }
{
	ui.setupUi(this);
	//this->ui.goCardlessButton->hide();

	this->populateList();
	this->connectButtons();
}

Lecture12_demo_Adapter::~Lecture12_demo_Adapter()
{
}

void Lecture12_demo_Adapter::connectButtons()
{
	// change current castle when the selection in the list is changed
	QObject::connect(this->ui.housesListWidget, &QListWidget::itemSelectionChanged, this, [&]() {this->setCurrentCastle(); });

	QObject::connect(this->ui.payPalButton, &QPushButton::clicked, this, [&]()
		{
			std::unique_ptr<PaymentService> service = std::make_unique<PayPal>();
			QMessageBox::information(NULL, "Information", "<font size = 18 > " + QString::fromStdString(this->ctrl.buy(std::move(service))));
		}
	);

	QObject::connect(this->ui.skrillButton, &QPushButton::clicked, this, [&]()
		{
			std::unique_ptr<PaymentService> service = std::make_unique<Skrill>();
			QMessageBox::information(NULL, "Information", "<font size = 18 > " + QString::fromStdString(this->ctrl.buy(std::move(service))));
		}
	);

	QObject::connect(this->ui.goCardlessButton, &QPushButton::clicked, this, [&]()
		{
			// use class adapter
			std::unique_ptr<PaymentService> service = std::make_unique<AdapterClass>(0.78);
			
			// use object adapter
			/*GoCardlessUK goCardlessService;
			std::unique_ptr<PaymentService> service = std::make_unique<AdapterObject>(0.78, goCardlessService);*/
			QMessageBox::information(NULL, "Information", "<font size = 18 > " + QString::fromStdString(this->ctrl.buy(std::move(service))));
		}
	);
}

void Lecture12_demo_Adapter::populateList()
{
	// clear the list, if there are elements in it
	if (this->ui.housesListWidget->count() > 0)
		this->ui.housesListWidget->clear();

	for (auto c : this->ctrl.getCastles())
	{
		QString itemInList = QString::fromStdString(c.getDescription() + ", " + c.getLocation() + ", ") + QString::number(c.getStartPrice());
		QListWidgetItem *item = new QListWidgetItem(itemInList);
		QFont font("Courier", 20, 10, true);
		item->setFont(font);
		this->ui.housesListWidget->addItem(item);
	}

	// set the selection on the first item in the list
	if (this->ui.housesListWidget->count() > 0)
		this->ui.housesListWidget->setCurrentRow(0);

}

void Lecture12_demo_Adapter::setCurrentCastle()
{
	if (this->ui.housesListWidget->count() == 0)
		return;

	// get selected index
	QModelIndexList index = this->ui.housesListWidget->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		return;
	}

	int idx = index.at(0).row();
	this->ctrl.setCurrent(idx);
}