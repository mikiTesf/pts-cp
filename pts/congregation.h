#ifndef CONGREGATION_H
#define CONGREGATION_H

#include <string>

class congregation
{
private:
    int id;
    std::string name;
public:
    congregation();
    congregation(std::string name);
    congregation(int id, std::string name);

    void setName(std::string name);

    int getId();
    std::string getName();
};

#endif // CONGREGATION_H
