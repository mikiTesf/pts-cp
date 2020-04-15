#include "database.h"

#include <QtSql>
#include <QString>
#include <iostream>

namespace dbInit {

bool PTSDbInitializer::initDB() {
    const QString SQLITE_DRIVER("QSQLITE");
    QSqlDatabase database;

    if (QSqlDatabase::isDriverAvailable(SQLITE_DRIVER)) {
        std::cout << "found the proper SQLite driver" << std:: endl;
        database = QSqlDatabase::addDatabase(SQLITE_DRIVER);
        database.setDatabaseName(this->DB_NAME);

        if (database.open ()) {
            std::cout << "successfully connected to the database" << std::endl;
        }

        return true;
    } else {
        qWarning() << "ERROR: " << database.lastError();
        return false;
    }
}

void PTSDbInitializer::createNecessaryTables() {
    QSqlQuery query(this->DATABASE);
    QString queryString;
    // create the congregation table
    queryString = "CREATE TABLE `congregation` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `name` VARCHAR )";
    query.exec(queryString);
    // create the elder table
    queryString = "CREATE TABLE `elder` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `firstName` VARCHAR NOT NULL ,";
    queryString.append ("`middleName` VARCHAR NOT NULL , `lastName` VARCHAR , `phoneNumber` VARCHAR NOT NULL ,");
    queryString.append ("`talk_id` INTEGER NOT NULL , `congregation_id` INTEGER NOT NULL , `enabled` BOOLEAN DEFAULT 1 NOT NULL )");
    query.exec(queryString);
    // create the program table
    queryString = "CREATE TABLE `program` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `date` VARCHAR NOT NULL";
    queryString.append (" , `congregation_id` INTEGER NOT NULL , `elder_id` INTEGER , `isFree` BOOLEAN )");
    query.exec(queryString);
    // create the talk table
    queryString = "CREATE TABLE `talk` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `talkNumber` INTEGER NOT NULL , `title` VARCHAR )";
    query.exec(queryString);
}

void PTSDbInitializer::closeConnection() {
    return;
}

}
