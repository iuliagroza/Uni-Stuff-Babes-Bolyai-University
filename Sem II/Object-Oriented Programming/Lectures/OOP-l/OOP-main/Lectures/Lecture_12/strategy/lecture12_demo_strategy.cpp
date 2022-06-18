#include "lecture12_demo_strategy.h"
#include <fstream>
#include <sstream>
#include <QFileDialog>
#include <QMessageBox>

Lecture12_demo_Strategy::Lecture12_demo_Strategy(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->creatorStrategy = std::move(std::make_unique<CreateStrategy>());
	
	// initialize castles
	this->castles.push_back(strategy::Castle{ "Highclere Castle", "England", 4 });
	this->castles.push_back(strategy::Castle{ "Chambord Castle", "France", 3 });
	this->castles.push_back(strategy::Castle{ "Scaliger Castle", "Italy", 2 });
	this->castles.push_back(strategy::Castle{ "Windsor Castle", "England", 6 });

	// make the connections
	QObject::connect(this->ui.actionSave_As_CSV, &QAction::triggered, this, [&]() {
		this->saveFile(this->getFilename(FileType::CSV), FileType::CSV);
	});

	QObject::connect(this->ui.actionSave_As_HTML, &QAction::triggered, this, [&]() {
		this->saveFile(this->getFilename(FileType::HTML), FileType::HTML);
	});
}

Lecture12_demo_Strategy::~Lecture12_demo_Strategy()
{
}

std::string Lecture12_demo_Strategy::getFilename(FileType fileType)
{
	QString fileName;
	switch (fileType)
	{
	case CSV:
		fileName = QFileDialog::getSaveFileName(this, "Save File", "", "CSV Files (*.csv)");
		break;
	case HTML:
		fileName = QFileDialog::getSaveFileName(this, "Save File", "", "HTML Files (*.html)");
		break;
	default:
		break;
	}
	return fileName.toStdString();
}

void Lecture12_demo_Strategy::saveFile(const std::string& filename, FileType fileType)
{
	this->saveFileStrategy = std::move(this->creatorStrategy->create(fileType, filename, this->castles));
	try
	{
		this->saveFileStrategy->saveFile();
		// read from the file and show the content in the text edit
		this->showFileContent(filename, fileType);
	}
	catch (std::runtime_error& e)
	{
		QMessageBox::critical(NULL, "Error", e.what());
	}
}

void Lecture12_demo_Strategy::showFileContent(const std::string & filename, FileType fileType)
{
	std::ifstream f{ filename };
	if (!f.is_open())
	{
		QMessageBox::critical(0, "Error", "File could not be opened!");
		return;
	}

	std::stringstream s;
	s << f.rdbuf();
	switch (fileType)
	{
	case CSV:
		this->ui.textEdit->setText(QString::fromStdString(s.str()));
		break;
	case HTML:
		this->ui.textEdit->setHtml(QString::fromStdString(s.str()));
		break;
	default:
		break;
	}
	f.close();
}
