#include "Penguin.h"
#include "Dog.h"
#include "Zoo.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace abstract_base_class;

vector<Animal *> createAnimals() {
    // Animal a{ "black", 20 }; //Animal is an abstract class; objects of this type can no longer be created

    vector<Animal *> animals;
    Animal *p1 = new Penguin{"black", 7, "Magellanic"};
    Penguin *p2 = new Penguin{"white and black", 6, "Emperor"};
    Dog *d1 = new Dog{"black", 35, "rottweiler", 2};
    Dog *d2 = new Dog{"beige", 25, "Labrador retriever", 4};

    animals.push_back(p1);
    animals.push_back(d1);
    animals.push_back(p2);
    animals.push_back(d2);

    return animals;
}

void destroyAnimals(vector<Animal *> animals) {
    for (auto a : animals)
        delete a;
}

void homogenousContainer() {
    vector<Animal *> animals = createAnimals();

    for (auto a : animals) {
        // send the same message to all animals: to print their information and to speak
        cout << a->toString() << endl;
        a->speak();
        cout << endl;
    }

    destroyAnimals(animals);
}

// ------------------------------------------------------------------------------------------------------

void filterAnimals() {
    vector<Animal *> animals = createAnimals();

    // create Zoo
    Zoo z(animals);

    // create the two filters
    FilterWeightLessThan filterByWeight{30};
    FilterColor filterByColour{"black"};

    // apply the filters and print the results
    cout << "Animals having the weight less than 30 kg: " << endl;
    vector<Animal *> byWeight = z.filterBy(filterByWeight);
    for (auto a : byWeight)
        cout << a->toString() << endl;

    cout << "Animals having the colour \"black\": " << endl;
    vector<Animal *> byColour = z.filterBy(filterByColour);
    for (auto a : byColour)
        cout << a->toString() << endl;

    // deallocate the resources
    destroyAnimals(animals);
}

// ------------------------------------------------------------------------------------------------------

//int main() {
//
//
//    homogenousContainer();
//
////    filterAnimals();
//
//    return 0;
//}