#include "database.h"

#include <QtSql>
#include <QString>
#include <iostream>

namespace dbInit {

QSqlDatabase PTSDbInitializer::DATABASE;

PTSDbInitializer::PTSDbInitializer(QString DB_NAME) {
    this->DB_NAME = DB_NAME;
}

bool PTSDbInitializer::initDB() {
    const QString SQLITE_DRIVER("QSQLITE");

    if (QSqlDatabase::isDriverAvailable(SQLITE_DRIVER)) {
        std::cout << "found the proper SQLite driver" << std:: endl;
        PTSDbInitializer::DATABASE = QSqlDatabase::addDatabase(SQLITE_DRIVER);
        PTSDbInitializer::DATABASE.setDatabaseName(this->DB_NAME);

        if (PTSDbInitializer::DATABASE.open()) {
            std::cout << "successfully connected to the database" << std::endl;
        }

        PTSDbInitializer::createNecessaryTables();

        return true;
    } else {
        qWarning() << "ERROR: " << PTSDbInitializer::DATABASE.lastError();
        return false;
    }
}

void PTSDbInitializer::createNecessaryTables() {
    QSqlQuery query(PTSDbInitializer::DATABASE);
    QString queryString;
    // create the congregation table
    queryString = "CREATE TABLE IF NOT EXISTS `congregation` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `name` VARCHAR );";
    query.exec(queryString);
    // create the elder table
    queryString = "CREATE TABLE IF NOT EXISTS `elder` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `firstName` VARCHAR NOT NULL ,";
    queryString.append ("`middleName` VARCHAR NOT NULL , `lastName` VARCHAR , `phoneNumber` VARCHAR NOT NULL ,");
    queryString.append ("`talk_id` INTEGER NOT NULL , `congregation_id` INTEGER NOT NULL , `enabled` BOOLEAN DEFAULT 1 NOT NULL );");
    query.exec(queryString);
    // create the program table
    queryString = "CREATE TABLE IF NOT EXISTS `program` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `date` VARCHAR NOT NULL";
    queryString.append (" , `congregation_id` INTEGER NOT NULL , `elder_id` INTEGER , `isFree` BOOLEAN );");
    query.exec(queryString);
    // create the talk table
    queryString = "CREATE TABLE IF NOT EXISTS `talk` (`id` INTEGER PRIMARY KEY AUTOINCREMENT , `talkNumber` INTEGER NOT NULL , `title` VARCHAR );";
    query.exec(queryString);

    PTSDbInitializer::DATABASE.commit();
}

QSqlDatabase PTSDbInitializer::getDatabase() {
    return PTSDbInitializer::DATABASE;
}

void PTSDbInitializer::closeConnection() {
    PTSDbInitializer::DATABASE.close ();
}

}
