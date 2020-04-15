#include "mainwindow.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    const QString DB_NAME = "data.db3";
    dbInit::PTSDbInitializer ptsDbInitializer(DB_NAME);


//    return a.exec();
    return 0;
}
