#include "ModelView_stub.h"
#include <QtWidgets/QApplication>
#include "TableViewWidget.h"
#include "ListViewWidget.h"
#include "ShoppingBasket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShoppingBasket basket{};
    basket.addProduct(Product{ "Apples", 18 });
    basket.addProduct(Product{ "Butter", 16 });
    basket.addProduct(Product{ "Orange juice", 22 });
    basket.addProduct(Product{ "Surgical mask", 3 });

    ProductsModel* model = new ProductsModel{basket};

    TableViewWidget* tableW = new TableViewWidget{model};
    ListViewWidget* listW = new ListViewWidget{model};

    tableW->show();
    listW->show();

    return a.exec();
}
