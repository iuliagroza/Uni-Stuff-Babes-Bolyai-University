#ifndef LECTURE12_DEMO_ITERATOR_H
#define LECTURE12_DEMO_ITERATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_lecture12_demo_iterator.h"
#include "Multimap.h"
#include "Castle.h"
#include "Iterator.h"
#include <memory>

class Lecture12_demo_Iterator : public QMainWindow
{
	Q_OBJECT

private:
	Multimap* castles;
	std::unique_ptr<Iterator> iterator;
	Ui::Lecture12_demo_IteratorClass ui;

public:
	Lecture12_demo_Iterator(QWidget *parent = 0);
	~Lecture12_demo_Iterator();

private:
	void showCurrentCastle();

	void next();
	void slideShow();
};

#endif // LECTURE12_DEMO_ITERATOR_H
