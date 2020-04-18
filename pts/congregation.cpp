#include "congregation.h"

namespace pts {

Congregation::Congregation() { };

Congregation::Congregation(std::string name) {
    this->name = name;
};

Congregation::Congregation(int id, std::string name) {
    this->id = id;
    this->name = name;
};

int Congregation::getId() const {
    return this->id;
}

std::string Congregation::getName() const {
    return this->name;
}

void Congregation::setId(int id) {
    this->id = id;
}

void Congregation::setName(std::string name) {
    this->name = name;
}

} // end of namespace pts
