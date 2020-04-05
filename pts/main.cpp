#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include "sqlite/sqlite3.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Pointer to SQLite connection
    sqlite3* db;

    // Save the connection result
    int exit = 0;
    exit = sqlite3_open("data.db", &db);

    // Test if there was an error
    if (exit) { std::cout << "DB Open Error: " << sqlite3_errmsg(db) << std::endl; }

    else { std::cout << "Opened Database Successfully!" << std::endl; }

    // Close the connection
    sqlite3_close(db);

    return a.exec();
}
