#include "talk.h"
#include <string>

talk::talk() { }

talk::talk(std::string title, int talkNumber) {
    this->title = title;
    this->talkNumber = talkNumber;
}

talk::talk(int id, int talkNumber, std::string title) {
    this->id = id;
    this->talkNumber = talkNumber;
    this->title = title;
}

int talk::getId() {
    return this->id;
}

int talk::getTalkNumber() {
    return this->talkNumber;
}

void talk::setTalkNumber(int talkNumber) {
    this->talkNumber = talkNumber;
}

std::string talk::getTalkTitle() {
    return this->title;
}

void talk::setTalkTitle(std::string title) {
    this->title = title;
}
