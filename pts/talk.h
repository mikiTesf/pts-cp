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

    int getId();
    int getTalkNumber();

    void setTalkNumber(int talkNumber);
    std::string getTalkTitle();
    void setTalkTitle(std::string title);
};

#endif // TALK_H
