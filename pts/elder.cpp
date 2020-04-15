#include "elder.h"

elder::elder() { };

elder::elder(
    std::string firstName,
    std::string middleName,
    std::string lastName,
    std::string phoneNumber,
    class talk talk,
    class congregation congregation,
    bool enabled)
{
    this->firstName = firstName;
    this->middleName = middleName;
    this->lastName = lastName;
    this->phoneNumber = phoneNumber;
    this->talk = talk;
    this->congregation = congregation;
    this->enabled = enabled;
}

void elder::setFirstName(std::string firstName){
    this->firstName = firstName;
}

void elder::setMiddleName(std::string middleName){
    this->middleName = middleName;
}

void elder::setLastName(std::string lastName){
    this->lastName = lastName;
}

void elder::setPhoneNumber(std::string phoneNumber){
    this->phoneNumber = phoneNumber;
}

void elder::setTalk(class talk talk){
    this->talk = talk;
}

void elder::setCongregation(class congregation congregation){
    this->congregation = congregation;
}

void elder::setEnabled(bool enabled){
    this->enabled = enabled;
}

int elder::getId(){
    return this->id;
}

std::string elder::getFirstName(){
    return this->firstName;
}

std::string elder::getMiddleName(){
    return this->middleName;
}

std::string elder::getLastName(){
    return this->lastName;
}

std::string elder::getPhoneNumber(){
    return this->phoneNumber;
}

class talk elder::getTalk(){
    return this->talk;
}

class congregation elder::getCongregation(){
    return this->congregation;
}

bool elder::getEnabled(){
    return this->enabled;
}
