#pragma once

#include "Animal.h"

namespace Lecture_7_streams {
    class Penguin : public Animal {
    private:
        std::string type;
        std::string rankAndOccupation;

    public:
        Penguin(std::string _colour, double _weight, std::string _type, std::string _rankAndOccupation);

        ~Penguin();

        std::string getType() const;

        //std::string toString() const;

        std::string toString() const override;

        friend std::ostream &operator<<(std::ostream &stream, const Penguin &p);
    };
}
