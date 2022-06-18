#include "StudentsModel.h"
#include <qcolor.h>
#include <qbrush.h>

StudentsModel::StudentsModel(Repository& repo): repo{repo}
{
}

int StudentsModel::rowCount(const QModelIndex& parent) const
{
	return repo.getSize();
}

int StudentsModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant StudentsModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	Student s = repo[row];
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0:
			return QString::fromStdString(s.getName());
		case 1:
			return QString::fromStdString(s.getGroup());
		case 2:
			return QString::number(s.getSeminarGrade());
		case 3:
			return QString::number(s.getLabGrade());
		}
	}
	else if (role == Qt::BackgroundRole) {
		if(row & 1)
			return QBrush(QColor(224, 224, 224));
	}
	return QVariant();
}

QVariant StudentsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
		switch (section) {
		case 0:
			return QString("Name");
		case 1:
			return QString("Group");
		case 2:
			return QString("Seminar grade");
		case 3:
			return QString("Lab grade");
		default:
			break;
		}
	return QVariant();
}

Qt::ItemFlags StudentsModel::flags(const QModelIndex& index) const
{
	if (index.column() == 2 or index.column() == 3)
		return Qt::ItemIsEditable | Qt::ItemIsEnabled;

	return Qt::ItemFlags();
}

bool StudentsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	int row = index.row();
	int column = index.column();

	Student& s = this->repo[row];

	if (role == Qt::EditRole || role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 2:
			s.setSeminarGrade(value.toDouble());
			break;
		case 3:
			s.setLabGrade(value.toDouble());
			break;
		default:
			break;
		}
	}

	emit dataChanged(index, index);

	return true;
}
