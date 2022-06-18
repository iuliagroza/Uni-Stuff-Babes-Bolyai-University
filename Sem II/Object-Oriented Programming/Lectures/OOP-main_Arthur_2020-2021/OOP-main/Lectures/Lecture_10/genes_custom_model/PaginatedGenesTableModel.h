#pragma once
#include <QAbstractTableModel>
#include "GeneRepository.h"

using namespace genes_custom_model;

class PaginatedGenesTableModel : public QAbstractTableModel
{
private:
	GeneRepository& repo;
	static const int ITEMS_PER_PAGE;

	int loadedRows; // count how many rows were loaded

public:
	PaginatedGenesTableModel(GeneRepository& r, QObject* parent = NULL);
	~PaginatedGenesTableModel();

	// number of rows
	int rowCount(const QModelIndex &parent = QModelIndex{}) const override;

	// number of columns
	int columnCount(const QModelIndex &parent = QModelIndex{}) const override;

	// Value at a given position
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// add header data
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	// will be called when a cell is edited
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

	// used to set certain properties of a cell
	Qt::ItemFlags flags(const QModelIndex & index) const override;

protected:
	// override the following two methods for pagination
	bool canFetchMore(const QModelIndex & parent) const override;
	void fetchMore(const QModelIndex & parent) override;
};

