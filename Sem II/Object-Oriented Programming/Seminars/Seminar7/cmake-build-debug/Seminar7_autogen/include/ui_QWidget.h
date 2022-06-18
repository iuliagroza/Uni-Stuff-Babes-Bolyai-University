/********************************************************************************
** Form generated from reading UI file 'qwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QWIDGET_H
#define UI_QWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QWidget
{
public:

    void setupUi(QWidget *QWidget)
    {
        if (QWidget->objectName().isEmpty())
            QWidget->setObjectName(QString::fromUtf8("QWidget"));
        QWidget->resize(400, 300);

        retranslateUi(QWidget);

        QMetaObject::connectSlotsByName(QWidget);
    } // setupUi

    void retranslateUi(QWidget *QWidget)
    {
        QWidget->setWindowTitle(QCoreApplication::translate("QWidget", "QWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QWidget: public Ui_QWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QWIDGET_H
