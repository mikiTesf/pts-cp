#include "constants.h"
#include "mainwindow.h"
#include "database.h"

#include "excel_generator.h"
#include "elder.h"

#include <QApplication>
#include <iostream>
#include <vector>

using namespace pts;
using sqlite_orm::where;
using sqlite_orm::c;

int main(int argc, char *argv[])
{
//    // initialize database
//    PTSDatabase::init();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//    //return 0;

    lxw_workbook* workbook = workbook_new("PTS.xlsx");
    pts::ExcelGenerator excelGenerator;

    for (auto congregation : pts::PTSDatabase::getAllCongregations()) {
        lxw_worksheet* worksheet = workbook_add_worksheet(workbook, congregation.getName().c_str());

        std::vector<Elder> elders = pts::PTSDatabase::getStorage()
                .get_all<Elder>(where(c(&Elder::getCongregationId) = congregation.getId()));

        std::cout << "inserting congregation name..." << std::endl;
        excelGenerator.insertCongregationName(worksheet, congregation.getName().c_str());
        std::cout << "inserting columns and elders names..." << std::endl;
        excelGenerator.insertColumnsAndElderNames(worksheet, elders);
        std::cout << "inserting instruction messages..." << std::endl;
        excelGenerator.insertInstructionMessage(worksheet);
    }

    std::cout << "saving workbook..." << std::endl;
    workbook_close(workbook);

    return 0;
}
