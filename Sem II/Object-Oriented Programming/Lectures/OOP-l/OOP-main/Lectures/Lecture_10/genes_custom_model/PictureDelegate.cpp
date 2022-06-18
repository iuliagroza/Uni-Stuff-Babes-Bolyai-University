#include "PictureDelegate.h"
#include <QPixmap>
#include <QPainter>
#include "../../Lecture_9/genes/Gene.h"

PictureDelegate::PictureDelegate(QWidget *parent) : QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QString organism = index.model()->data(index, Qt::EditRole).toString();

	// show a picture only in the second column; the other columns remain unchanged
	if (index.column() != 1)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	if (organism.contains("Ecoli"))
	{
		QPixmap pixMap("Ecoli.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
	else if (organism.contains("Human"))
	{
		QPixmap pixMap("human.jpg");
		painter->drawPixmap(option.rect, pixMap);
	}
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	// show a picture only in the second column; the other columns remain unchanged
	if (index.column() == 1)
	{
		return QSize(32, 100);
	}

	return QStyledItemDelegate::sizeHint(option, index);
}
