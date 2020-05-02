#include "program.h"

namespace pts {

Program::Program() { }

void Program::setId(int id) {
    this->id = id;
}

void Program::setDate(std::string date) {
    this->date = date;
}

void Program::setCongregationId(int congregation_id) {
    this->congregation_id = congregation_id;
}

void Program::setElderId(int elder_id) {
    this->elder_id = elder_id;
}

void Program::setFree(bool free) {
    this->is_free = free;
}

int Program::getId() const {
    return this->id;
}

std::string Program::getDate() const {
    return this->date;
}

int Program::getCongregationId() const {
    return this->congregation_id;
}

int Program::getElderId() const {
    return this->elder_id;
}

bool Program::getFree() const {
    return this->is_free;
}

} // end of namespace
