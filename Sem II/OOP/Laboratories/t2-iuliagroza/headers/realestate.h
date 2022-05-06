#pragma once
#include "dwelling.h"
#include "client.h"
#include <fstream>
#include <vector>
#include <random>


class RealEstateAgency{
public:
    std::vector<Dwelling*> dwellingRepo;
    std::vector<Client*> clientRepo;

    Dwelling* addDwelling(Dwelling* m);
    void addClient(Client *c); // a
    void removeClient(const std::string& nam);
    std::vector<Dwelling*> getAllDwellings() const; // a
    std::vector<Client*> getAllClients() const; // a
    std::vector<Client*> getInterestedClients(Dwelling* d) const;
    void writeToFile(const std::string& fileName) const;

    ~RealEstateAgency() {
        for(auto i: this->dwellingRepo)
            delete i;
        for(auto i: this->clientRepo)
            delete i;
    }
};