#ifndef TALK_H
#define TALK_H

#include <string>

class talk
{
private:
    int id;
    int talkNumber;
    std::string title;
public:
    talk();
    talk(std::string title, int talkNumber);
    talk(int id, int talkNumber, std::string talkTitle);

    int getId() {
        return this->id;
    }

    int getTalkNumber() {
        return this->talkNumber;
    }

    void setTalkNumber(int talkNumber) {
        this->talkNumber = talkNumber;
    }

    std::string getTalkTitle() {
        return this->title;
    }

    void setTalkTitle(std::string title) {
        this->title = title;
    }
};

#endif // TALK_H
