#ifndef PROGRAM_H
#define PROGRAM_H

#include <ctime>

namespace pts {

class Program
{
private:
    int id;
    time_t date;
    int congregation_id;
    int elder_id;
    bool is_free;
public:
    Program();

    void setID(int);
    void setDate(time_t);
    void setCongregationID(int);
    void setElderID(int);
    void setFree(bool);

    int getID();
    time_t getDate();
    int getCongregationID();
    int getElderID();
    bool getFree();
};

}

#endif // PROGRAM_H
