#include "talk.h"
#include <string>

namespace pts {

Talk::Talk() { }

Talk::Talk(std::string title, int talkNumber) {
    this->title = title;
    this->talkNumber = talkNumber;
}

Talk::Talk(int id, int talkNumber, std::string title) {
    this->id = id;
    this->talkNumber = talkNumber;
    this->title = title;
}

int Talk::getId() const {
    return this->id;
}

int Talk::getTalkNumber() const {
    return this->talkNumber;
}

std::string Talk::getTalkTitle() const {
    return this->title;
}

void Talk::setId(int id) {
    this->id = id;
}

void Talk::setTalkNumber(int talkNumber) {
    this->talkNumber = talkNumber;
}


void Talk::setTalkTitle(std::string title) {
    this->title = title;
}

} // end of namespace pts
