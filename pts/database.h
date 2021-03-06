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

using sqlite_orm::make_storage;
using sqlite_orm::make_table;
using sqlite_orm::make_column;
using sqlite_orm::primary_key;
using sqlite_orm::autoincrement;
using sqlite_orm::foreign_key;
using sqlite_orm::distinct;
using sqlite_orm::where;
using sqlite_orm::c;
using sqlite_orm::order_by;

static auto initDB(string path) {

        return make_storage(path,
                            make_table("congregation",
                                       make_column("id", &Congregation::setId, &Congregation::getId, primary_key(), autoincrement()),
                                       make_column("name", &Congregation::setName, &Congregation::getName)),
                            make_table("talk",
                                       make_column("id", &Talk::setId, &Talk::getId, primary_key(), autoincrement()),
                                       make_column("talk_number", &Talk::setTalkNumber, &Talk::getTalkNumber),
                                       make_column("title", &Talk::setTalkTitle, &Talk::getTalkTitle)),
                            make_table("elder",
                                       make_column("id", &Elder::setId, &Elder::getId, primary_key(), autoincrement()),
                                       make_column("first_name", &Elder::setFirstName, &Elder::getFirstName),
                                       make_column("middle_name", &Elder::setMiddleName, &Elder::getMiddleName),
                                       make_column("last_name", &Elder::setLastName, &Elder::getLastName),
                                       make_column("phone_number", &Elder::setPhoneNumber, &Elder::getPhoneNumber),
                                       make_column("talk_id", &Elder::setTalkId, &Elder::getTalkId),
                                       make_column("congregation_id", &Elder::setCongregationId, &Elder::getCongregationId),
                                       make_column("enabled", &Elder::setEnabled, &Elder::getEnabled),
                                       foreign_key(&Elder::getCongregationId).references(&Congregation::getId).on_delete.cascade().on_update.cascade(),
                                       foreign_key(&Elder::getTalkId).references(&Talk::getId).on_update.cascade()),
                            make_table("program",
                                       make_column("id", &Program::setId, &Program::getId, primary_key(), autoincrement()),
                                       make_column("date", &Program::setDate, &Program::getDate),
                                       make_column("congregation_id", &Program::setCongregationId, &Program::getCongregationId),
                                       make_column("elder_id", &Program::setElderId, &Program::getElderId),
                                       make_column("is_free", &Program::setFree, &Program::getFree),
                                       foreign_key(&Program::getCongregationId).references(&Congregation::getId).on_delete.cascade().on_update.cascade(),
                                       foreign_key(&Program::getElderId).references(&Elder::getId).on_delete.cascade().on_update.cascade())
        );
    }

using Storage = decltype(initDB(""));
static Storage storage = initDB(pts::constants::DB_NAME);

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

public: static auto getAllEnabledEldersOfCongregation(int congregationId) {
        // replace with a single query that fetches for all elders of the congregation with the given
        // id `congregationId` and that are also `enabled`
        std::vector<pts::Elder> eldersInCongregation = storage.get_all<Elder>
                (where(c(&Elder::getCongregationId) = congregationId));
        std::vector<pts::Elder> enabledElders;

        for (Elder elder : eldersInCongregation) {
            if (elder.getEnabled()) {
                enabledElders.push_back(elder);
            }
        }

        return enabledElders;
    }

public: static auto getAllCongregations() {

        return storage.get_all<Congregation>();
    }

public: static std::vector<pts::Congregation> getCongregationByName(std::string congregationName) {
        return storage.get_all<pts::Congregation>(where(c(&Congregation::getName) = congregationName));
    }

public: static auto getAllTalks() {

        return storage.get_all<Talk>();
    }

public: static auto getAllPrograms() {

        return storage.get_all<Program>();
    }

public: static auto getDistinctProgramDates() {
        return storage.select(distinct(&Program::getDate), order_by(&Program::getDate));
    }

public: static auto getTalksForCongregation(int congregationId) {
        return storage.get_all<Program>(where(c(&Program::getCongregationId) = congregationId),
                                        order_by(&Program::getDate));
    }

public: static auto getTalksByElder(int elderId) {
        return storage.get_all<Program>(where(c(&Program::getElderId) = elderId), order_by(&Program::getDate));
    }

public: static std::vector<pts::Talk> getTalkByTalkNumber(int talkNumber) {
        return storage.get_all<pts::Talk>(where(c(&Talk::getTalkNumber) = talkNumber));
    }

public: static void removeTalkByTalkNumber(int talkNumber) {
        storage.remove_all<pts::Talk>(where(c(&Talk::getTalkNumber) = talkNumber));
    }

public: static std::vector<pts::Elder> getEldersByTalkNumber(int talkId) {
        return storage.get_all<pts::Elder>(where(c(&Elder::getTalkId) = talkId));
    }

public: static void removeElderByPhoneNumber(std::string phoneNumber) {
        storage.remove_all<pts::Elder>(where(c(&Elder::getPhoneNumber) = phoneNumber));
    }

public: static pts::Elder getElderByPhoneNumber(std::string phoneNumber) {
        return storage.get_all<pts::Elder>(where(c(&Elder::getPhoneNumber) = phoneNumber)).at(0);
    }
};

} // end of namespace pts

#endif // DATABASE_H
