#include "database.h"


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
static Storage storage = initDB("pts.bin");



} // end of namespace pts
