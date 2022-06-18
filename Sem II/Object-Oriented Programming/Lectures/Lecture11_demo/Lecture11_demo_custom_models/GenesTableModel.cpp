#include "GenesTableModel.h"
#include <QFont>
#include <QBrush>

GenesTableModel::GenesTableModel(GeneRepository& r, QObject* parent) : QAbstractTableModel{ parent }, repo{ r }
{
}

GenesTableModel::~GenesTableModel()
{
}

int GenesTableModel::rowCount(const QModelIndex & parent) const
{
	//if (parent.isValid())	// for tree view
	//	return 0;
	int genesNumber = this->repo.getSize();
	//return genesNumber;

	// Show a new empty row at the end, to allow adding data
	return genesNumber + 1;
}

int GenesTableModel::columnCount(const QModelIndex & parent) const
{
	return 3;
}

QVariant GenesTableModel::data(const QModelIndex & index, int role) const
{
	int row = index.row();
	int column = index.column(); 

	// get the genes
	std::vector<Gene> genes = this->repo.getGenes();

	// Allow adding in the table
	// this is to show an empty row at the end of the table - to allow adding new genes
	if (row == genes.size())
	{
		return QVariant();
	}

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
			return QBrush{ QColor{0, 250, 154} };
		}
	}

	return QVariant{};
}

QVariant GenesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool GenesTableModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	// set the new data to the gene
	int geneIndex = index.row();

	// get the genes
	std::vector<Gene> genes = this->repo.getGenes();

	// Allow adding in the table
	//if the index is >= number of genes => a new gene is added
	if (geneIndex == genes.size())
	{
		this->beginInsertRows(QModelIndex{}, geneIndex, geneIndex);

		switch (index.column())
		{
		case 0:
			this->repo.addGene(Gene{ value.toString().toStdString(), "", "" });
			break;
		case 1:
			this->repo.addGene(Gene{ "", value.toString().toStdString(), ""});
			break;
		case 2:
			this->repo.addGene(Gene{ "", "", value.toString().toStdString() });
			break;
		}

		this->endInsertRows();
		return true;
	}

	Gene& currentGene = genes[geneIndex];
	switch (index.column())
	{
	case 0:
		currentGene.setName(value.toString().toStdString());
		break;
	case 1:
		currentGene.setOrganismName(value.toString().toStdString());
		break;
	case 2:
		currentGene.setFunction(value.toString().toStdString());
	}
	this->repo.updateGene(geneIndex, currentGene);

	// emit the dataChanged signal
	emit dataChanged(index, index);

	return true;
}

Qt::ItemFlags GenesTableModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
