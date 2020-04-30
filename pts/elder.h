#include "talk.h"
#include "congregation.h"
#include <string>

namespace pts {

#ifndef ELDER_H
#define ELDER_H

class Elder
{
private:
    int id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string phoneNumber;
    int talk_id;
    int congregation_id;
    bool enabled;
public:
    Elder();

    Elder(
        std::string firstName,
        std::string middleName,
        std::string lastName,
        std::string phoneNumber,
        int talk_id,
        int congregation_id,
        bool enabled
    );

    Elder(
        std::string firstName,
        std::string middleName,
        std::string lastName,
        std::string phoneNumber,
        Talk talk,
        Congregation congregation,
        bool enabled
    );

    void setId(int id);
    void setFirstName(std::string firstName);
    void setMiddleName(std::string middleName);
    void setLastName(std::string lastName);
    void setPhoneNumber(std::string phoneNumber);
    void setTalkId(int talk_id);
    void setCongregationId(int congregation_id);
    void setEnabled(bool enabled);

    int getId() const;
    std::string getFirstName() const;
    std::string getMiddleName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;
    int getTalkId() const;
    int getCongregationId() const;
    Talk getTalk() const;
    Congregation getCongregation() const;
    bool getEnabled() const;

};

#endif // ELDER_H

} // end of namespace pts
