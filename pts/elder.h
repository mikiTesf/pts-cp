#ifndef ELDER_H
#define ELDER_H

#include "talk.h"
#include "congregation.h"
#include <string>

class elder
{
private:
    int id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string phoneNumber;
    talk talk;
    congregation congregation;
    bool enabled;
public:
    elder();

    elder(
        std::string firstName,
        std::string middleName,
        std::string lastName,
        std::string phoneNumber,
        class talk talk,
        class congregation congregation,
        bool enabled
    );

    void setFirstName(std::string firstName);
    void setMiddleName(std::string middleName);
    void setLastName(std::string lastName);
    void setPhoneNumber(std::string phoneNumber);
    void setTalk(class talk talk);
    void setCongregation(class congregation congregation);
    void setEnabled(bool enabled);

    int getId();
    std::string getFirstName();
    std::string getMiddleName();
    std::string getLastName();
    std::string getPhoneNumber();
    class talk getTalk();
    class congregation getCongregation();
    bool getEnabled();

};

#endif // ELDER_H
