#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <stdio.h>

#define DO_SYNCHRONIZE

#define NUM_THREADS 5
#define NUM_PRODUCTS 200
#define MIN_PRICE 1
#define MAX_PRICE 19
#define MIN_QUANTITY 20
#define MAX_QUANTITY 100
#define MAX_PRODUCTS_SALE 20 // maximum products in a sale

using namespace std;

ostream &operator<<(ostream &os, const Inventory &inventory)
{
    os << "Inventory:" << endl;
    for (map<Product, int>::const_iterator it = inventory.inventory.begin(); it != inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        os << "\t" << product << ", quantity: " << quantity << endl;
    }

    return os;
}

string to_string(const Inventory &Inventory)
{
    string str = "Inventory:\n";

    for (map<Product, int>::const_iterator it = Inventory.inventory.begin(); it != Inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        str = str + "\t" + to_string(product) + ", quantity: " + to_string(quantity) + "\n";
    }
    return str;
}

ostream &operator<<(ostream &os, const Bill &bill)
{
    os << "Bill:\n";
    int i = 1;
    for (map<Product, int>::const_iterator it = bill.items.begin(); it != bill.items.end(); it++, i++)
    {
        os << "\t" << i << ". " << it->first << ", quantity: " << it->second << endl;
    }
    os << "\t--------------------" << endl;
    os << "\tTOTAL: " << bill.totalPrice << endl;
    return os;
}

ostream &operator<<(ostream &os, const Supermarket &supermarket)
{
    os << "Supermarket:\n";
    os << "Supermarket's inventory: " << supermarket.inventory << endl;
    os << "Supermarket's amount of money: " << supermarket.money << endl;
    os << "Supermarket's bills:\n";
    for (vector<Bill>::const_iterator it = supermarket.bills.begin(); it != supermarket.bills.end(); it++)
    {
        os << "\tBill: " << (*it) << endl;
    }
    return os;
}

Supermarket gSupermarket;
mutex Inventory::inventoryMutex;
mutex Supermarket::inventoryAndSoldItemsMutex;
mutex Supermarket::billsAndMoneyMutex;

void threadFunction(int threadId)
{
    int operation;

    printf("[T %d] started.\n", threadId);
    srand((time(NULL) - (threadId * 14 - 29)));

    operation = rand() % 2;

    if (0 == operation)
    {
        int numProductsToBuy;
        printf("[Thread %d] is performing a sale operation.\n", threadId);

        map<Product, int> products = map<Product, int>();
        numProductsToBuy = 1 + rand() % MAX_PRODUCTS_SALE;

        for (int i = 0; i < numProductsToBuy; i++)
        {
            int pId = rand() % NUM_PRODUCTS;
            Product p = Product(pId);

            if (0 == products.count(p))
            {
                products[p] = 1;
            }
            else
            {
                products[p] += 1;
            }
        }
        gSupermarket.sale(products);
    }
    else
    {
        printf("[Thread %d] is performing a check operation.\n", threadId);

        gSupermarket.checkInventory(threadId);
    }

    printf("[Thread %d] finished.\n", threadId);
}

void initSupermarketInventory(int numProducts, int minQuantity, int maxQuantity, int minPrice, int maxPrice)
{
    Inventory inventory = Inventory();

    for (int id = 0; id < numProducts; id++)
    {
        string name = "prod#" + to_string(id);
        int price = minPrice + (rand() % static_cast<int>(maxPrice - minPrice + 1));
        int quantity = minQuantity + (rand() % static_cast<int>(maxQuantity - minQuantity + 1));

        inventory.addProduct(Product(id, name, price), quantity);
    }

    gSupermarket = Supermarket(inventory);
}

int main()
{
    vector<thread> threads = vector<thread>();

    srand(static_cast<int>(time(NULL)));

    initSupermarketInventory(NUM_PRODUCTS, MIN_QUANTITY, MAX_QUANTITY, MIN_PRICE, MAX_PRICE);
    auto start_time = chrono::high_resolution_clock::now();

    cout << gSupermarket << endl;
    auto end_time = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    for (int tId = 1; tId <= NUM_THREADS; tId++)
    {
        threads.push_back(thread(&threadFunction, tId));
    }

    for (int tId = 0; tId < NUM_THREADS; tId++)
    {
        threads[tId].join();
    }

    gSupermarket.checkInventory(0);

    cout << gSupermarket << endl;
    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    return 0;
}
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <stdio.h>

#define DO_SYNCHRONIZE

