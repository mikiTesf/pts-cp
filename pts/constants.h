#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace pts {

namespace constants {

    static const char* DB_NAME = "pts.bin";
    // The following regex pattern does not filter for '/' as the character is usually used to abbriviate long names
    static const std::string SPECIAL_CHARACTERS_PATTERN = "[\\\\+\\-=\\[\\]#$%^&*()_@{};':|,.<>]*";
    static const std::string PHONE_NUMBER_PATTERN = "^(\\+251|0)[0-9]{9}$";

} // end of namespace constants

} // end of namespace pts

#endif // CONSTANTS_H
