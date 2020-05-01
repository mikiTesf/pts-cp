#include "program.h"

namespace pts {

Program::Program() { }

void Program::setId(int id) {
    this->id = id;
}

void Program::setDate(time_t date) {
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

int Program::getId() {
    return this->id;
}

time_t Program::getDate() {
    return this->date;
}

int Program::getCongregationId() {
    return this->congregation_id;
}

int Program::getElderId() {
    return this->elder_id;
}

bool Program::getFree() {
    return this->is_free;
}

} // end of namespace