#define NUM_THREADS 5
#define NUM_PRODUCTS 200
#define MIN_PRICE 1
#define MAX_PRICE 19
#define MIN_QUANTITY 20
#define MAX_QUANTITY 100
#define MAX_PRODUCTS_SALE 20 // maximum products in a sale

using namespace std;

ostream &operator<<(ostream &os, const Inventory &inventory)
{
    os << "Inventory:" << endl;
    for (map<Product, int>::const_iterator it = inventory.inventory.begin(); it != inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        os << "\t" << product << ", quantity: " << quantity << endl;
    }

    return os;
}

string to_string(const Inventory &Inventory)
{
    string str = "Inventory:\n";

    for (map<Product, int>::const_iterator it = Inventory.inventory.begin(); it != Inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        str = str + "\t" + to_string(product) + ", quantity: " + to_string(quantity) + "\n";
    }
    return str;
}

ostream &operator<<(ostream &os, const Bill &bill)
{
    os << "Bill:\n";
    int i = 1;
    for (map<Product, int>::const_iterator it = bill.items.begin(); it != bill.items.end(); it++, i++)
    {
        os << "\t" << i << ". " << it->first << ", quantity: " << it->second << endl;
    }
    os << "\t--------------------" << endl;
    os << "\tTOTAL: " << bill.totalPrice << endl;
    return os;
}

ostream &operator<<(ostream &os, const Supermarket &supermarket)
{
    os << "Supermarket:\n";
    os << "Supermarket's inventory: " << supermarket.inventory << endl;
    os << "Supermarket's amount of money: " << supermarket.money << endl;
    os << "Supermarket's bills:\n";
    for (vector<Bill>::const_iterator it = supermarket.bills.begin(); it != supermarket.bills.end(); it++)
    {
        os << "\tBill: " << (*it) << endl;
    }
    return os;
}

Supermarket gSupermarket;
mutex Inventory::inventoryMutex;
mutex Supermarket::inventoryAndSoldItemsMutex;
mutex Supermarket::billsAndMoneyMutex;

void threadFunction(int threadId)
{
    int operation;

    printf("[T %d] started.\n", threadId);
    srand((time(NULL) - (threadId * 14 - 29)));

    operation = rand() % 2;

    if (0 == operation)
    {
        int numProductsToBuy;
        printf("[Thread %d] is performing a sale operation.\n", threadId);

        map<Product, int> products = map<Product, int>();
        numProductsToBuy = 1 + rand() % MAX_PRODUCTS_SALE;

        for (int i = 0; i < numProductsToBuy; i++)
        {
            int pId = rand() % NUM_PRODUCTS;
            Product p = Product(pId);

            if (0 == products.count(p))
            {
                products[p] = 1;
            }
            else
            {
                products[p] += 1;
            }
        }
        gSupermarket.sale(products);
    }
    else
    {
        printf("[Thread %d] is performing a check operation.\n", threadId);

        gSupermarket.checkInventory(threadId);
    }

    printf("[Thread %d] finished.\n", threadId);
}

void initSupermarketInventory(int numProducts, int minQuantity, int maxQuantity, int minPrice, int maxPrice)
{
    Inventory inventory = Inventory();

    for (int id = 0; id < numProducts; id++)
    {
        string name = "prod#" + to_string(id);
        int price = minPrice + (rand() % static_cast<int>(maxPrice - minPrice + 1));
        int quantity = minQuantity + (rand() % static_cast<int>(maxQuantity - minQuantity + 1));

        inventory.addProduct(Product(id, name, price), quantity);
    }

    gSupermarket = Supermarket(inventory);
}

int main()
{
    vector<thread> threads = vector<thread>();

    srand(static_cast<int>(time(NULL)));

    initSupermarketInventory(NUM_PRODUCTS, MIN_QUANTITY, MAX_QUANTITY, MIN_PRICE, MAX_PRICE);
    auto start_time = chrono::high_resolution_clock::now();

    cout << gSupermarket << endl;
    auto end_time = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    for (int tId = 1; tId <= NUM_THREADS; tId++)
    {
        threads.push_back(thread(&threadFunction, tId));
    }

    for (int tId = 0; tId < NUM_THREADS; tId++)
    {
        threads[tId].join();
    }

    gSupermarket.checkInventory(0);

    cout << gSupermarket << endl;
    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    return 0;
}
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <stdio.h>

#define DO_SYNCHRONIZE

