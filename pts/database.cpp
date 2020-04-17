#include "congregation.h"
#include "talk.h"
#include "elder.h"
#include "database.h"

#include <iostream>

namespace ptsDbHandle {

sqlite3* PTSDbHandle::DATABASE;

PTSDbHandle::PTSDbHandle(std::string DB_NAME) {
    this->DB_NAME = DB_NAME;
}

bool PTSDbHandle::initDB() {
    int status = sqlite3_open(this->DB_NAME.c_str(), &PTSDbHandle::DATABASE);

    if (status) {
        std::cout << "could not open " << this->DB_NAME << ": " << sqlite3_errmsg(PTSDbHandle::DATABASE) << "\n";
    } else {
        std::cout << this->DB_NAME << " ready for further operations\n" << std::endl;
        // sqlite_orm performs automatic open/close operations on the database. Hence, to avoid
        // accidental modifications of the database in between the time of initialization and the
        // following database operation, the database will be closed
        sqlite3_close(PTSDbHandle::DATABASE);
    }

    createNecessaryTables();

    return true;
}

void PTSDbHandle::createNecessaryTables() {

}

}
