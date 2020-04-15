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
