#ifndef PROGRAM_H
#define PROGRAM_H

#include <ctime>
#include <string>

namespace pts {

class Program
{
private:
    int id;
    std::string date;
    int congregation_id;
    int elder_id;
    bool is_free;
public:
    Program();

    void setId(int);
    void setDate(std::string);
    void setCongregationId(int);
    void setElderId(int);
    void setFree(bool);

    int getId() const;
    std::string getDate() const;
    int getCongregationId() const;
    int getElderId() const;
    bool getFree() const;
};

}

#endif // PROGRAM_H
