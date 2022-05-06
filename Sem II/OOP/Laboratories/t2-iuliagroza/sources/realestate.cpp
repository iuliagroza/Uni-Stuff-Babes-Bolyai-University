#include "../headers/realestate.h"

Dwelling* RealEstateAgency::addDwelling(Dwelling *m) {
    this->dwellingRepo.push_back(m);
    return m;
}

void RealEstateAgency::addClient(Client *c) {
    this->clientRepo.push_back(c);
}

std::vector<Dwelling *> RealEstateAgency::getAllDwellings() const {
    return this->dwellingRepo;
}

std::vector<Client *> RealEstateAgency::getInterestedClients(Dwelling* d) const{
    std::vector<Client*> k;
    for(auto i: this->getAllClients()){
        if(i->isInterested(d))
            k.push_back(i);

    }
    return k;
}

void RealEstateAgency::writeToFile(const std::string& fileName) const {
    std::ofstream g(fileName);
    for(auto i: this->getAllClients()){
        g<<i->to_string()<<std::endl;
    }
    g.close();
}

std::vector<Client *> RealEstateAgency::getAllClients() const {
    return this->clientRepo;
}

void RealEstateAgency::removeClient(const std::string& nam) {
    for (int i=0; i<this->clientRepo.size(); i++)
        if (this->clientRepo[i]->getName() == nam) {
            this->clientRepo.erase(this->clientRepo.begin() + i);
        }
}
