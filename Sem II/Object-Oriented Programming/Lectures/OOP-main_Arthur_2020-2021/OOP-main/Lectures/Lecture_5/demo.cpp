#include "Penguin.h"
#include "Dog.h"
#include <iostream>

using namespace std;

void showAnimal(Animal a) {
    cout << a.toString() << endl;
}

void showDog(Dog d) {
    cout << d.toString() << endl;
}

void substitutionPrinciple() {
    Penguin penguin{"black and white", 10, "Magellanic"};
    Dog dog{"brown", 20, "Labrador Retriever", 2.5};

    Animal animal{"green", 0.2};
    showAnimal(animal);

    animal = penguin;        // implicit upcast
    showAnimal(penguin);    // implicit upcast
    showAnimal(dog);        // implicit upcast
    cout << endl;

    //dog = animal;	// error!
    //showDog(animal); // error !
}

void pointersAndInheritance() {
    Animal *animal = new Animal{"black", 65};
    cout << animal->toString() << endl;

    Penguin *penguin = new Penguin{"black and white", 12, "Imperial"};
//    animal = penguin;    // this is allowed;
    // In this particular case, is it correct, or can you identify an error? Hint: look at the deallocation at the end of the function.

    cout << animal->toString() << endl;
    //penguin = animal; //error!

    delete penguin;
    delete animal; // !!! memory error
}

void methodOverriding() {
    Penguin penguin{"black and white", 10, "Magellanic"};
    Dog dog{"brown", 20, "Labrador Retriever", 2.5};

    cout << penguin.toString() << endl;
    cout << dog.toString() << endl;
}

void demo() {
    Penguin penguin{"black and white", 10, "Magellanic"};
    // penguin is an animal => we can use any method from the Animal class
    cout << penguin.toString() << endl;

    // constructing and destructing objects of derived classes
    {
        Penguin penguin{"black and white", 10, "Magellanic"};
        Dog dog{"brown", 20, "Labrador Retriever", 2.5};
        cout << dog.toString();
    }

    // ---------------------------------------------------------------------------------------------------
    //Substitution principle
//    substitutionPrinciple();

    // ---------------------------------------------------------------------------------------------------
    // Pointers and inheritance
//    pointersAndInheritance();

    // ---------------------------------------------------------------------------------------------------
    // Method orverriding
//    methodOverriding();
}

//int main() {
//    demo();
//    return 0;
//}