#pragma once
#include <QStyledItemDelegate>
#include "GeneRepository.h"

class PictureDelegate:	public QStyledItemDelegate
{
public:
	PictureDelegate(QWidget *parent = 0);

	// these two functions need to be overridden to draw an image for each item
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};

