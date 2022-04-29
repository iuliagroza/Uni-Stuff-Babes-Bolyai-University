#ifndef T1_IULIAGROZA_REPOSITORY_H
#define T1_IULIAGROZA_REPOSITORY_H
#include "../utils/DynamicArray.h"
#include "../domain/Bill.h"

class Repository {
private:
    DynamicArray<Bill> bills;

public:
    DynamicArray<Bill> get_bills();

    bool remove_bill(Bill bill);

    int find_bill(Bill bill);

    void add_bill(Bill bill);
};


#endif