#define NUM_THREADS 5
#define NUM_PRODUCTS 200
#define MIN_PRICE 1
#define MAX_PRICE 19
#define MIN_QUANTITY 20
#define MAX_QUANTITY 100
#define MAX_PRODUCTS_SALE 20 // maximum products in a sale

using namespace std;

ostream &operator<<(ostream &os, const Inventory &inventory)
{
    os << "Inventory:" << endl;
    for (map<Product, int>::const_iterator it = inventory.inventory.begin(); it != inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        os << "\t" << product << ", quantity: " << quantity << endl;
    }

    return os;
}

string to_string(const Inventory &Inventory)
{
    string str = "Inventory:\n";

    for (map<Product, int>::const_iterator it = Inventory.inventory.begin(); it != Inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        str = str + "\t" + to_string(product) + ", quantity: " + to_string(quantity) + "\n";
    }
    return str;
}

ostream &operator<<(ostream &os, const Bill &bill)
{
    os << "Bill:\n";
    int i = 1;
    for (map<Product, int>::const_iterator it = bill.items.begin(); it != bill.items.end(); it++, i++)
    {
        os << "\t" << i << ". " << it->first << ", quantity: " << it->second << endl;
    }
    os << "\t--------------------" << endl;
    os << "\tTOTAL: " << bill.totalPrice << endl;
    return os;
}

ostream &operator<<(ostream &os, const Supermarket &supermarket)
{
    os << "Supermarket:\n";
    os << "Supermarket's inventory: " << supermarket.inventory << endl;
    os << "Supermarket's amount of money: " << supermarket.money << endl;
    os << "Supermarket's bills:\n";
    for (vector<Bill>::const_iterator it = supermarket.bills.begin(); it != supermarket.bills.end(); it++)
    {
        os << "\tBill: " << (*it) << endl;
    }
    return os;
}

Supermarket gSupermarket;
mutex Inventory::inventoryMutex;
mutex Supermarket::inventoryAndSoldItemsMutex;
mutex Supermarket::billsAndMoneyMutex;

void threadFunction(int threadId)
{
    int operation;

    printf("[T %d] started.\n", threadId);
    srand((time(NULL) - (threadId * 14 - 29)));

    operation = rand() % 2;

    if (0 == operation)
    {
        int numProductsToBuy;
        printf("[Thread %d] is performing a sale operation.\n", threadId);

        map<Product, int> products = map<Product, int>();
        numProductsToBuy = 1 + rand() % MAX_PRODUCTS_SALE;

        for (int i = 0; i < numProductsToBuy; i++)
        {
            int pId = rand() % NUM_PRODUCTS;
            Product p = Product(pId);

            if (0 == products.count(p))
            {
                products[p] = 1;
            }
            else
            {
                products[p] += 1;
            }
        }
        gSupermarket.sale(products);
    }
    else
    {
        printf("[Thread %d] is performing a check operation.\n", threadId);

        gSupermarket.checkInventory(threadId);
    }

    printf("[Thread %d] finished.\n", threadId);
}

void initSupermarketInventory(int numProducts, int minQuantity, int maxQuantity, int minPrice, int maxPrice)
{
    Inventory inventory = Inventory();

    for (int id = 0; id < numProducts; id++)
    {
        string name = "prod#" + to_string(id);
        int price = minPrice + (rand() % static_cast<int>(maxPrice - minPrice + 1));
        int quantity = minQuantity + (rand() % static_cast<int>(maxQuantity - minQuantity + 1));

        inventory.addProduct(Product(id, name, price), quantity);
    }

    gSupermarket = Supermarket(inventory);
}

int main()
{
    vector<thread> threads = vector<thread>();

    srand(static_cast<int>(time(NULL)));

    initSupermarketInventory(NUM_PRODUCTS, MIN_QUANTITY, MAX_QUANTITY, MIN_PRICE, MAX_PRICE);
    auto start_time = chrono::high_resolution_clock::now();

    cout << gSupermarket << endl;
    auto end_time = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    for (int tId = 1; tId <= NUM_THREADS; tId++)
    {
        threads.push_back(thread(&threadFunction, tId));
    }

    for (int tId = 0; tId < NUM_THREADS; tId++)
    {
        threads[tId].join();
    }

    gSupermarket.checkInventory(0);

    cout << gSupermarket << endl;
    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    return 0;
}
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <stdio.h>

#define DO_SYNCHRONIZE

