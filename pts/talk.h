#include <string>

namespace pts {

#ifndef TALK_H
#define TALK_H

class Talk
{
private:
    int id;
    int talkNumber;
    std::string title;
public:
    Talk();
    Talk(std::string title, int talkNumber);
    Talk(int id, int talkNumber, std::string talkTitle);

    int getId() const;
    int getTalkNumber() const;
    std::string getTalkTitle() const;

    void setId(int id);
    void setTalkNumber(int talkNumber);
    void setTalkTitle(std::string title);
};

#endif // TALK_H

}// end of namespace pts
