#ifndef DATABASE_H
#define DATABASE_H
#include "constants.h"
#include "sqlite_orm/sqlite_orm.h"
#include <string>
#include "elder.h"
#include "talk.h"
#include "congregation.h"

namespace pts {

using std::string;

static auto initDB(string path){

        using namespace sqlite_orm;
        return make_storage(path,
                            make_table("elder",
                                       make_column("id", &Elder::setId, &Elder::getId, primary_key()),
                                       make_column("first_name", &Elder::setFirstName, &Elder::getFirstName),
                                       make_column("middle_name", &Elder::setMiddleName, &Elder::getMiddleName),
                                       make_column("last_name", &Elder::setLastName, &Elder::getLastName),
                                       make_column("phone_number", &Elder::setPhoneNumber, &Elder::getPhoneNumber),
                                       make_column("talk_id", &Elder::setTalkId, &Elder::getTalkId),
                                       make_column("congregation_id", &Elder::setCongregationId, &Elder::getCongregationId),
                                       make_column("enabled", &Elder::setEnabled, &Elder::getEnabled)),
                            make_table("congregation",
                                       make_column("id", &Congregation::setId, &Congregation::getId, primary_key()),
                                       make_column("name", &Congregation::setName, &Congregation::getName)),
                            make_table("talk",
                                       make_column("id", &Talk::setId, &Talk::getId, primary_key()),
                                       make_column("talk_number", &Talk::setTalkNumber, &Talk::getTalkNumber),
                                       make_column("title", &Talk::setTalkTitle, &Talk::getTalkTitle))
                            );
    }

using Storage = decltype(initDB(""));
static Storage storage = initDB(constants::DB_NAME);

class PTSDatabase {

public: static void init(){

        storage.sync_schema();
    }
public: static bool save (){
        return  true;
    }

public: static Storage getStorage (){
        return storage;
    }

public: static Congregation save (Congregation congregation){
        congregation.setId(storage.insert(congregation));
        return congregation;
    }

public: static Elder save (Elder elder){
        elder.setId(storage.insert(elder));
        return elder;
    }

public: static Talk save (Talk talk){
        talk.setId(storage.insert(talk));
        return talk;
    }

public: static auto getAllElders(){

        return storage.get_all<Elder>();
    }

public: static auto getAllCongregations(){

        return storage.get_all<Congregation>();
    }

public: static auto getAllTalks(){

        return storage.get_all<Talk>();
    }
};
} // end of namespace pts
#endif // DATABASE_H