#define NUM_THREADS 5
#define NUM_PRODUCTS 200
#define MIN_PRICE 1
#define MAX_PRICE 19
#define MIN_QUANTITY 20
#define MAX_QUANTITY 100
#define MAX_PRODUCTS_SALE 20 // maximum products in a sale

using namespace std;

ostream &operator<<(ostream &os, const Inventory &inventory)
{
    os << "Inventory:" << endl;
    for (map<Product, int>::const_iterator it = inventory.inventory.begin(); it != inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        os << "\t" << product << ", quantity: " << quantity << endl;
    }

    return os;
}

string to_string(const Inventory &Inventory)
{
    string str = "Inventory:\n";

    for (map<Product, int>::const_iterator it = Inventory.inventory.begin(); it != Inventory.inventory.end(); it++)
    {
        Product product = it->first;
        int quantity = it->second;
        str = str + "\t" + to_string(product) + ", quantity: " + to_string(quantity) + "\n";
    }
    return str;
}

ostream &operator<<(ostream &os, const Bill &bill)
{
    os << "Bill:\n";
    int i = 1;
    for (map<Product, int>::const_iterator it = bill.items.begin(); it != bill.items.end(); it++, i++)
    {
        os << "\t" << i << ". " << it->first << ", quantity: " << it->second << endl;
    }
    os << "\t--------------------" << endl;
    os << "\tTOTAL: " << bill.totalPrice << endl;
    return os;
}

ostream &operator<<(ostream &os, const Supermarket &supermarket)
{
    os << "Supermarket:\n";
    os << "Supermarket's inventory: " << supermarket.inventory << endl;
    os << "Supermarket's amount of money: " << supermarket.money << endl;
    os << "Supermarket's bills:\n";
    for (vector<Bill>::const_iterator it = supermarket.bills.begin(); it != supermarket.bills.end(); it++)
    {
        os << "\tBill: " << (*it) << endl;
    }
    return os;
}

Supermarket gSupermarket;
mutex Inventory::inventoryMutex;
mutex Supermarket::inventoryAndSoldItemsMutex;
mutex Supermarket::billsAndMoneyMutex;

void threadFunction(int threadId)
{
    int operation;

    printf("[T %d] started.\n", threadId);
    srand((time(NULL) - (threadId * 14 - 29)));

    operation = rand() % 2;

    if (0 == operation)
    {
        int numProductsToBuy;
        printf("[Thread %d] is performing a sale operation.\n", threadId);

        map<Product, int> products = map<Product, int>();
        numProductsToBuy = 1 + rand() % MAX_PRODUCTS_SALE;

        for (int i = 0; i < numProductsToBuy; i++)
        {
            int pId = rand() % NUM_PRODUCTS;
            Product p = Product(pId);

            if (0 == products.count(p))
            {
                products[p] = 1;
            }
            else
            {
                products[p] += 1;
            }
        }
        gSupermarket.sale(products);
    }
    else
    {
        printf("[Thread %d] is performing a check operation.\n", threadId);

        gSupermarket.checkInventory(threadId);
    }

    printf("[Thread %d] finished.\n", threadId);
}

void initSupermarketInventory(int numProducts, int minQuantity, int maxQuantity, int minPrice, int maxPrice)
{
    Inventory inventory = Inventory();

    for (int id = 0; id < numProducts; id++)
    {
        string name = "prod#" + to_string(id);
        int price = minPrice + (rand() % static_cast<int>(maxPrice - minPrice + 1));
        int quantity = minQuantity + (rand() % static_cast<int>(maxQuantity - minQuantity + 1));

        inventory.addProduct(Product(id, name, price), quantity);
    }

    gSupermarket = Supermarket(inventory);
}

int main()
{
    vector<thread> threads = vector<thread>();

    srand(static_cast<int>(time(NULL)));

    initSupermarketInventory(NUM_PRODUCTS, MIN_QUANTITY, MAX_QUANTITY, MIN_PRICE, MAX_PRICE);
    auto start_time = chrono::high_resolution_clock::now();

    cout << gSupermarket << endl;
    auto end_time = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    for (int tId = 1; tId <= NUM_THREADS; tId++)
    {
        threads.push_back(thread(&threadFunction, tId));
    }

    for (int tId = 0; tId < NUM_THREADS; tId++)
    {
        threads[tId].join();
    }

    gSupermarket.checkInventory(0);

    cout << gSupermarket << endl;
    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end_time - start_time).count();
    cout << fixed << setprecision(10) << "Time elapsed: " << duration << " milliseconds" << endl;

    return 0;
}
