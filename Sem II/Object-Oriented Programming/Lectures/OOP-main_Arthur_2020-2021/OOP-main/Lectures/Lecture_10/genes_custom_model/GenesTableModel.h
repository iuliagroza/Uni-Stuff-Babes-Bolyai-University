#pragma once
#include <QAbstractTableModel>
#include "GeneRepository.h"

//using namespace genes_custom_model;

class GenesTableModel: public QAbstractTableModel
{
private:
    genes_custom_model::GeneRepository& repo;

public:
	GenesTableModel(genes_custom_model::GeneRepository& r, QObject* parent = NULL);
	~GenesTableModel();

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
};

