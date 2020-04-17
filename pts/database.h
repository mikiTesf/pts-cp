#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite/sqlite3.h"

#include <string>

namespace ptsDbHandle {

using std::string;

class PTSDbHandle {
private:
    std::string DB_NAME;
    static sqlite3* DATABASE;

    void createNecessaryTables();
public:

    PTSDbHandle(std::string DB_NAME);

    bool initDB();

    static sqlite3* getDatabase();
};

}

#endif // DATABASE_H
