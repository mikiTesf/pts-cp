#include "elder.h"

namespace pts {

Elder::Elder() { };

Elder::Elder(
    std::string firstName,
    std::string middleName,
    std::string lastName,
    std::string phoneNumber,
    int talk_id,
    int congregation_id,
    bool enabled)
{
    this->firstName = firstName;
    this->middleName = middleName;
    this->lastName = lastName;
    this->phoneNumber = phoneNumber;
    this->talk_id = talk_id;
    this->congregation_id = congregation_id;
    this->enabled = enabled;
}

Elder::Elder(
    std::string firstName,
    std::string middleName,
    std::string lastName,
    std::string phoneNumber,
    Talk talk,
    Congregation congregation,
    bool enabled)
{
    this->firstName = firstName;
    this->middleName = middleName;
    this->lastName = lastName;
    this->phoneNumber = phoneNumber;
    this->talk_id = talk.getId();
    this->congregation_id = congregation.getId();
    this->enabled = enabled;
}

void Elder::setId(int id){
    this->id = id;
}

void Elder::setFirstName(std::string firstName){
    this->firstName = firstName;
}

void Elder::setMiddleName(std::string middleName){
    this->middleName = middleName;
}

void Elder::setLastName(std::string lastName){
    this->lastName = lastName;
}

void Elder::setPhoneNumber(std::string phoneNumber){
    this->phoneNumber = phoneNumber;
}

void Elder::setTalkId(int talk_id){
    this->talk_id = talk_id;
}

void Elder::setCongregationId(int congregation_id){
    this->congregation_id = congregation_id;
}

void Elder::setEnabled(bool enabled){
    this->enabled = enabled;
}

int Elder::getId() const {
    return this->id;
}

std::string Elder::getFirstName() const {
    return this->firstName;
}

std::string Elder::getMiddleName() const {
    return this->middleName;
}

std::string Elder::getLastName() const {
    return this->lastName;
}

std::string Elder::getPhoneNumber() const {
    return this->phoneNumber;
}

int Elder::getTalkId() const {
    return this->talk_id;
}

int Elder::getCongregationId() const {
    return this->congregation_id;
}

bool Elder::getEnabled() const {
    return this->enabled;
}

} // end of namespace pts
