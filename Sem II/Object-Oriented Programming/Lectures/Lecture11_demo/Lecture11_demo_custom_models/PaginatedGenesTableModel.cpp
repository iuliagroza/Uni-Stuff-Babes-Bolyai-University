#include "PaginatedGenesTableModel.h"
#include <QFont>
#include <QBrush>
#include <algorithm>
#include <QDebug>
#include <QMessageBox>

const int PaginatedGenesTableModel::ITEMS_PER_PAGE = 10;

PaginatedGenesTableModel::PaginatedGenesTableModel(GeneRepository& r, QObject* parent) : QAbstractTableModel{ parent }, repo{ r }
{
	this->loadedRows = 0;
}

PaginatedGenesTableModel::~PaginatedGenesTableModel()
{
}

int PaginatedGenesTableModel::rowCount(const QModelIndex & parent) const
{
	int size = this->repo.getSize();
	if (size <= this->loadedRows)
		return size;
	return this->loadedRows;
}

int PaginatedGenesTableModel::columnCount(const QModelIndex & parent) const
{
	return 3;
}

QVariant PaginatedGenesTableModel::data(const QModelIndex & index, int role) const
{
	// get the genes
	std::vector<Gene> genes = this->repo.getGenes();

	int row = index.row();
	int column = index.column();

	// get the gene from the current row
	Gene g = genes[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(g.getName());
		case 1:
			return QString::fromStdString(g.getOrganismName());
		case 2:
			return QString::fromStdString(g.getGeneFunction());
		default:
			break;
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Times", 15, 10, true);
		font.setItalic(false);
		return font;
	}
	if (role == Qt::BackgroundRole)
	{
		if (row % 2 == 1)
		{
			return QBrush{ QColor{ 0, 250, 154 } };
		}
	}

	return QVariant{};
}

QVariant PaginatedGenesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Gene name" };
			case 1:
				return QString{ "Organism name" };
			case 2:
				return QString{ "Gene function" };
			default:
				break;
			}
		}
	}
	if (role == Qt::FontRole)
	{
		QFont font("Times", 15, 10, true);
		font.setBold(true);
		font.setItalic(false);
		return font;
	}

	return QVariant{};
}

bool PaginatedGenesTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	// set the new data to the gene
	int geneIndex = index.row();
	Gene currentGene = this->repo.getGenes()[geneIndex];
	switch (index.column())
	{
	case 0:
		this->repo.updateGene(geneIndex, Gene{ value.toString().toStdString(), currentGene.getOrganismName(), currentGene.getGeneFunction() });
		break;
	case 1:
		this->repo.updateGene(geneIndex, Gene{ currentGene.getName(), value.toString().toStdString(), currentGene.getGeneFunction() });
		break;
	case 2:
		this->repo.updateGene(geneIndex, Gene{ currentGene.getName(), currentGene.getOrganismName(), value.toString().toStdString() });
		break;
	default:
		break;
	}

	// emit the dataChanged signal
	emit dataChanged(index, index);

	return true;
}

Qt::ItemFlags PaginatedGenesTableModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool PaginatedGenesTableModel::canFetchMore(const QModelIndex & parent) const
{
	return this->repo.getSize() > this->loadedRows;
}

void PaginatedGenesTableModel::fetchMore(const QModelIndex & parent)
{
	int remainedItems = this->repo.getSize() - this->loadedRows;
	int itemsToFetch = std::min(remainedItems, ITEMS_PER_PAGE);
	this->beginInsertRows(QModelIndex{}, this->loadedRows, this->loadedRows + itemsToFetch - 1);
	this->loadedRows += itemsToFetch;
	this->endInsertRows();

	// Uncomment - to show how many items were fetched
	// QMessageBox::information(NULL, "Time", "<font size = 20 > " + QString::number(this->loadedRows) + " items were fetched." + "</font>");
	qDebug() << "Fetched: " << this->loadedRows;
}
