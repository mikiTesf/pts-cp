#ifndef DATABASE_H
#define DATABASE_H

#include "constants.h"
#include "elder.h"
#include "talk.h"
#include "program.h"
#include "congregation.h"

#include "sqlite_orm/sqlite_orm.h"

#include <string>

namespace pts {

using std::string;

static auto initDB(string path) {

        using namespace sqlite_orm;
        return make_storage(path,
                            make_table("elder",
                                       make_column("id", &Elder::setId, &Elder::getId, primary_key(), autoincrement()),
                                       make_column("first_name", &Elder::setFirstName, &Elder::getFirstName),
                                       make_column("middle_name", &Elder::setMiddleName, &Elder::getMiddleName),
                                       make_column("last_name", &Elder::setLastName, &Elder::getLastName),
                                       make_column("phone_number", &Elder::setPhoneNumber, &Elder::getPhoneNumber),
                                       make_column("talk_id", &Elder::setTalkId, &Elder::getTalkId),
                                       make_column("congregation_id", &Elder::setCongregationId, &Elder::getCongregationId),
                                       make_column("enabled", &Elder::setEnabled, &Elder::getEnabled)),
                            make_table("congregation",
                                       make_column("id", &Congregation::setId, &Congregation::getId, primary_key(), autoincrement()),
                                       make_column("name", &Congregation::setName, &Congregation::getName)),
                            make_table("talk",
                                       make_column("id", &Talk::setId, &Talk::getId, primary_key(), autoincrement()),
                                       make_column("talk_number", &Talk::setTalkNumber, &Talk::getTalkNumber),
                                       make_column("title", &Talk::setTalkTitle, &Talk::getTalkTitle)),
                            make_table("program",
                                       make_column("id", &Program::setId, &Program::getId, primary_key(), autoincrement()),
                                       make_column("date", &Program::setDate, &Program::getDate),
                                       make_column("congregation_id", &Program::setCongregationId, &Program::getCongregationId),
                                       make_column("elder_id", &Program::setElderId, &Program::getElderId),
                                       make_column("is_free", &Program::setFree, &Program::getFree))
        );
    }

using Storage = decltype(initDB(""));
static Storage storage = initDB(constants::DB_NAME);

class PTSDatabase {

public: static void init() {
        storage.sync_schema();
    }

public: static Storage getStorage () {
        return storage;
    }

public: static void save (Congregation &congregation) {
        congregation.setId(storage.insert(congregation));
    }

public: static void save (Elder &elder) {
        elder.setId(storage.insert(elder));
    }

public: static void save (Talk &talk) {
        talk.setId(storage.insert(talk));
    }

public: static void save (Program &program) {
        program.setId(storage.insert(program));
    }

public: static auto getAllElders() {

        return storage.get_all<Elder>();
    }

public: static auto getAllCongregations() {

        return storage.get_all<Congregation>();
    }

public: static auto getAllTalks() {

        return storage.get_all<Talk>();
    }

public: static auto getAllPrograms() {

        return storage.get_all<Program>();
    }
};

} // end of namespace pts

#endif // DATABASE_H
