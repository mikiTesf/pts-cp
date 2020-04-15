#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSql>
#include <QSqlDatabase>

namespace dbInit {

class PTSDbInitializer {
private:
    QString DB_NAME;
    QSqlDatabase DATABASE;

    void createNecessaryTables();
public:

    PTSDbInitializer(QString DB_NAME) {
        this->DB_NAME = DB_NAME;
    }

    bool initDB();
    void closeConnection();
};


}

#endif // DATABASE_H
