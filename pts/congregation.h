

#include <string>

namespace pts {

#ifndef CONGREGATION_H
#define CONGREGATION_H

class Congregation
{
private:
    int id;
    std::string name;
public:
    Congregation();
    Congregation(std::string name);
    Congregation(int id, std::string name);

    void setId(int id);
    void setName(std::string name);

    int getId() const;
    std::string getName() const;
};

#endif // CONGREGATION_H
} // end of namespace pts
