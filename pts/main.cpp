#include "constants.h"
#include "mainwindow.h"
#include <QApplication>
#include "database.h"

using namespace pts;

int main(int argc, char *argv[])
{
    // initialize database
    PTSDatabase::init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //return 0;
}
