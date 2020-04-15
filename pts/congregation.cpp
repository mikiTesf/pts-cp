#include "congregation.h"

congregation::congregation() { };

congregation::congregation(std::string name) {
    this->name = name;
};

congregation::congregation(int id, std::string name) {
    this->id = id;
    this->name = name;
};

int congregation::getId() {
    return this->id;
}

std::string congregation::getName() {
    return this->name;
}

void congregation::setName(std::string name) {
    this->name = name;
}
