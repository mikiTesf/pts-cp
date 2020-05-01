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

    void setId(int);
    void setDate(time_t);
    void setCongregationId(int);
    void setElderId(int);
    void setFree(bool);

    int getId();
    time_t getDate();
    int getCongregationId();
    int getElderId();
    bool getFree();
};

}

#endif // PROGRAM_H
